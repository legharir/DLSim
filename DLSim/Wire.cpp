#include "Wire.h"

#include <QPainter>

void Wire::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    if (m_highlighted)
    {
        painter->setPen(Qt::red);
    }

    painter->drawLine(line());
}

void Wire::setHighlighted(bool highlight)
{
    m_highlighted = highlight;
}
