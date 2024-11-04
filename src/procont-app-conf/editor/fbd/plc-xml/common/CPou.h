//
// Created by artem on 10/28/24.
//

#ifndef EDITORSD_CPOU_H
#define EDITORSD_CPOU_H

#include "../includes.h"
#include "../CInterface.h"
#include "CBody.h"
#include "../sfc/CActions.h"
#include "../CTransitions.h"

class CPou
{
public:
    CPou();
    CPou(const CPou & other);
    explicit CPou(const QDomNode & dom_node);
    ~CPou();

    QDomNode    dom_node() const;
    bool        is_empty() const;

    QString     name() const;
    void        set_name(const QString &name);
    QString     type() const;
    void        set_type(const QString & type);

    CInterface * interface();
    QList<CBody*>   * bodies();
    CActions        * actions();
    CTransitions    * transitions();
    CAddData        * add_data();
    CDocumentation  * documentation();

private:
    QString       m_name;
    QString       m_type;
    QString       m_global_id;
    CInterface  * m_interface;
    CActions    * m_actions;
    CTransitions* m_transitions;
    CAddData    * m_add_data;
    CDocumentation * m_doc;

    QList<CBody*>   * m_bodies;

};


#endif //EDITORSD_CPOU_H
