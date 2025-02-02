#pragma once
#include "OpenGLWidget.hpp"

class Nv12GLWidget : public BaseOpenGlWideget, protected QOpenGLFunctions {
private:
    GLuint textureUniformY, textureUniformUV; // opengl中y、u、v分量位置
    GLuint idY, idUV;

protected:
    virtual void initializeGL() override;
    virtual void paintGL() override;

public:
    Nv12GLWidget(QWidget *parent = nullptr) : BaseOpenGlWideget(parent) {}
};
