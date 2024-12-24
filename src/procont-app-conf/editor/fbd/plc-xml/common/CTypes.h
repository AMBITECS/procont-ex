//
// Created by artem on 12/16/24.
//

#ifndef PROCONT_CTYPES_H
#define PROCONT_CTYPES_H

#include "CUserType.h"
#include "editor/fbd/plc-xml/includes.h"
#include "CPou.h"
class CProject;
class CTypes
{
public:
    explicit CTypes(CProject *project);
    CTypes(const CTypes &);
    explicit CTypes(const QDomNode &node, CProject *parent);
    ~CTypes();

    CTypes & operator = (const CTypes &rhs);
    [[nodiscard]] QDomNode    dom_node() const;

    CProject    * parent();
    void          set_parent(CProject * parent);



    std::vector<CUserType*> * user_types();
    std::vector<CPou*>      * pous();


    CPou    * add_pou(const QString &pou_name);
    CPou    * add_pou(CPou *pou);   //!< returns pou pointer if pou_name is unical
    CPou    * add_pou(const QDomNode &pou_node); //!< pou name has to be unical
    CPou    * find_pou_by_name(const QString &pou_name); //!< returns pou pointer if pou_name is unical
    CPou    * remove_pou(CPou *pou);   //!< don't forget to delete


    CUserType   * add_user_type(const EUserTypes &user_type);
    CUserType   * add_user_type(const QDomNode &node);
    CUserType   * find_user_type_by_name(const QString &name);
    CUserType   * remove_user_type(CUserType * user_type); //!< don't forget to delete

    CVariable   * find_iface_variable(const QString &name);

    bool    is_empty() const;

protected:

private:
    std::vector<CUserType*> * m_user_types;
    std::vector<CPou*>      * m_pous;
    CProject                * m_parent{nullptr};
};


#endif //PROCONT_CTYPES_H
