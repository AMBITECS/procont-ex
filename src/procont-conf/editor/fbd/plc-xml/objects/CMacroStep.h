//
// Created by artem on 10/24/24.
//

#ifndef EDITORSD_CMACROSTEP_H
#define EDITORSD_CMACROSTEP_H

#include "../includes.h"
#include "../CPosition.h"
#include "../CConnectionPointIn.h"
#include "../CConnectionPointOut.h"
#include "../CDocumentation.h"
#include "../common/CBody.h"


/**
 * @brief XML Format for IEC 61131-3 page 42. It provides a graphical representation of several steps
 * and transitions into one element.
 */
class CMacroStep
{
public:
    CMacroStep();
    CMacroStep(const CMacroStep &other);
    CMacroStep(CMacroStep && other) noexcept;
    CMacroStep(const QDomNode & dom_node);
    ~CMacroStep();

    uint64_t        local_id() const;
    void            set_local_id(const uint64_t & local_id);

    float           height() const;
    void            set_height(const float & height);

    float           width() const;
    void            set_width(const float & width);

    QString         name() const;
    void            set_name(const QString &name);

    uint16_t        exec_order() const;
    void            set_exec_order(const uint16_t & exec_order);

    QString         global_id() const;
    void            set_global_id(const QString &glob_id);

    CPosition  *    position();
    CConnectionPointIn * connection_point_in();
    CConnectionPointOut* connection_point_out();
    CAddData           * add_data();
    CDocumentation     * documentation();
    CBody              * body();

private:
};


#endif //EDITORSD_CMACROSTEP_H
