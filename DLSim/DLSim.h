#pragma once

#include "ui_DLSim.h"

#include <QMainWindow>

#include <memory>

#include "SimulationScene.h"


class DLSim : public QMainWindow
{
    Q_OBJECT

public:
    DLSim(QWidget *parent = Q_NULLPTR);

private:
    Ui::DLSimClass ui;
    std::unique_ptr<SimulationScene> m_scene;
};
