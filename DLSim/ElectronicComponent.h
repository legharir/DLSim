#pragma once

#include <memory>
#include <optional>
#include <vector>

#include <QGraphicsObject>

#include "Terminal.h"

class ElectronicComponent : public QGraphicsObject
{
    Q_OBJECT;

public:
    struct Connection
    {
        bool isSource;
        QGraphicsLineItem& wire;
        const ElectronicComponent& connectedComponent;
    };

    ElectronicComponent();

    void setTerminalsHighlighted(bool highlight);

    const Terminal* getIntersectingTerminal(const QPointF& scenePoint) const;

    void addConnection(const Connection& connection);

    const std::vector<std::unique_ptr<Terminal>>& getTerminals() const;

    // QGraphicsItem overrides.
    QVariant itemChange(GraphicsItemChange change, const QVariant& value);

    std::vector<Connection> m_connections;

signals:
    void beginWire(const QPointF& point);
    void updateWire(const QPointF& point);
    void endWire(const QPointF& point, ElectronicComponent& fromComponent);

    void moved(ElectronicComponent& component, const QPointF& delta);

protected:
    void addTerminal(std::unique_ptr<Terminal> terminal);

    std::vector<std::unique_ptr<Terminal>> m_terminals;
};
