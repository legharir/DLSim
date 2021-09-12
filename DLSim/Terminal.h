#pragma once

#include <QGraphicsLineItem>
#include <QObject>

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
    void mousePressed(const QPointF& point);
    void mouseMoved(const QPointF& point);
    void mouseReleased(const QPointF& point);

private:
    bool m_highlighted = false;
};
