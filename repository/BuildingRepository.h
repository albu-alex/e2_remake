//
// Created by Alex on 7/6/2021.
//

#ifndef QT_BUILDINGREPOSITORY_H
#include "Repository.h"
#include "Building.h"
#define QT_BUILDINGREPOSITORY_H


class BuildingRepository: public Repository<Building>, public ObserverUpdate{
private:
    std::vector<Building> buildings;
    void saveToFile() override;
public:
    BuildingRepository(){;}
    ~BuildingRepository() override{;}
    void loadFromFile() override;
    bool add(const Building& newBuilding) override;
    bool updateDescription(Building& building, const std::string& newDescription);
    bool updateLocation(Building& building, const std::string& newLocation);
    std::vector<Building> getBuildings() const;
};


#endif //QT_BUILDINGREPOSITORY_H
