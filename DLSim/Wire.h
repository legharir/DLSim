#pragma once

#include <QGraphicsLineItem>

class Wire : public QGraphicsLineItem
{
public:
    using QGraphicsLineItem::QGraphicsLineItem;

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;

    void setHighlighted(bool highlight);

private:
    bool m_highlighted = false;
};
