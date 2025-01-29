//
// Created by artem on 12/26/24.
//

#ifndef PROCONT_CGLOBALVARS_H
#define PROCONT_CGLOBALVARS_H

#include <QDomNode>
#include "../variables/CVariable.h"

class CResource;

class CGlobalVars
{
public:
    explicit CGlobalVars(CResource * parent);
    CGlobalVars(CResource *parent, const QDomNode &node);
    CGlobalVars(const CGlobalVars &);
    ~CGlobalVars();

    CResource   * parent();

    [[nodiscard]] QDomNode    dom_node() const;
    [[nodiscard]] bool        is_empty() const;

    CVariable*  add_variable(CVariable * global_var);
    CVariable*  remove_var(CVariable *variable);
    CVariable*  remove_var(const uint16_t &index);
    std::vector <CVariable*> * variables();

private:
    CResource               * m_parent;
    std::vector<CVariable*> * m_variables;
};


#endif //PROCONT_CGLOBALVARS_H
