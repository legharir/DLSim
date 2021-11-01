#include "Terminal.h"

#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QStyleOptionGraphicsItem>

#include <QDebug>

#include "ElectronicComponent.h"
#include "MathTools.h"

Terminal::Terminal(Type type, Polarity polarity, ElectronicComponent* parent, const std::string& name)
    : QGraphicsLineItem(parent)
    , m_component(parent)
    , m_type(type)
    , m_polarity(polarity)
    , m_name(name)
{
    QGraphicsLineItem::setAcceptHoverEvents(true);
    QGraphicsLineItem::setAcceptDrops(true);
}

void Terminal::setHighlighted(bool highlight)
{
    m_highlighted = highlight;
}

bool Terminal::containsScenePoint(const QPointF& scenePoint) const
{
    return contains(mapFromScene(scenePoint));
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
    emit mousePressed(this, QGraphicsLineItem::mapToScene(midpoint));
}

void Terminal::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    emit mouseMoved(event->scenePos());
}

void Terminal::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    emit mouseReleased(this, event->scenePos());
}

Terminal::Type Terminal::getType() const
{
    return m_type;
}

Terminal::Polarity Terminal::getPolarity() const
{
    return m_polarity;
}

std::string Terminal::getName() const
{
    return m_name;
}

ElectronicComponent* Terminal::getComponent()
{
    return m_component;
}

const ElectronicComponent* Terminal::getComponent() const
{
    return m_component;
}
