//
// Created by Alex on 7/6/2021.
//

#ifndef QT_ETHNOLOGISTREPOSITORY_H
#include "Repository.h"
#include "Ethnologist.h"
#define QT_ETHNOLOGISTREPOSITORY_H


class EthnologistRepository:public Repository<Ethnologist>, public ObserverUpdate{
private:
    std::vector<Ethnologist> ethnologists;
    void saveToFile() override;
public:
    EthnologistRepository(){;}
    ~EthnologistRepository() override{;}
    void loadFromFile() override;
    bool add(const Ethnologist& newEthnologist) override;
    std::vector<Ethnologist> getEthnologists() const;
};


#endif //QT_ETHNOLOGISTREPOSITORY_H
