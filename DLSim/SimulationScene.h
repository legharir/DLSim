#pragma once

#include <QGraphicsScene>

class ElectronicComponent;

class SimulationScene : public QGraphicsScene
{
	Q_OBJECT

public:
	SimulationScene();

private:
	std::vector<ElectronicComponent*> m_electronicComponents;

	bool m_drawingWire = false;
	QGraphicsLineItem* m_curWire = nullptr;

	void addComponent(ElectronicComponent* component);


	void onBeginWire(QPointF point);
	void onUpdateWire(QPointF point);
	void onEndWire(QPointF point);
};

