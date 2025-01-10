//
// Created by artem on 11/17/24.
//

#include "CInstEditor.h"
#include "editor/fbd/plc-xml/common/CVariablesAnalytics.h"
#include <QPalette>
#include <QKeyEvent>
#include <QTimer>
#include <regex>
#include "../../common/resources/colors.h"
#include "../graphics/CFbdObject.h"

CInstEditor::CInstEditor(CFilter *filter, QWidget *parent) : QLineEdit(parent)
{
    //m_existing = new std::vector<std::pair<QString, EDefinedDataTypes>>();
    m_filter = filter;
    m_object = nullptr;


    connect(this, &CInstEditor::textChanged,   this, &CInstEditor::text_changed);
    connect(this, &CInstEditor::returnPressed, this, &CInstEditor::editing_complete);
    connect(this, &CInstEditor::editingFinished, this, &CInstEditor::editing_complete);
    connect(this, &CInstEditor::focusOutEvent, this, &CInstEditor::focus_out);

    this->setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);

    m_type = EDefinedDataTypes::DDT_DERIVED;

    auto colors = new CDiagramColors();

    m_error_bkg        = colors->base_colors().err_color; //QColor(255, 25, 91);
    m_error_foreground = colors->base_colors().diag_text_def; //QColor(255, 255,255);
    m_norm_bkg         = this->palette().color(QPalette::ColorRole::Base);
    m_norm_foreground  = this->palette().color(QPalette::ColorRole::Text);

    delete colors;
}

CInstEditor::~CInstEditor()
= default;

void CInstEditor::text_changed(const QString &str)
{
    if (m_not_process)
    {
        return;
    }
    std::string  var_name = str.toStdString();

    check_is_correct(str);
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

    std::string  var_name = text().toStdString();

    auto res = m_filter->filter_string(var_name, ff_all_flags);

    res ? set_norm() : set_error();

    if (m_old_name != text().toStdString())
    {
        m_old_name == "???" ? emit insert_new() : emit rename();
        return;
    }
    emit escaped();
}

void CInstEditor::focus_out(QFocusEvent *event)
{
    editing_complete();
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

void CInstEditor::check_is_correct(const QString &str)
{
    std::string var_name = str.toStdString();
    auto res = m_filter->filter_string(var_name, ff_all_flags);

    res ? set_norm() : set_error();
}

void CInstEditor::set_diagram_object(CFbdObject *object)
{
    m_object = object;
    check_is_correct(m_object->instance_name());

    this->setText(m_object->instance_name());
    this->selectAll();
}

void CInstEditor::focusInEvent(QFocusEvent *event)
{
    QLineEdit::focusInEvent(event);
    QTimer::singleShot(0, this, &QLineEdit::selectAll);
}


