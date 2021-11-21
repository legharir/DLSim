#include "Switch.h"

#include <QPainter>

#include "CircleTerminal.h"

Switch::Switch()
{
    auto terminal = new CircleTerminal(Terminal::Type::Input, this);
    terminal->setObjectName("switch_1");
    terminal->setRect(-5, -5, 5, 5);
    addTerminal(terminal);

    terminal = new CircleTerminal(Terminal::Type::Input, this);
    terminal->setObjectName("switch_2");
    terminal->setRect(20, -5, 5, 5);
    addTerminal(terminal);
}

void Switch::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    if (m_isClosed)
    {
        painter->drawLine(0, 0, 20, 0);
    }
    else
    {
        painter->drawLine(0, 0, 20, 10);
    }
}

QRectF Switch::boundingRect() const
{
    return QRectF(0, 0, 20, 20);
}

void Switch::mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event)
{
    m_isClosed = !m_isClosed;
    ElectronicComponent::mouseDoubleClickEvent(event);
    update();
}
