#pragma once

#include <QGraphicsItem>
#include <QObject>

class ElectronicComponent;

class Terminal : public QObject, public QGraphicsItem
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

    Terminal(Type type, ElectronicComponent* parent = nullptr, Polarity polarity = Polarity::None);

    Type getType() const;
    Polarity getPolarity() const;

    ElectronicComponent* getComponent();
    const ElectronicComponent* getComponent() const;

    void setHighlighted(bool highlight);

    bool containsScenePoint(const QPointF& scenePoint) const;

    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;

signals:
    void mousePressed(const Terminal* terminal, const QPointF& point);
    void mouseMoved(const QPointF& point);
    void mouseReleased(Terminal* terminal, const QPointF& point);
    void moved(const Terminal& terminal, const QPointF& point);

protected:
    Type m_type;
    Polarity m_polarity;

    bool m_highlighted = false;

    std::string m_name;

    ElectronicComponent* m_component;
};
