#pragma once

#include <QGraphicsLineItem>
#include <QObject>

class ElectronicComponent;

class Terminal : public QObject, public QGraphicsLineItem
{
    Q_OBJECT

public:
    enum class Type
    {
        Input,
        Output
    };

    enum class Polarity
    {
        None,
        Negative,
        Positive,
    };

    Terminal(Type type, Polarity polarity = Polarity::None, ElectronicComponent* parent = nullptr);

    void setHighlighted(bool highlight);

    // QGraphicsLineItem overrides
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
    QPainterPath shape() const override;
    QRectF boundingRect() const override;

    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;

    Type getType() const;

    const ElectronicComponent* component;

signals:
    void mousePressed(const QPointF& point);
    void mouseMoved(const QPointF& point);
    void mouseReleased(const QPointF& point);

private:
    Type m_type;
    Polarity m_polarity;

    bool m_highlighted = false;
};
