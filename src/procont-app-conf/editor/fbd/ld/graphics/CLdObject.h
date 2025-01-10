//
// Created by artem on 1/10/25.
//

#ifndef PROCONT_CLDOBJECT_H
#define PROCONT_CLDOBJECT_H

#include "../../common/CDiagramObject.h"

class CLdObject : public CDiagramObject
{
public:
    CLdObject(CLadder *parent);
    ~CLdObject() override;

    void    set_parent(CLadder *parent, const QPointF &rel_pos);


protected:


private:

};


#endif //PROCONT_CLDOBJECT_H
