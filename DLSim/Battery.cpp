#include "Battery.h"

#include <QGraphicsItem>
#include <QGraphicsLineItem>
#include <QPainter>
#include <QPointF>

#include "LineTerminal.h"

Battery::Battery()
{
    auto* positiveTerminal = new LineTerminal(Terminal::Type::Input, this, Terminal::Polarity::Positive);
    positiveTerminal->setObjectName("pos terminal");
    positiveTerminal->setLine(QLineF(10, 0, 20, 0));
    addTerminal(positiveTerminal);

    auto* negativeTerminal = new LineTerminal(Terminal::Type::Output, this, Terminal::Polarity::Negative);
    negativeTerminal->setObjectName("neg terminal");
    negativeTerminal->setLine(QLineF(0, 50, 30, 50));
    addTerminal(negativeTerminal);
}

const Terminal* Battery::getPositiveTerminal() const
{
    for (const auto& terminal : m_terminals)
    {
        if (terminal->getPolarity() == Terminal::Polarity::Positive)
        {
            return terminal;
        }
    }

    throw std::runtime_error("No negative terminal exists");
}

const Terminal* Battery::getNegativeTerminal() const
{
    for (const auto& terminal : m_terminals)
    {
        if (terminal->getPolarity() == Terminal::Polarity::Negative)
        {
            return terminal;
        }
    }

    throw std::runtime_error("No negative terminal exists");
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
