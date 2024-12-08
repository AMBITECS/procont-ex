#include "ctreeobject.h"
#include <QApplication>
#include <QDrag>
#include <QMimeData>
#include <QList>
#include <QIcon>


CTreeObject::CTreeObject(QWidget *parent) : QTreeWidget(parent)
{
    QStringList columnsName; columnsName << tr("Components");
    setHeaderLabels(columnsName);
}

CTreeObject::~CTreeObject()
= default;

void CTreeObject::mousePressEvent(QMouseEvent *event)
{
    m_dragStart = event->pos();
    m_drag_item = this->itemAt(m_dragStart);
}

void CTreeObject::mouseMoveEvent(QMouseEvent *event)
{
    if (!(event->buttons() & Qt::LeftButton))
    {
        return;
    }
    if ((event->pos() - m_dragStart).manhattanLength()
        < QApplication::startDragDistance())
    {
        return;
    }

    if (m_drag_item == nullptr || m_drag_item->childCount() > 0)
    {
        return;
    }


    m_drag = new QDrag( this );
    auto* mimeData = new QMimeData();
    mimeData->setProperty("source", "palette");
    mimeData->setProperty("element", m_drag_item->data(0, Qt::UserRole).toInt());
    m_drag->setMimeData( mimeData );
    QPixmap pix = m_drag_item->icon(0).pixmap(16,16);
    m_drag->setPixmap( pix );

    Qt::DropAction result = m_drag->exec( Qt::MoveAction );

    emit dragging_complete();

    if( result == Qt::MoveAction )
    {

    }
}

