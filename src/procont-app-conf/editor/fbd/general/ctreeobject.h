#ifndef CTREEOBJECT_H
#define CTREEOBJECT_H

#include <QTreeWidget>
#include <QMouseEvent>

class CTreeObject : public QTreeWidget
{
    Q_OBJECT
public:
    explicit CTreeObject(QWidget *parent = nullptr);
    ~CTreeObject() override;

    QDrag *     get_drag();

    void clear();

protected:
    void mousePressEvent( QMouseEvent* event ) override;
    void mouseMoveEvent( QMouseEvent* event ) override;

private:
    QPoint    m_dragStart;
    QDrag   * m_drag{nullptr};
    QTreeWidgetItem * m_drag_item{nullptr};

};

#endif // CTREEOBJECT_H
