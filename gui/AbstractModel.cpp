//
// Created by Alex on 7/7/2021.
//

#include "AbstractModel.h"


AbstractModel::AbstractModel(BuildingRepository &_buildingRepository, QObject *parent):buildingRepository(_buildingRepository), QAbstractTableModel{parent} {;}

AbstractModel::~AbstractModel(){
    ;
}

int AbstractModel::rowCount(const QModelIndex &parent) const {
    return this->buildingRepository.getBuildings().size();
}

int AbstractModel::columnCount(const QModelIndex &parent) const {
    return 4;
}

QVariant AbstractModel::data(const QModelIndex &index, int role) const {
    int row = index.row();
    int column = index.column();
    if(role == Qt::FontRole){
        QFont qFont{QString::fromStdString(this->font_name), this->font_size};
        return qFont;
    }
    if(role == Qt::DisplayRole){
        Building currentBuilding = this->buildingRepository.getBuildings()[row];
        if(column < 0 || column > 3)
            throw std::exception();
        if(column == 0)
            return QString::fromStdString(currentBuilding.getID());
        if(column == 1)
            return QString::fromStdString(currentBuilding.getDescription());
        if(column == 2)
            return QString::fromStdString(currentBuilding.getThematicArea());
        if(column == 3){
            return QString::fromStdString(currentBuilding.getLocation());
        }
    }
    return QVariant();
}

QVariant AbstractModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if(role == Qt::FontRole){
        QFont qFont{QString::fromStdString(this->font_name), this->font_size};
        qFont.setBold(true);
        return qFont;
    }
    if(role == Qt::DisplayRole){
        if(orientation == Qt::Horizontal){
            if(section < 0 || section > 3)
                throw std::exception();
            if(section == 0)
                return QString{"ID"};
            if(section == 1)
                return QString{"Description"};
            if(section == 2)
                return QString{"Thematic Area"};
            if(section == 3)
                return QString{"Location"};
        }
    }
    return QVariant();
}

bool AbstractModel::setData(const QModelIndex &index, const QVariant &value, int role) {
    if(!index.isValid() || role != Qt::EditRole)
        return false;
    int row = index.row();
    int column = index.column();
    if(row == this->buildingRepository.getBuildings().size()){
        this->beginInsertRows(QModelIndex{}, row, row);
        if(column < 0 || column > 3)
            throw std::exception();
        if(column == 0)
            this->buildingRepository.getBuildings().emplace_back(value.toString().toStdString(), "", "", "");
        if(column == 1)
            this->buildingRepository.getBuildings().emplace_back("", value.toString().toStdString(), "", "");
        if(column == 2)
            this->buildingRepository.getBuildings().emplace_back("", "", value.toString().toStdString(), "");
        if(column == 3)
            this->buildingRepository.getBuildings().emplace_back("", "", "", value.toString().toStdString());
        this->endInsertRows();
        return true;
    }
    Building currentBuilding = this->buildingRepository.getBuildings()[row];
    if(column < 0 || column > 3)
        throw std::exception();
    if(column == 0)
        currentBuilding.setID(value.toString().toStdString());
    if(column == 1)
        currentBuilding.setDescription(value.toString().toStdString());
    if(column == 2)
        currentBuilding.setThematicArea(value.toString().toStdString());
    if(column == 3)
        currentBuilding.setLocation(value.toString().toStdString());
    this->buildingRepository.getBuildings()[row] = currentBuilding;
    emit dataChanged(index, index);
    return true;
}

Qt::ItemFlags AbstractModel::flags(const QModelIndex &index) const {
    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

void AbstractModel::updateInternalData() {
    endResetModel();
}