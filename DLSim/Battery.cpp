#include "Battery.h"

#include <QGraphicsLineItem>
#include <QPainter>
#include <QPointF>

#include "LineTerminal.h"

Battery::Battery()
{
    auto positiveTerminal = std::make_unique<LineTerminal>(Terminal::Type::Input, this, Terminal::Polarity::Positive);
    positiveTerminal->setObjectName("pos terminal");
    positiveTerminal->setLine(QLineF(10, 0, 20, 0));
    addTerminal(std::move(positiveTerminal));

    auto negativeTerminal = std::make_unique<LineTerminal>(Terminal::Type::Output, this, Terminal::Polarity::Negative);
    negativeTerminal->setObjectName("neg terminal");
    negativeTerminal->setLine(QLineF(0, 50, 30, 50));
    addTerminal(std::move(negativeTerminal));
}

const Terminal* Battery::getPositiveTerminal() const
{
    for (const auto& terminal : m_terminals)
    {
        if (terminal->getPolarity() == Terminal::Polarity::Positive)
        {
            return terminal.get();
        }
    }

    return nullptr;
}

const Terminal* Battery::getNegativeTerminal() const
{
    for (const auto& terminal : m_terminals)
    {
        if (terminal->getPolarity() == Terminal::Polarity::Negative)
        {
            return terminal.get();
        }
    }

    return nullptr;
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
