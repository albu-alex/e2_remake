//
// Created by Alex on 7/6/2021.
//

#include "Ethnologist.h"

Ethnologist::Ethnologist(const std::string &_name, const std::string &_thematicArea):name(_name),thematicArea(_thematicArea) {;}

std::string Ethnologist::getName() const {
    return this->name;
}

std::string Ethnologist::getThematicArea() const {
    return this->thematicArea;
}

void Ethnologist::setName(const std::string &newName) {
    this->name = newName;
}

void Ethnologist::setThematicArea(const std::string &newThematicArea) {
    this->thematicArea = newThematicArea;
}

bool Ethnologist::operator==(const Ethnologist &ethnologist) {
    return this->name == ethnologist.name;
}

bool Ethnologist::operator!=(const Ethnologist &ethnologist) {
    return this->name != ethnologist.name;
}

std::ostream& operator <<(std::ostream& output, const Ethnologist& ethnologist){
    std::string ethnologist_to_string = ethnologist.name + ";" + ethnologist.thematicArea;
    output << ethnologist_to_string;
    return output;
}

std::istream& operator >>(std::istream& input, Ethnologist& ethnologist){
    std::getline(input, ethnologist.name, ';');
    std::getline(input, ethnologist.thematicArea, '\n');
    return input;
}