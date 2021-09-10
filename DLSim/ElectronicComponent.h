#pragma once

#include <optional>

#include <QGraphicsObject>

class Terminal;

class ElectronicComponent : public QGraphicsObject
{
    Q_OBJECT

public:
    ElectronicComponent();

    void setTerminalsHighlighted(bool highlight);

    // Returns an std::optional containing the terminal that intersects with the
    // given point (in scene coordinates).
    std::optional<const Terminal*> getTerminal(const QPointF& scenePoint);

signals:
    void beginWire(QPointF point);
    void updateWire(QPointF point);
    void endWire(QPointF point);

protected:
    void addTerminal(Terminal* terminal);

    std::vector<Terminal*> m_terminals;
};
