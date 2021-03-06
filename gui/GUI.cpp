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
    this->ethnologist_name = this->ethnologist.getName();
    this->ethnologist_thematicArea = this->ethnologist.getThematicArea();
    this->description = new QLineEdit{};
    this->location = new QLineEdit{};
    this->id = new QLineEdit{};
    this->add = new QPushButton{"Add"};
    this->updateLocation = new QPushButton{"Update location"};
    this->updateDescription = new QPushButton{"Update description"};

    this->table = new AbstractModel{this->buildingRepository, this->ethnologist_thematicArea};
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

    QWidget::setWindowTitle(QString::fromStdString(this->ethnologist_name));
    QPalette qPalette = palette();
    qPalette.setColor(QPalette::Background, Qt::lightGray);
    QWidget::setAutoFillBackground(true);
    QWidget::setPalette(qPalette);
    this->pickRandomColor();
}

void GUI::pickRandomColor() {
    std::vector<Qt::GlobalColor> colors;
    colors.emplace_back(Qt::red);
    colors.emplace_back(Qt::darkRed);
    colors.emplace_back(Qt::yellow);
    colors.emplace_back(Qt::darkYellow);
    colors.emplace_back(Qt::magenta);
    colors.emplace_back(Qt::darkMagenta);
    colors.emplace_back(Qt::green);
    colors.emplace_back(Qt::darkGreen);
    int choice = rand()%8;
    QPalette qPalette = palette();
    qPalette.setColor(QPalette::Base, colors[choice]);
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
    QObject::connect(this->updateDescription, &QPushButton::clicked, this, &GUI::updateDescriptionButton_handler);
    QObject::connect(this->updateLocation, &QPushButton::clicked, this, &GUI::updateLocationButton_handler);
    QObject::connect(this->tableView, &QTableView::clicked, this, &GUI::checkIfUpdatePossible);
}

void GUI::checkIfUpdatePossible() {
    int index = this->getSelectedIndex();
    std::string thematicArea = this->filterProxyModel->index(index, 2).data().toString().toStdString();
    if(thematicArea != this->ethnologist_thematicArea){
        this->updateDescription->setEnabled(false);
        this->updateLocation->setEnabled(false);
        return;
    }
    this->updateDescription->setEnabled(true);
    this->updateLocation->setEnabled(true);
}

void GUI::updateDescriptionButton_handler() {
    std::string newDescription = this->description->text().toStdString();
    if(newDescription.empty()){
        QMessageBox::critical(this, "Error", "New description cannot be empty!");
        return;
    }
    int index = this->getSelectedIndex();
    std::string ID = this->filterProxyModel->index(index, 0).data().toString().toStdString();
    std::string _description = this->filterProxyModel->index(index, 1).data().toString().toStdString();
    std::string thematicArea = this->filterProxyModel->index(index, 2).data().toString().toStdString();
    std::string _location = this->filterProxyModel->index(index, 3).data().toString().toStdString();
    Building newBuilding{ID, _description, thematicArea, _location};
    this->buildingRepository.updateDescription(newBuilding, newDescription);
}

void GUI::updateLocationButton_handler() {
    std::string newLocation = this->location->text().toStdString();
    if(newLocation.empty()){
        QMessageBox::critical(this, "Error", "New location cannot be empty!");
        return;
    }
    int index = this->getSelectedIndex();
    std::string ID = this->filterProxyModel->index(index, 0).data().toString().toStdString();
    std::string _description = this->filterProxyModel->index(index, 1).data().toString().toStdString();
    std::string thematicArea = this->filterProxyModel->index(index, 2).data().toString().toStdString();
    std::string _location = this->filterProxyModel->index(index, 3).data().toString().toStdString();
    Building newBuilding{ID, _description, thematicArea, _location};
    this->buildingRepository.updateLocation(newBuilding, newLocation);
}