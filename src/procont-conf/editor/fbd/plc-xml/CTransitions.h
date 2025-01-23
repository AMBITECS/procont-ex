//
// Created by artem on 10/20/24.
//

#ifndef EDITORSD_CTRANSITIONS_H
#define EDITORSD_CTRANSITIONS_H

#include "includes.h"

class CTransitions
{
public:
    CTransitions();
    explicit CTransitions(const QDomNode & dom_node);
    ~CTransitions();

    [[nodiscard]] bool        is_empty() const;
    [[nodiscard]] QDomNode    dom_node() const;

};


#endif //EDITORSD_CTRANSITIONS_H
