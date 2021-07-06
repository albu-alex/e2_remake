//
// Created by Alex on 7/6/2021.
//

#include "EthnologistRepository.h"

bool EthnologistRepository::add(const Ethnologist &newEthnologist) {
    auto found = std::find(this->ethnologists.begin(), this->ethnologists.end(), newEthnologist);
    if(found == this->ethnologists.end()){
        this->ethnologists.push_back(newEthnologist);
        this->saveToFile();
        this->notify();
        return true;
    }
    return false;
}

void EthnologistRepository::saveToFile() {
    std::ofstream output(R"(D:\Cursuri\clion_projects\e2_remake\ethnologists.txt)");
    if(!output.is_open())
        throw std::runtime_error("File could not open correctly!");
    for(const auto &ethnologist: this->ethnologists){
        if(&ethnologist == &this->ethnologists.back())
            output << ethnologist;
        else
            output << ethnologist << std::endl;
    }
    output.close();
}

void EthnologistRepository::loadFromFile() {
    std::ifstream input(R"(D:\Cursuri\clion_projects\e2_remake\ethnologists.txt)");
    if(!input.is_open())
        throw std::runtime_error("File could not open correctly!");
    Ethnologist newEthnologist;
    while(!input.eof() && input >> newEthnologist)
        this->add(newEthnologist);
    input.close();
}

std::vector<Ethnologist> EthnologistRepository::getEthnologists() const {
    return this->ethnologists;
}