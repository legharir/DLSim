#include "DLSim.h"

DLSim::DLSim(QWidget *parent)
    : QMainWindow(parent)
    , m_scene(std::make_unique<SimulationScene>())
{
    ui.setupUi(this);
    ui.graphicsView->setScene(m_scene.get());
    ui.graphicsView->setDragMode(QGraphicsView::DragMode::RubberBandDrag);
}
