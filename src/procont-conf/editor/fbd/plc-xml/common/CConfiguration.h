//
// Created by artem on 12/27/24.
//

#ifndef PROCONT_CCONFIGURATION_H
#define PROCONT_CCONFIGURATION_H

#include "CResource.h"

class CInstances;

class CConfiguration
{
public:
    explicit CConfiguration(CInstances *parent);
    CConfiguration(CInstances *parent, const QDomNode &node);
    CConfiguration(const CConfiguration &);
    ~CConfiguration();

    [[nodiscard]] QDomNode    dom_node() const;
    [[nodiscard]] bool        is_empty() const;

    [[nodiscard]] QString     name() const;
    void        set_name(const QString & name);

    CInstances * parent();
    void         set_parent(CInstances *parent);

    std::vector<CResource*> * resources();

private:
    CInstances             * m_parent;
    std::string               m_name;
    std::vector<CResource*> * m_resources;
};


#endif //PROCONT_CCONFIGURATION_H
