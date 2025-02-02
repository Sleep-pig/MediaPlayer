#include "OpenGLWidget.hpp"

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
