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
    setSelected = set2;
    setWindowTitle("Qt GUI Application Example");
    resize(960, 720);
    
    
    gridLayout = new QGridLayout();
    widget = new QWidget();
    widget->setLayout(gridLayout);
    
    setCentralWidget(widget);
    { //set column
        callButtonLabel(
            gridLayout,
            gridLayout->rowCount(),
            QString("Print"),
            this,
            [](MainWindow* This, QLabel *label){
                label->setText(QString::fromStdString(This->set->output()));
            }
        );
        callButtonLabel(
            gridLayout,
            gridLayout->rowCount(),
            QString("Print~"),
            this,
            [](MainWindow* This, QLabel *label){
                label->setText(QString::fromStdString(This->set->operator~().output()));
            }
        );
        
        callButtonLine(
            gridLayout,
            gridLayout->rowCount(),
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
            gridLayout->rowCount(),
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
            gridLayout->rowCount(),
            QString("set=setSelected"),
            this,
            [](MainWindow *This, QLabel *label){
                label->setText(QString::fromStdString(
                    (This->set->operator=(*This->setSelected)).output()
                ));
            }
        );
        callButtonLabel(
            gridLayout,
            gridLayout->rowCount(),
            QString("set/setSelected"),
            this,
            [](MainWindow *This, QLabel *label){
                label->setText(QString::fromStdString(
                    (This->set->operator/(*This->setSelected)).output()
                ));
            }
        );
        callButtonLabel(
            gridLayout,
            gridLayout->rowCount(),
            QString("set/=setSelected"),
            this,
            [](MainWindow *This, QLabel *label){
                label->setText(QString::fromStdString(
                    (This->set->operator/=(*This->setSelected)).output()
                ));
            }
        );
        callButtonLabel(
            gridLayout,
            gridLayout->rowCount(),
            QString("set&setSelected"),
            this,
            [](MainWindow *This, QLabel *label){
                label->setText(QString::fromStdString(
                    (This->set->operator&(*This->setSelected)).output()
                ));
            }
        );
        callButtonLabel(
            gridLayout,
            gridLayout->rowCount(),
            QString("set&=setSelected"),
            this,
            [](MainWindow *This, QLabel *label){
                label->setText(QString::fromStdString(
                    (This->set->operator&=(*This->setSelected)).output()
                ));
            }
        );
        callButtonLabel(
            gridLayout,
            gridLayout->rowCount(),
            QString("set|setSelected"),
            this,
            [](MainWindow *This, QLabel *label){
                label->setText(QString::fromStdString(
                    (This->set->operator|(*This->setSelected)).output()
                ));
            }
        );
        callButtonLabel(
            gridLayout,
            gridLayout->rowCount(),
            QString("set|=setSelected"),
            this,
            [](MainWindow *This, QLabel *label){
                label->setText(QString::fromStdString(
                    (This->set->operator|=(*This->setSelected)).output()
                ));
            }
        );
        callButtonLineLabel(
            gridLayout,
            gridLayout->rowCount(),
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
            gridLayout->rowCount(),
            QString("set==setSelected"),
            this,
            [](MainWindow *This, QLabel *label){
                label->setText(
                    (This->set->operator==(*This->setSelected)) ? "true" : "false"
                );
            }
        );
        callButtonLabel(
            gridLayout,
            gridLayout->rowCount(),
            QString("set!=setSelected"),
            this,
            [](MainWindow *This, QLabel *label){
                label->setText(
                    (This->set->operator!=(*This->setSelected)) ? "true" : "false"
                );
            }
        );
        callButtonLabel(
            gridLayout,
            gridLayout->rowCount(),
            QString("Max"),
            this,
            [](MainWindow* This, QLabel *label){
                label->setText(QChar::fromLatin1(This->set->max()));
            }
        );
        callButtonLabel(
            gridLayout,
            gridLayout->rowCount(),
            QString("Min"),
            this,
            [](MainWindow* This, QLabel *label){
                label->setText(QChar::fromLatin1(This->set->min()));
            }
        );
    }
}

MainWindow::~MainWindow()
{
    delete set;
    delete set2;
};