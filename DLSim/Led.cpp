#include "Led.h"

#include <QPainter>

#include "CircleTerminal.h"

Led::Led()
{
    auto* terminal = new CircleTerminal(Terminal::Type::Input, this);
    terminal->setObjectName("led");
    terminal->setRect(-6, 8, 5, 5);
    addTerminal(std::move(terminal));
}

void Led::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    painter->drawRect(0, 0, 20, 20);
}

QRectF Led::boundingRect() const
{
    return QRectF(0, 0, 20, 20);
}
