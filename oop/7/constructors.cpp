#include "constructors.hpp"

#include <QPushButton>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QWidget>


void callButtonLabel(QGridLayout *layout, int row, const QString &bText, SetColumnBox* context, funcT1 &&func){
    QPushButton *button = new QPushButton(bText);
    QLabel *label = new QLabel();
    layout->addWidget(button, row, 0); 
    layout->addWidget(label, row, 1);
    (void)QObject::connect(button, &QPushButton::clicked,
        [label, context, func]{func(context, label);});  
}


void callButtonLine(QGridLayout *layout, int row, const QString &bText, SetColumnBox* context, funcT2 &&func){
    QPushButton *button = new QPushButton(bText);
    QLineEdit *line = new QLineEdit();
    line->setMaxLength(1);
    line->setMaximumWidth(70);
    layout->addWidget(button, row, 0); 
    layout->addWidget(line, row, 1);
    (void)QObject::connect(button, &QPushButton::clicked, 
        [line, context, func]{func(context, line);});
}


void callButtonLineLabel(QGridLayout *layout, int row, const QString &bText, SetColumnBox* context, funcT3 &&func){
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



CallButtonLabelBox::CallButtonLabelBox(const QString &bText, SetColumnBox* context, funcT1 &&func) : func1(func){
    layout = new QHBoxLayout();
    layout->setContentsMargins(0,0,0,0);
    button = new QPushButton(bText);
    label = new QLabel();
    layout->addWidget(button);
    layout->addWidget(label);
    (void)QObject::connect(button, &QPushButton::clicked,
        [label=label, context, func=func1]{func(context, label);});  
    this->setLayout(layout);
    this->setContentsMargins(0,0,0,0);
}

CallButtonLineBox::CallButtonLineBox(const QString& bText, SetColumnBox* context, funcT2&& func) : func2(func){
    layout = new QHBoxLayout();
    layout->setContentsMargins(0,0,0,0);
    button = new QPushButton(bText);
    line = new QLineEdit();
    // line->setMaxLength(1);
    layout->addWidget(button, 1);
    layout->addWidget(line, 1);
    (void)QObject::connect(button, &QPushButton::clicked, 
        [line=line, context, func=func2]{func(context, line);});
    this->setLayout(layout);
    this->setContentsMargins(0,0,0,0);
}

callButtonLineLabelBox::callButtonLineLabelBox(const QString & bText, SetColumnBox * context, funcT3 && func) : func3(func){
    layout = new QHBoxLayout();
    layout->setContentsMargins(0,0,0,0);
    button = new QPushButton(bText);
    line = new QLineEdit();
    line->setMaxLength(1);
    // line->setMaximumWidth(70);
    QLabel *label = new QLabel();

    layout->addWidget(button, 2);
    layout->addWidget(line, 1);
    layout->addWidget(label, 1);
    (void)QObject::connect(button, &QPushButton::clicked, 
        [line=line, label, context, func=func3]{
            func(context, line, label);
        });
    this->setLayout(layout);
}
