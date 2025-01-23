//
// Created by artem on 1/9/25.
//

#include "CContact.h"

CContact::CContact()
= default;

CContact::CContact(CBody *parent) : CCoil(parent)
{}

CContact::CContact(const CContact &other) : CCoil(other)
{}

CContact::CContact(CBody *parent, const QDomNode &node) : CCoil(parent, node)
{}

CContact::~CContact()
= default;
