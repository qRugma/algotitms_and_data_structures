#include "mainwindow.h"

#include "set.hpp"
#include "constructors.hpp"

#include <utility>

#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent){
    
    set = new Set("asd");
    set2 = new Set("pas");

    auto method =[this](QLabel *label){
            label->setText(QString::fromStdString(this->set->output()));
        };
    setWindowTitle("Qt GUI Application Example");
    resize(960, 720);
    
    gridLayout = new QGridLayout();
    
    widget = new QWidget();
    widget->setLayout(gridLayout);
    
    setCentralWidget(widget);
    
    callButtonLabel(
        gridLayout,
        0,
        QString("Print"),
        this,
        [](MainWindow* This, QLabel *label){
            label->setText(QString::fromStdString(This->set->output()));
        }
    );
    callButtonLabel(
        gridLayout,
        1,
        QString("Print~"),
        this,
        [](MainWindow* This, QLabel *label){
            label->setText(QString::fromStdString(This->set->operator~().output()));
        }
    );
    callButtonLineLabel(
        gridLayout,
        2,
        "Includes",
        this,
        [](MainWindow *This, QLineEdit *line, QLabel *label){
            QString text = line->text();
            if (text.size() == 1)
                label->setText(This->set->includes(text[0].toLatin1()) ? "true" : "false");
        }
    );
    callButtonLabel(
        gridLayout,
        3,
        QString("Max"),
        this,
        [](MainWindow* This, QLabel *label){
            label->setText(QChar::fromLatin1(This->set->max()));
        }
    );
    callButtonLabel(
        gridLayout,
        4,
        QString("Min"),
        this,
        [](MainWindow* This, QLabel *label){
            label->setText(QChar::fromLatin1(This->set->min()));
        }
    );

    callButtonLine(
        gridLayout,
        5,
        QString("+="),
        this,
        [](MainWindow* This, QLineEdit *line){
            QString text = line->text();
            if (text.size()==1)
                *(This->set)+=text[0].toLatin1();
        }
    );
    callButtonLine(
        gridLayout,
        6,
        QString("-="),
        this,
        [](MainWindow *This, QLineEdit *line){
            QString text = line->text();
            if (text.size()==1)
                *(This->set)-=text[0].toLatin1();
        }
    );
    callButtonLabel(
        gridLayout,
        7,
        QString("set/set2"),
        this,
        [](MainWindow *This, QLabel *label){
            label->setText(QString::fromStdString(
                (This->set->operator/(*This->set2)).output()
            ));
        }
    );

}

MainWindow::~MainWindow()
{
    delete set;
    delete set2;
};