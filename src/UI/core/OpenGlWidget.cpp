#include "OpenGlWidget.hpp"
#include <GL/gl.h>
#include <GL/glext.h>
#include <qopenglfunctions.h>
#include <qopenglshaderprogram.h>

#define VERTEXIN  0
#define TEXTUREIN 1

char const *vsrc = {R"(
    attribute vec4 vertexIn; 
    attribute vec2 textureIn; 
    varying vec2 textureOut;  
    void main(void)           
    {                         
        gl_Position = vertexIn; 
        textureOut = textureIn; 
    })"};
char const *nv12_fsrc = {R"(
    varying vec2 textureOut;
    uniform sampler2D textureY;
    uniform sampler2D textureUV;
    void main(void)
    {
        vec3 yuv; 
        vec3 rgb; 
        yuv.x = texture2D(textureY, textureOut.st).r - 0.0625; 
        yuv.y = texture2D(textureUV, textureOut.st).r - 0.5; 
        yuv.z = texture2D(textureUV, textureOut.st).g - 0.5; 
        rgb = mat3( 1,       1,         1,         
                    0,       -0.39465,  2.03211,   
                    1.13983, -0.58060,  0) * yuv;  
        gl_FragColor = vec4(rgb, 1); 
    })"};
char const *yuv420_fsrc = {R"(
    varying vec2 textureOut; 
    uniform sampler2D textureY; 
    uniform sampler2D textureU; 
    uniform sampler2D textureV; 
    void main(void) 
    { 
        vec3 yuv; 
        vec3 rgb; 
        yuv.x = texture2D(textureY, textureOut).r; 
        yuv.y = texture2D(textureU, textureOut).r - 0.5; 
        yuv.z = texture2D(textureV, textureOut).r - 0.5; 
        rgb = mat3( 1,       1,         1, 
                    0,       -0.39465,  2.03211, 
                    1.13983, -0.58060,  0) * yuv; 
        gl_FragColor = vec4(rgb, 1); 
    })"};

static GLfloat const yuv420_vertices[]{
    // 顶点坐标
    -1.0f, -1.0f, -1.0f, +1.0f, +1.0f, +1.0f, +1.0f, -1.0f,
    // 纹理坐标
    0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f};

static GLfloat const nv12_vertices[]{
    -1.0f, 1.0f, 1.0f, 1.0f, 1.0f, -1.0f, -1.0f, -1.0f,

    0.0f,  0.0f, 1.0f, 0.0f, 1.0f, 1.0f,  0.0f,  1.0f};

void initGLFuncs(QOpenGLFunctions *glFuncs, GLclampf red = 0.0f,
                 GLclampf green = 0.0f, GLclampf blue = 0.0f,
                 GLclampf alpha = 1.0f) {
    if (!glFuncs) {
        return;
    }

    // 初始化OpenGL函数
    glFuncs->initializeOpenGLFunctions();
    // 开启深度测试
    glFuncs->glEnable(GL_DEPTH_TEST);
    // 设置清屏颜色
    glFuncs->glClearColor(red, green, blue, alpha);
}

void loadTexture(QOpenGLFunctions *glFuncs, GLenum textureType,
                 GLuint textureId, GLsizei width, GLsizei height, GLenum format,
                 GLvoid const *pixels) {
    // 激活纹理
    glFuncs->glActiveTexture(textureType);
    // 绑定纹理
    glFuncs->glBindTexture(GL_TEXTURE_2D, textureId);
    // 加载纹理
    glFuncs->glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format,
                          GL_UNSIGNED_BYTE, pixels);
    // 设置纹理参数
    glFuncs->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFuncs->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glFuncs->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
                             GL_CLAMP_TO_EDGE);
    glFuncs->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,
                             GL_CLAMP_TO_EDGE);
}

void BaseOpenGlWideget::initShader(void const *vertices, int count,
                                   char const *fsrc) {
    vbo.create();
    vbo.bind();
    vbo.allocate(vertices, count);

    program = new QOpenGLShaderProgram(this);
    program->addCacheableShaderFromSourceCode(QOpenGLShader::Vertex, vsrc);
    program->addCacheableShaderFromSourceCode(QOpenGLShader::Fragment, fsrc);

    program->bindAttributeLocation("vertexIn", VERTEXIN);
    program->bindAttributeLocation("textureIn", TEXTUREIN);
    program->link();
    program->bind();
    program->enableAttributeArray(VERTEXIN);
    program->enableAttributeArray(TEXTUREIN);
    program->setAttributeBuffer(VERTEXIN, GL_FLOAT, 0, 2, 2 * sizeof(GLfloat));
    program->setAttributeBuffer(TEXTUREIN, GL_FLOAT, 8 * sizeof(GLfloat), 2,
                                2 * sizeof(GLfloat));
}

void BaseOpenGlWideget::setPixelData(uint8_t *pixelData, int width,
                                     int height) {
    if (!pixelData) {
        return ;
    }

    //视频和窗口的长宽比
    videoRatio = (float)width / height;
    widgetRatio = (float)this->width() / this->height();

    //窗口比较胖矮，调整视频左右居中，即高跟窗口一致，宽按照之前视频比例缩放
    if (widgetRatio > videoRatio) {
        viewH = this->height();
        viewW = this->height() * videoRatio;
        x = (this->width() - viewW) / 2;//视频左右居中
        y = 0;//上下不用
    } else {// 窗口瘦高，调整视频上下居中，即宽跟窗口一致，高按照之前视频比例缩放，
        viewW = this->width();
        viewH = this->width() * videoRatio;
        x = 0; // 左右不用
        y = (this->height() - viewH) / 2;//上下居中
    }

    //保存原来视频长宽
    videoH = height;
    videoW = width;
}
