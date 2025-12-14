#include "constructors.hpp"

#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>

void callButtonLabel(QGridLayout *layout, int row, const QString &bText, MainWindow* context, funcT1 &&func){
    QPushButton *button = new QPushButton(bText);
    QLabel *label = new QLabel();
    layout->addWidget(button, row, 0); 
    layout->addWidget(label, row, 1);
    (void)QObject::connect(button, &QPushButton::clicked,
        [label, context, func]{func(context, label);});  
}


void callButtonLine(QGridLayout *layout, int row, const QString &bText, MainWindow* context, funcT2 &&func){
    QPushButton *button = new QPushButton(bText);
    QLineEdit *line = new QLineEdit();
    line->setMaxLength(1);
    line->setMaximumWidth(70);
    layout->addWidget(button, row, 0); 
    layout->addWidget(line, row, 1);
    (void)QObject::connect(button, &QPushButton::clicked, 
        [line, context, func]{func(context, line);});
}


void callButtonLineLabel(QGridLayout *layout, int row, const QString &bText, MainWindow* context, funcT3 &&func){
    QGridLayout *innerGridLayout = new QGridLayout();
    QWidget *innerWidget = new QWidget();
    innerWidget->setLayout(innerGridLayout);

    QPushButton *button = new QPushButton(bText);
    QLineEdit *line = new QLineEdit();
    line->setMaxLength(1);
    line->setMaximumWidth(70);
    QLabel *label = new QLabel();

    layout->addWidget(button, row, 0); 
    layout->addWidget(innerWidget, row, 1);
    innerGridLayout->addWidget(line, 0, 0);
    innerGridLayout->addWidget(label, 0, 1);
    (void)QObject::connect(button, &QPushButton::clicked, 
        [line, label, context, func]{
            func(context, line, label);
        });  
}
