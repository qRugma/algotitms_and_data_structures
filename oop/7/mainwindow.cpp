#include "mainwindow.h"

#include "set.hpp"
// #include "constructors.hpp"
#include "setcolumn.hpp"

#include <utility>

#include <QGridLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent){
    
    sets.push_back(new Set(""));
    setSelected = sets.front();
    setWindowTitle("Qt GUI Application Example");
    resize(960, 720);
    
    boxLayout = new QHBoxLayout();
    QWidget *innerWidget = new QWidget();
    innerWidget->setLayout(boxLayout);

    gridLayout = new QGridLayout();
    widget = new QWidget();
    widget->setLayout(gridLayout);
    
    setCentralWidget(widget);

    QPushButton *create = new QPushButton("Create");

    gridLayout->addWidget(create);
    gridLayout->addWidget(innerWidget);
    QObject::connect(
        create,
        &QPushButton::clicked,
        this,
        MainWindow::createColumn
    );

    createColumn();
    createColumn();
}

MainWindow::~MainWindow(){
    for(auto set : sets)
        delete set;
};


SetColumnBox* MainWindow::createColumn(){
    sets.push_back(new Set(""));
    columns.push_back(new SetColumnBox(sets.back(), setSelected));
    QObject::connect(
        this,
        &MainWindow::select,
        columns.back(),
        SetColumnBox::newSelected
    );
    QObject::connect(
        columns.back(),
        &SetColumnBox::SelectedChange,
        this,
        MainWindow::newSelected
    );
    QObject::connect(
        columns.back(),
        &SetColumnBox::deleted,
        this,
        MainWindow::columnDelete
    );
    std::cout << columns.size() << std::endl;
    boxLayout->addWidget(columns.back());
    return columns.back();
}

void MainWindow::columnDelete(SetColumnBox *deleted){
    auto itS = sets.begin()++;
    for(auto it= columns.begin(); it != columns.end(); it++, itS++)
        if (*it == deleted){
            delete *it;
            columns.erase(it);
            if (*itS == setSelected)
                newSelected(sets.front());
            delete *itS;
            sets.erase(itS);
            return;
        }
}

void MainWindow::newSelected(Set * setSelect_){
    setSelected = setSelect_;
    emit(this->select(setSelected));
}