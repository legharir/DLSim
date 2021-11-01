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

    Terminal(
        Type type,
        Polarity polarity = Polarity::None,
        ElectronicComponent* parent = nullptr,
        const std::string& name = "unnamed");

    Type getType() const;
    Polarity getPolarity() const;

    std::string getName() const;

    ElectronicComponent* getComponent();
    const ElectronicComponent* getComponent() const;

    void setHighlighted(bool highlight);

    bool containsScenePoint(const QPointF& scenePoint) const;

    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;

    // QGraphicsLineItem overrides
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
    QPainterPath shape() const override;
    QRectF boundingRect() const override;

signals:
    void mousePressed(const Terminal* terminal, const QPointF& point);
    void mouseMoved(const QPointF& point);
    void mouseReleased(Terminal* terminal, const QPointF& point);
    void moved(const Terminal& terminal, const QPointF& point);

private:
    Type m_type;
    Polarity m_polarity;

    bool m_highlighted = false;

    std::string m_name;

    ElectronicComponent* m_component;
};
