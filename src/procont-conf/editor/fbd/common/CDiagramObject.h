//
// Created by artem on 12/24/24.
//

#ifndef PROCONT_CDIAGRAMOBJECT_H
#define PROCONT_CDIAGRAMOBJECT_H

#include <QPointF>

class CLadder;

class CDiagramObject
{
public:
    explicit CDiagramObject(CLadder *parent);
    virtual ~CDiagramObject();

};


#endif //PROCONT_CDIAGRAMOBJECT_H
