#include "Battery.h"

#include <QPainter>
#include <QPointF>

#include "Terminal.h"

Battery::Battery()
{
    auto positiveTerminal = std::make_unique<Terminal>(Terminal::Type::Input, Terminal::Polarity::Positive, this);
    positiveTerminal->setLine(QLineF(10, 0, 20, 0));
    addTerminal(std::move(positiveTerminal));

    auto negativeTerminal = std::make_unique<Terminal>(Terminal::Type::Output, Terminal::Polarity::Negative, this);
    negativeTerminal->setLine(QLineF(0, 50, 30, 50));
    addTerminal(std::move(negativeTerminal));
}

void Battery::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    painter->drawRect(10, 0, 10, 5);
    painter->drawRect(0, 5, 30, 45);
}

QRectF Battery::boundingRect() const
{
    return QRectF(0, 0, 30, 50);
}
