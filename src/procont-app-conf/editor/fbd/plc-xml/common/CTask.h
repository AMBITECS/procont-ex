//
// Created by artem on 12/26/24.
//

#ifndef PROCONT_CTASK_H
#define PROCONT_CTASK_H

#include <QDomNode>

class CResource;


class CTask
{
public:
    CTask(CResource * parent);
    CTask(CResource *parent, const QDomNode &node);
    CTask(const CTask &);
    ~CTask();

    QDomNode    dom_node() const;
    bool        is_empty() const;
};


#endif //PROCONT_CTASK_H
