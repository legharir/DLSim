#pragma once

#include <optional>
#include <vector>

#include <QGraphicsObject>

class Terminal;

class ElectronicComponent : public QGraphicsObject
{
    Q_OBJECT

public:
    struct Connection
    {
        bool isSource;
        QGraphicsLineItem& wire;
        const ElectronicComponent& connectedComponent;
    };

    ElectronicComponent();

    void setTerminalsHighlighted(bool highlight);

    // Returns an std::optional containing the terminal that intersects with the
    // given point (in scene coordinates).
    std::optional<Terminal*> getTerminal(const QPointF& scenePoint);

    void addConnection(const Connection& connection);

    // QGraphicsItem overrides.
    QVariant itemChange(GraphicsItemChange change, const QVariant& value);

    std::vector<Connection> m_connections;

signals:
    void beginWire(const QPointF& point);
    void updateWire(const QPointF& point);
    void endWire(const QPointF& point, ElectronicComponent& fromComponent);

    void moved(ElectronicComponent& component, const QPointF& delta);

protected:
    void addTerminal(Terminal* terminal);

    std::vector<Terminal*> m_terminals;
};
