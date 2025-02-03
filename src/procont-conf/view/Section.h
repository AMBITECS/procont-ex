#ifndef SECTION_H
#define SECTION_H

#include <QFrame>
#include <QGridLayout>
#include <QParallelAnimationGroup>
#include <QScrollArea>
#include <QToolButton>
#include <QWidget>

class Section : public QWidget {
    Q_OBJECT
private:
    bool _m_fixed{false};
    QGridLayout* mainLayout;
    QToolButton* toggleButton;
    QFrame* headerLine;
    QParallelAnimationGroup* toggleAnimation;
    QScrollArea* contentArea;
    int animationDuration;

public:
    explicit Section(const QString & title = "", const bool fixed = false, const int animationDuration = 100, QWidget* parent = 0);

    void setContentLayout(QLayout & contentLayout);

private slots:
    void slot_toggle_btn(bool);
};

#endif // SECTION_H
