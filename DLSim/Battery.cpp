#include "Battery.h"

#include <QPainter>

#include "Terminal.h"

Battery::Battery()
{
	addTerminal(new Terminal(0, 0, 20, 0, this));
}

void Battery::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    painter->drawLine(0, 0, 0, 50);
	painter->drawLine(0, 50, 20, 50);
	painter->drawLine(20, 50, 20, 0);
}

QRectF Battery::boundingRect() const
{
    return QRectF(0, 0, 20, 50);
}
