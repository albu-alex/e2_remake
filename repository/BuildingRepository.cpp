//
// Created by Alex on 7/6/2021.
//

#include "BuildingRepository.h"

bool BuildingRepository::add(const Building &newBuilding) {
    auto found = std::find(this->buildings.begin(), this->buildings.end(), newBuilding);
    if(found == this->buildings.end()){
        this->buildings.push_back(newBuilding);
        this->saveToFile();
        this->notify();
        return true;
    }
    return false;
}

bool BuildingRepository::updateLocation(Building &building, const std::string &newLocation) {
    for(auto & _building:this->buildings)
        if(_building == building){
            _building.setLocation(newLocation);
            this->saveToFile();
            this->notify();
            return true;
        }
    return false;
}

bool BuildingRepository::updateDescription(Building &building, const std::string &newDescription) {
    for(auto & _building:this->buildings)
        if(_building == building){
            _building.setDescription(newDescription);
            this->saveToFile();
            this->notify();
            return true;
        }
    return false;
}

void BuildingRepository::saveToFile() {
    std::ofstream output(R"(D:\Cursuri\clion_projects\e2_remake\buildings.txt)");
    if(!output.is_open())
        throw std::runtime_error("File could not open correctly!");
    for(const auto &building: this->buildings){
        if(&building == &this->buildings.back())
            output << building;
        else
            output << building << std::endl;
    }
    output.close();
}

void BuildingRepository::loadFromFile() {
    std::ifstream input(R"(D:\Cursuri\clion_projects\e2_remake\buildings.txt)");
    if(!input.is_open())
        throw std::runtime_error("File could not open correctly!");
    Building newBuilding;
    while(!input.eof() && input >> newBuilding)
        this->add(newBuilding);
    input.close();
}

std::vector<Building> BuildingRepository::getBuildings() const {
    return this->buildings;
}