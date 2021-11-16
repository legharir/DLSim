#include "Terminal.h"

#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QStyleOptionGraphicsItem>

#include "ElectronicComponent.h"
#include "MathTools.h"

Terminal::Terminal(Type type, ElectronicComponent* parent, Polarity polarity)
    : QGraphicsItem(parent)
    , m_component(parent)
    , m_type(type)
    , m_polarity(polarity)
{
    QGraphicsItem::setAcceptHoverEvents(true);
    QGraphicsItem::setAcceptDrops(true);
}

void Terminal::setHighlighted(bool highlight)
{
    m_highlighted = highlight;
}

bool Terminal::containsScenePoint(const QPointF& scenePoint) const
{
    return contains(mapFromScene(scenePoint));
}

void Terminal::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    emit mousePressed(this, QGraphicsItem::mapToScene(boundingRect().center()));
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

ElectronicComponent* Terminal::getComponent()
{
    return m_component;
}

const ElectronicComponent* Terminal::getComponent() const
{
    return m_component;
}
