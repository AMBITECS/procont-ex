#include "SpinBoxMultiRange.h".h"

#include <QDebug>

#include <QLineEdit>

CMultiRangeSpinBox::CMultiRangeSpinBox(QWidget *parent) :
    QDoubleSpinBox(parent)
{
    connect(this, SIGNAL(textChanged(QString)), this, SLOT(slot_textChanged(QString)));

    lineEdit()->setValidator(new QDoubleValidator);
}

void CMultiRangeSpinBox::addRange(double min, double max)
{
    if(min <= max)
    {
        bool success = true;
        auto values = m_ranges.values();
        for(const auto &i : qAsConst(values))
        {
            if((min - i.maxValue())*(i.minValue()-max) > 0)
            {
                success = false;
                break;
            }
        }

        if(success)
        {
            m_indexes.insert(min, m_indexes.size());
            m_ranges.insert(m_indexes.value(min), CRange(min, max));

            if(m_min > min) m_min = min;
            if(m_max < max) m_max = max;
        }

        setToolTip(getTooltip());
    }
}

QString CMultiRangeSpinBox::getTooltip() const
{
    QString tooltip = QString();
    auto keys = m_indexes.keys();
    for(const auto &i : qAsConst(keys))
    {
        tooltip += QString("[%1, %2]").arg(m_ranges.value(m_indexes.value(i)).minValue()).arg(m_ranges.value(m_indexes.value(i)).maxValue());
        tooltip += "\n";
    }
    tooltip = tooltip.remove(tooltip.size()-1, 1);
    return tooltip;
}

int CMultiRangeSpinBox::findRangeIndex(double value) const
{
    auto index = -1;
    auto keys = m_ranges.keys();
    for(const auto &i : qAsConst(keys))
    {
        if(value >= m_ranges.value(i).minValue() && value <= m_ranges.value(i).maxValue())
        {
            index = i;
            break;
        }
    }

    return index;
}

int CMultiRangeSpinBox::findNextUpRangeIndex(double value) const
{
    auto index = -1;
    auto keys = m_indexes.keys();
    for(const auto &i : qAsConst(keys))
    {
        if(value < m_ranges.value(m_indexes.value(i)).minValue())
        {
            index = m_indexes.value(i);
            break;
        }
    }

    return index;
}

int CMultiRangeSpinBox::findNextDownRangeIndex(double value) const
{
    auto index = -1;
    auto keys = m_indexes.keys();
    std::reverse(std::begin(keys), std::end(keys));
    for(const auto &i : qAsConst(keys))
    {
        if(value > m_ranges.value(m_indexes.value(i)).maxValue())
        {
            index = m_indexes.value(i);
            break;
        }
    }

    return index;
}

void CMultiRangeSpinBox::stepBy(int steps)
{
    double next = value() + steps*singleStep();
    double current_index = findRangeIndex(next);

    if(current_index == -1)
    {
        if(steps > 0)
        {
            auto next_index = findNextUpRangeIndex(next);
            if(next_index != -1)
                setValue(m_ranges.value(next_index).minValue());
        }

        if(steps < 0)
        {
            auto next_index = findNextDownRangeIndex(next);
            if(next_index != -1)
                setValue(m_ranges.value(next_index).maxValue());
        }
    }
    else
    {
        setValue(next);
    }
}

QAbstractSpinBox::StepEnabled CMultiRangeSpinBox::stepEnabled() const
{
    int flag = QAbstractSpinBox::StepNone;

    if(value() < m_max)
        flag |= QAbstractSpinBox::StepUpEnabled;

    if(value() > m_min)
        flag |= QAbstractSpinBox::StepDownEnabled;

    return (QAbstractSpinBox::StepEnabledFlag)flag;
}

void CMultiRangeSpinBox::setValue(double val)
{
    if(findRangeIndex(val) != -1)
    {
        auto index = findRangeIndex(val);
        setRange(m_ranges.value(index).minValue(), m_ranges.value(index).maxValue());
    }

    QDoubleSpinBox::setValue(val);
}

QValidator::State CMultiRangeSpinBox::validate(QString &input, int &pos) const
{
    Q_UNUSED(pos);

    auto value = input.toDouble();

    if(findRangeIndex(value) == -1)
    {
        if(findNextUpRangeIndex(value) != -1 || findNextDownRangeIndex(value) != -1)
            return QValidator::Intermediate;

        return QValidator::Invalid;
    }
    else
    {
        return QValidator::Acceptable;
    }
}

void CMultiRangeSpinBox::slot_textChanged(const QString &text)
{
    auto value = text.toDouble();
    if(findRangeIndex(value) != -1)
        setValue(value);
}
