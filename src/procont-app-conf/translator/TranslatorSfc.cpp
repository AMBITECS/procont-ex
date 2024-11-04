#include "TranslatorSfc.h"
#include "TranslatorFbd.h"
#include "TranslatorIL.h"
#include "TranslatorLD.h"
#include "TranslatorST.h"

TranslatorSFC::TranslatorSFC() {}

// *** POU
//
//-----------------------------------------------------------------------------------
void TranslatorSFC::Code_STgenerator(T_POU pou_, QString &text_)
{
    parseItem(&pou_);
    AllVar_STgenerator(&pou_, text_);

    _m_SFC_inline_counter = 1;

    foreach(T_POU_SFC_ITEM _it, _m_step_item)
        if(_it._initialStep == "true")
        {
            Step_STcode(_it, text_, true);
            _m_step_item[_it._localId]._is_used = true;
        }

    foreach(T_POU_SFC_ITEM _it, _m_transition_item)
        Transition_STcode(_it._localId, text_);

    switch(pou_._pouType)
    {
    case PT_FUNCTION:{          text_ += "END_FUNCTION\n\n";        }break;
    case PT_FUNCTION_BLOCK:{    text_ += "END_FUNCTION_BLOCK\n\n";  }break;
    case PT_PROGRAMM:{          text_ += "END_PROGRAM\n\n";         }break;
    case PT_MAX:{}break;
    case PT_NOT_DEFINED:{}break;
    }
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
void TranslatorSFC::Code_STgenerator(T_POU_BODY_SFC _sfc, QString &text_)
{
    parseItem(&_sfc);
//    AllVar_STgenerator(&pou_, text_);

    _m_SFC_inline_counter = 1;

    foreach(T_POU_SFC_ITEM _it, _m_step_item)
        if(_it._initialStep == "true")
        {
            Step_STcode(_it, text_, true);
            _m_step_item[_it._localId]._is_used = true;
        }

    foreach(T_POU_SFC_ITEM _it, _m_transition_item)
        Transition_STcode(_it._localId, text_);
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
void TranslatorSFC::parseItem(T_POU *pou_)
{
    quint32 _connect;

    _m_step_item.clear();
    _m_transition_item.clear();
    _m_jump_step_item.clear();
    _m_selDivergence_item.clear();
    _m_selConvergence_item.clear();
    _m_simDivergence_item.clear();
    _m_simConvergence_item.clear();
    _m_action.clear();

    for(int _i = 0; _i < (int)pou_->_actions.size(); _i++) _m_action.push_back(pou_->_actions[_i]);

    for(int _i = 0; _i < (int)pou_->_body._SFC._item.size(); _i++)
        if(pou_->_body._SFC._item[_i]._initialStep == "true")
            pou_->_body._SFC._item[_i]._is_chain_used = true;

    for(int _i = 0; _i < (int)pou_->_body._SFC._item.size(); _i++)
        if(checkIsChainUsed(pou_, _i)) _i = 0;

    for(int _i = 0; _i < (int)pou_->_body._SFC._item.size(); _i++)
        if(pou_->_body._SFC._item[_i]._is_chain_used)
            switch(pou_->_body._SFC._item[_i]._type)
            {
            case IT_SFC_TRANSITION:{                _m_transition_item.insert(pou_->_body._SFC._item[_i]._localId, pou_->_body._SFC._item[_i]);       }break;
            case IT_SFC_SELECTION_DIVERGENCE:{      _m_selDivergence_item.insert(pou_->_body._SFC._item[_i]._localId, pou_->_body._SFC._item[_i]);    }break;
            case IT_SFC_SELECTION_CONVERGENCE:{     _m_selConvergence_item.insert(pou_->_body._SFC._item[_i]._localId, pou_->_body._SFC._item[_i]);   }break;
            case IT_SFC_SIMULTANEUS_DIVERGENCE:{    _m_simDivergence_item.insert(pou_->_body._SFC._item[_i]._localId, pou_->_body._SFC._item[_i]);    }break;
            case IT_SFC_SIMULTANEUS_CONVERGENCE:{   _m_simConvergence_item.insert(pou_->_body._SFC._item[_i]._localId, pou_->_body._SFC._item[_i]);   }break;
            case IT_SFC_STEP:{                      _m_step_item.insert(pou_->_body._SFC._item[_i]._localId, pou_->_body._SFC._item[_i]);             }break;
            case IT_SFC_ACTION_BLOCK:{              _m_action_block_item.insert(pou_->_body._SFC._item[_i]._localId, pou_->_body._SFC._item[_i]);     }break;
            case IT_SFC_JUMP_STEP:{                 _m_jump_step_item.insert(pou_->_body._SFC._item[_i]._localId, pou_->_body._SFC._item[_i]);        }break;
            case IT_SFC_NOT_DEFINED:
            case IT_SFC_COMMENT:
            case IT_SFC_TYPE_MAX:{}break;
            }

    foreach(T_POU_SFC_ITEM _it, _m_jump_step_item)
    {
        foreach(T_POU_SFC_ITEM _t, _m_step_item)
        if(_it._targetName == _t._name)
        {
            T_CONNECTION_POINT_IN _point_in;
            T_CONNECTION _connection;
            _connection._refLocalId = _it._point_in[0]._connection[0]._refLocalId;
            if(itemIsTransition(_connection._refLocalId))       _m_step_item[_t._localId]._in_connection = IT_SFC_TRANSITION_CONNECTION;
            if(itemIsSelConvergence(_connection._refLocalId))   _m_step_item[_t._localId]._in_connection = IT_SFC_SEL_CONVERGENCE_CONNECTION;
            if(itemIsSelDivergence(_connection._refLocalId))    _m_step_item[_t._localId]._in_connection = IT_SFC_SEL_DIVERGENCE_CONNECTION;
            if(itemIsSimConvergence(_connection._refLocalId))   _m_step_item[_t._localId]._in_connection = IT_SFC_SIM_CONVERGENCE_CONNECTION;
            if(itemIsSimDivergence(_connection._refLocalId))    _m_step_item[_t._localId]._in_connection = IT_SFC_SIM_DIVERGENCE_CONNECTION;
            _point_in._connection.push_back(_connection);
            _m_step_item[_t._localId]._point_in.push_back(_point_in);
            break;
        }
    }

    foreach(T_POU_SFC_ITEM _it, _m_jump_step_item)
    {
        foreach(T_POU_SFC_ITEM _t, _m_transition_item)
        if(_it._targetName == _t._name)
        {
            T_CONNECTION_POINT_IN _point_in;
            T_CONNECTION _connection;
            _connection._refLocalId = _it._point_in[0]._connection[0]._refLocalId;
            if(itemIsStep(_connection._refLocalId))             _m_transition_item[_t._localId]._in_connection = IT_SFC_STEP_CONNECTION;
            if(itemIsSelConvergence(_connection._refLocalId))   _m_transition_item[_t._localId]._in_connection = IT_SFC_SEL_CONVERGENCE_CONNECTION;
            if(itemIsSelDivergence(_connection._refLocalId))    _m_transition_item[_t._localId]._in_connection = IT_SFC_SEL_DIVERGENCE_CONNECTION;
            if(itemIsSimConvergence(_connection._refLocalId))   _m_transition_item[_t._localId]._in_connection = IT_SFC_SIM_CONVERGENCE_CONNECTION;
            if(itemIsSimDivergence(_connection._refLocalId))    _m_transition_item[_t._localId]._in_connection = IT_SFC_SIM_DIVERGENCE_CONNECTION;
            _point_in._connection.push_back(_connection);
            _m_transition_item[_t._localId]._point_in.push_back(_point_in);
            break;
        }
    }

    foreach(T_POU_SFC_ITEM _it, _m_selDivergence_item)
    {
        _connect = 0;
        foreach(T_POU_SFC_ITEM _t, _m_step_item)
            for(int _i = 0; _i < _t._point_in.size(); _i++)
                if(!_t._point_in[_i]._connection.empty())
                    if(_it._localId == _t._point_in[_i]._connection[0]._refLocalId)
                    {
                        _m_step_item[_t._localId]._in_connection = IT_SFC_SEL_DIVERGENCE_CONNECTION;
                        _m_selDivergence_item[_it._localId]._point_out[_connect]._refLocalId = _t._localId;
                        _connect++;
                    }
        _connect = 0;
        foreach(T_POU_SFC_ITEM _t, _m_transition_item)
            for(int _i = 0; _i < _t._point_in.size(); _i++)
                if(!_t._point_in[_i]._connection.empty())
                    if(_it._localId == _t._point_in[_i]._connection[0]._refLocalId)
                    {
                        _m_transition_item[_t._localId]._in_connection = IT_SFC_SEL_DIVERGENCE_CONNECTION;
                        _m_selDivergence_item[_it._localId]._point_out[_connect]._refLocalId = _t._localId;
                        _connect++;
                    }
    }

    foreach(T_POU_SFC_ITEM _it, _m_selConvergence_item)
    {
        _connect = 0;
        foreach(T_POU_SFC_ITEM _t, _m_step_item)
            for(int _i = 0; _i < _t._point_in.size(); _i++)
                if(!_t._point_in[_i]._connection.empty())
                    if(_it._localId == _t._point_in[_i]._connection[0]._refLocalId)
                    {
                        _m_step_item[_t._localId]._in_connection = IT_SFC_SEL_CONVERGENCE_CONNECTION;
                        _m_selConvergence_item[_it._localId]._point_out[_connect]._refLocalId = _t._localId;
                        _connect++;
                    }
        _connect = 0;
        foreach(T_POU_SFC_ITEM _t, _m_transition_item)
            for(int _i = 0; _i < _t._point_in.size(); _i++)
                if(!_t._point_in[_i]._connection.empty())
                    if(_it._localId == _t._point_in[_i]._connection[0]._refLocalId)
                    {
                        _m_transition_item[_t._localId]._in_connection = IT_SFC_SEL_CONVERGENCE_CONNECTION;
                        _m_selConvergence_item[_it._localId]._point_out[_connect]._refLocalId = _t._localId;
                        _connect++;
                    }
    }

    foreach(T_POU_SFC_ITEM _it, _m_simDivergence_item)
    {
        _connect = 0;
        foreach(T_POU_SFC_ITEM _t, _m_step_item)
            for(int _i = 0; _i < _t._point_in.size(); _i++)
                if(!_t._point_in[_i]._connection.empty())
                    if(_it._localId == _t._point_in[_i]._connection[0]._refLocalId)
                    {
                        _m_step_item[_t._localId]._in_connection = IT_SFC_SIM_DIVERGENCE_CONNECTION;
                        _m_simDivergence_item[_it._localId]._point_out[_connect]._refLocalId = _t._localId;
                        _connect++;
                    }
        _connect = 0;
        foreach(T_POU_SFC_ITEM _t, _m_transition_item)
            for(int _i = 0; _i < _t._point_in.size(); _i++)
                if(!_t._point_in[_i]._connection.empty())
                    if(_it._localId == _t._point_in[_i]._connection[0]._refLocalId)
                    {
                        _m_transition_item[_t._localId]._in_connection = IT_SFC_SIM_DIVERGENCE_CONNECTION;
                        _m_simDivergence_item[_it._localId]._point_out[_connect]._refLocalId = _t._localId;
                        _connect++;
                    }
    }

    foreach(T_POU_SFC_ITEM _it, _m_simConvergence_item)
    {
        _connect = 0;
        foreach(T_POU_SFC_ITEM _t, _m_step_item)
            for(int _i = 0; _i < _t._point_in.size(); _i++)
                if(!_t._point_in[_i]._connection.empty())
                    if(_it._localId == _t._point_in[_i]._connection[0]._refLocalId)
                    {
                        _m_step_item[_t._localId]._in_connection = IT_SFC_SIM_CONVERGENCE_CONNECTION;
                        _m_simConvergence_item[_it._localId]._point_out[_connect]._refLocalId = _t._localId;
                        _connect++;
                    }
        _connect = 0;
        foreach(T_POU_SFC_ITEM _t, _m_transition_item)
            for(int _i = 0; _i < _t._point_in.size(); _i++)
                if(!_t._point_in[_i]._connection.empty())
                    if(_it._localId == _t._point_in[_i]._connection[0]._refLocalId)
                    {
                        _m_transition_item[_t._localId]._in_connection = IT_SFC_SIM_CONVERGENCE_CONNECTION;
                        _m_simConvergence_item[_it._localId]._point_out[_connect]._refLocalId = _t._localId;
                        _connect++;
                    }
    }

    foreach(T_POU_SFC_ITEM _it, _m_transition_item)
    {
        _connect = 0;
        foreach(T_POU_SFC_ITEM _t, _m_step_item)
            for(int _i = 0; _i < _t._point_in.size(); _i++)
                if(!_t._point_in[_i]._connection.empty())
                    if(_it._localId == _t._point_in[_i]._connection[0]._refLocalId)
                    {
                        _m_step_item[_t._localId]._in_connection = IT_SFC_TRANSITION_CONNECTION;
                        _m_transition_item[_it._localId]._point_out[_connect]._refLocalId = _t._localId;
                        _m_transition_item[_it._localId]._out_connection = IT_SFC_STEP_CONNECTION;
                        _connect++;
                    }
        _connect = 0;
        foreach(T_POU_SFC_ITEM _t, _m_selDivergence_item)
            for(int _i = 0; _i < _t._point_in.size(); _i++)
                if(!_t._point_in[_i]._connection.empty())
                    if(_it._localId == _t._point_in[_i]._connection[0]._refLocalId)
                    {
                        _m_transition_item[_it._localId]._point_out[_connect]._refLocalId = _t._localId;
                        _m_transition_item[_it._localId]._out_connection = IT_SFC_SEL_DIVERGENCE_CONNECTION;
                        _connect++;
                    }
        foreach(T_POU_SFC_ITEM _t, _m_selConvergence_item)
            for(int _i = 0; _i < _t._point_in.size(); _i++)
                if(!_t._point_in[_i]._connection.empty())
                    if(_it._localId == _t._point_in[_i]._connection[0]._refLocalId)
                    {
                        _m_transition_item[_it._localId]._point_out[_connect]._refLocalId = _t._localId;
                        _m_transition_item[_it._localId]._out_connection = IT_SFC_SEL_CONVERGENCE_CONNECTION;
                        _connect++;
                    }
        foreach(T_POU_SFC_ITEM _t, _m_simDivergence_item)
            for(int _i = 0; _i < _t._point_in.size(); _i++)
                if(!_t._point_in[_i]._connection.empty())
                    if(_it._localId == _t._point_in[_i]._connection[0]._refLocalId)
                    {
                        _m_transition_item[_it._localId]._point_out[_connect]._refLocalId = _t._localId;
                        _m_transition_item[_it._localId]._out_connection = IT_SFC_SIM_DIVERGENCE_CONNECTION;
                        _connect++;
                    }
        foreach(T_POU_SFC_ITEM _t, _m_simConvergence_item)
            for(int _i = 0; _i < _t._point_in.size(); _i++)
                if(!_t._point_in[_i]._connection.empty())
                    if(_it._localId == _t._point_in[_i]._connection[0]._refLocalId)
                    {
                        _m_transition_item[_it._localId]._point_out[_connect]._refLocalId = _t._localId;
                        _m_transition_item[_it._localId]._out_connection = IT_SFC_SIM_CONVERGENCE_CONNECTION;
                        _connect++;
                    }
    }

    foreach(T_POU_SFC_ITEM _it, _m_step_item)
    {
        _connect = 0;
        foreach(T_POU_SFC_ITEM _t, _m_transition_item)
            for(int _i = 0; _i < _t._point_in.size(); _i++)
                if(!_t._point_in[_i]._connection.empty())
                    if(_it._localId == _t._point_in[_i]._connection[0]._refLocalId)
                    {
                        _m_step_item[_it._localId]._point_out[_connect]._refLocalId = _t._localId;
                        _m_step_item[_it._localId]._out_connection = IT_SFC_TRANSITION_CONNECTION;
                        _connect++;
                    }
        _connect = 0;
        foreach(T_POU_SFC_ITEM _t, _m_selDivergence_item)
            for(int _i = 0; _i < _t._point_in.size(); _i++)
                if(!_t._point_in[_i]._connection.empty())
                    if(_it._localId == _t._point_in[_i]._connection[0]._refLocalId)
                    {
                        _m_step_item[_it._localId]._point_out[_connect]._refLocalId = _t._localId;
                        _m_step_item[_it._localId]._out_connection = IT_SFC_SEL_DIVERGENCE_CONNECTION;
                        _connect++;
                    }
        foreach(T_POU_SFC_ITEM _t, _m_selConvergence_item)
            for(int _i = 0; _i < _t._point_in.size(); _i++)
                if(!_t._point_in[_i]._connection.empty())
                    if(_it._localId == _t._point_in[_i]._connection[0]._refLocalId)
                    {
                        _m_step_item[_it._localId]._point_out[_connect]._refLocalId = _t._localId;
                        _m_step_item[_it._localId]._out_connection = IT_SFC_SEL_CONVERGENCE_CONNECTION;
                        _connect++;
                    }
        foreach(T_POU_SFC_ITEM _t, _m_simDivergence_item)
            for(int _i = 0; _i < _t._point_in.size(); _i++)
                if(!_t._point_in[_i]._connection.empty())
                    if(_it._localId == _t._point_in[_i]._connection[0]._refLocalId)
                    {
                        _m_step_item[_it._localId]._point_out[_connect]._refLocalId = _t._localId;
                        _m_step_item[_it._localId]._out_connection = IT_SFC_SIM_DIVERGENCE_CONNECTION;
                        _connect++;
                    }
        foreach(T_POU_SFC_ITEM _t, _m_simConvergence_item)
            for(int _i = 0; _i < _t._point_in.size(); _i++)
                if(!_t._point_in[_i]._connection.empty())
                    if(_it._localId == _t._point_in[_i]._connection[0]._refLocalId)
                    {
                        _m_step_item[_it._localId]._point_out[_connect]._refLocalId = _t._localId;
                        _m_step_item[_it._localId]._out_connection = IT_SFC_SIM_CONVERGENCE_CONNECTION;
                        _connect++;
                    }
    }
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
void TranslatorSFC::parseItem(T_POU_BODY_SFC *_sfc)
{
    quint32 _connect;

    _m_step_item.clear();
    _m_transition_item.clear();
    _m_jump_step_item.clear();
    _m_selDivergence_item.clear();
    _m_selConvergence_item.clear();
    _m_simDivergence_item.clear();
    _m_simConvergence_item.clear();
    _m_action.clear();

//    for(int _i = 0; _i < (int)pou_->_actions.size(); _i++) _m_action.push_back(pou_->_actions[_i]);

    for(int _i = 0; _i < (int)_sfc->_item.size(); _i++)
        if(_sfc->_item[_i]._initialStep == "true")
            _sfc->_item[_i]._is_chain_used = true;

    // for(int _i = 0; _i < (int)_sfc->_item.size(); _i++)
    //     if(checkIsChainUsed(pou_, _i)) _i = 0;

    for(int _i = 0; _i < (int)_sfc->_item.size(); _i++)
        if(_sfc->_item[_i]._is_chain_used)
            switch(_sfc->_item[_i]._type)
            {
            case IT_SFC_TRANSITION:{                _m_transition_item.insert(_sfc->_item[_i]._localId, _sfc->_item[_i]);       }break;
            case IT_SFC_SELECTION_DIVERGENCE:{      _m_selDivergence_item.insert(_sfc->_item[_i]._localId, _sfc->_item[_i]);    }break;
            case IT_SFC_SELECTION_CONVERGENCE:{     _m_selConvergence_item.insert(_sfc->_item[_i]._localId, _sfc->_item[_i]);   }break;
            case IT_SFC_SIMULTANEUS_DIVERGENCE:{    _m_simDivergence_item.insert(_sfc->_item[_i]._localId, _sfc->_item[_i]);    }break;
            case IT_SFC_SIMULTANEUS_CONVERGENCE:{   _m_simConvergence_item.insert(_sfc->_item[_i]._localId, _sfc->_item[_i]);   }break;
            case IT_SFC_STEP:{                      _m_step_item.insert(_sfc->_item[_i]._localId, _sfc->_item[_i]);             }break;
            case IT_SFC_ACTION_BLOCK:{              _m_action_block_item.insert(_sfc->_item[_i]._localId, _sfc->_item[_i]);     }break;
            case IT_SFC_JUMP_STEP:{                 _m_jump_step_item.insert(_sfc->_item[_i]._localId, _sfc->_item[_i]);        }break;
            case IT_SFC_NOT_DEFINED:
            case IT_SFC_COMMENT:
            case IT_SFC_TYPE_MAX:{}break;
            }

    foreach(T_POU_SFC_ITEM _it, _m_jump_step_item)
    {
        foreach(T_POU_SFC_ITEM _t, _m_step_item)
        if(_it._targetName == _t._name)
        {
            T_CONNECTION_POINT_IN _connection;
            _connection._connection[0]._refLocalId = _it._point_in[0]._connection[0]._refLocalId;
            if(itemIsTransition(_connection._connection[0]._refLocalId))       _m_step_item[_t._localId]._in_connection = IT_SFC_TRANSITION_CONNECTION;
            if(itemIsSelConvergence(_connection._connection[0]._refLocalId))   _m_step_item[_t._localId]._in_connection = IT_SFC_SEL_CONVERGENCE_CONNECTION;
            if(itemIsSelDivergence(_connection._connection[0]._refLocalId))    _m_step_item[_t._localId]._in_connection = IT_SFC_SEL_DIVERGENCE_CONNECTION;
            if(itemIsSimConvergence(_connection._connection[0]._refLocalId))   _m_step_item[_t._localId]._in_connection = IT_SFC_SIM_CONVERGENCE_CONNECTION;
            if(itemIsSimDivergence(_connection._connection[0]._refLocalId))    _m_step_item[_t._localId]._in_connection = IT_SFC_SIM_DIVERGENCE_CONNECTION;
            _m_step_item[_t._localId]._point_in.push_back(_connection);
            break;
        }
    }

    foreach(T_POU_SFC_ITEM _it, _m_jump_step_item)
    {
        foreach(T_POU_SFC_ITEM _t, _m_transition_item)
        if(_it._targetName == _t._name)
        {
            T_CONNECTION_POINT_IN _connection;
            _connection._connection[0]._refLocalId = _it._point_in[0]._connection[0]._refLocalId;
            if(itemIsStep(_connection._connection[0]._refLocalId))             _m_transition_item[_t._localId]._in_connection = IT_SFC_STEP_CONNECTION;
            if(itemIsSelConvergence(_connection._connection[0]._refLocalId))   _m_transition_item[_t._localId]._in_connection = IT_SFC_SEL_CONVERGENCE_CONNECTION;
            if(itemIsSelDivergence(_connection._connection[0]._refLocalId))    _m_transition_item[_t._localId]._in_connection = IT_SFC_SEL_DIVERGENCE_CONNECTION;
            if(itemIsSimConvergence(_connection._connection[0]._refLocalId))   _m_transition_item[_t._localId]._in_connection = IT_SFC_SIM_CONVERGENCE_CONNECTION;
            if(itemIsSimDivergence(_connection._connection[0]._refLocalId))    _m_transition_item[_t._localId]._in_connection = IT_SFC_SIM_DIVERGENCE_CONNECTION;
            _m_transition_item[_t._localId]._point_in.push_back(_connection);
            break;
        }
    }

    foreach(T_POU_SFC_ITEM _it, _m_selDivergence_item)
    {
        _connect = 0;
        foreach(T_POU_SFC_ITEM _t, _m_step_item)
            for(int _i = 0; _i < _t._point_in.size(); _i++)
                if(_it._localId == _t._point_in[_i]._connection[0]._refLocalId)
                {
                    _m_step_item[_t._localId]._in_connection = IT_SFC_SEL_DIVERGENCE_CONNECTION;
                    _m_selDivergence_item[_it._localId]._point_out[_connect]._refLocalId = _t._localId;
                    _connect++;
                }
        _connect = 0;
        foreach(T_POU_SFC_ITEM _t, _m_transition_item)
            for(int _i = 0; _i < _t._point_in.size(); _i++)
                if(_it._localId == _t._point_in[_i]._connection[0]._refLocalId)
                {
                    _m_transition_item[_t._localId]._in_connection = IT_SFC_SEL_DIVERGENCE_CONNECTION;
                    _m_selDivergence_item[_it._localId]._point_out[_connect]._refLocalId = _t._localId;
                    _connect++;
                }
    }

    foreach(T_POU_SFC_ITEM _it, _m_selConvergence_item)
    {
        _connect = 0;
        foreach(T_POU_SFC_ITEM _t, _m_step_item)
            for(int _i = 0; _i < _t._point_in.size(); _i++)
                if(_it._localId == _t._point_in[_i]._connection[0]._refLocalId)
                {
                    _m_step_item[_t._localId]._in_connection = IT_SFC_SEL_CONVERGENCE_CONNECTION;
                    _m_selConvergence_item[_it._localId]._point_out[_connect]._refLocalId = _t._localId;
                    _connect++;
                }
        _connect = 0;
        foreach(T_POU_SFC_ITEM _t, _m_transition_item)
            for(int _i = 0; _i < _t._point_in.size(); _i++)
                if(_it._localId == _t._point_in[_i]._connection[0]._refLocalId)
                {
                    _m_transition_item[_t._localId]._in_connection = IT_SFC_SEL_CONVERGENCE_CONNECTION;
                    _m_selConvergence_item[_it._localId]._point_out[_connect]._refLocalId = _t._localId;
                    _connect++;
                }
    }

    foreach(T_POU_SFC_ITEM _it, _m_simDivergence_item)
    {
        _connect = 0;
        foreach(T_POU_SFC_ITEM _t, _m_step_item)
            for(int _i = 0; _i < _t._point_in.size(); _i++)
                if(_it._localId == _t._point_in[_i]._connection[0]._refLocalId)
                {
                    _m_step_item[_t._localId]._in_connection = IT_SFC_SIM_DIVERGENCE_CONNECTION;
                    _m_simDivergence_item[_it._localId]._point_out[_connect]._refLocalId = _t._localId;
                    _connect++;
                }
        _connect = 0;
        foreach(T_POU_SFC_ITEM _t, _m_transition_item)
            for(int _i = 0; _i < _t._point_in.size(); _i++)
                if(_it._localId == _t._point_in[_i]._connection[0]._refLocalId)
                {
                    _m_transition_item[_t._localId]._in_connection = IT_SFC_SIM_DIVERGENCE_CONNECTION;
                    _m_simDivergence_item[_it._localId]._point_out[_connect]._refLocalId = _t._localId;
                    _connect++;
                }
    }

    foreach(T_POU_SFC_ITEM _it, _m_simConvergence_item)
    {
        _connect = 0;
        foreach(T_POU_SFC_ITEM _t, _m_step_item)
            for(int _i = 0; _i < _t._point_in.size(); _i++)
                if(_it._localId == _t._point_in[_i]._connection[0]._refLocalId)
                {
                    _m_step_item[_t._localId]._in_connection = IT_SFC_SIM_CONVERGENCE_CONNECTION;
                    _m_simConvergence_item[_it._localId]._point_out[_connect]._refLocalId = _t._localId;
                    _connect++;
                }
        _connect = 0;
        foreach(T_POU_SFC_ITEM _t, _m_transition_item)
            for(int _i = 0; _i < _t._point_in.size(); _i++)
                if(_it._localId == _t._point_in[_i]._connection[0]._refLocalId)
                {
                    _m_transition_item[_t._localId]._in_connection = IT_SFC_SIM_CONVERGENCE_CONNECTION;
                    _m_simConvergence_item[_it._localId]._point_out[_connect]._refLocalId = _t._localId;
                    _connect++;
                }
    }

    foreach(T_POU_SFC_ITEM _it, _m_transition_item)
    {
        _connect = 0;
        foreach(T_POU_SFC_ITEM _t, _m_step_item)
            for(int _i = 0; _i < _t._point_in.size(); _i++)
                if(_it._localId == _t._point_in[_i]._connection[0]._refLocalId)
                {
                    _m_step_item[_t._localId]._in_connection = IT_SFC_TRANSITION_CONNECTION;
                    _m_transition_item[_it._localId]._point_out[_connect]._refLocalId = _t._localId;
                    _m_transition_item[_it._localId]._out_connection = IT_SFC_STEP_CONNECTION;
                    _connect++;
                }
        _connect = 0;
        foreach(T_POU_SFC_ITEM _t, _m_selDivergence_item)
            for(int _i = 0; _i < _t._point_in.size(); _i++)
                if(_it._localId == _t._point_in[_i]._connection[0]._refLocalId)
                {
                    _m_transition_item[_it._localId]._point_out[_connect]._refLocalId = _t._localId;
                    _m_transition_item[_it._localId]._out_connection = IT_SFC_SEL_DIVERGENCE_CONNECTION;
                    _connect++;
                }
        foreach(T_POU_SFC_ITEM _t, _m_selConvergence_item)
            for(int _i = 0; _i < _t._point_in.size(); _i++)
                if(_it._localId == _t._point_in[_i]._connection[0]._refLocalId)
                {
                    _m_transition_item[_it._localId]._point_out[_connect]._refLocalId = _t._localId;
                    _m_transition_item[_it._localId]._out_connection = IT_SFC_SEL_CONVERGENCE_CONNECTION;
                    _connect++;
                }
        foreach(T_POU_SFC_ITEM _t, _m_simDivergence_item)
            for(int _i = 0; _i < _t._point_in.size(); _i++)
                if(_it._localId == _t._point_in[_i]._connection[0]._refLocalId)
                {
                    _m_transition_item[_it._localId]._point_out[_connect]._refLocalId = _t._localId;
                    _m_transition_item[_it._localId]._out_connection = IT_SFC_SIM_DIVERGENCE_CONNECTION;
                    _connect++;
                }
        foreach(T_POU_SFC_ITEM _t, _m_simConvergence_item)
            for(int _i = 0; _i < _t._point_in.size(); _i++)
                if(_it._localId == _t._point_in[_i]._connection[0]._refLocalId)
                {
                    _m_transition_item[_it._localId]._point_out[_connect]._refLocalId = _t._localId;
                    _m_transition_item[_it._localId]._out_connection = IT_SFC_SIM_CONVERGENCE_CONNECTION;
                    _connect++;
                }
    }

    foreach(T_POU_SFC_ITEM _it, _m_step_item)
    {
        _connect = 0;
        foreach(T_POU_SFC_ITEM _t, _m_transition_item)
            for(int _i = 0; _i < _t._point_in.size(); _i++)
                if(_it._localId == _t._point_in[_i]._connection[0]._refLocalId)
                {
                    _m_step_item[_it._localId]._point_out[_connect]._refLocalId = _t._localId;
                    _m_step_item[_it._localId]._out_connection = IT_SFC_TRANSITION_CONNECTION;
                    _connect++;
                }
        _connect = 0;
        foreach(T_POU_SFC_ITEM _t, _m_selDivergence_item)
            for(int _i = 0; _i < _t._point_in.size(); _i++)
                if(_it._localId == _t._point_in[_i]._connection[0]._refLocalId)
                {
                    _m_step_item[_it._localId]._point_out[_connect]._refLocalId = _t._localId;
                    _m_step_item[_it._localId]._out_connection = IT_SFC_SEL_DIVERGENCE_CONNECTION;
                    _connect++;
                }
        foreach(T_POU_SFC_ITEM _t, _m_selConvergence_item)
            for(int _i = 0; _i < _t._point_in.size(); _i++)
                if(_it._localId == _t._point_in[_i]._connection[0]._refLocalId)
                {
                    _m_step_item[_it._localId]._point_out[_connect]._refLocalId = _t._localId;
                    _m_step_item[_it._localId]._out_connection = IT_SFC_SEL_CONVERGENCE_CONNECTION;
                    _connect++;
                }
        foreach(T_POU_SFC_ITEM _t, _m_simDivergence_item)
            for(int _i = 0; _i < _t._point_in.size(); _i++)
                if(_it._localId == _t._point_in[_i]._connection[0]._refLocalId)
                {
                    _m_step_item[_it._localId]._point_out[_connect]._refLocalId = _t._localId;
                    _m_step_item[_it._localId]._out_connection = IT_SFC_SIM_DIVERGENCE_CONNECTION;
                    _connect++;
                }
        foreach(T_POU_SFC_ITEM _t, _m_simConvergence_item)
            for(int _i = 0; _i < _t._point_in.size(); _i++)
                if(_it._localId == _t._point_in[_i]._connection[0]._refLocalId)
                {
                    _m_step_item[_it._localId]._point_out[_connect]._refLocalId = _t._localId;
                    _m_step_item[_it._localId]._out_connection = IT_SFC_SIM_CONVERGENCE_CONNECTION;
                    _connect++;
                }
    }
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
bool TranslatorSFC::checkIsChainUsed(T_POU *pou_, quint64 _index_item)
{
    bool _result = false;

    if(_index_item == 42)
        _index_item = 42;
    if(pou_->_body._SFC._item[_index_item]._initialStep == "true") return false;
    if(pou_->_body._SFC._item[_index_item]._type == IT_SFC_COMMENT) return false;
    if(pou_->_body._SFC._item[_index_item]._is_chain_used) return false;

    if(pou_->_body._SFC._item[_index_item]._type == IT_SFC_JUMP_STEP)
    {
        for(int _j = 0; _j < (int)pou_->_body._SFC._item.size(); _j++)
            if((pou_->_body._SFC._item[_index_item]._point_in[0]._connection[0]._refLocalId == pou_->_body._SFC._item[_j]._localId) && (pou_->_body._SFC._item[_j]._is_chain_used))
            {
                pou_->_body._SFC._item[_index_item]._is_chain_used = true;
                _result = true;
                break;
            }

        if(pou_->_body._SFC._item[_index_item]._is_chain_used)
            for(int _j = 0; _j < (int)pou_->_body._SFC._item.size(); _j++)
                if((pou_->_body._SFC._item[_index_item]._targetName == pou_->_body._SFC._item[_j]._name) && (!pou_->_body._SFC._item[_j]._is_chain_used))
                {
                    pou_->_body._SFC._item[_j]._is_chain_used = true;
                    break;
                }
    }else{
        for(int _j = 0; _j < (int)pou_->_body._SFC._item.size(); _j++)
            if(!pou_->_body._SFC._item[_index_item]._point_in[0]._connection.empty())
                if((pou_->_body._SFC._item[_index_item]._point_in[0]._connection[0]._refLocalId == pou_->_body._SFC._item[_j]._localId) && (pou_->_body._SFC._item[_j]._is_chain_used))
                {
                    pou_->_body._SFC._item[_index_item]._is_chain_used = true;
                    _result = true;
                    break;
                }
    }
    return _result;
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
void TranslatorSFC::Transition_STcode(quint64 _index, QString &text_)
{
    QString _data;
    QString _from_ST_code;
    QString _to_ST_code;

    if(_m_transition_item[_index]._is_used) return;

    if(itemIsStep(_m_transition_item[_index]._point_in[0]._connection[0]._refLocalId))
    {
        _from_ST_code = _m_step_item[_m_transition_item[_index]._point_in[0]._connection[0]._refLocalId]._name;
    }else
    if(itemIsSelConvergence(_m_transition_item[_index]._point_in[0]._connection[0]._refLocalId))
    {
    }else
    if(itemIsSelDivergence(_m_transition_item[_index]._point_in[0]._connection[0]._refLocalId))
    {
        _from_ST_code = _m_step_item[_m_selDivergence_item[_m_transition_item[_index]._point_in[0]._connection[0]._refLocalId]._point_in[0]._connection[0]._refLocalId]._name;
    }else
    if(itemIsSimConvergence(_m_transition_item[_index]._point_in[0]._connection[0]._refLocalId))
    {
        if(_m_simConvergence_item[_m_transition_item[_index]._point_in[0]._connection[0]._refLocalId]._point_in.size() > 1) _from_ST_code = "(";
        for(int _i = 0; _i < _m_simConvergence_item[_m_transition_item[_index]._point_in[0]._connection[0]._refLocalId]._point_in.size(); _i++)
        {
            _from_ST_code += _m_step_item[_m_simConvergence_item[_m_transition_item[_index]._point_in[0]._connection[0]._refLocalId]._point_in[_i]._connection[0]._refLocalId]._name;
            if(_i < (_m_simConvergence_item[_m_transition_item[_index]._point_in[0]._connection[0]._refLocalId]._point_in.size() - 1)) _from_ST_code += ", ";
        }
        if(_m_simConvergence_item[_m_transition_item[_index]._point_in[0]._connection[0]._refLocalId]._point_in.size() > 1) _from_ST_code += ")";
    }else
    if(itemIsSimDivergence(_m_transition_item[_index]._point_in[0]._connection[0]._refLocalId))
    {

    }

    if(itemIsStep(_m_transition_item[_index]._point_out[0]._refLocalId))
    {
        _to_ST_code = _m_step_item[_m_transition_item[_index]._point_out[0]._refLocalId]._name;
    }else
    if(itemIsSelConvergence(_m_transition_item[_index]._point_out[0]._refLocalId))
    {
        _to_ST_code = _m_step_item[_m_selConvergence_item[_m_transition_item[_index]._point_out[0]._refLocalId]._point_out[0]._refLocalId]._name;
    }else
    if(itemIsSelDivergence(_m_transition_item[_index]._point_out[0]._refLocalId))
    {
    }else
    if(itemIsSimConvergence(_m_transition_item[_index]._point_out[0]._refLocalId))
    {
    }else
    if(itemIsSimDivergence(_m_transition_item[_index]._point_out[0]._refLocalId))
    {
        if(_m_simDivergence_item[_m_transition_item[_index]._point_out[0]._refLocalId]._point_out.size()) _to_ST_code = "(";
        for(int _i = 0; _i < _m_simDivergence_item[_m_transition_item[_index]._point_out[0]._refLocalId]._point_out.size(); _i++)
        {
            _to_ST_code += _m_step_item[_m_simDivergence_item[_m_transition_item[_index]._point_out[0]._refLocalId]._point_out[_i]._refLocalId]._name;
            if(_i < (_m_simDivergence_item[_m_transition_item[_index]._point_out[0]._refLocalId]._point_out.size() - 1)) _to_ST_code += ", ";
        }
        if(_m_simDivergence_item[_m_transition_item[_index]._point_out[0]._refLocalId]._point_out.size()) _to_ST_code += ")";
    }

    _data = QString("  TRANSITION FROM %1 TO %2\n    := %3;\n  END_TRANSITION\n\n")
                .arg(_from_ST_code, _to_ST_code, _m_transition_item[_index]._condition[0]._ST_code);

    if(itemIsStep(_m_transition_item[_index]._point_out[0]._refLocalId))
    {
        if(!_m_step_item[_m_transition_item[_index]._point_out[0]._refLocalId]._is_used)
        {
            Step_STcode(_m_step_item[_m_transition_item[_index]._point_out[0]._refLocalId], _data);
            _m_step_item[_m_transition_item[_index]._point_out[0]._refLocalId]._is_used = true;
        }
    }else
    if(itemIsSelConvergence(_m_transition_item[_index]._point_out[0]._refLocalId))
    {
        if(!_m_step_item[_m_selConvergence_item[_m_transition_item[_index]._point_out[0]._refLocalId]._point_out[0]._refLocalId]._is_used)
        {
            Step_STcode(_m_step_item[_m_selConvergence_item[_m_transition_item[_index]._point_out[0]._refLocalId]._point_out[0]._refLocalId], _data);
            _m_step_item[_m_selConvergence_item[_m_transition_item[_index]._point_out[0]._refLocalId]._point_out[0]._refLocalId]._is_used = true;
        }
    }else
    if(itemIsSelDivergence(_m_transition_item[_index]._point_out[0]._refLocalId))
    {
    }else
    if(itemIsSimConvergence(_m_transition_item[_index]._point_out[0]._refLocalId))
    {
    }else
    if(itemIsSimDivergence(_m_transition_item[_index]._point_out[0]._refLocalId))
    {
        for(int _i = 0; _i < _m_simDivergence_item[_m_transition_item[_index]._point_out[0]._refLocalId]._point_out.size(); _i++)
        {
            if(!_m_step_item[_m_simDivergence_item[_m_transition_item[_index]._point_out[0]._refLocalId]._point_out[_i]._refLocalId]._is_used)
            {
                Step_STcode(_m_step_item[_m_simDivergence_item[_m_transition_item[_index]._point_out[0]._refLocalId]._point_out[_i]._refLocalId], _data);
                _m_step_item[_m_simDivergence_item[_m_transition_item[_index]._point_out[0]._refLocalId]._point_out[_i]._refLocalId]._is_used = true;
            }
        }
    }

    _m_transition_item[_index]._is_used = true;
    text_ += _data;
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
void TranslatorSFC::Step_STcode(T_POU_SFC_ITEM _step, QString &text_, bool _is_initial /* = false*/)
{
    QString _data;
    quint32 _action_localId = 0;
    bool _result = false;

    if(_is_initial) _data = QString("  INITIAL_STEP %1:\n").arg(_step._name);
    else            _data = QString("  STEP %1:\n").arg(_step._name);

    foreach(T_POU_SFC_ITEM _it, _m_action_block_item)
        if(_it._point_in[0]._connection[0]._refLocalId == _step._localId)
        {
            _action_localId = _it._localId;
            _result = true;
            break;
        }

    if(_result)
    {
        for(int _i = 0; _i < (int)_m_action_block_item[_action_localId]._action.size(); _i++)
            if(_m_action_block_item[_action_localId]._action[_i]._action_type == AR_INLINE)
            {
                if(_m_action_block_item[_action_localId]._action[_i]._indicator == "")
                    _data += QString("    %1_INLINE%2(%3);\n")
                                 .arg(_step._name.toUpper())
                                 .arg(_m_SFC_inline_counter + _i)
                                 .arg(_m_action_block_item[_action_localId]._action[_i]._qualifier);
                else
                    _data += QString("    %1_INLINE%2(%3, %4);\n")
                                 .arg(_step._name.toUpper())
                                 .arg(_m_SFC_inline_counter + _i)
                                 .arg(_m_action_block_item[_action_localId]._action[_i]._qualifier,
                                      _m_action_block_item[_action_localId]._action[_i]._indicator);
            }else{
                if(_m_action_block_item[_action_localId]._action[_i]._indicator == "")
                    _data += QString("    %1(%2);\n")
                                 .arg(_m_action_block_item[_action_localId]._action[_i]._reference_name,
                                      _m_action_block_item[_action_localId]._action[_i]._qualifier);
                else
                    _data += QString("    %1(%2, %3);\n")
                                 .arg(_m_action_block_item[_action_localId]._action[_i]._reference_name,
                                      _m_action_block_item[_action_localId]._action[_i]._qualifier,
                                      _m_action_block_item[_action_localId]._action[_i]._indicator);
            }
    }
    _data += "  END_STEP\n\n";

    if(_result)
    {
        for(int _i = 0; _i < (int)_m_action_block_item[_action_localId]._action.size(); _i++)
            if(_m_action_block_item[_action_localId]._action[_i]._action_type == AR_INLINE)
            {
                _data += QString("  ACTION %1_INLINE%2:\n    %3\n  END_ACTION\n\n")
                                        .arg(_step._name.toUpper())
                                        .arg(_m_SFC_inline_counter + _i)
                                        .arg(_m_action_block_item[_action_localId]._action[_i]._ST_code);
            }else{
                for(int _j = 0; _j < _m_action.size(); _j++)
                    if(_m_action[_j]._name == _m_action_block_item[_action_localId]._action[_i]._reference_name)
                    {
                        if(!_m_action[_j]._is_used)
                        {
                            QString _action_text;
                            _m_action[_j]._is_used = true;
                            switch(_m_action[_j]._type)
                            {
                            case PBT_FBD:{      TranslatorFBD *_gen = new TranslatorFBD();  _gen->Code_STgenerator(_m_action[_j]._FBD, _action_text);   delete _gen;  }break;
                            case PBT_ST:{       TranslatorST *_gen = new TranslatorST();    _gen->Code_STgenerator(_m_action[_j]._ST, _action_text);    delete _gen;  }break;
                            case PBT_IL:{       TranslatorIL *_gen = new TranslatorIL();    _gen->Code_STgenerator(_m_action[_j]._IL, _action_text);    delete _gen;  }break;
                            case PBT_LD:{       TranslatorLD *_gen = new TranslatorLD();    _gen->Code_STgenerator(_m_action[_j]._LD, _action_text);    delete _gen;  }break;
                            case PBT_SFC:
                            case PBT_NOT_DEFINED:
                            case PBT_MAX:{}break;
                            }
                            _data += QString("  ACTION %1\n%2  END_ACTION\n\n")
                                            .arg(_m_action[_j]._name, _action_text);
                        }
                        break;
                    }
            }
        _m_SFC_inline_counter += _m_action_block_item[_action_localId]._action.size();
    }
    text_ += _data;
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
bool TranslatorSFC::itemIsTransition(quint32 _id)
{
    if(_m_transition_item.find(_id) != _m_transition_item.end())
        return true;
    return false;
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
bool TranslatorSFC::itemIsStep(quint32 _id)
{
    if(_m_step_item.find(_id) != _m_step_item.end())
        return true;
    return false;
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
bool TranslatorSFC::itemIsSelConvergence(quint32 _id)
{
    if(_m_selConvergence_item.find(_id) != _m_selConvergence_item.end())
        return true;
    return false;
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
bool TranslatorSFC::itemIsSelDivergence(quint32 _id)
{
    if(_m_selDivergence_item.find(_id) != _m_selDivergence_item.end())
        return true;
    return false;
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
bool TranslatorSFC::itemIsSimConvergence(quint32 _id)
{
    if(_m_simConvergence_item.find(_id) != _m_simConvergence_item.end())
        return true;
    return false;
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
bool TranslatorSFC::itemIsSimDivergence(quint32 _id)
{
    if(_m_simDivergence_item.find(_id) != _m_simDivergence_item.end())
        return true;
    return false;
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
