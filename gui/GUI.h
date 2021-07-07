//
// Created by Alex on 7/7/2021.
//

#ifndef QT_GUI_H
#include "Observer.h"
#include <QWidget>
#include <QListWidget>
#include <QFormLayout>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QLabel>
#include <QTableView>
#include <QMainWindow>
#include <qstringlistmodel.h>
#include <QSortFilterProxyModel>
#include <QMessageBox>
#include "AbstractModel.h"
#include "BuildingRepository.h"
#include "EthnologistRepository.h"
#define QT_GUI_H


class GUI: public QWidget ,public Observer{
    Q_OBJECT
private:
    std::string ethnologist_name, ethnologist_thematicArea;
    Ethnologist& ethnologist;
    BuildingRepository& buildingRepository;
    QLineEdit* description, *location, *id;
    AbstractModel* table;
    QTableView* tableView;
    QSortFilterProxyModel* filterProxyModel;
    QPushButton* add, *updateLocation, *updateDescription;
public:
    explicit GUI(Ethnologist& _ethnologist, BuildingRepository& _buildingRepository, QWidget* parent = nullptr);
    ~GUI() override;
    void initGUI();
    void connectSignalAndSlots();
    void update() override;
    int getSelectedIndex();
    void pickRandomColor();
    void checkIfUpdatePossible();
public slots:
    void addButton_handler();
    void updateLocationButton_handler();
    void updateDescriptionButton_handler();
};


#endif //QT_GUI_H
