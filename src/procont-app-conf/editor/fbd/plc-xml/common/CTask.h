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
    explicit CTask(CResource * parent);
    CTask(CResource *parent, const QDomNode &node);
    CTask(const CTask &);
    ~CTask();

    [[nodiscard]] QDomNode    dom_node() const;
    CResource   * parent();

    [[nodiscard]] uint32_t    interval_millisec() const;
    void        set_interval(const uint32_t &millisec);

    [[nodiscard]] uint16_t    priority() const;
    void    set_priority(const uint16_t &priority);

    [[nodiscard]] QString     name() const;
    void        set_name(const QString &name);

private:
    CResource       * m_parent;
    uint32_t          m_period{0};
    std::string       m_name{};
    uint16_t          m_priority{0};
};


#endif //PROCONT_CTASK_H
