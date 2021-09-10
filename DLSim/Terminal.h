#pragma once

#include <QObject>
#include <QGraphicsLineItem>

class Terminal : public QObject, public QGraphicsLineItem
{
	Q_OBJECT

public:
    Terminal(qreal x1, qreal y1, qreal x2, qreal y2, QGraphicsItem* parent = nullptr);

    void setHighlighted(bool highlight);

    // QGraphicsLineItem overrides
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
	QPainterPath shape() const override;
    QRectF boundingRect() const override;

    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;

signals:
    void mousePressed(QPointF point);
    void mouseMoved(QPointF point);
    void mouseReleased(QPointF point);

private:
    bool m_highlighted = false;
};

