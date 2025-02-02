#pragma once
#include <GL/gl.h>
#include <OpenGLWidget.hpp>
#include <qopenglfunctions.h>

class Yuv420GLWidget : public BaseOpenGlWideget, protected QOpenGLFunctions {
private:
    GLuint textureUniformY, textureUniformU, textureUniformV;
    GLuint idY, idU, idV;

protected:
    virtual void initializeGL() override;
    virtual void paintGL() override;

public:
    Yuv420GLWidget(QWidget *parent = nullptr) : BaseOpenGlWideget(parent) {}
};
