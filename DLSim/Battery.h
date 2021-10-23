#pragma once

#include "ElectronicComponent.h"

class Battery : public ElectronicComponent
{
public:
    Battery();

    const Terminal* getPositiveTerminal() const;
    const Terminal* getNegativeTerminal() const;

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
    QRectF boundingRect() const override;
};
