//
// Created by artem on 10/20/24.
//

#ifndef EDITORSD_CIFACEVARS_H
#define EDITORSD_CIFACEVARS_H

#include "../includes.h"
#include "CVariable.h"

/**
 * @brief local variables, temporary variables, input variables, output variables, input/output variables, external
 *  variables, global variables and access path variables. They are defined with the same XML structure,
 *  with the same attributes. all types above are the same as CIfaceVars
 *  @details XML Format for IEC 61131-3 page 26
 */
class CIfaceVars
{
public:
    CIfaceVars();
    CIfaceVars(const CIfaceVars & other);
    explicit CIfaceVars(const QDomNode &dom_node);
    CIfaceVars(CIfaceVars && other) noexcept;
    virtual ~CIfaceVars();

    [[nodiscard]] QDomNode    dom_node() const;

    [[nodiscard]] QString     name() const;
    void        set_name(const QString &name);

    [[nodiscard]] bool        is_constant() const;
    void        set_constant(const bool &constant);

    [[nodiscard]] bool        is_retain() const;
    void        set_retain(const bool &retain);

    [[nodiscard]] bool        is_persistent() const;
    void        set_persistent( const bool & persistent );

    void        clean();
    std::vector<CVariable*> * variables();

    CAddData *  add_data();
    CDocumentation * documentation();

    [[nodiscard]] bool is_empty() const;

protected:
    QString     m_name;
    QString     m_var_type;
    bool        m_constant{false};
    bool        m_retain{false};
    bool        m_persistent{false};

    std::vector<CVariable*> * m_variables;
    CAddData            m_add_data;
    CDocumentation      m_document;
};

class CAccessVars : public CIfaceVars
{
public:
    CAccessVars();
    ~CAccessVars() override;
};

class CLocalVars : public CIfaceVars
{
public:
    CLocalVars();
    ~CLocalVars() override;
};

class CGlobalVars : public CIfaceVars
{
public:
    CGlobalVars();
    ~CGlobalVars() override;
};

class CExternalVars : public CIfaceVars
{
public:
    CExternalVars();
    ~CExternalVars() override;
};

class CTempVars : public CIfaceVars
{
public:
    CTempVars();
    ~CTempVars() override;
};

class CInVars : public CIfaceVars
{
public:
    CInVars();
    ~CInVars() override;
};

class COutVars : public CIfaceVars
{
public:
    COutVars();
    ~COutVars() override;
};

class CInOutVars : public CIfaceVars
{
public:
    CInOutVars();
    ~CInOutVars() override;
};

#endif //EDITORSD_CIFACEVARS_H
