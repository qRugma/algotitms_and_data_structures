#include "mainwindow.h"

#include "buttonclickhandler.h"
#include "set.hpp"
#include <utility>

#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>

template<typename methodT, typename valueT>
bool call(Set &set, methodT &&method, valueT value){
    return (set.*method)(value);
}


MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent){

    set = Set("asd");

    auto method = &Set::includes;

    std::cout << call(set, method, 'a') << std::endl;    


    setWindowTitle("Qt GUI Application Example");
    resize(960, 720);
    
    gridLayout = new QGridLayout();

    widget = new QWidget();
    widget->setLayout(gridLayout);

    setCentralWidget(widget);

    {
        QLabel *label = new QLabel(QString::fromStdString(this->set.output()));
        gridLayout->addWidget(label, 0, 1);
        buttonClickHandlers[0] = new ButtonClickHandler(&set, label, 0);
    }

    {
        QPushButton *button = new QPushButton("Print");
        gridLayout->addWidget(button, 0, 0); 
        (void)QObject::connect(button, &QPushButton::clicked, buttonClickHandlers[0], &ButtonClickHandler::onButtonClicked);  
    }

    
    // { // print
    //     QPushButton *button = new QPushButton("Print");
    //     gridLayout->addWidget(button, 9, 0); 
    //     QLabel *label = new QLabel(QString::fromStdString(this->set.output()));
    //     gridLayout->addWidget(label, 9, 1);
    //     (void)QObject::connect(button, &QPushButton::clicked, this, [this]{this->set+=this->appendValue;});  
    // }
    { // +=   
        QPushButton *button = new QPushButton(QString("Button ") + "+=");
        (void)QObject::connect(button, &QPushButton::clicked, this, [this]{this->set+=this->appendValue;});  
        gridLayout->addWidget(button, 10, 0); 
        QLineEdit *line = new QLineEdit();
        line->setMaxLength(1);
        line->setMaximumWidth(70);
        gridLayout->addWidget(line, 10, 1);
        (void)QObject::connect(line, &QLineEdit::textChanged, this, [this](QString str){this->appendValue = str[0].toLatin1();});  
    }
    { // -=    
        QPushButton *button = new QPushButton(QString("Button ") + "-=");
        (void)QObject::connect(button, &QPushButton::clicked, this, [this]{this->set-=this->popValue;});  
        gridLayout->addWidget(button, 11, 0); 
        QLineEdit *line = new QLineEdit();
        line->setMaxLength(1);
        line->setMaximumWidth(70);
        gridLayout->addWidget(line, 11, 1);
        (void)QObject::connect(line, &QLineEdit::textChanged, this, [this](QString str){this->popValue = str[0].toLatin1();});  
    }
    

}

MainWindow::~MainWindow()
{
    for (int i = 0; i < 10; i++)
    {
        delete buttonClickHandlers[i];
    }
};