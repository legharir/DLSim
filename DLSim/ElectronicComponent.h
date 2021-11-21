#pragma once

#include <unordered_set>

#include <QGraphicsObject>

class Terminal;

class ElectronicComponent : public QGraphicsObject
{
    Q_OBJECT;

public:
    ElectronicComponent();

    void setTerminalsHighlighted(bool highlight);

    Terminal* getIntersectingTerminal(const QPointF& scenePoint) const;

    std::unordered_set<const Terminal*> getTerminals() const;

    bool containsScenePoint(const QPointF& scenePoint) const;

    // QGraphicsItem overrides.
    QVariant itemChange(GraphicsItemChange change, const QVariant& value);

signals:
    void beginWire(const Terminal* terminal, const QPointF& point);
    void updateWire(const QPointF& point);
    void endWire(Terminal* terminal, const QPointF& point);

    void moved(const ElectronicComponent* component, const QPointF& delta);

protected:
    void addTerminal(Terminal* terminal);

    std::unordered_set<Terminal*> m_terminals;
};
