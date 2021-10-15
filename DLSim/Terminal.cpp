#include "Terminal.h"

#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QStyleOptionGraphicsItem>

#include <QDebug>

#include "ElectronicComponent.h"
#include "MathTools.h"

Terminal::Terminal(Type type, Polarity polarity, ElectronicComponent* parent)
    : QGraphicsLineItem(parent)
    , m_type(type)
    , m_polarity(polarity)
{
    QGraphicsLineItem::setAcceptHoverEvents(true);
    QGraphicsLineItem::setAcceptDrops(true);
}

void Terminal::setHighlighted(bool highlight)
{
    m_highlighted = highlight;
}

void Terminal::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    if (m_highlighted || option->state & QStyle::State_MouseOver)
    {
        painter->setPen(Qt::cyan);
    }
    painter->drawLine(line());
}

QPainterPath Terminal::shape() const
{
    QPainterPath path;
    QRectF rect(line().p1(), line().p2());
    path.addRect(rect.marginsAdded(QMarginsF(5, 5, 5, 5)));
    return path;
}

QRectF Terminal::boundingRect() const
{
    return QGraphicsLineItem::boundingRect();
}

void Terminal::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    const auto midpoint = MathTools::midpoint(line());
    emit mousePressed(QGraphicsLineItem::mapToScene(midpoint));
}

void Terminal::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    emit mouseMoved(event->scenePos());
}

void Terminal::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    emit mouseReleased(event->scenePos());
}

Terminal::Type Terminal::getType() const
{
    return m_type;
}
