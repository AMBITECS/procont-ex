//
// Created by artem on 11/17/24.
//

#include "CInstEditor.h"
#include <QPalette>
#include <QKeyEvent>
#include <regex>

CInstEditor::CInstEditor(QWidget *parent) : QLineEdit(parent)
{
    m_existing = new std::vector<std::pair<QString, EDefinedDataTypes>>();

    m_norm_bkg         = this->palette().color(QPalette::ColorRole::Base);
    m_norm_foreground  = this->palette().color(QPalette::ColorRole::Text);
    m_error_bkg        = QColor(255, 25, 91);
    m_error_foreground = QColor(255, 255,255);

    connect(this, &CInstEditor::textChanged,   this, &CInstEditor::text_changed);
    connect(this, &CInstEditor::returnPressed, this, &CInstEditor::editing_complete);

    this->setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);

    m_type = EDefinedDataTypes::DDT_UNDEF;
}

CInstEditor::~CInstEditor()
{
    delete m_existing;
}

void CInstEditor::set_existing(std::vector<std::pair<QString, EDefinedDataTypes>> *existing,
                               const QString &c_name, const EDefinedDataTypes &type)
{
    m_existing->clear();
    m_type = type;

    m_rename = false;
    m_rename_required = false;
    on_exit = false;

    m_old_name = c_name.toStdString();

    /// if renaming current instance
    for (auto &var : *existing)
    {
        if (var.first == c_name && var.second == type)
        {
            m_rename = true;
            continue;
        }
        m_existing->push_back(var);
    }

    int found = find(c_name.toStdString());

    /// renaming because var with other type has the same name
    if (found > 0)
    {
        m_rename = true;
        m_rename_required = true;
    }

    this->setText(c_name);
}

void CInstEditor::text_changed(const QString &str)
{
    if (m_not_process)
    {
        return;
    }

    bool not_found = find(str.toStdString()) == 0;
    bool regex_ok = regex(str.toStdString());
    bool renaming = !m_rename_required || m_old_name != str.toStdString();

    not_found && regex_ok && renaming ? set_norm() : set_error();
}

bool CInstEditor::is_error() const
{
    return m_is_error;
}

void CInstEditor::set_norm()
{
    QPalette palette;
    palette.setColor(QPalette::ColorRole::Base, m_norm_bkg);
    palette.setColor(QPalette::ColorRole::Text, m_norm_foreground);
    this->setPalette(palette);

    this->setToolTip("Приемлемое наименование.");

    m_is_error = false;
}

void CInstEditor::editing_complete()
{
    on_exit = true;
    bool not_found = find(text().toStdString()) == 0;
    bool regex_ok = regex(text().toStdString());
    bool renaming = !m_rename_required || m_old_name != text().toStdString();

    not_found && regex_ok && renaming ? set_norm() : set_error();

    if (m_old_name != text().toStdString())
    {
        m_old_name == "???" ? emit insert_new() : emit rename();
        return;
    }
    emit escaped();
}

void CInstEditor::focusOutEvent(QFocusEvent *event)
{
    if (!on_exit)
    {
        emit escaped();
    }
}

void CInstEditor::set_error()
{
    QPalette palette;
    palette.setColor(QPalette::ColorRole::Base, m_error_bkg);
    palette.setColor(QPalette::ColorRole::Text, m_error_foreground);
    this->setPalette(palette);

    this->setToolTip("Такое наименование существует или неприемлемое.");

    m_is_error = true;
}

QColor CInstEditor::color() const
{
    return this->palette().color(QPalette::ColorRole::Base);
}

void CInstEditor::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
        case Qt::Key_Escape:
            on_exit = true;
            emit escaped();
            break;
        default:
            break;
    }

    QLineEdit::keyPressEvent(event);
}

bool CInstEditor::regex(const std::string &str)
{
    const char *reg = "[a-zA-Z][a-zA-Z_0-9]*";
    bool res =  std::regex_match(str, std::regex(reg));
    return res;
}

int CInstEditor::find(const std::string &name)
{
    int count = 0;
    for (auto &var : *m_existing)
    {
        if (var.first.toStdString() == name)
        {
            count++;
        }
    }

    return count;
}


