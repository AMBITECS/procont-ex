#ifndef COGLWIDGET_H
#define COGLWIDGET_H

#include <QOpenGLWidget>
#include <QScrollBar>
#include <QOpenGLFunctions>
#include <QDomNode>

#include "cgraphicshelper.h"
#include "COglStyle.h"
#include "../../general/ctreeobject.h"
#include "../../../st/CodeEditorWidget.h"

struct s_ogl_startup
{
    QDomNode    * node{nullptr};
    CTreeObject * tree{nullptr};
    QScrollBar  * vertical{nullptr};
    QScrollBar  * horizontal{nullptr};
    bool          is_editable{false};
    CodeEditorWidget * st_widget{nullptr};

};

class COglWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    explicit COglWidget(s_ogl_startup * ogl_startup, QWidget *parent = nullptr);
    ~COglWidget() override;

    // open GL
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

    // context
    void showEvent( QShowEvent* event ) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *evt) override;
    void keyReleaseEvent(QKeyEvent *evt) override;

    // drag & drop
    void dropEvent(QDropEvent *event) override;
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;
    void dragLeaveEvent(QDragLeaveEvent *event) override;


protected slots:
    void  vertical_scroll_moved(int position);
    void  horizontal_scroll_moved(int position);
    void  project_loaded();
    void  diagram_resized(const int &w, const int &h);

signals:
    void  scroll_bars_moving(const QPoint & newPos);

protected:


private:
    std::vector<CLadder*>   * m_ladders;
    CGraphicsHelper     * m_helper;
    QScrollBar          * m_vertical;
    QScrollBar          * m_horizontal;

    QOpenGLFunctions    * m_funcGL{nullptr};
    QPaintDevice        * m_paint_dev;
    QPoint                m_start_move;
    QString               mime_data_text{"application/x-qabstractitemmodeldatalist"};
    COglStyle           * m_style;

    int                   m_X_scroll{0};
    int                   m_Y_scroll{0};

    /// проба пера
    const float PI =3.141592653; //Замечательно число Пи
    int height{0};      //Высота персонажа, тут нуль, дабы смещения не происходило.

    void draw_ladders();
};

#endif // COGLWIDGET_H

/*Here's an implementation of gluLookAt:
vec3_t x, y, z;
mat4_t m;

// view direction
z[0] = eyex - centerx;
z[1] = eyey - centery;
z[2] = eyez - centerz;

// default y to up
y[0] = upx;
y[1] = upy;
y[2] = upz;

// force x, y and z to be all perpendicular to each other
vec3_Normalise(z);
vec3_Cross(y, z, x);
vec3_Cross(z, x, y);

// normalise
vec3_Normalise(x);
vec3_Normalise(y);

// Stuff them all into a matrix
m[0] = x[0]; m[1] = y[0]; m[2] = z[0]; m[3] = 0;
m[4] = x[1]; m[5] = y[1]; m[6] = z[1]; m[7] = 0;
m[8] = x[2]; m[9] = y[2]; m[10] = z[2]; m[11] = 0;
m[12] = 0; m[13] = 0; m[14] = 0; m[15] = 1;

// tell gl all about it
mat4_Translate(-eyex, -eyey, -eyez, m);
mat4_Mult(modelview, m, modelview);*/
