//
// Created by Alex on 7/6/2021.
//

#ifndef QT_ETHNOLOGIST_H
#include <string>
#define QT_ETHNOLOGIST_H


class Ethnologist {
private:
    std::string name;
    std::string thematicArea;
public:
    Ethnologist(){;}
    ~Ethnologist(){;}
    Ethnologist(const std::string& _name, const std::string& _thematicArea);
    std::string getName() const;
    std::string getThematicArea() const;
    void setName(const std::string& newName);
    void setThematicArea(const std::string& newThematicArea);
    bool operator ==(const Ethnologist& ethnologist);
    bool operator !=(const Ethnologist& ethnologist);
    friend std::ostream& operator <<(std::ostream& output, const Ethnologist& ethnologist);
    friend std::istream& operator >>(std::istream& input, Ethnologist& ethnologist);
};


#endif //QT_ETHNOLOGIST_H
