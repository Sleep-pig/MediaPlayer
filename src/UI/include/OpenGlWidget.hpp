#pragma once
#include <cstdint>
#include <GL/gl.h>
#include <memory>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
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

void setPixelData(uint8_t *pixelData,int width,int height);
};
