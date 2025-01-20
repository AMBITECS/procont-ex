//
// Created by artem on 12/27/24.
//

#ifndef PROCONT_CINSTANCES_H
#define PROCONT_CINSTANCES_H

#include "CConfiguration.h"

class CProject;

class CInstances
{
public:
    CInstances() = delete;
    explicit CInstances(CProject *parent);
    CInstances(const CInstances &);
    CInstances(CProject *parent, const QDomNode &node);
    ~CInstances();

    [[nodiscard]] QDomNode      dom_node() const;
    CProject    * parent();

    CConfiguration *  find_config_by_name(const QString &name);

    CConfiguration * add_configuration(CConfiguration *configuration);
    CConfiguration * add_configuration();
    CConfiguration * remove_configuration(CConfiguration * configuration);
    CConfiguration * remove_configuration(const uint16_t & index);
    CConfiguration * get_configuration(const uint16_t &index);
    std::vector<CConfiguration*> *  configurations();
    bool    is_empty() const;

private:
    CProject * m_parent;
    std::vector<CConfiguration*>    * m_configurations;
};


#endif //PROCONT_CINSTANCES_H
