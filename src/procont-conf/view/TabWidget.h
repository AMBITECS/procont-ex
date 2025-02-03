#ifndef TABWIDGET_H
#define TABWIDGET_H

// ----------------------------------------------------------------------------
// *** TabBar ***

/*!
 * \brief The TabBar class
 */

#include <QTabBar>

class TabBar : public QTabBar
{
    Q_OBJECT
public:
    TabBar(const QHash<QString, QColor> &colors, QWidget *parent = nullptr);

    void setTabColor(int index_, const QColor &color_);
    void setTabAnimate(int index_, bool enable, QColor color_);

protected:
    void paintEvent(QPaintEvent */*event*/);
    void timerEvent(QTimerEvent */*event*/);

private:
    QHash<QString, QColor> _m_colors_style;
    QHash<int, QColor> _m_colors_animate;
    QHash<int, QColor> _n_colors_default;
    int _m_timer{-1};
};
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** TabWidget ***

/*!
 * \brief The TabWidget class
 */

#include <QTabWidget>

class TabWidget : public QTabWidget
{
    Q_OBJECT
public:
    TabWidget(QWidget *parent = nullptr);

    void setTabColor(int index, const QColor &color_);
    void setTabAnimate(int index, bool enable, QColor color_ = Qt::darkGray);
};
// ----------------------------------------------------------------------------

#endif // TABWIDGET_H
