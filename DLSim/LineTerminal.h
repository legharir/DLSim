#pragma once

#include "Terminal.h"

#include <QGraphicsLineItem>

class LineTerminal : public Terminal, public QGraphicsLineItem
{
public:
    LineTerminal(Terminal::Type type, ElectronicComponent* parent = nullptr, Polarity polarity = Polarity::None);

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
    QPainterPath shape() const override;
    QRectF boundingRect() const override;
};
