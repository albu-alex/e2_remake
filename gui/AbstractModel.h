//
// Created by Alex on 7/7/2021.
//

#ifndef QT_ABSTRACTMODEL_H
#include "BuildingRepository.h"
#include <QAbstractTableModel>
#include <QFont>
#define NULL_NAME "AEIOU"
#define QT_ABSTRACTMODEL_H


class AbstractModel:public QAbstractTableModel {
private:
    BuildingRepository& buildingRepository;
    const int font_size = 15;
    const std::string font_name = "Times New Roman";
public:
    explicit AbstractModel(BuildingRepository& _buildingRepository, QObject* parent= nullptr);
    ~AbstractModel() override;
    int rowCount(const QModelIndex &parent = QModelIndex{}) const override;
    int columnCount(const QModelIndex &parent = QModelIndex{}) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    void updateInternalData();
};


#endif //QT_ABSTRACTMODEL_H
