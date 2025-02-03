//
// Created by artem on 10/20/24.
//

#ifndef EDITORSD_CDATA_H
#define EDITORSD_CDATA_H

#include "includes.h"


/**
 * @refitem XML Formats for IEC 61131-3 Version 2.01 – Official Release page 22
 * @brief
 *  CData is a part of the CAddData like the data's list is the content of the addData
 * @attention коварный тип ANY. Обозначает любую сущность от "Variable" до "POU" возможно даже только для этой перемнной
 * придётся наследовать все эти типы от какго-нибудь базового. Пока реализован будет через QDomNode с соответствующим
 * геморроем. Пока эта переменная адекватно не реализована будет сложность с парсингом CodeSys, т.к. все POU там части
 * addData, т.е. являются переменными m_any, но к сожалению не только POU, но и другие составляющие. Надо будет думать.
 * В крайнем случае можно закостылить:
 * @code typedef std::variant&lt;CPou, CInterface, CBody,...> anyType;
 * // или ------------
 * enum EInstancesType { E_POU, E_Interface,...};
 *      void * any;
 *      EInstancesType  any_type;
 *
 */
class CData
{
public:
    CData();
    CData(const CData &);
    //CData(CData &&) noexcept;
    explicit CData(const QDomNode &node);
    ~CData();

    QDomNode     dom_node();

    [[nodiscard]] QString     name() const;
    void        set_name(const QString &name);

    [[nodiscard]] QString     handle_unknown() const;
    void        set_handle_unknown(const QString &handle_unknown);

    [[nodiscard]] QDomNode    any_node() const;
    void        set_any_node(const QDomNode &any_instance);

private:
    QString     m_name{};
    QString     m_handle_undef{};
    QDomNode    m_any{};
};


#endif //EDITORSD_CDATA_H
