//
// Created by nechi on 04.11.2024.
//

#include <QPainter>
#include "OglWidget.h"
#include "../../../fbd/graphics/COglStyle.h"

OglWidget::OglWidget(QWidget *parent) : QOpenGLWidget(parent)
{

}

OglWidget::~OglWidget()
{
    //QOpenGLWidget::~QOpenGLWidget();
}

void OglWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter;
    painter.begin(this);
    QImage image(":/codesys/images/Procont.jpg");

    //Set image adaptive window size
    QImage result = image.scaled(this->width(),this->height(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
    painter.drawImage(QPoint(0,0),result);
    painter.end();

    //QOpenGLWidget::paintEvent(event);
}

void OglWidget::initializeGL()
{
    if (!m_funcGL)
    {
        m_funcGL = QOpenGLContext::currentContext()->functions();
    }

    m_funcGL->glClearColor(1, 1, 1, 1);
    m_funcGL->glEnable(GL_ALPHA_TEST);
    m_funcGL->glEnable(GL_DEPTH_TEST);
    m_funcGL->glEnable(GL_COLOR_MATERIAL);

    // разрешаем освещение
    m_funcGL->glEnable(GL_LIGHTING);

    // включаем нулевую лампу
    m_funcGL->glEnable(GL_LIGHT0);

    // разрешаем смешение цветов и прозрачность
    m_funcGL->glEnable(GL_BLEND);
    m_funcGL->glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void OglWidget::resizeGL(int w, int h)
{
    QOpenGLWidget::resizeGL(w, h);
}
