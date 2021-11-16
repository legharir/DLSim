#include "CircleTerminal.h"

#include <QPainter>
#include <QStyleOptionGraphicsItem>

CircleTerminal::CircleTerminal(Terminal::Type type, ElectronicComponent* parent, Polarity polarity)
    : Terminal(type, parent, polarity)
{
    setRect(0, 0, 5, 5);
    QGraphicsItem::setPos(10, 10);
}

void CircleTerminal::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    if (m_highlighted || option->state & QStyle::State_MouseOver)
    {
        painter->setPen(Qt::cyan);
    }
    painter->drawEllipse(QGraphicsEllipseItem::rect());
}

QPainterPath CircleTerminal::shape() const
{
    QPainterPath path;
    path.addRect(QGraphicsEllipseItem::rect());
    return path;
}

QRectF CircleTerminal::boundingRect() const
{
    return QGraphicsEllipseItem::boundingRect();
}
