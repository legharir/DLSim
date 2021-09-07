#include "Led.h"

#include "Terminal.h"

Led::Led()
{
    addTerminal(new Terminal(0, 0, 20, 0, this));
    addTerminal(new Terminal(20, 0, 20, 20, this));
    addTerminal(new Terminal(20, 20, 0, 20, this));
    addTerminal(new Terminal(0, 20, 0, 0, this));
}

void Led::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
}

QRectF Led::boundingRect() const
{
    return QRectF(0, 0, 20, 20);
}
