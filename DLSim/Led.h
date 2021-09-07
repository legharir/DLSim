#pragma once

#include "ElectronicComponent.h"

class Led : public ElectronicComponent
{
public:
    Led();

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
    QRectF boundingRect() const override;
};

