#pragma once
#include <cstdint>
#include <GL/gl.h>
#include <memory>
#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLWidget>

static void initGLFuncs(QOpenGLFunctions *glFuncs, GLclampf red = 0.0f,
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

static void loadTexture(QOpenGLFunctions *glFuncs, GLenum textureType,
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

class BaseOpenGlWideget : public QOpenGLWidget {
private:
    QOpenGLBuffer vbo;
    QOpenGLShaderProgram *program{nullptr};

protected:
    std::unique_ptr<uint8_t> dataPtr;
    GLsizei videoW, videoH;
    float videoRatio = 1.0f;

    GLint x, y;
    GLsizei viewW, viewH;
    float widgetRatio = 1.0f;
    void initShader(void const *vertices, int count, char const *fsrc);

    GLuint programUniformLocation(char const *name) {
        return program->uniformLocation(name);
    }

public:
    BaseOpenGlWideget(QWidget *parent = nullptr) : QOpenGLWidget(parent) {}

    void setPixelData(uint8_t *pixelData, int width, int height);
};
