//
// Created by artem on 12/23/24.
//

#ifndef PROCONT_COPENGLDIAGRAM_H
#define PROCONT_COPENGLDIAGRAM_H

#include <QOpenGLWidget>

class COpenGlDiagram : public QOpenGLWidget
{
    Q_OBJECT
public:
    COpenGlDiagram(QWidget *parent = nullptr);
    ~COpenGlDiagram() override;


};


#endif //PROCONT_COPENGLDIAGRAM_H
