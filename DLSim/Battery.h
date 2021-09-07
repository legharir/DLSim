#pragma once

#include "ElectronicComponent.h"

class Battery : public ElectronicComponent
{
public:
    Battery();

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
    QRectF boundingRect() const override;
};

