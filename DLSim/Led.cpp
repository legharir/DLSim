#include "Led.h"

#include <QPainter>

#include "Terminal.h"

Led::Led()
{
    auto terminal = std::make_unique<Terminal>(Terminal::Type::Input, Terminal::Polarity::None, this, "led");
    terminal->setLine(QLineF(0, 0, 20, 0));
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
