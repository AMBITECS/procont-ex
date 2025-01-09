//
// Created by artem on 1/9/25.
//

#ifndef PROCONT_CCONTACT_H
#define PROCONT_CCONTACT_H

#include "CCoil.h"

class CContact : public CCoil
{
public:
    CContact();
    explicit CContact(CBody *parent);
    CContact(const CContact &);
    CContact(CBody *parent, const QDomNode & node);
    ~CContact() override;

protected:

private:

};


#endif //PROCONT_CCONTACT_H
