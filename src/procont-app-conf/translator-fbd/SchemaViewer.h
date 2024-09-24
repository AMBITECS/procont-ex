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

#include "XmlParser.h"

class QPaintEvent;

class FBDviewer : public QWidget
{
    Q_OBJECT
public:
    explicit FBDviewer(QWidget *parent = nullptr);

    void setXmlFile(QString _file);
    void setNode(const QDomNode & node_);

    void ST_generator(QString _file_name);
    void ST_generate(QString & _buffer);

protected:
    void paintEvent(QPaintEvent *) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

    void checkPOU_item_position(int _p, int _i);

    void GlobalType_STgenerator(QString &text_);
    void Program_STgenerator(QString &text_);
    void ProgramCode_STgenerator(QString &text_);
    void Configuration_STgenerator(QString &text_);

    void Block_STgenerator(T_POU_FBD_ITEM_SHORT _block, QString &text_);
    void Func_STgenerator(T_POU_FBD_ITEM_SHORT _func, QString &text_);
    void Var_STgenerator(T_POU_FBD_ITEM_SHORT _var, QString &text_);

protected:
    QString getTypeByVar(QString _var_name);

    void parseItem();

    void prepareConnectContinuation();
    void prepareLocalVar(QString &);
    void prepareBlock();
    void prepareFuncTempVar();
    void prepareFunc();
    void prepareVar();
    void prepareVarType();

    bool itemIsBlock(quint32 _id);
    bool itemIsFunc(quint32 _id);
    bool itemIsInVar(quint32 _id);
    bool itemIsOutVar(quint32 _id);
    bool itemIsInOutVar(quint32 _id);
    bool itemIsConnect(quint32 _id);
    bool itemIsContinuation(quint32 _id);

    quint32 linkConnect(quint32 _connect_id);

protected:
    bool                    _m_is_drawing;
    quint32                 _m_pou_number;
    QVector<T_POU>          _m_pou;
    QVector<T_UDT>          _m_udt;

    QMap<quint64, T_POU_FBD_ITEM> _m_pou_item;

    QMap<quint64, T_POU_FBD_ITEM_SHORT> _m_pou_block_item;
    QMap<quint64, T_POU_FBD_ITEM_SHORT> _m_pou_func_item;
    QMap<quint64, T_POU_FBD_ITEM_SHORT> _m_pou_in_var_item;
    QMap<quint64, T_POU_FBD_ITEM_SHORT> _m_pou_out_var_item;
    QMap<quint64, T_POU_FBD_ITEM_SHORT> _m_pou_in_out_var_item;
    QMap<quint64, T_POU_FBD_ITEM_SHORT> _m_pou_connect_item;
    QMap<quint64, T_POU_FBD_ITEM_SHORT> _m_pou_continuation_item;

    QMultiMap<quint64, T_POU_FBD_ITEM_SHORT> _m_pou_execution_order_item;

    QMap<quint64, T_POU_FBD_ITEM_SHORT> _m_pou_generator_item;

    T_INSTANCES             _m_inst;
    PLCopenXmlParser        _m_XMLparser;

    QMutex                  _m_draw_mutex;

    QFile                   _m_ST_file;

    quint32             _m_old_mouse_x;
    quint32             _m_old_mouse_y;
    quint32             _m_mouse_x;
    quint32             _m_mouse_y;
    bool                _m_left_mouse_button;
    bool                _m_right_mouse_button;
    bool                _m_left_right_mouse_button;
};

#endif // SCHEMAVIEWER_H
