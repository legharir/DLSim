#pragma once

#include <memory>
#include <optional>
#include <vector>

#include <QGraphicsObject>

class Terminal;

class ElectronicComponent : public QGraphicsObject
{
    Q_OBJECT;

public:
    struct Connection
    {
        bool isSource;
        QGraphicsLineItem* wire;
    };

    ElectronicComponent();

    void setTerminalsHighlighted(bool highlight);

    Terminal* getIntersectingTerminal(const QPointF& scenePoint) const;

    const std::vector<Connection>& getConnections() const;
    void addConnection(const Connection& connection);

    const std::vector<std::unique_ptr<Terminal>>& getTerminals() const;

    // QGraphicsItem overrides.
    QVariant itemChange(GraphicsItemChange change, const QVariant& value);

signals:
    void beginWire(const Terminal* terminal, const QPointF& point);
    void updateWire(const QPointF& point);
    void endWire(Terminal* terminal, const QPointF& point);

    void moved(const ElectronicComponent* component, const QPointF& delta);

protected:
    void addTerminal(std::unique_ptr<Terminal> terminal);

    std::vector<std::unique_ptr<Terminal>> m_terminals;

private:
    std::vector<Connection> m_connections;
};
