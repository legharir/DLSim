#include "LineTerminal.h"

#include <QPainter>
#include <QPainterPath>
#include <QStyleOptionGraphicsItem>

LineTerminal::LineTerminal(Terminal::Type type, ElectronicComponent* parent, Polarity polarity)
    : Terminal(type, parent, polarity)
{
    setLine(20, 20, 20, 20);
    QGraphicsLineItem::setPos(20, 20);
}

void LineTerminal::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    if (m_highlighted || option->state & QStyle::State_MouseOver)
    {
        painter->setPen(Qt::cyan);
    }
    painter->drawLine(line());
}

QPainterPath LineTerminal::shape() const
{
    QPainterPath path;
    QRectF rect(line().p1(), line().p2());
    path.addRect(rect.marginsAdded(QMarginsF(5, 5, 5, 5)));
    return path;
}

QRectF LineTerminal::boundingRect() const
{
    return QGraphicsLineItem::boundingRect();
}
