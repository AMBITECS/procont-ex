#include "TranslatorST.h"

TranslatorST::TranslatorST() {}

// *** POU
//
//-----------------------------------------------------------------------------------
void TranslatorST::Code_STgenerator(T_POU pou_, QString &text_)
{
    AllVar_STgenerator(&pou_, text_);

    for(int _i = 0; _i < pou_._body._ST._ST_code.size(); _i++)
        text_ += QString("  %1\n").arg(pou_._body._ST._ST_code.at(_i));

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
void TranslatorST::Code_STgenerator(T_POU_BODY_ST _st, QString &text_)
{
    for(int _i = 0; _i < _st._ST_code.size(); _i++)
        text_ += QString("  %1\n").arg(_st._ST_code.at(_i));
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
