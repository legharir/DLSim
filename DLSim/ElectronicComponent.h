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
    ElectronicComponent();

    void setTerminalsHighlighted(bool highlight);

    Terminal* getIntersectingTerminal(const QPointF& scenePoint) const;

    //void addConnection(const Connection& connection);

    const std::vector<std::unique_ptr<Terminal>>& getTerminals() const;

    // QGraphicsItem overrides.
    QVariant itemChange(GraphicsItemChange change, const QVariant& value);

signals:
    void beginWire(const Terminal* terminal, const QPointF& point);
    void updateWire(const QPointF& point);
    void endWire(const Terminal* terminal, const QPointF& point);

    void moved(ElectronicComponent& component, const QPointF& delta);

protected:
    void addTerminal(std::unique_ptr<Terminal> terminal);

    std::vector<std::unique_ptr<Terminal>> m_terminals;

private:
    //std::vector<Connection> m_connections;
};
