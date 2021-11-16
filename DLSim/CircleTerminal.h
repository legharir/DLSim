#pragma once

#include "Terminal.h"

#include <QGraphicsEllipseItem>

class CircleTerminal : public Terminal, public QGraphicsEllipseItem
{
public:
    CircleTerminal(Terminal::Type type, ElectronicComponent* parent = nullptr, Polarity polarity = Polarity::None);

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
    QPainterPath shape() const override;
    QRectF boundingRect() const override;
};
