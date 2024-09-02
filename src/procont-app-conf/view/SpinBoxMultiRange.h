#ifndef CMULTIRANGESPINBOX_H
#define CMULTIRANGESPINBOX_H

#include <QDoubleSpinBox>

class CRange
{
public:
    CRange() = default;
    CRange(double minValue, double maxValue)
        : m_minValue(minValue), m_maxValue(maxValue)
    {}

    double minValue() const { return m_minValue; }
    double maxValue() const { return m_maxValue; }

private:
    double m_minValue = 0;
    double m_maxValue = 0;
};

class CMultiRangeSpinBox : public QDoubleSpinBox
{
    Q_OBJECT
public:
    CMultiRangeSpinBox(QWidget *parent = nullptr);

    virtual void stepBy(int steps) override;

    virtual QValidator::State validate(QString &input, int &pos) const override;

    void setValue(double val);

    void addRange(double min, double max);

protected:
    virtual QAbstractSpinBox::StepEnabled stepEnabled() const override;

protected slots:
    void slot_textChanged(const QString &text);

private:
    int findRangeIndex(double) const;
    int findNextUpRangeIndex(double) const;
    int findNextDownRangeIndex(double) const;
    QString getTooltip() const;

private:
    QMap<int, CRange> m_ranges;
    QMap<double, int> m_indexes;
    double m_min = 0;
    double m_max = 0;
};

#endif // CMULTIRANGESPINBOX_H
