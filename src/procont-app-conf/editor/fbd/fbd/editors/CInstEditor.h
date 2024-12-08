//
// Created by artem on 11/17/24.
//

#ifndef EDITORSD_CINSTEDITOR_H
#define EDITORSD_CINSTEDITOR_H

#include <QLineEdit>
#include "../../plc-xml/includes.h"

class CInstEditor : public QLineEdit
{
    Q_OBJECT
public:
    explicit CInstEditor(QWidget *parent = nullptr);
    ~CInstEditor() override;

    void  set_existing(std::vector<std::pair<QString, EDefinedDataTypes>> *existing, const QString &c_name, const EDefinedDataTypes &type);
    [[nodiscard]] bool  is_error() const;
    [[nodiscard]] QColor  color() const;

signals:
    void  escaped();
    void  rename();
    void  insert_new();

protected slots:
    void    text_changed(const QString &str);
    void    editing_complete();


protected:
    void    keyPressEvent(QKeyEvent *event) override;
    void    focusOutEvent(QFocusEvent* event) override;


private:
    std::vector<std::pair<QString, EDefinedDataTypes>> * m_existing;
    QColor  m_norm_bkg;
    QColor  m_norm_foreground;
    QColor  m_error_bkg;
    QColor  m_error_foreground;
    bool    m_is_error{false};
    bool    m_not_process{false};
    bool    m_rename{false};
    bool    m_rename_required{false};
    EDefinedDataTypes   m_type;
    std::string  m_old_name;

    bool  on_exit{false};

    void    set_norm();
    void    set_error();

    bool regex(const std::string &str);
    int  find(const std::string &name);
};


#endif //EDITORSD_CINSTEDITOR_H
