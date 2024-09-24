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
void FBDviewer::setXmlFile(QString _file)
{
    T_POU       _pou;
    T_UDT       _udt;
    quint32 _pou_counter = 0;
    quint32 _udt_counter = 0;

    _m_is_drawing = false;

    if(_m_XMLparser.setXmlFile(_file))
    {
        // ---------------------------------------------------------------
        while(_m_XMLparser.UDT(_udt_counter, &_udt))
        {
            _m_draw_mutex.lock();
            _m_udt.push_back(_udt);
            _m_draw_mutex.unlock();
            _udt_counter++;
        }
        // ---------------------------------------------------------------
        while(_m_XMLparser.POU(_pou_counter, &_pou))
        {
            for(int _i = 0; _i < (int)_pou._body._FBD._item.size(); _i++)
            {
                _pou._body._FBD._item[_i]._show         = true;
                _pou._body._FBD._item[_i]._select       = false;
                _pou._body._FBD._item[_i]._select_move  = false;
                _pou._body._FBD._item[_i]._rect.setX(_pou._body._FBD._item[_i]._pos_x);
                _pou._body._FBD._item[_i]._rect.setY(_pou._body._FBD._item[_i]._pos_y);
                _pou._body._FBD._item[_i]._rect.setWidth(_pou._body._FBD._item[_i]._width);
                _pou._body._FBD._item[_i]._rect.setHeight(_pou._body._FBD._item[_i]._height);
            }
            _m_draw_mutex.lock();
            _pou._active = false;
            _m_pou.push_back(_pou);
            _m_draw_mutex.unlock();
            _pou._body._FBD._item.clear();
            _pou_counter++;
        }
        _m_pou[0]._active = true;
        // ---------------------------------------------------------------
        _m_XMLparser.INSTANCES(&_m_inst);
        // ---------------------------------------------------------------
        _m_is_drawing = true;
    }
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
void FBDviewer::setNode(const QDomNode & node_)
{
    T_POU       _pou;
    T_UDT       _udt;
    quint32 _pou_counter = 0;
    quint32 _udt_counter = 0;

    _m_is_drawing = false;

    if(_m_XMLparser.setNode(node_))
    {
        // ---------------------------------------------------------------
        if(_m_XMLparser.UDT(_udt_counter, &_udt))
        {
            _m_draw_mutex.lock();
            _m_udt.push_back(_udt);
            _m_draw_mutex.unlock();
            _udt_counter++;
        }
        // ---------------------------------------------------------------
        if(_m_XMLparser.POU(_pou_counter, &_pou))
        {
            for(int _i = 0; _i < (int)_pou._body._FBD._item.size(); _i++)
            {
                _pou._body._FBD._item[_i]._show         = true;
                _pou._body._FBD._item[_i]._select       = false;
                _pou._body._FBD._item[_i]._select_move  = false;
                _pou._body._FBD._item[_i]._rect.setX(_pou._body._FBD._item[_i]._pos_x);
                _pou._body._FBD._item[_i]._rect.setY(_pou._body._FBD._item[_i]._pos_y);
                _pou._body._FBD._item[_i]._rect.setWidth(_pou._body._FBD._item[_i]._width);
                _pou._body._FBD._item[_i]._rect.setHeight(_pou._body._FBD._item[_i]._height);
            }
            _m_draw_mutex.lock();
            _pou._active = false;
            _m_pou.push_back(_pou);
            _m_draw_mutex.unlock();
            _pou._body._FBD._item.clear();
            _pou_counter++;
        }
        _m_pou[0]._active = true;
        // ---------------------------------------------------------------
        _m_XMLparser.INSTANCES(&_m_inst);
        // ---------------------------------------------------------------
        _m_is_drawing = true;
    }
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
void FBDviewer::paintEvent(QPaintEvent *)
{
    QPainter _painter(this);

    if(_m_draw_mutex.tryLock())
    {
        for(int _p = 0; _p < (int)_m_pou.size(); _p++)
        {
            if(!_m_pou[_p]._active) continue;
            for(int _i = 0; _i < (int)_m_pou[_p]._body._FBD._item.size(); _i++)
            {
//                if(_m_pou[_p]._body._FBD._item[_i]._type != IT_OUTPUT)
//                    _m_pou[_p]._body._FBD._item[_i]._show = false;
//                if(!_m_pou[_p]._body._FBD._item[_i]._show) continue;

                _m_pou[_p]._body._FBD._item[_i]._select = _m_pou[_p]._body._FBD._item[_i]._rect.contains(_m_mouse_x, _m_mouse_y);

                QColor _color = _m_pou[_p]._body._FBD._item[_i]._select ? Qt::blue : Qt::black;
                QFont _font = QFont("Arial", 8, _m_pou[_p]._body._FBD._item[_i]._select ? QFont::Bold : QFont::Normal);
                QPen _pen;
                _pen.setColor(_color);
                _pen.setWidth(_m_pou[_p]._body._FBD._item[_i]._select ? 2 : 1);

                _painter.setFont(_font);
                QFontMetrics _fm(_font);

                _painter.setPen(_pen);
                _painter.setBrush(Qt::NoBrush);

                checkPOU_item_position(_p, _i);

                _m_pou[_p]._body._FBD._item[_i]._rect.setX(_m_pou[_p]._body._FBD._item[_i]._pos_x);
                _m_pou[_p]._body._FBD._item[_i]._rect.setY(_m_pou[_p]._body._FBD._item[_i]._pos_y);
                _m_pou[_p]._body._FBD._item[_i]._rect.setWidth(_m_pou[_p]._body._FBD._item[_i]._width);
                _m_pou[_p]._body._FBD._item[_i]._rect.setHeight(_m_pou[_p]._body._FBD._item[_i]._height);

                _painter.drawRect(_m_pou[_p]._body._FBD._item[_i]._rect);

                switch(_m_pou[_p]._body._FBD._item[_i]._type)
                {
                case IT_MAX:{}break;
                case IT_NOT_DEFINED:{}break;
                case IT_FUNCTION:
                case IT_BLOCK:{
                    _painter.drawText(_m_pou[_p]._body._FBD._item[_i]._rect.x()
                                      + (_m_pou[_p]._body._FBD._item[_i]._rect.width() / 2.0)
                                      - (_fm.horizontalAdvance(_m_pou[_p]._body._FBD._item[_i]._typeName) / 2.0),
                                      _m_pou[_p]._body._FBD._item[_i]._rect.y() + _fm.height(),
                                      _m_pou[_p]._body._FBD._item[_i]._typeName);

                    _painter.drawText(_m_pou[_p]._body._FBD._item[_i]._rect.x() +
                                      (_m_pou[_p]._body._FBD._item[_i]._rect.width() / 2.0) -
                                      (_fm.horizontalAdvance(_m_pou[_p]._body._FBD._item[_i]._instanceName) / 2.0),
                                      _m_pou[_p]._body._FBD._item[_i]._rect.y() - (_fm.height() / 2.0),
                                      _m_pou[_p]._body._FBD._item[_i]._instanceName);

                    for(int _j = 0; _j < (int)_m_pou[_p]._body._FBD._item[_i]._inputVariables.size(); _j++)
                    {
                        _painter.drawText(_m_pou[_p]._body._FBD._item[_i]._rect.x() + _m_pou[_p]._body._FBD._item[_i]._inputVariables[_j]._relPosition._x + 3,
                                          _m_pou[_p]._body._FBD._item[_i]._rect.y() + _m_pou[_p]._body._FBD._item[_i]._inputVariables[_j]._relPosition._y + (_fm.height() / 3.0),
                                          _m_pou[_p]._body._FBD._item[_i]._inputVariables[_j]._formalParameter);

                        _painter.drawLine(_m_pou[_p]._body._FBD._item[_i]._rect.x() + _m_pou[_p]._body._FBD._item[_i]._inputVariables[_j]._relPosition._x,
                                            _m_pou[_p]._body._FBD._item[_i]._rect.y() + _m_pou[_p]._body._FBD._item[_i]._inputVariables[_j]._relPosition._y,
                                            _m_pou[_p]._body._FBD._item[_i]._rect.x() + _m_pou[_p]._body._FBD._item[_i]._inputVariables[_j]._relPosition._x - 10,
                                            _m_pou[_p]._body._FBD._item[_i]._rect.y() + _m_pou[_p]._body._FBD._item[_i]._inputVariables[_j]._relPosition._y);

                        for(int _c = 1; _c < (int)_m_pou[_p]._body._FBD._item[_i]._inputVariables[_j]._connection._position.size(); _c++)
                            _painter.drawLine(_m_pou[_p]._body._FBD._item[_i]._inputVariables[_j]._connection._position[_c - 1]._x,
                                                _m_pou[_p]._body._FBD._item[_i]._inputVariables[_j]._connection._position[_c - 1]._y,
                                                _m_pou[_p]._body._FBD._item[_i]._inputVariables[_j]._connection._position[_c]._x,
                                                _m_pou[_p]._body._FBD._item[_i]._inputVariables[_j]._connection._position[_c]._y);
                    }

                    for(int _j = 0; _j < (int)_m_pou[_p]._body._FBD._item[_i]._outputVariables.size(); _j++)
                    {
                        _painter.drawText(_m_pou[_p]._body._FBD._item[_i]._rect.x() + _m_pou[_p]._body._FBD._item[_i]._outputVariables[_j]._relPosition._x
                                          - _fm.horizontalAdvance(_m_pou[_p]._body._FBD._item[_i]._outputVariables[_j]._formalParameter) - 3,
                                          _m_pou[_p]._body._FBD._item[_i]._rect.y() + _m_pou[_p]._body._FBD._item[_i]._outputVariables[_j]._relPosition._y + (_fm.height() / 3.0),
                                          _m_pou[_p]._body._FBD._item[_i]._outputVariables[_j]._formalParameter);

                        _painter.drawLine(_m_pou[_p]._body._FBD._item[_i]._rect.x() + _m_pou[_p]._body._FBD._item[_i]._outputVariables[_j]._relPosition._x,
                                            _m_pou[_p]._body._FBD._item[_i]._rect.y() + _m_pou[_p]._body._FBD._item[_i]._outputVariables[_j]._relPosition._y,
                                            _m_pou[_p]._body._FBD._item[_i]._rect.x() + _m_pou[_p]._body._FBD._item[_i]._outputVariables[_j]._relPosition._x + 10,
                                            _m_pou[_p]._body._FBD._item[_i]._rect.y() + _m_pou[_p]._body._FBD._item[_i]._outputVariables[_j]._relPosition._y);

                        for(int _c = 1; _c < (int)_m_pou[_p]._body._FBD._item[_i]._outputVariables[_j]._connection._position.size(); _c++)
                            _painter.drawLine(_m_pou[_p]._body._FBD._item[_i]._outputVariables[_j]._connection._position[_c - 1]._x,
                                                _m_pou[_p]._body._FBD._item[_i]._outputVariables[_j]._connection._position[_c - 1]._y,
                                                _m_pou[_p]._body._FBD._item[_i]._outputVariables[_j]._connection._position[_c]._x,
                                                _m_pou[_p]._body._FBD._item[_i]._outputVariables[_j]._connection._position[_c]._y);
                    }

                    for(int _j = 0; _j < (int)_m_pou[_p]._body._FBD._item[_i]._inOutVariables.size(); _j++)
                    {
                        _painter.drawText(_m_pou[_p]._body._FBD._item[_i]._rect.x() + _m_pou[_p]._body._FBD._item[_i]._inOutVariables[_j]._relPosition._x
                                          - _fm.horizontalAdvance(_m_pou[_p]._body._FBD._item[_i]._inOutVariables[_j]._formalParameter) - 3,
                                          _m_pou[_p]._body._FBD._item[_i]._rect.y() + _m_pou[_p]._body._FBD._item[_i]._inOutVariables[_j]._relPosition._y + (_fm.height() / 3.0),
                                          _m_pou[_p]._body._FBD._item[_i]._inOutVariables[_j]._formalParameter);

                    }
                }break;
                case IT_INPUT:
                {
                    _painter.drawText(_m_pou[_p]._body._FBD._item[_i]._rect.x()
                                      + (_m_pou[_p]._body._FBD._item[_i]._rect.width() / 2.0)
                                      - (_fm.horizontalAdvance(_m_pou[_p]._body._FBD._item[_i]._expression) / 2.0),
                                      _m_pou[_p]._body._FBD._item[_i]._rect.y() + _fm.height(),
                                      _m_pou[_p]._body._FBD._item[_i]._expression);
                }break;
                case IT_OUTPUT:
                {
                    _painter.drawText(_m_pou[_p]._body._FBD._item[_i]._rect.x()
                                      + (_m_pou[_p]._body._FBD._item[_i]._rect.width() / 2.0)
                                      - (_fm.horizontalAdvance(_m_pou[_p]._body._FBD._item[_i]._expression) / 2.0),
                                      _m_pou[_p]._body._FBD._item[_i]._rect.y() + _fm.height(),
                                      _m_pou[_p]._body._FBD._item[_i]._expression);

                    _painter.drawLine(_m_pou[_p]._body._FBD._item[_i]._rect.x() + _m_pou[_p]._body._FBD._item[_i]._relPositionIn._x - 10,
                                        _m_pou[_p]._body._FBD._item[_i]._rect.y() + _m_pou[_p]._body._FBD._item[_i]._relPositionIn._y,
                                        _m_pou[_p]._body._FBD._item[_i]._rect.x() + _m_pou[_p]._body._FBD._item[_i]._relPositionIn._x,
                                        _m_pou[_p]._body._FBD._item[_i]._rect.y() + _m_pou[_p]._body._FBD._item[_i]._relPositionIn._y);

                    for(int _c = 1; _c < (int)_m_pou[_p]._body._FBD._item[_i]._connection._position.size(); _c++)
                        _painter.drawLine(_m_pou[_p]._body._FBD._item[_i]._connection._position[_c - 1]._x,
                                            _m_pou[_p]._body._FBD._item[_i]._connection._position[_c - 1]._y,
                                            _m_pou[_p]._body._FBD._item[_i]._connection._position[_c]._x,
                                            _m_pou[_p]._body._FBD._item[_i]._connection._position[_c]._y);
                }break;
                case IT_INPUT_OUTPUT:{
                    _painter.drawText(_m_pou[_p]._body._FBD._item[_i]._rect.x()
                                      + (_m_pou[_p]._body._FBD._item[_i]._rect.width() / 2.0)
                                      - (_fm.horizontalAdvance(_m_pou[_p]._body._FBD._item[_i]._expression) / 2.0),
                                      _m_pou[_p]._body._FBD._item[_i]._rect.y() + _fm.height(),
                                      _m_pou[_p]._body._FBD._item[_i]._expression);

                    _painter.drawLine(_m_pou[_p]._body._FBD._item[_i]._rect.x() + _m_pou[_p]._body._FBD._item[_i]._relPositionIn._x - 10,
                                        _m_pou[_p]._body._FBD._item[_i]._rect.y() + _m_pou[_p]._body._FBD._item[_i]._relPositionIn._y,
                                        _m_pou[_p]._body._FBD._item[_i]._rect.x() + _m_pou[_p]._body._FBD._item[_i]._relPositionIn._x,
                                        _m_pou[_p]._body._FBD._item[_i]._rect.y() + _m_pou[_p]._body._FBD._item[_i]._relPositionIn._y);

                    for(int _c = 1; _c < (int)_m_pou[_p]._body._FBD._item[_i]._connection._position.size(); _c++)
                        _painter.drawLine(_m_pou[_p]._body._FBD._item[_i]._connection._position[_c - 1]._x,
                                            _m_pou[_p]._body._FBD._item[_i]._connection._position[_c - 1]._y,
                                            _m_pou[_p]._body._FBD._item[_i]._connection._position[_c]._x,
                                            _m_pou[_p]._body._FBD._item[_i]._connection._position[_c]._y);
                }break;
                case IT_CONNECTOR:{
                    _painter.drawText(_m_pou[_p]._body._FBD._item[_i]._rect.x()
                                      + (_m_pou[_p]._body._FBD._item[_i]._rect.width() / 2.0)
                                      - (_fm.horizontalAdvance(_m_pou[_p]._body._FBD._item[_i]._expression) / 2.0),
                                      _m_pou[_p]._body._FBD._item[_i]._rect.y() + _fm.height(),
                                      _m_pou[_p]._body._FBD._item[_i]._name);

                    for(int _c = 1; _c < (int)_m_pou[_p]._body._FBD._item[_i]._connection._position.size(); _c++)
                        _painter.drawLine(_m_pou[_p]._body._FBD._item[_i]._connection._position[_c - 1]._x,
                                            _m_pou[_p]._body._FBD._item[_i]._connection._position[_c - 1]._y,
                                            _m_pou[_p]._body._FBD._item[_i]._connection._position[_c]._x,
                                            _m_pou[_p]._body._FBD._item[_i]._connection._position[_c]._y);
                }break;
                case IT_CONTINUATION:{
                    _painter.drawText(_m_pou[_p]._body._FBD._item[_i]._rect.x()
                                      + (_m_pou[_p]._body._FBD._item[_i]._rect.width() / 2.0)
                                      - (_fm.horizontalAdvance(_m_pou[_p]._body._FBD._item[_i]._expression) / 2.0),
                                      _m_pou[_p]._body._FBD._item[_i]._rect.y() + _fm.height(),
                                      _m_pou[_p]._body._FBD._item[_i]._name);

                    for(int _c = 1; _c < (int)_m_pou[_p]._body._FBD._item[_i]._connection._position.size(); _c++)
                        _painter.drawLine(_m_pou[_p]._body._FBD._item[_i]._connection._position[_c - 1]._x,
                                            _m_pou[_p]._body._FBD._item[_i]._connection._position[_c - 1]._y,
                                            _m_pou[_p]._body._FBD._item[_i]._connection._position[_c]._x,
                                            _m_pou[_p]._body._FBD._item[_i]._connection._position[_c]._y);
                }break;
                case IT_COMMENT:{
//                    _painter.drawText(_m_pou[_p]._body._FBD._item[_i]._rect.x()
//                                      + (_m_pou[_p]._body._FBD._item[_i]._rect.width() / 2.0)
//                                      - (_fm.horizontalAdvance(_m_pou[_p]._body._FBD._item[_i]._expression) / 2.0),
//                                      _m_pou[_p]._body._FBD._item[_i]._rect.y() + _fm.height(),
//                                      _m_pou[_p]._body._FBD._item[_i]._comment._content);
                }break;
                }
            }
        }
        _m_draw_mutex.unlock();
    }
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
void FBDviewer::checkPOU_item_position(int _p, int _i)
{
    if(_m_pou[_p]._body._FBD._item[_i]._select && _m_left_mouse_button)
    {
        quint32 _delta_x = _m_old_mouse_x - _m_mouse_x;
        quint32 _delta_y = _m_old_mouse_y - _m_mouse_y;

        _m_pou[_p]._body._FBD._item[_i]._pos_x -= _delta_x;
        _m_pou[_p]._body._FBD._item[_i]._pos_y -= _delta_y;

        switch(_m_pou[_p]._body._FBD._item[_i]._type)
        {
        case IT_MAX:{}break;
        case IT_NOT_DEFINED:{}break;
        case IT_FUNCTION:
        case IT_BLOCK:{
            for(int _j = 0; _j < (int)_m_pou[_p]._body._FBD._item[_i]._inputVariables.size(); _j++)
            {
                for(int _c = 0; _c < (int)_m_pou[_p]._body._FBD._item[_i]._inputVariables[_j]._connection._position.size(); _c++)
                {
                    _m_pou[_p]._body._FBD._item[_i]._inputVariables[_j]._connection._position[_c]._x -= _delta_x;
                    _m_pou[_p]._body._FBD._item[_i]._inputVariables[_j]._connection._position[_c]._y -= _delta_y;
                }
            }
            for(int _j = 0; _j < (int)_m_pou[_p]._body._FBD._item[_i]._outputVariables.size(); _j++)
            {
                for(int _c = 0; _c < (int)_m_pou[_p]._body._FBD._item[_i]._outputVariables[_j]._connection._position.size(); _c++)
                {
                    _m_pou[_p]._body._FBD._item[_i]._outputVariables[_j]._connection._position[_c]._x -= _delta_x;
                    _m_pou[_p]._body._FBD._item[_i]._outputVariables[_j]._connection._position[_c]._y -= _delta_y;
                }
            }
        }break;
        case IT_INPUT:{
        }break;
        case IT_OUTPUT:{
//            _m_pou[_p]._body._FBD._item[_i]._relPosition._x -= _delta_x;
//            _m_pou[_p]._body._FBD._item[_i]._relPosition._y -= _delta_y;
            for(int _c = 0; _c < (int)_m_pou[_p]._body._FBD._item[_i]._connection._position.size(); _c++)
            {
                _m_pou[_p]._body._FBD._item[_i]._connection._position[_c]._x -= _delta_x;
                _m_pou[_p]._body._FBD._item[_i]._connection._position[_c]._y -= _delta_y;
            }
        }break;
        case IT_INPUT_OUTPUT:{
        }break;
        case IT_CONNECTOR:{
        }break;
        case IT_CONTINUATION:{
        }break;
        case IT_COMMENT:{
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
//-----------------------------------------------------------------------------------
void FBDviewer::ST_generator(QString _file_name)
{
    _m_ST_file.setFileName(_file_name);
    _m_ST_file.open(QIODevice::WriteOnly | QIODevice::Text);

    QString _data = {};

    GlobalType_STgenerator(_data);
    Program_STgenerator(_data);
    Configuration_STgenerator(_data);

    if(_data.size() && _m_ST_file.isOpen())
        _m_ST_file.write(_data.toLocal8Bit());
    _m_ST_file.close();
}

void FBDviewer::ST_generate(QString &_buffer)
{
    GlobalType_STgenerator(_buffer);
    Program_STgenerator(_buffer);
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
void FBDviewer::GlobalType_STgenerator(QString &text_)
{
    QString _data;

    if(!_m_udt.empty()) _data = QString("TYPE\n");

    for(int _i = 0; _i < (int)_m_udt.size(); _i++)
    {
        switch(_m_udt[_i]._type)
        {
        case DT_MAX:{}break;
        case DT_ARRAY:{
            int _range_counter = 0;
            int _ini_val_counter = 0;
            //            datatype0 : ARRAY [10..20,50..60] OF WORD := [1, 1];
            _data += QString("  %1 : ARRAY [").arg(_m_udt[_i]._name);
            int _size = (int)_m_udt[_i]._array._range.size();
            for(int _j = 0; _j < _size; _j++)
            {
                QString _range = QString("%1..%2").arg(_m_udt[_i]._array._range[_j]._begin).arg(_m_udt[_i]._array._range[_j]._end);
                _data += _range;
                _range_counter++;
                if(_range_counter < _size)_data += ",";
            }
            _data += QString("] OF %1").arg(_m_udt[_i]._array._type);
            if(_m_udt[_i]._initial_value_present)
            {
                _data += " := [";
                int _init_size = (int)_m_udt[_i]._initial_value.size();
                for(int _j = 0; _j < _init_size; _j++)
                {
                    QString _val = QString("%1").arg(_m_udt[_i]._initial_value[_j]);
                    _data += _val;
                    _ini_val_counter++;
                    if(_ini_val_counter < _init_size)_data += ", ";
                }
                _data += "];\n";
            }else _data += QString(";\n");
        }break;
        case DT_STRUCT:{
            //            datatype5 : STRUCT
            //              p0 : datatype3;
            //              p1 : DINT;
            //              p2 : DINT;
            //              p3 : DINT;
            //            END_STRUCT;
            _data += QString("  %1 : STRUCT\n").arg(_m_udt[_i]._name);
            for(int _j = 0; _j < (int)_m_udt[_i]._struct.size(); _j++)
            {
                QString _part = QString("    %1 : %2;\n").arg(_m_udt[_i]._struct[_j]._name).arg(_m_udt[_i]._struct[_j]._type);
                _data += _part;
            }
            _data += "  END_STRUCT;\n";
        }break;
        case DT_ENUM:{
            //            datatype3 : (firstType, secondType) := firstType;
            _data += QString("  %1 : (%2").arg(_m_udt[_i]._name).arg(_m_udt[_i]._enum._value[0]);
            for(int _j = 1; _j < (int)_m_udt[_i]._enum._value.size(); _j++)
                _data += QString(", %1").arg(_m_udt[_i]._name);

            if(_m_udt[_i]._initial_value_present)   _data += QString(") := %1;\n").arg(_m_udt[_i]._initial_value[0]);
            else                                    _data += QString(");\n");
        }break;
        case DT_REDEFINE:{
            _data += QString("  %1 : %2;\n").arg(_m_udt[_i]._name).arg(_m_udt[_i]._redefined_name);
        }break;
        case DT_SUBRANGE_SIGNED:{
            //            datatype1 : INT (0..0) := 0;
            _data += QString("  %1 : %2 (%3..%4)").arg(_m_udt[_i]._name)
                        .arg(_m_udt[_i]._sign_unsign_range._type)
                        .arg(_m_udt[_i]._sign_unsign_range._begin)
                        .arg(_m_udt[_i]._sign_unsign_range._end);
            if(_m_udt[_i]._initial_value_present)   _data += QString(" := %1;\n").arg(_m_udt[_i]._initial_value[0]);
            else                                    _data += QString(";\n");
        }break;
        case DT_SUBRANGE_UNSIGNED:{
            //            datatype1 : UINT (0..0) := 0;
            _data += QString("  %1 : %2 (%3..%4)").arg(_m_udt[_i]._name)
                        .arg(_m_udt[_i]._sign_unsign_range._type)
                        .arg(_m_udt[_i]._sign_unsign_range._begin)
                        .arg(_m_udt[_i]._sign_unsign_range._end);
            if(_m_udt[_i]._initial_value_present)   _data += QString(" := %1;\n").arg(_m_udt[_i]._initial_value[0]);
            else                                    _data += QString(";\n");
        }break;
        }
            }

    if(!_m_udt.empty())
        _data += QString("END_TYPE\n\n");

    text_ += _data;
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
void FBDviewer::Program_STgenerator(QString &text_)
{
    for(int _i = 0; _i < (int)_m_pou.size(); _i++)
    {
        _m_pou_number = _i;
        ProgramCode_STgenerator(text_);
    }
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
void FBDviewer::prepareLocalVar(QString &text_)
{
    QString _data;
    QString _type_name;

    _data = QString("PROGRAM %1\n").arg(_m_pou[_m_pou_number]._name);
    _data += "  VAR\n";
    for(int _j = 0; _j < (int)_m_pou[_m_pou_number]._interface._localVars.size(); _j++)
    {
        if(_m_pou[_m_pou_number]._interface._localVars[_j]._type_name == "string")  _type_name = _m_pou[_m_pou_number]._interface._localVars[_j]._type_name.toUpper();
        else                                                                        _type_name = _m_pou[_m_pou_number]._interface._localVars[_j]._type_name;

        QString _var;
        if(_m_pou[_m_pou_number]._interface._localVars[_j]._initialValue._simpleValue == "")
        {
            _var = QString("    %1 : %2;\n").arg(_m_pou[_m_pou_number]._interface._localVars[_j]._name)
            .arg(_type_name);
        }else{
            if(_m_pou[_m_pou_number]._interface._localVars[_j]._type_name == "string")
            {
                _var = QString("    %1 : %2 := '%3';\n").arg(_m_pou[_m_pou_number]._interface._localVars[_j]._name)
                .arg(_type_name)
                    .arg(_m_pou[_m_pou_number]._interface._localVars[_j]._initialValue._simpleValue);
            }else{
                _var = QString("    %1 : %2 := %3;\n").arg(_m_pou[_m_pou_number]._interface._localVars[_j]._name)
                .arg(_type_name)
                    .arg(_m_pou[_m_pou_number]._interface._localVars[_j]._initialValue._simpleValue);
            }
        }
        _data += _var;
    }
    foreach(T_POU_FBD_ITEM_SHORT _it, _m_pou_func_item)
    {
        QString _var_code = QString("    _%1 : %2;\n")
        .arg(_m_pou_func_item[_it._localId]._expression)
            .arg(_m_pou_func_item[_it._localId]._out_var_type);

        _data += _var_code;
    }

    _data += "  END_VAR\n\n";

    text_ += _data;
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
QString FBDviewer::getTypeByVar(QString _var_name)
{
    QString _type_name;
    for(int _j = 0; _j < (int)_m_pou[_m_pou_number]._interface._localVars.size(); _j++)
        if(_m_pou[_m_pou_number]._interface._localVars[_j]._name == _var_name)
        {
            if(_m_pou[_m_pou_number]._interface._localVars[_j]._type_name == "string")  _type_name = _m_pou[_m_pou_number]._interface._localVars[_j]._type_name.toUpper();
            else                                                                        _type_name = _m_pou[_m_pou_number]._interface._localVars[_j]._type_name;
        }
    return _type_name;
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
void FBDviewer::ProgramCode_STgenerator(QString &text_)
{
    QString _data = {};

    _m_pou_item.clear();
    _m_pou_execution_order_item.clear();
    _m_pou_generator_item.clear();

    for(int _i = 0; _i < (int)_m_pou[_m_pou_number]._body._FBD._item.size(); _i++)
        _m_pou_item.insert(_m_pou[_m_pou_number]._body._FBD._item[_i]._localId, _m_pou[_m_pou_number]._body._FBD._item[_i]);

    parseItem();
    prepareFuncTempVar();
    prepareVarType();
    prepareConnectContinuation();
    prepareVar();
    prepareFunc();
    prepareLocalVar(text_);
    prepareBlock();

    _m_pou_execution_order_item.clear();
    foreach(T_POU_FBD_ITEM_SHORT _it, _m_pou_block_item)
        if(_it._executionOrderId != 0)
        {
            _m_pou_execution_order_item.insert(_it._executionOrderId, _it);
            _m_pou_block_item.remove(_it._localId);
        }

    foreach(T_POU_FBD_ITEM_SHORT _it, _m_pou_func_item)
        if(_it._executionOrderId != 0)
        {
            _m_pou_execution_order_item.insert(_it._executionOrderId, _it);
            _m_pou_func_item.remove(_it._localId);
        }

    foreach(T_POU_FBD_ITEM_SHORT _it, _m_pou_execution_order_item)
    {
        switch(_it._type)
        {
        case IT_BLOCK:{         Block_STgenerator(_it, text_); }break;
        case IT_FUNCTION:{      Func_STgenerator(_it, text_);  }break;
        case IT_OUTPUT:{        Var_STgenerator(_it, text_);   }break;
        case IT_INPUT_OUTPUT:{  Var_STgenerator(_it, text_);   }break;
        case IT_MAX:
        case IT_COMMENT:
        case IT_INPUT:
        case IT_CONNECTOR:
        case IT_NOT_DEFINED:
        case IT_CONTINUATION:{}break;
        }
    }

    foreach(T_POU_FBD_ITEM_SHORT _it, _m_pou_block_item)        Block_STgenerator(_it, text_);
    foreach(T_POU_FBD_ITEM_SHORT _it, _m_pou_func_item)         Func_STgenerator(_it, text_);
    foreach(T_POU_FBD_ITEM_SHORT _it, _m_pou_in_out_var_item)   Var_STgenerator(_it, text_);
    foreach(T_POU_FBD_ITEM_SHORT _it, _m_pou_out_var_item)      Var_STgenerator(_it, text_);

    _data = "\nEND_PROGRAM\n\n";

    text_ += _data;
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
void FBDviewer::Block_STgenerator(T_POU_FBD_ITEM_SHORT _block, QString &text_)
{
    QString _data;

    if(_block._inputVariables.isEmpty()) return;

    _data = "  ";
    _data += _block._instanceName + "(";
    for(int _j = 0; _j < _block._inputVariables.size(); _j++)
    {
        _data += _block._inputVariables[_j];
        if((_j + 1) < _block._inputVariables.size()) _data += ", ";
    }
    _data += ");\n";
    text_ += _data;
    if(!_block._outputVariables.isEmpty())
    {
        _data = "  ";
        _data += _block._outputVariables[0] + ";\n";
        text_ += _data;
    }
    if(!_block._inOutVariables.isEmpty())
    {
        _data = "  ";
        _data += _block._inOutVariables[0] + ";\n";
        text_ += _data;
    }
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
void FBDviewer::Func_STgenerator(T_POU_FBD_ITEM_SHORT _func, QString &text_)
{
    QString _data;

    if(_func._inputVariables.isEmpty()) return;

    _data = "  ";
    _data += _func._expression + " := ";
    _data += _func._typeName + "(";

    for(int _j = 0; _j < _func._inputVariables.size(); _j++)
    {
        _data += _func._inputVariables[_j];
        if((_j + 1) < _func._inputVariables.size()) _data += ", ";
    }
    _data += ");\n";
    text_ += _data;

    if(!_func._outputVariables.isEmpty())
    {
        _data = "  ";
        _data += _func._outputVariables[0] + ";\n";
        text_ += _data;
    }
    if(!_func._inOutVariables.isEmpty())
    {
        _data = "  ";
        _data += _func._inOutVariables[0] + ";\n";
        text_ += _data;
    }
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
void FBDviewer::Var_STgenerator(T_POU_FBD_ITEM_SHORT _var, QString &text_)
{
    QString _data;

    if(_var._is_used) return;
    if(_var._inputVariables.isEmpty()) return;

    _data = "  ";
    _data += _var._inputVariables[0] + ";\n";
    text_ += _data;
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
void FBDviewer::prepareBlock()
{
    QString _var;
    foreach(T_POU_FBD_ITEM_SHORT _it, _m_pou_block_item)
    {
        quint32 _block_id = _it._localId;

        for(int _v = 0; _v < (int)_m_pou_item[_block_id]._inputVariables.size(); _v++)
        {
            if(_m_pou_item[_block_id]._inputVariables[_v]._connection._refLocalId != -1)
            {
                quint32 _var_id = _m_pou_item[_block_id]._inputVariables[_v]._connection._refLocalId;
                _var = _m_pou_item[_block_id]._inputVariables[_v]._formalParameter + " := ";

                if(itemIsBlock(_var_id))
                {
                    _var += _m_pou_block_item[_var_id]._instanceName;
                    _var += ".";
                    _var += _m_pou_item[_block_id]._inputVariables[_v]._connection._formalParameter;
                }else
                if(itemIsFunc(_var_id))
                {
                    _var += _m_pou_func_item[_var_id]._expression;
                }else
                if(itemIsInVar(_var_id))
                {
                    _var += _m_pou_in_var_item[_var_id]._expression;
                }else
                if(itemIsInOutVar(_var_id))
                {
                    _var += _m_pou_in_out_var_item[_var_id]._expression;
                }else
                if(itemIsContinuation(_var_id))
                {
                    if(!_m_pou_continuation_item[_var_id]._inputVariables.isEmpty())
                        _var += _m_pou_continuation_item[_var_id]._inputVariables[0];
                }
                _m_pou_block_item[_block_id]._inputVariables.push_back(_var);
            }
        }
    }
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
void FBDviewer::prepareFuncTempVar()
{
    foreach(T_POU_FBD_ITEM_SHORT _it, _m_pou_func_item)
    {
        quint32 _func_id = _it._localId;

        QString _var = QString("%1%2_TMP_VAR")
                               .arg(_m_pou_item[_func_id]._typeName)
                               .arg(_func_id);
        _m_pou_func_item[_func_id]._expression = _var;
        _m_pou_item[_func_id]._expression = _var;
    }
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
void FBDviewer::prepareFunc()
{
    QString _var;
    QString _temp_var;
    QString _var_type;

    foreach(T_POU_FBD_ITEM_SHORT _it, _m_pou_func_item)
    {
        quint32 _func_id = _it._localId;

        for(int _v = 0; _v < (int)_m_pou_item[_func_id]._inputVariables.size(); _v++)
        {
            if(_m_pou_item[_func_id]._inputVariables[_v]._connection._refLocalId != -1)
            {
                quint32 _var_id = _m_pou_item[_func_id]._inputVariables[_v]._connection._refLocalId;
                _var = "";

                if(itemIsBlock(_var_id))
                {
                    _var += _m_pou_block_item[_var_id]._instanceName;
                    _var += ".";
                    _var += _m_pou_item[_func_id]._inputVariables[_v]._connection._formalParameter;
                }else
                if(itemIsFunc(_var_id))
                {
                    _var += _m_pou_func_item[_var_id]._expression;
                }else
                if(itemIsInVar(_var_id))
                {
                    _var += _m_pou_in_var_item[_var_id]._expression;
                }else
                if(itemIsOutVar(_var_id))
                {
                    _var += _m_pou_in_var_item[_var_id]._expression;
                }else
                if(itemIsInOutVar(_var_id))
                {
                    _var += _m_pou_in_out_var_item[_var_id]._expression;
                }else
                if(itemIsContinuation(_var_id))
                {
                    if(!_m_pou_continuation_item[_var_id]._inputVariables.isEmpty())
                        _var += _m_pou_continuation_item[_var_id]._inputVariables[0];
                }
                _m_pou_func_item[_func_id]._inputVariables.push_back(_var);
            }
        }
    }
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
void FBDviewer::prepareVarType()
{
    QString _var_type;

    foreach(T_POU_FBD_ITEM_SHORT _it, _m_pou_out_var_item)
    {
        quint32 _out_var_id = _it._localId;
        quint32 _connect_id = _m_pou_item[_out_var_id]._connection._refLocalId;

        if(itemIsBlock(_connect_id))
        {
        }else
        if(itemIsFunc(_connect_id))
        {
            _m_pou_func_item[_connect_id]._out_var_type = _m_pou_out_var_item[_out_var_id]._out_var_type;
        }else
        if(itemIsInVar(_connect_id))
        {
        }else
        if(itemIsInOutVar(_connect_id))
        {
        }else
        if(itemIsContinuation(_connect_id))
        {
            _m_pou_continuation_item[_connect_id]._out_var_type = _m_pou_out_var_item[_out_var_id]._out_var_type;
        }
    }
    foreach(T_POU_FBD_ITEM_SHORT _it, _m_pou_in_out_var_item)
    {
        quint32 _out_var_id = _it._localId;
        quint32 _connect_id = _m_pou_item[_out_var_id]._connection._refLocalId;

        if(itemIsBlock(_connect_id))
        {
        }else
        if(itemIsFunc(_connect_id))
        {
            _m_pou_func_item[_connect_id]._out_var_type = _m_pou_out_var_item[_out_var_id]._out_var_type;
        }else
        if(itemIsInVar(_connect_id))
        {
        }else
        if(itemIsInOutVar(_connect_id))
        {
        }else
        if(itemIsContinuation(_connect_id))
        {
            _m_pou_continuation_item[_connect_id]._out_var_type = _m_pou_out_var_item[_out_var_id]._out_var_type;
        }
    }
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
void FBDviewer::prepareVar()
{
    bool _is_connected;
    QString _var;

    foreach(T_POU_FBD_ITEM_SHORT _it, _m_pou_out_var_item)
    {
        _is_connected = false;
        quint32 _out_var_id = _it._localId;
        quint32 _connect_id = _m_pou_item[_out_var_id]._connection._refLocalId;
        _var = _m_pou_item[_out_var_id]._expression + " := ";

        if(itemIsBlock(_connect_id))
        {
            _is_connected = true;
            _var += _m_pou_block_item[_connect_id]._instanceName;
            _var += ".";
            _var += _m_pou_item[_out_var_id]._connection._formalParameter;
            _m_pou_block_item[_connect_id]._outputVariables.push_back(_var);
            _m_pou_out_var_item[_out_var_id]._is_used = true;
        }else
            if(itemIsFunc(_connect_id))
            {
                _is_connected = true;
                _var += _m_pou_func_item[_connect_id]._expression;
                _m_pou_func_item[_connect_id]._outputVariables.push_back(_var);
                _m_pou_out_var_item[_out_var_id]._is_used = true;
            }else
                if(itemIsInVar(_connect_id))
                {
                    _is_connected = true;
                    _var += _m_pou_in_var_item[_connect_id]._expression;
                }else
                    if(itemIsInOutVar(_connect_id))
                    {
                        _is_connected = true;
                        _var += _m_pou_in_out_var_item[_connect_id]._expression;
                    }else
                        if(itemIsContinuation(_connect_id))
                        {
                            if(!_m_pou_continuation_item[_connect_id]._inputVariables.isEmpty())
                            {
                                _is_connected = true;
                                _var += _m_pou_continuation_item[_connect_id]._inputVariables[0];
                                quint32 _connect_dev_id = _m_pou_item[_connect_id]._connection._refLocalId;
                                if(itemIsBlock(_connect_dev_id))
                                {
                                    _m_pou_block_item[_connect_dev_id]._outputVariables.push_back(_var);
                                    _m_pou_out_var_item[_out_var_id]._is_used = true;
                                }else
                                    if(itemIsFunc(_connect_dev_id))
                                    {
                                        _m_pou_func_item[_connect_dev_id]._outputVariables.push_back(_var);
                                        _m_pou_out_var_item[_out_var_id]._is_used = true;
                                    }
                            }
                        }
        if(_is_connected)
            _m_pou_out_var_item[_out_var_id]._inputVariables.push_back(_var);
    }

    foreach(T_POU_FBD_ITEM_SHORT _it, _m_pou_in_out_var_item)
    {
        _is_connected = false;
        quint32 _out_var_id = _it._localId;
        quint32 _connect_id = _m_pou_item[_out_var_id]._connection._refLocalId;
        _var = _m_pou_item[_out_var_id]._expression + " := ";

        if(itemIsBlock(_connect_id))
        {
            _is_connected = true;
            _var += _m_pou_block_item[_connect_id]._instanceName;
            _var += ".";
            _var += _m_pou_item[_out_var_id]._connection._formalParameter;
            _m_pou_block_item[_connect_id]._inOutVariables.push_back(_var);
            _m_pou_in_out_var_item[_out_var_id]._is_used = true;
        }else
            if(itemIsFunc(_connect_id))
            {
                _is_connected = true;
                _var += _m_pou_func_item[_connect_id]._expression;
                _m_pou_func_item[_connect_id]._inOutVariables.push_back(_var);
                _m_pou_in_out_var_item[_out_var_id]._is_used = true;
            }else
                if(itemIsInVar(_connect_id))
                {
                    _is_connected = true;
                    _var += _m_pou_in_var_item[_connect_id]._expression;
                }else
                    if(itemIsInOutVar(_connect_id))
                    {
                        _is_connected = true;
                        _var += _m_pou_in_out_var_item[_connect_id]._expression;
                    }else
                        if(itemIsContinuation(_connect_id))
                        {
                            if(!_m_pou_continuation_item[_connect_id]._inputVariables.isEmpty())
                            {
                                _is_connected = true;
                                _var += _m_pou_continuation_item[_connect_id]._inputVariables[0];
                            }
                        }
        if(_is_connected)
            _m_pou_in_out_var_item[_out_var_id]._inputVariables.push_back(_var);
    }
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
quint32 FBDviewer::linkConnect(quint32 _connect_id)
{
    quint32 _id = 0;
    foreach(T_POU_FBD_ITEM_SHORT _it, _m_pou_continuation_item)
        if(_it._name == _m_pou_connect_item[_connect_id]._name)
        {
            _id = _it._localId;
            break;
        }
    return _id;
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
void FBDviewer::prepareConnectContinuation()
{
    QString _var;
    foreach(T_POU_FBD_ITEM_SHORT _it, _m_pou_connect_item)
    {
        qint32 _connect_id = _it._localId;
        switch(_m_pou_item[_m_pou_item[_connect_id]._connection._refLocalId]._type)
        {
        case IT_BLOCK:{
            _var = QString("%1.%2")
            .arg(_m_pou_item[_m_pou_item[_connect_id]._connection._refLocalId]._instanceName)
                .arg(_m_pou_item[_connect_id]._connection._formalParameter);
            _m_pou_connect_item[_connect_id]._out_var_type = _m_pou_block_item[_m_pou_item[_connect_id]._connection._refLocalId]._out_var_type;
        }break;
        case IT_FUNCTION:{
            _var = QString("%1")
            .arg(_m_pou_item[_m_pou_item[_connect_id]._connection._refLocalId]._expression);
            _m_pou_connect_item[_connect_id]._out_var_type = _m_pou_func_item[_m_pou_item[_connect_id]._connection._refLocalId]._out_var_type;
        }break;
        case IT_INPUT:{
            _var = QString("%1")
            .arg(_m_pou_item[_m_pou_item[_connect_id]._connection._refLocalId]._expression);
            _m_pou_connect_item[_connect_id]._out_var_type = _m_pou_in_var_item[_m_pou_item[_connect_id]._connection._refLocalId]._out_var_type;
        }break;
        case IT_OUTPUT:{
            _var = QString("%1")
            .arg(_m_pou_item[_m_pou_item[_connect_id]._connection._refLocalId]._expression);
            _m_pou_connect_item[_connect_id]._out_var_type = _m_pou_out_var_item[_m_pou_item[_connect_id]._connection._refLocalId]._out_var_type;
        }break;
        case IT_INPUT_OUTPUT:{
            _var = QString("%1")
            .arg(_m_pou_item[_m_pou_item[_connect_id]._connection._refLocalId]._expression);
            _m_pou_connect_item[_connect_id]._out_var_type = _m_pou_in_out_var_item[_m_pou_item[_connect_id]._connection._refLocalId]._out_var_type;
        }break;
        case IT_MAX:
        case IT_NOT_DEFINED:
        case IT_COMMENT:
        case IT_CONNECTOR:
        case IT_CONTINUATION:{}break;
        }
        _m_pou_connect_item[_connect_id]._outputVariables.push_back(_var);
        quint32 _continuation_id = linkConnect(_connect_id);
        if(_continuation_id != 0)
        {
            _m_pou_continuation_item[_continuation_id]._inputVariables.push_back(_var);
            _m_pou_connect_item[_connect_id]._out_var_type = _m_pou_continuation_item[_continuation_id]._out_var_type;
            _m_pou_item[_continuation_id]._connection._refLocalId = _m_pou_item[_connect_id]._connection._refLocalId;
            //            _m_pou_connect_item[_connect_id]._link = _continuation_id;
            //            _m_pou_continuation_item[_continuation_id]._link = _connect_id;
        }
    }

    foreach(T_POU_FBD_ITEM_SHORT _it, _m_pou_continuation_item)
    {
        qint32 _connect_id = _it._localId;
        switch(_m_pou_item[_m_pou_item[_connect_id]._connection._refLocalId]._type)
        {
        case IT_BLOCK:{
        }break;
        case IT_FUNCTION:{
            _m_pou_func_item[_m_pou_item[_connect_id]._connection._refLocalId]._out_var_type = _it._out_var_type;
        }break;
        case IT_INPUT:{
        }break;
        case IT_OUTPUT:{
        }break;
        case IT_INPUT_OUTPUT:{
        }break;
        case IT_MAX:
        case IT_NOT_DEFINED:
        case IT_COMMENT:
        case IT_CONNECTOR:
        case IT_CONTINUATION:{}break;
        }
    }
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
void FBDviewer::Configuration_STgenerator(QString &text_)
{
    if(!_m_inst._configuration.size())
        return;

    QString _data = {};
    _data = QString("CONFIGURATION %1\n").arg(_m_inst._configuration[0]._name);
    _data += QString(" RESOURCE %1 ON PLC\n").arg(_m_inst._configuration[0]._resource._name);
    for(int _i = 0; _i < _m_inst._configuration[0]._resource._task.size(); _i++)
    {
        _data += QString("   TASK %1(INTERVAL := %2,PRIORITY := %3);\n")
        .arg(_m_inst._configuration[0]._resource._task[_i]._name)
            .arg(_m_inst._configuration[0]._resource._task[_i]._interval)
            .arg(_m_inst._configuration[0]._resource._task[_i]._priority);
    }
    for(int _i = 0; _i < _m_inst._configuration[0]._resource._task.size(); _i++)
    {
        for(int _j = 0; _j < _m_inst._configuration[0]._resource._task[_i]._pouInstance.size(); _j++)
        {
            _data += QString("   PROGRAM %1 WITH %2 : %3;\n")
            .arg(_m_inst._configuration[0]._resource._task[_i]._pouInstance[_j]._name)
                .arg(_m_inst._configuration[0]._resource._task[_i]._name)
                .arg(_m_inst._configuration[0]._resource._task[_i]._pouInstance[_j]._typeName);
        }
    }
    _data += "  END_RESOURCE\n";
    _data += "END_CONFIGURATION\n";

    text_ += _data;
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
void FBDviewer::parseItem()
{
    T_POU_FBD_ITEM_SHORT _item;

    _m_pou_block_item.clear();
    _m_pou_func_item.clear();
    _m_pou_in_var_item.clear();
    _m_pou_out_var_item.clear();
    _m_pou_in_out_var_item.clear();
    _m_pou_connect_item.clear();
    _m_pou_continuation_item.clear();

    for(int _i = 0; _i < (int)_m_pou[_m_pou_number]._body._FBD._item.size(); _i++)
        if(_m_pou[_m_pou_number]._body._FBD._item[_i]._type == IT_BLOCK)
        {
            _item._type                 = _m_pou[_m_pou_number]._body._FBD._item[_i]._type;
            _item._localId              = _m_pou[_m_pou_number]._body._FBD._item[_i]._localId;
            _item._executionOrderId     = _m_pou[_m_pou_number]._body._FBD._item[_i]._executionOrderId;
            _item._negated              = _m_pou[_m_pou_number]._body._FBD._item[_i]._negated;
            _item._expression           = _m_pou[_m_pou_number]._body._FBD._item[_i]._expression;
            _item._name                 = _m_pou[_m_pou_number]._body._FBD._item[_i]._name;
            _item._typeName             = _m_pou[_m_pou_number]._body._FBD._item[_i]._typeName;
            _item._instanceName         = _m_pou[_m_pou_number]._body._FBD._item[_i]._instanceName;
            _item._out_var_type         = "BOOL";
            _item._inOutVariables.clear();
            _item._inputVariables.clear();
            _item._outputVariables.clear();
            _m_pou_block_item.insert(_item._localId, _item);
        }

    for(int _i = 0; _i < (int)_m_pou[_m_pou_number]._body._FBD._item.size(); _i++)
        if(_m_pou[_m_pou_number]._body._FBD._item[_i]._type == IT_FUNCTION)
        {
            _item._type                 = _m_pou[_m_pou_number]._body._FBD._item[_i]._type;
            _item._localId              = _m_pou[_m_pou_number]._body._FBD._item[_i]._localId;
            _item._executionOrderId     = _m_pou[_m_pou_number]._body._FBD._item[_i]._executionOrderId;
            _item._negated              = _m_pou[_m_pou_number]._body._FBD._item[_i]._negated;
            _item._expression           = _m_pou[_m_pou_number]._body._FBD._item[_i]._expression;
            _item._name                 = _m_pou[_m_pou_number]._body._FBD._item[_i]._name;
            _item._typeName             = _m_pou[_m_pou_number]._body._FBD._item[_i]._typeName;
            _item._instanceName         = _m_pou[_m_pou_number]._body._FBD._item[_i]._instanceName;
            _item._out_var_type         = "";
            _item._inOutVariables.clear();
            _item._inputVariables.clear();
            _item._outputVariables.clear();
            _m_pou_func_item.insert(_item._localId, _item);
        }

    for(int _i = 0; _i < (int)_m_pou[_m_pou_number]._body._FBD._item.size(); _i++)
        if(_m_pou[_m_pou_number]._body._FBD._item[_i]._type == IT_INPUT)
        {
            _item._type                 = _m_pou[_m_pou_number]._body._FBD._item[_i]._type;
            _item._localId              = _m_pou[_m_pou_number]._body._FBD._item[_i]._localId;
            _item._executionOrderId     = _m_pou[_m_pou_number]._body._FBD._item[_i]._executionOrderId;
            _item._negated              = _m_pou[_m_pou_number]._body._FBD._item[_i]._negated;
            _item._expression           = _m_pou[_m_pou_number]._body._FBD._item[_i]._expression;
            _item._name                 = _m_pou[_m_pou_number]._body._FBD._item[_i]._name;
            _item._typeName             = _m_pou[_m_pou_number]._body._FBD._item[_i]._typeName;
            _item._instanceName         = _m_pou[_m_pou_number]._body._FBD._item[_i]._instanceName;
            _item._out_var_type         = getTypeByVar(_item._expression);
            _item._inOutVariables.clear();
            _item._inputVariables.clear();
            _item._outputVariables.clear();
            _m_pou_in_var_item.insert(_item._localId, _item);
        }

    for(int _i = 0; _i < (int)_m_pou[_m_pou_number]._body._FBD._item.size(); _i++)
        if(_m_pou[_m_pou_number]._body._FBD._item[_i]._type == IT_OUTPUT)
        {
            _item._type                 = _m_pou[_m_pou_number]._body._FBD._item[_i]._type;
            _item._localId              = _m_pou[_m_pou_number]._body._FBD._item[_i]._localId;
            _item._executionOrderId     = _m_pou[_m_pou_number]._body._FBD._item[_i]._executionOrderId;
            _item._negated              = _m_pou[_m_pou_number]._body._FBD._item[_i]._negated;
            _item._expression           = _m_pou[_m_pou_number]._body._FBD._item[_i]._expression;
            _item._name                 = _m_pou[_m_pou_number]._body._FBD._item[_i]._name;
            _item._typeName             = _m_pou[_m_pou_number]._body._FBD._item[_i]._typeName;
            _item._instanceName         = _m_pou[_m_pou_number]._body._FBD._item[_i]._instanceName;
            _item._out_var_type         = getTypeByVar(_item._expression);
            _item._inOutVariables.clear();
            _item._inputVariables.clear();
            _item._outputVariables.clear();
            _m_pou_out_var_item.insert(_item._localId, _item);
        }

    for(int _i = 0; _i < (int)_m_pou[_m_pou_number]._body._FBD._item.size(); _i++)
        if(_m_pou[_m_pou_number]._body._FBD._item[_i]._type == IT_INPUT_OUTPUT)
        {
            _item._type                 = _m_pou[_m_pou_number]._body._FBD._item[_i]._type;
            _item._localId              = _m_pou[_m_pou_number]._body._FBD._item[_i]._localId;
            _item._executionOrderId     = _m_pou[_m_pou_number]._body._FBD._item[_i]._executionOrderId;
            _item._negated              = _m_pou[_m_pou_number]._body._FBD._item[_i]._negated;
            _item._expression           = _m_pou[_m_pou_number]._body._FBD._item[_i]._expression;
            _item._name                 = _m_pou[_m_pou_number]._body._FBD._item[_i]._name;
            _item._typeName             = _m_pou[_m_pou_number]._body._FBD._item[_i]._typeName;
            _item._instanceName         = _m_pou[_m_pou_number]._body._FBD._item[_i]._instanceName;
            _item._out_var_type         = getTypeByVar(_item._expression);
            _item._inOutVariables.clear();
            _item._inputVariables.clear();
            _item._outputVariables.clear();
            _m_pou_in_out_var_item.insert(_item._localId, _item);
        }

    for(int _i = 0; _i < (int)_m_pou[_m_pou_number]._body._FBD._item.size(); _i++)
        if(_m_pou[_m_pou_number]._body._FBD._item[_i]._type == IT_CONNECTOR)
        {
            _item._type                 = _m_pou[_m_pou_number]._body._FBD._item[_i]._type;
            _item._localId              = _m_pou[_m_pou_number]._body._FBD._item[_i]._localId;
            _item._executionOrderId     = _m_pou[_m_pou_number]._body._FBD._item[_i]._executionOrderId;
            _item._negated              = _m_pou[_m_pou_number]._body._FBD._item[_i]._negated;
            _item._expression           = _m_pou[_m_pou_number]._body._FBD._item[_i]._expression;
            _item._name                 = _m_pou[_m_pou_number]._body._FBD._item[_i]._name;
            _item._typeName             = _m_pou[_m_pou_number]._body._FBD._item[_i]._typeName;
            _item._instanceName         = _m_pou[_m_pou_number]._body._FBD._item[_i]._instanceName;
            _item._inOutVariables.clear();
            _item._inputVariables.clear();
            _item._outputVariables.clear();
            _m_pou_connect_item.insert(_item._localId, _item);
        }

    for(int _i = 0; _i < (int)_m_pou[_m_pou_number]._body._FBD._item.size(); _i++)
        if(_m_pou[_m_pou_number]._body._FBD._item[_i]._type == IT_CONTINUATION)
        {
            _item._type                 = _m_pou[_m_pou_number]._body._FBD._item[_i]._type;
            _item._localId              = _m_pou[_m_pou_number]._body._FBD._item[_i]._localId;
            _item._executionOrderId     = _m_pou[_m_pou_number]._body._FBD._item[_i]._executionOrderId;
            _item._negated              = _m_pou[_m_pou_number]._body._FBD._item[_i]._negated;
            _item._expression           = _m_pou[_m_pou_number]._body._FBD._item[_i]._expression;
            _item._name                 = _m_pou[_m_pou_number]._body._FBD._item[_i]._name;
            _item._typeName             = _m_pou[_m_pou_number]._body._FBD._item[_i]._typeName;
            _item._instanceName         = _m_pou[_m_pou_number]._body._FBD._item[_i]._instanceName;
            _item._inOutVariables.clear();
            _item._inputVariables.clear();
            _item._outputVariables.clear();
            _m_pou_continuation_item.insert(_item._localId, _item);
        }
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
bool FBDviewer::itemIsBlock(quint32 _id)
{
    if(_m_pou_block_item.find(_id) != _m_pou_block_item.end())
        return true;
    return false;
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
bool FBDviewer::itemIsFunc(quint32 _id)
{
    if(_m_pou_func_item.find(_id) != _m_pou_func_item.end())
        return true;
    return false;
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
bool FBDviewer::itemIsInVar(quint32 _id)
{
    if(_m_pou_in_var_item.find(_id) != _m_pou_in_var_item.end())
        return true;
    return false;
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
bool FBDviewer::itemIsOutVar(quint32 _id)
{
    if(_m_pou_out_var_item.find(_id) != _m_pou_out_var_item.end())
        return true;
    return false;
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
bool FBDviewer::itemIsInOutVar(quint32 _id)
{
    if(_m_pou_in_out_var_item.find(_id) != _m_pou_in_out_var_item.end())
        return true;
    return false;
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
bool FBDviewer::itemIsConnect(quint32 _id)
{
    if(_m_pou_connect_item.find(_id) != _m_pou_connect_item.end())
        return true;
    return false;
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
bool FBDviewer::itemIsContinuation(quint32 _id)
{
    if(_m_pou_continuation_item.find(_id) != _m_pou_continuation_item.end())
        return true;
    return false;
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
