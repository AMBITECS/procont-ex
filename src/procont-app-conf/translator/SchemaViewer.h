#ifndef SCHEMAVIEWER_H
#define SCHEMAVIEWER_H

#include <QObject>
#include <QFont>
#include <QVector>
#include <QMutex>
#include <QImage>
#include <QBitmap>
#include <QPicture>
#include <QPainter>
#include <QMouseEvent>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsTextItem>
#include <QStandardItemModel>

#include "XmlParser.h"
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
// typedef struct{
//     QString _name;
//     quint32 _baseinputnumber;
//     QString _input_type;
//     QString _output_type;
//     QString _comment;
//     bool    _extensible;
//     QString _filter;
// }T_FUNCTION_RETURN_TYPE;
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
class QPaintEvent;

class FBDviewer : public QWidget
{
    Q_OBJECT
public:
    explicit FBDviewer(QWidget *parent = nullptr);

    void showNode(const QDomNode & node_);

protected:
    void paintEvent(QPaintEvent *) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

    void checkPOU_item_position(int _i);

protected:
    bool                _m_is_drawing;

    QMutex              _m_draw_mutex;

    quint32             _m_old_mouse_x;
    quint32             _m_old_mouse_y;
    quint32             _m_mouse_x;
    quint32             _m_mouse_y;
    bool                _m_left_mouse_button;
    bool                _m_right_mouse_button;
    bool                _m_left_right_mouse_button;

    T_POU _m_pou;
};

#endif // SCHEMAVIEWER_H
