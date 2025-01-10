//
// Created by artem on 12/26/24.
//

#ifndef PROCONT_CRESOURCE_H
#define PROCONT_CRESOURCE_H

#include <QDomNode>
#include "CTask.h"
#include "CGlobalVars.h"

class CConfiguration;

class CResource
{
public:
    explicit CResource(CConfiguration *parent);
    CResource(CConfiguration * parent, const QDomNode &node);
    CResource(const CResource &);
    ~CResource();

    [[nodiscard]] QDomNode    dom_node() const;
    CConfiguration  * parent();

    [[nodiscard]] QString name() const;
    void    set_name(const QString &name);

    CTask       *   task();
    CGlobalVars *   global_vars();

private:
    std::string       m_name{};
    CTask           * m_task;
    CGlobalVars     * m_global_vars;
    CConfiguration  * m_parent;

};


#endif //PROCONT_CRESOURCE_H
