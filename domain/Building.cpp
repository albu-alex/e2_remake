//
// Created by Alex on 7/6/2021.
//

#include "Building.h"


Building::Building(const std::string &_id, const std::string &_description, const std::string &_thematicArea,
                   const std::string &_location):id(_id),description(_description),thematicArea(_thematicArea),location(_location) {;}


std::string Building::getID() const {
    return this->id;
}

std::string Building::getDescription() const {
    return this->description;
}

std::string Building::getThematicArea() const {
    return this->thematicArea;
}

std::string Building::getLocation() const {
    return this->location;
}

void Building::setID(const std::string &newID) {
    this->id = newID;
}

void Building::setDescription(const std::string &newDescription) {
    this->description = newDescription;
}

void Building::setThematicArea(const std::string &newThematicArea) {
    this->thematicArea = newThematicArea;
}

void Building::setLocation(const std::string &newLocation) {
    this->location = newLocation;
}

bool Building::operator==(const Building &building) {
    return this->id == building.id;
}

bool Building::operator!=(const Building &building) {
    return this->id != building.id;
}

std::ostream& operator <<(std::ostream& output, const Building& building){
    std::string building_to_string = building.id + ";" + building.description + ";" + building.thematicArea + ";" + building.location;
    output << building_to_string;
    return output;
}

std::istream& operator >>(std::istream& input, Building& building){
    std::getline(input, building.id, ';');
    std::getline(input, building.description, ';');
    std::getline(input, building.thematicArea, ';');
    std::getline(input, building.location, '\n');
    return input;
}