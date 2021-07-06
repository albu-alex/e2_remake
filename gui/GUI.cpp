//
// Created by Alex on 7/7/2021.
//

#include "GUI.h"

GUI::GUI(Ethnologist &_ethnologist, BuildingRepository &_buildingRepository, QWidget *parent):ethnologist(_ethnologist),buildingRepository(_buildingRepository),QWidget{parent} {
    this->buildingRepository.loadFromFile();
    this->buildingRepository.addObserver(this);
    this->initGUI();
    this->connectSignalAndSlots();
    this->show();
}

void GUI::update() {
    this->table->updateInternalData();
}