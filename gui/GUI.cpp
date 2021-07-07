//
// Created by Alex on 7/7/2021.
//

#include "GUI.h"

GUI::GUI(Ethnologist &_ethnologist, BuildingRepository &_buildingRepository, QWidget *parent):ethnologist(_ethnologist),buildingRepository(_buildingRepository),QWidget{parent} {
    this->buildingRepository.loadFromFile();
    this->buildingRepository.addObserver(this);
    this->initGUI();
    this->connectSignalAndSlots();
    this->show();
}

void GUI::update() {
    this->table->updateInternalData();
}

GUI::~GUI(){
    this->buildingRepository.removeObserver(this);
}

void GUI::initGUI() {
    QVBoxLayout* main = new QVBoxLayout{this};
    this->description = new QLineEdit{};
    this->location = new QLineEdit{};
    this->id = new QLineEdit{};
    this->add = new QPushButton{"Add"};
    this->updateLocation = new QPushButton{"Update location"};
    this->updateDescription = new QPushButton{"Update description"};

    this->table = new AbstractModel{this->buildingRepository};
    this->tableView = new QTableView{};
    this->filterProxyModel = new QSortFilterProxyModel{};
    this->filterProxyModel->setSourceModel(this->table);
    this->tableView->setSortingEnabled(true);
    //how to filter by blue colors?
    this->tableView->setModel(this->filterProxyModel);

    main->addWidget(this->tableView);

    QGridLayout* buttons = new QGridLayout{};
    buttons->addWidget(this->add, 0, 0);
    buttons->addWidget(this->updateDescription, 1, 0);
    buttons->addWidget(this->updateLocation, 1, 1);
    main->addLayout(buttons);

    QFormLayout* updates = new QFormLayout{};
    updates->addRow("Description", this->description);
    updates->addRow("Location", this->location);
    updates->addRow("ID", this->id);
    main->addLayout(updates);

    this->ethnologist_name = this->ethnologist.getName();
    this->ethnologist_thematicArea = this->ethnologist.getThematicArea();
    QWidget::setWindowTitle(QString::fromStdString(this->ethnologist_name));
    QPalette qPalette = palette();
    qPalette.setColor(QPalette::Background, Qt::lightGray);
    QWidget::setAutoFillBackground(true);
    QWidget::setPalette(qPalette);
    qPalette.setColor(QPalette::Base, Qt::red);
    this->tableView->setAutoFillBackground(true);
    this->tableView->setPalette(qPalette);
}

int GUI::getSelectedIndex() {
    auto selectedIndexes = this->tableView->selectionModel()->selectedIndexes();
    if(selectedIndexes.isEmpty())
        return -1;
    int selectedRow = selectedIndexes.at(0).row();
    return selectedRow;
}

void GUI::addButton_handler() {
    std::string newID = this->id->text().toStdString();
    std::string newDescription = this->description->text().toStdString();
    std::string newLocation = this->location->text().toStdString();
    if(newDescription.empty() || newID.empty() || newLocation.empty()){
        QMessageBox::critical(this, "Error", "Building descriptions cannot be empty!");
        return;
    }
    Building newBuilding{newID, newDescription, this->ethnologist_thematicArea, newLocation};
    bool isAdded = this->buildingRepository.add(newBuilding);
    if(!isAdded){
        QMessageBox::critical(this, "Error", "Buildings ID cannot be duplicates!");
        return;
    }
}

void GUI::connectSignalAndSlots() {
    QObject::connect(this->add, &QPushButton::clicked, this, &GUI::addButton_handler);
}

void GUI::updateDescriptionButton_handler() {
    ;
}

void GUI::updateLocationButton_handler() {
    ;
}