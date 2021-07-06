//
// Created by Alex on 7/6/2021.
//

#ifndef QT_BUILDING_H
#include <string>
#define QT_BUILDING_H


class Building {
private:
    std::string id;
    std::string description;
    std::string thematicArea;
    std::string location;
public:
    Building(){;}
    ~Building(){;}
    Building(const std::string& _id, const std::string& _description, const std::string& _thematicArea, const std::string& _location);
    std::string getID() const;
    std::string getDescription() const;
    std::string getThematicArea() const;
    std::string getLocation() const;
    void setID(const std::string& newID);
    void setDescription(const std::string& newDescription);
    void setThematicArea(const std::string& newThematicArea);
    void setLocation(const std::string& newLocation);
    bool operator ==(const Building& building);
    bool operator !=(const Building& building);
    friend std::ostream& operator <<(std::ostream& output, const Building& building);
    friend std::istream& operator >>(std::istream& input, Building& building);
};


#endif //QT_BUILDING_H
