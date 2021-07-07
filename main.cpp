//
// Created by Alex on 7/7/2021.
//

#include "GUI.h"
#include <QtWidgets>

int main(int argc, char** argv){
    QApplication a{argc, argv};
    EthnologistRepository ethnologistRepository{};
    BuildingRepository buildingRepository{};
    ethnologistRepository.loadFromFile();
    std::vector<GUI*> gui;
    for(int i=0;i<ethnologistRepository.getEthnologists().size();i++)
        gui.push_back(new GUI{ethnologistRepository.getEthnologists()[i], buildingRepository});
    return a.exec();
}