#include "Yuv420GLWidget.hpp"
#include <GL/gl.h>
#include <QOpenGLTexture>
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

void Yuv420GLWidget::initializeGL() {
    initGLFuncs(this);
    initShader(yuv420_vertices, sizeof(yuv420_vertices), yuv420_fsrc);
    textureUniformY = programUniformLocation("textureY");
    textureUniformU = programUniformLocation("textureU");
    textureUniformV = programUniformLocation("textureV");
    auto textureY = new QOpenGLTexture(QOpenGLTexture::Target2D);
    auto textureU = new QOpenGLTexture(QOpenGLTexture::Target2D);
    auto textureV = new QOpenGLTexture(QOpenGLTexture::Target2D);
    textureY->create();
    textureU->create();
    textureV->create();
    idY = textureY->textureId();
    idU = textureU->textureId();
    idV = textureV->textureId();
}

void Yuv420GLWidget::paintGL() {
    if (dataPtr == nullptr) {
        return;
    }
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 注释后画面卡死
    glDisable(GL_DEPTH_TEST); // 关闭深度测试, 注释后内存占用增加
    glViewport(x, y, viewW, viewH);

    int halfW = videoW >> 1;
    int halfH = videoH >> 1;

    loadTexture(this, GL_TEXTURE0, idY, videoW, videoH, GL_RED, dataPtr.get());
    loadTexture(this, GL_TEXTURE1, idU, halfW, halfH, GL_RED,
                dataPtr.get() + videoW * videoH);
    loadTexture(this, GL_TEXTURE2, idV, halfW, halfH, GL_RED,
                dataPtr.get() + halfW * halfH * 5);

    glUniform1i(textureUniformY, 0);
    glUniform1i(textureUniformU, 1);
    glUniform1i(textureUniformV, 2);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}
