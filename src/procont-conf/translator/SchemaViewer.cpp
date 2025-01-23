//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
#include <QTextStream>
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
#include "SchemaViewer.h"
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
FBDviewer::FBDviewer(QWidget *parent) : QWidget(parent)
{
    _m_is_drawing               = false;
    _m_left_mouse_button        = false;
    _m_right_mouse_button       = false;
    _m_left_right_mouse_button  = false;
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
// void FBDviewer::setXmlFile(QString _file)
// {
//     T_POU       _pou;
//     T_UDT       _udt;
//     quint32 _pou_counter = 0;
//     quint32 _udt_counter = 0;

//     _m_is_drawing = false;

//     if(_m_XMLparser.setXmlFile(_file))
//     {
//         // ---------------------------------------------------------------
//         while(_m_XMLparser.UDT(_udt_counter, &_udt))
//         {
//             _m_draw_mutex.lock();
//             _m_udt.push_back(_udt);
//             _m_draw_mutex.unlock();
//             _udt_counter++;
//         }
//         // ---------------------------------------------------------------
//         while(_m_XMLparser.POU(_pou_counter, &_pou))
//         {
//             for(int _i = 0; _i < (int)_pou._body._FBD._item.size(); _i++)
//             {
//                 _pou._body._FBD._item[_i]._show         = true;
//                 _pou._body._FBD._item[_i]._select       = false;
//                 _pou._body._FBD._item[_i]._select_move  = false;
//                 _pou._body._FBD._item[_i]._rect.setX(_pou._body._FBD._item[_i]._pos_x);
//                 _pou._body._FBD._item[_i]._rect.setY(_pou._body._FBD._item[_i]._pos_y);
//                 _pou._body._FBD._item[_i]._rect.setWidth(_pou._body._FBD._item[_i]._width);
//                 _pou._body._FBD._item[_i]._rect.setHeight(_pou._body._FBD._item[_i]._height);
//             }
//             _m_draw_mutex.lock();
//             _pou._active = false;
//             _m_pou.push_back(_pou);
//             _m_draw_mutex.unlock();
//             _pou._body._FBD._item.clear();
//             _pou._body._ST._ST_code.clear();
//             _pou._body._IL._IL_code.clear();
//             _pou._body._documentation = "";
//             _pou_counter++;
//         }
//         _m_pou[0]._active = true;
//         // ---------------------------------------------------------------
//         _m_XMLparser.INSTANCES(&_m_inst);
//         // ---------------------------------------------------------------
//         _m_is_drawing = true;
//     }
// }
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
void FBDviewer::showNode(const QDomNode & node_)
{
    _m_is_drawing = false;
    if(PLCopenXmlParser::parsePOU(node_, &_m_pou))
    {
        for(int _i = 0; _i < (int)_m_pou._body._FBD._item.size(); _i++)
        {
            _m_pou._body._FBD._item[_i]._show         = true;
            _m_pou._body._FBD._item[_i]._select       = false;
            _m_pou._body._FBD._item[_i]._select_move  = false;
            _m_pou._body._FBD._item[_i]._rect.setX(_m_pou._body._FBD._item[_i]._pos_x);
            _m_pou._body._FBD._item[_i]._rect.setY(_m_pou._body._FBD._item[_i]._pos_y);
            _m_pou._body._FBD._item[_i]._rect.setWidth(_m_pou._body._FBD._item[_i]._width);
            _m_pou._body._FBD._item[_i]._rect.setHeight(_m_pou._body._FBD._item[_i]._height);
        }
        _m_draw_mutex.lock();
        _m_pou._active = true;
        _m_draw_mutex.unlock();
    }
    _m_is_drawing = true;
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
void FBDviewer::paintEvent(QPaintEvent *)
{
    QPainter _painter(this);

    if(_m_draw_mutex.tryLock())
    {
        for(int _i = 0; _i < (int)_m_pou._body._FBD._item.size(); _i++)
        {
            _m_pou._body._FBD._item[_i]._select = _m_pou._body._FBD._item[_i]._rect.contains(_m_mouse_x, _m_mouse_y);

            QColor _color = _m_pou._body._FBD._item[_i]._select ? Qt::blue : Qt::black;
            QFont _font = QFont("Arial", 8, _m_pou._body._FBD._item[_i]._select ? QFont::Bold : QFont::Normal);
            QPen _pen;
            _pen.setColor(_color);
            _pen.setWidth(_m_pou._body._FBD._item[_i]._select ? 2 : 1);

            _painter.setFont(_font);
            QFontMetrics _fm(_font);

            _painter.setPen(_pen);
            _painter.setBrush(Qt::NoBrush);

            checkPOU_item_position(_i);

            _m_pou._body._FBD._item[_i]._rect.setX(_m_pou._body._FBD._item[_i]._pos_x);
            _m_pou._body._FBD._item[_i]._rect.setY(_m_pou._body._FBD._item[_i]._pos_y);
            _m_pou._body._FBD._item[_i]._rect.setWidth(_m_pou._body._FBD._item[_i]._width);
            _m_pou._body._FBD._item[_i]._rect.setHeight(_m_pou._body._FBD._item[_i]._height);

            _painter.drawRect(_m_pou._body._FBD._item[_i]._rect);

            switch(_m_pou._body._FBD._item[_i]._type)
            {
            case IT_FBD_MAX:{}break;
            case IT_FBD_NOT_DEFINED:{}break;
            case IT_FBD_FUNCTION:
            case IT_FBD_BLOCK:{
                _painter.drawText(_m_pou._body._FBD._item[_i]._rect.x()
                                  + (_m_pou._body._FBD._item[_i]._rect.width() / 2.0)
                                      - (_fm.horizontalAdvance(_m_pou._body._FBD._item[_i]._typeName) / 2.0),
                                  _m_pou._body._FBD._item[_i]._rect.y() + _fm.height(),
                                  _m_pou._body._FBD._item[_i]._typeName);

                _painter.drawText(_m_pou._body._FBD._item[_i]._rect.x() +
                                      (_m_pou._body._FBD._item[_i]._rect.width() / 2.0) -
                                      (_fm.horizontalAdvance(_m_pou._body._FBD._item[_i]._instanceName) / 2.0),
                                  _m_pou._body._FBD._item[_i]._rect.y() - (_fm.height() / 2.0),
                                  _m_pou._body._FBD._item[_i]._instanceName);

                for(int _j = 0; _j < (int)_m_pou._body._FBD._item[_i]._inputVariables.size(); _j++)
                {
                    _painter.drawText(_m_pou._body._FBD._item[_i]._rect.x() + _m_pou._body._FBD._item[_i]._inputVariables[_j]._relPosition._x + 3,
                                      _m_pou._body._FBD._item[_i]._rect.y() + _m_pou._body._FBD._item[_i]._inputVariables[_j]._relPosition._y + (_fm.height() / 3.0),
                                      _m_pou._body._FBD._item[_i]._inputVariables[_j]._formalParameter);

                    _painter.drawLine(_m_pou._body._FBD._item[_i]._rect.x() + _m_pou._body._FBD._item[_i]._inputVariables[_j]._relPosition._x,
                                      _m_pou._body._FBD._item[_i]._rect.y() + _m_pou._body._FBD._item[_i]._inputVariables[_j]._relPosition._y,
                                      _m_pou._body._FBD._item[_i]._rect.x() + _m_pou._body._FBD._item[_i]._inputVariables[_j]._relPosition._x - 10,
                                      _m_pou._body._FBD._item[_i]._rect.y() + _m_pou._body._FBD._item[_i]._inputVariables[_j]._relPosition._y);

                    for(int _c = 1; _c < (int)_m_pou._body._FBD._item[_i]._inputVariables[_j]._connection._position.size(); _c++)
                        _painter.drawLine(_m_pou._body._FBD._item[_i]._inputVariables[_j]._connection._position[_c - 1]._x,
                                          _m_pou._body._FBD._item[_i]._inputVariables[_j]._connection._position[_c - 1]._y,
                                          _m_pou._body._FBD._item[_i]._inputVariables[_j]._connection._position[_c]._x,
                                          _m_pou._body._FBD._item[_i]._inputVariables[_j]._connection._position[_c]._y);
                }

                for(int _j = 0; _j < (int)_m_pou._body._FBD._item[_i]._outputVariables.size(); _j++)
                {
                    _painter.drawText(_m_pou._body._FBD._item[_i]._rect.x() + _m_pou._body._FBD._item[_i]._outputVariables[_j]._relPosition._x
                                          - _fm.horizontalAdvance(_m_pou._body._FBD._item[_i]._outputVariables[_j]._formalParameter) - 3,
                                      _m_pou._body._FBD._item[_i]._rect.y() + _m_pou._body._FBD._item[_i]._outputVariables[_j]._relPosition._y + (_fm.height() / 3.0),
                                      _m_pou._body._FBD._item[_i]._outputVariables[_j]._formalParameter);

                    _painter.drawLine(_m_pou._body._FBD._item[_i]._rect.x() + _m_pou._body._FBD._item[_i]._outputVariables[_j]._relPosition._x,
                                      _m_pou._body._FBD._item[_i]._rect.y() + _m_pou._body._FBD._item[_i]._outputVariables[_j]._relPosition._y,
                                      _m_pou._body._FBD._item[_i]._rect.x() + _m_pou._body._FBD._item[_i]._outputVariables[_j]._relPosition._x + 10,
                                      _m_pou._body._FBD._item[_i]._rect.y() + _m_pou._body._FBD._item[_i]._outputVariables[_j]._relPosition._y);

                    for(int _c = 1; _c < (int)_m_pou._body._FBD._item[_i]._outputVariables[_j]._connection._position.size(); _c++)
                        _painter.drawLine(_m_pou._body._FBD._item[_i]._outputVariables[_j]._connection._position[_c - 1]._x,
                                          _m_pou._body._FBD._item[_i]._outputVariables[_j]._connection._position[_c - 1]._y,
                                          _m_pou._body._FBD._item[_i]._outputVariables[_j]._connection._position[_c]._x,
                                          _m_pou._body._FBD._item[_i]._outputVariables[_j]._connection._position[_c]._y);
                }

                for(int _j = 0; _j < (int)_m_pou._body._FBD._item[_i]._inOutVariables.size(); _j++)
                {
                    _painter.drawText(_m_pou._body._FBD._item[_i]._rect.x() + _m_pou._body._FBD._item[_i]._inOutVariables[_j]._relPosition._x
                                          - _fm.horizontalAdvance(_m_pou._body._FBD._item[_i]._inOutVariables[_j]._formalParameter) - 3,
                                      _m_pou._body._FBD._item[_i]._rect.y() + _m_pou._body._FBD._item[_i]._inOutVariables[_j]._relPosition._y + (_fm.height() / 3.0),
                                      _m_pou._body._FBD._item[_i]._inOutVariables[_j]._formalParameter);

                }
            }break;
            case IT_FBD_INPUT:
            {
                _painter.drawText(_m_pou._body._FBD._item[_i]._rect.x()
                                  + (_m_pou._body._FBD._item[_i]._rect.width() / 2.0)
                                      - (_fm.horizontalAdvance(_m_pou._body._FBD._item[_i]._expression) / 2.0),
                                  _m_pou._body._FBD._item[_i]._rect.y() + _fm.height(),
                                  _m_pou._body._FBD._item[_i]._expression);
            }break;
            case IT_FBD_OUTPUT:
            {
                _painter.drawText(_m_pou._body._FBD._item[_i]._rect.x()
                                  + (_m_pou._body._FBD._item[_i]._rect.width() / 2.0)
                                      - (_fm.horizontalAdvance(_m_pou._body._FBD._item[_i]._expression) / 2.0),
                                  _m_pou._body._FBD._item[_i]._rect.y() + _fm.height(),
                                  _m_pou._body._FBD._item[_i]._expression);

                _painter.drawLine(_m_pou._body._FBD._item[_i]._rect.x() + _m_pou._body._FBD._item[_i]._relPositionIn._x - 10,
                                  _m_pou._body._FBD._item[_i]._rect.y() + _m_pou._body._FBD._item[_i]._relPositionIn._y,
                                  _m_pou._body._FBD._item[_i]._rect.x() + _m_pou._body._FBD._item[_i]._relPositionIn._x,
                                  _m_pou._body._FBD._item[_i]._rect.y() + _m_pou._body._FBD._item[_i]._relPositionIn._y);

                for(int _c = 1; _c < (int)_m_pou._body._FBD._item[_i]._connection._position.size(); _c++)
                    _painter.drawLine(_m_pou._body._FBD._item[_i]._connection._position[_c - 1]._x,
                                      _m_pou._body._FBD._item[_i]._connection._position[_c - 1]._y,
                                      _m_pou._body._FBD._item[_i]._connection._position[_c]._x,
                                      _m_pou._body._FBD._item[_i]._connection._position[_c]._y);
            }break;
            case IT_FBD_INPUT_OUTPUT:{
                _painter.drawText(_m_pou._body._FBD._item[_i]._rect.x()
                                  + (_m_pou._body._FBD._item[_i]._rect.width() / 2.0)
                                      - (_fm.horizontalAdvance(_m_pou._body._FBD._item[_i]._expression) / 2.0),
                                  _m_pou._body._FBD._item[_i]._rect.y() + _fm.height(),
                                  _m_pou._body._FBD._item[_i]._expression);

                _painter.drawLine(_m_pou._body._FBD._item[_i]._rect.x() + _m_pou._body._FBD._item[_i]._relPositionIn._x - 10,
                                  _m_pou._body._FBD._item[_i]._rect.y() + _m_pou._body._FBD._item[_i]._relPositionIn._y,
                                  _m_pou._body._FBD._item[_i]._rect.x() + _m_pou._body._FBD._item[_i]._relPositionIn._x,
                                  _m_pou._body._FBD._item[_i]._rect.y() + _m_pou._body._FBD._item[_i]._relPositionIn._y);

                for(int _c = 1; _c < (int)_m_pou._body._FBD._item[_i]._connection._position.size(); _c++)
                    _painter.drawLine(_m_pou._body._FBD._item[_i]._connection._position[_c - 1]._x,
                                      _m_pou._body._FBD._item[_i]._connection._position[_c - 1]._y,
                                      _m_pou._body._FBD._item[_i]._connection._position[_c]._x,
                                      _m_pou._body._FBD._item[_i]._connection._position[_c]._y);
            }break;
            case IT_FBD_CONNECTOR:{
                _painter.drawText(_m_pou._body._FBD._item[_i]._rect.x()
                                  + (_m_pou._body._FBD._item[_i]._rect.width() / 2.0)
                                      - (_fm.horizontalAdvance(_m_pou._body._FBD._item[_i]._expression) / 2.0),
                                  _m_pou._body._FBD._item[_i]._rect.y() + _fm.height(),
                                  _m_pou._body._FBD._item[_i]._name);

                for(int _c = 1; _c < (int)_m_pou._body._FBD._item[_i]._connection._position.size(); _c++)
                    _painter.drawLine(_m_pou._body._FBD._item[_i]._connection._position[_c - 1]._x,
                                      _m_pou._body._FBD._item[_i]._connection._position[_c - 1]._y,
                                      _m_pou._body._FBD._item[_i]._connection._position[_c]._x,
                                      _m_pou._body._FBD._item[_i]._connection._position[_c]._y);
            }break;
            case IT_FBD_CONTINUATION:{
                _painter.drawText(_m_pou._body._FBD._item[_i]._rect.x()
                                  + (_m_pou._body._FBD._item[_i]._rect.width() / 2.0)
                                      - (_fm.horizontalAdvance(_m_pou._body._FBD._item[_i]._expression) / 2.0),
                                  _m_pou._body._FBD._item[_i]._rect.y() + _fm.height(),
                                  _m_pou._body._FBD._item[_i]._name);

                for(int _c = 1; _c < (int)_m_pou._body._FBD._item[_i]._connection._position.size(); _c++)
                    _painter.drawLine(_m_pou._body._FBD._item[_i]._connection._position[_c - 1]._x,
                                      _m_pou._body._FBD._item[_i]._connection._position[_c - 1]._y,
                                      _m_pou._body._FBD._item[_i]._connection._position[_c]._x,
                                      _m_pou._body._FBD._item[_i]._connection._position[_c]._y);
            }break;
            case IT_FBD_COMMENT:{
            }break;
            }
        }
        _m_draw_mutex.unlock();
    }
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
void FBDviewer::checkPOU_item_position(int _i)
{
    if(_m_pou._body._FBD._item[_i]._select && _m_left_mouse_button)
    {
        quint32 _delta_x = _m_old_mouse_x - _m_mouse_x;
        quint32 _delta_y = _m_old_mouse_y - _m_mouse_y;

        _m_pou._body._FBD._item[_i]._pos_x -= _delta_x;
        _m_pou._body._FBD._item[_i]._pos_y -= _delta_y;

        switch(_m_pou._body._FBD._item[_i]._type)
        {
        case IT_FBD_MAX:{}break;
        case IT_FBD_NOT_DEFINED:{}break;
        case IT_FBD_FUNCTION:
        case IT_FBD_BLOCK:{
            for(int _j = 0; _j < (int)_m_pou._body._FBD._item[_i]._inputVariables.size(); _j++)
            {
                for(int _c = 0; _c < (int)_m_pou._body._FBD._item[_i]._inputVariables[_j]._connection._position.size(); _c++)
                {
                    _m_pou._body._FBD._item[_i]._inputVariables[_j]._connection._position[_c]._x -= _delta_x;
                    _m_pou._body._FBD._item[_i]._inputVariables[_j]._connection._position[_c]._y -= _delta_y;
                }
            }
            for(int _j = 0; _j < (int)_m_pou._body._FBD._item[_i]._outputVariables.size(); _j++)
            {
                for(int _c = 0; _c < (int)_m_pou._body._FBD._item[_i]._outputVariables[_j]._connection._position.size(); _c++)
                {
                    _m_pou._body._FBD._item[_i]._outputVariables[_j]._connection._position[_c]._x -= _delta_x;
                    _m_pou._body._FBD._item[_i]._outputVariables[_j]._connection._position[_c]._y -= _delta_y;
                }
            }
        }break;
        case IT_FBD_INPUT:{
        }break;
        case IT_FBD_OUTPUT:{
            for(int _c = 0; _c < (int)_m_pou._body._FBD._item[_i]._connection._position.size(); _c++)
            {
                _m_pou._body._FBD._item[_i]._connection._position[_c]._x -= _delta_x;
                _m_pou._body._FBD._item[_i]._connection._position[_c]._y -= _delta_y;
            }
        }break;
        case IT_FBD_INPUT_OUTPUT:{
        }break;
        case IT_FBD_CONNECTOR:{
        }break;
        case IT_FBD_CONTINUATION:{
        }break;
        case IT_FBD_COMMENT:{
        }break;
        }
    }
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
void FBDviewer::mouseMoveEvent(QMouseEvent *event)
{
    if(_m_draw_mutex.tryLock())
    {
        _m_old_mouse_x = _m_mouse_x;
        _m_old_mouse_y = _m_mouse_y;
        _m_mouse_x = event->x();
        _m_mouse_y = event->y();
        update();
        _m_draw_mutex.unlock();
    }
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
void FBDviewer::mousePressEvent(QMouseEvent *event)
{
    if(_m_draw_mutex.tryLock())
    {
        if(event->button() == Qt::LeftButton)   _m_left_mouse_button = true;
        if(event->button() == Qt::RightButton)  _m_right_mouse_button = true;
        update();
        _m_draw_mutex.unlock();
    }
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
void FBDviewer::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event)

    if(_m_draw_mutex.tryLock())
    {
        _m_left_mouse_button = false;
        _m_right_mouse_button = false;
        _m_draw_mutex.unlock();
    }
}
//-----------------------------------------------------------------------------------
//
//
//-----------------------------------------------------------------------------------
