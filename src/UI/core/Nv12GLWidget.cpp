#include "Nv12GLWidget.hpp"
#include <QOpenGLTexture>
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

static GLfloat const nv12_vertices[]{
    -1.0f, 1.0f, 1.0f, 1.0f, 1.0f, -1.0f, -1.0f, -1.0f,

    0.0f,  0.0f, 1.0f, 0.0f, 1.0f, 1.0f,  0.0f,  1.0f};

void Nv12GLWidget::initializeGL() {
    initGLFuncs(this);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    initShader(nv12_vertices, sizeof(nv12_vertices), nv12_fsrc);
    textureUniformY = programUniformLocation("textureY");
    textureUniformUV = programUniformLocation("textureUV");
    auto textureY = new QOpenGLTexture(QOpenGLTexture::Target2D);
    auto textureUV = new QOpenGLTexture(QOpenGLTexture::Target2D);
    textureY->create();
    textureUV->create();
    idY = textureY->textureId();
    idUV = textureUV->textureId();
}

void Nv12GLWidget::paintGL() {
    if (dataPtr == nullptr) {
        return;
    }
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 注释后画面卡死
    glDisable(GL_DEPTH_TEST); // 关闭深度测试, 注释后内存占用增加
    glViewport(x, y, viewW, viewH);

    loadTexture(this, GL_TEXTURE0, idY, videoW, videoH, GL_RED, dataPtr.get());
    loadTexture(this, GL_TEXTURE1, idUV, videoW / 2, videoH / 2, GL_RG,
                dataPtr.get() + videoW * videoH);

    glUniform1i(textureUniformY, 0);
    glUniform1i(textureUniformUV, 1);
    // glDrawArrays(GL_TRIANGLE_STRIP, 0, 4); //
    // GL_TRIANGLE_STRIP会导致屏幕左侧出现一个三角形
    // glDrawArrays(GL_TRIANGLE_FAN, 0, 4); // 与GL_QUADS效果相同, 原因暂不清楚
    glDrawArrays(GL_QUADS, 0, 4);
}
