#include "TabWidget.h"

#include <QStylePainter>
#include <QStyleOptionTab>

// ----------------------------------------------------------------------------
// *** TabBar ***

TabBar::TabBar(const QHash<QString, QColor> &colors, QWidget *parent) :
    QTabBar(parent)
{
    _m_colors_style = colors;
}

void TabBar::setTabColor(int index_, const QColor &color_)
{
    _m_colors_style.insert(tabText(index_), color_);
    repaint();
}

void TabBar::setTabAnimate(int index_, bool enable, QColor color_)
{
    if(true == enable && true == _m_colors_animate.contains(index_))
        return;

    if(false == enable && false == _m_colors_animate.contains(index_))
        return;

    if(enable)
    {
        _m_colors_animate.insert(index_, color_);

        if(_m_colors_style.contains(tabText(index_)))
            _n_colors_default.insert(index_, _m_colors_style.value(tabText(index_)));
        else
            _n_colors_default.insert(index_, palette().color(QPalette::Button));
    }
    else
    {
        _m_colors_animate.remove(index_);

        setTabColor(index_, _n_colors_default.value(index_));
        _n_colors_default.remove(index_);
    }

    if(true == _m_colors_animate.size() && -1 == _m_timer)
        _m_timer = startTimer(500);

    if(false == _m_colors_animate.size() && -1 != _m_timer)
    {
        killTimer(_m_timer);
        _m_timer = -1;
    }
}

void TabBar::paintEvent(QPaintEvent */*event*/){

    QStylePainter painter(this);
    QStyleOptionTab opt;

    for(int i = 0;i < count();i++)
    {
        initStyleOption(&opt, i);
        if(_m_colors_style.contains(opt.text)){
            opt.palette.setColor(QPalette::Button, _m_colors_style[opt.text]);
        }

        painter.drawControl(QStyle::CE_TabBarTabShape, opt);
        painter.drawControl(QStyle::CE_TabBarTabLabel, opt);
    }
}

void TabBar::timerEvent(QTimerEvent */*event*/)
{
    static auto counter{0};
    for(auto i : _m_colors_animate.keys())
    {
        if(counter % 2)
            setTabColor(i, _m_colors_animate.value(i));
        else
            setTabColor(i, _n_colors_default.value(i));
    }
    counter++;
}
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** TabWidget ***

TabWidget::TabWidget(QWidget *parent) :
    QTabWidget(parent)
{
    setTabBar(new TabBar({}));
}

void TabWidget::setTabColor(int index, const QColor &color_)
{
    auto _bar = reinterpret_cast<TabBar*>(tabBar());
    _bar->setTabColor(index, color_);
}

void TabWidget::setTabAnimate(int index, bool enable, QColor color_)
{
    auto _bar = reinterpret_cast<TabBar*>(tabBar());
    _bar->setTabAnimate(index, enable, color_);
}
// ----------------------------------------------------------------------------
