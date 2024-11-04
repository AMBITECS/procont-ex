#include "ctreeobject.h"
#include <QApplication>
#include <QDrag>
#include <QMimeData>
#include <QList>


CTreeObject::CTreeObject(QWidget *parent) : QTreeWidget(parent)
{}

CTreeObject::~CTreeObject()
= default;

void CTreeObject::mousePressEvent(QMouseEvent *event)
{
    m_dragStart = event->pos();
    m_drag_item = this->itemAt(m_dragStart);

    if (!m_drag_item)
    {
        return;
    }

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

    if (m_drag_item == nullptr)
    {
        return;
    }


    m_drag = new QDrag( this );
    auto* mimeData = new QMimeData();
    //mimeData->setImageData( QImage(":/codesys/images/24x24/default_element.png") );
    mimeData->setProperty("palette", 1);
    mimeData->setProperty("element", m_drag_item->data(0, Qt::UserRole).toInt());
    m_drag->setMimeData( mimeData );
    m_drag->setPixmap( QPixmap(":/codesys/images/24x24/default_element.png") );

    Qt::DropAction result = m_drag->exec( Qt::MoveAction );
    //qDebug() << "Drop action result: " << result;
    if( result == Qt::MoveAction ) {
        //setPixmap( QPixmap() );
        //setText( "" );
    }
}

QDrag *CTreeObject::get_drag()
{
    return m_drag;
}

