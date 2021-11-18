#pragma once

#include "ElectronicComponent.h"

class Switch : public ElectronicComponent
{
public:
    Switch();

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
    QRectF boundingRect() const override;

    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event) override;

private:
    bool m_isClosed = true;
    bool m_moved = false;
};
