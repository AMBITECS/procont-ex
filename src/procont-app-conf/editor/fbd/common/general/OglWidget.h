//
// Created by nechi on 04.11.2024.
//

#ifndef EDITORSD_OGLWIDGET_H
#define EDITORSD_OGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>

/**
 * @brief используется для купирования перегрузки приложения при появлении QOpenGlWidget на диаграмме в первый раз,
 * как лечение - загрузка приложения с УЖЕ существующим OpenGL-контекстом
 */
class OglWidget : public QOpenGLWidget
{
public:
    OglWidget(QWidget *parent = nullptr);
    ~OglWidget() override;

protected:
    void paintEvent(QPaintEvent *event) override;
    void initializeGL() override;
    void resizeGL(int w, int h) override;

private:
    QOpenGLFunctions    * m_funcGL{nullptr};

};


#endif //EDITORSD_OGLWIDGET_H
