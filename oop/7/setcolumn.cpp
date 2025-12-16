#include "setcolumn.hpp"
#include "constructors.hpp"
#include "set.hpp"

#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLineEdit>

SetColumnBox::SetColumnBox(Set *set_, Set *setSelected_){
    set = set_;
    setSelected = setSelected_;

    layout = new QVBoxLayout();
    layout->setSpacing(0);

    QPushButton *buttondel = new QPushButton("Delete"); 
    layout->addWidget(buttondel);
    QObject::connect(
        buttondel,
        &QPushButton::clicked,
        [this](){
            emit(this->deleted(this));
        }
    );
    buttonSelect = new QPushButton("Select");

    QObject::connect(
        buttonSelect,
        &QPushButton::clicked,
        [this, set=set, buttonSelect=buttonSelect](bool){
            buttonSelect->setEnabled(false);
            emit(this->SelectedChange(set));
        }
    );

    layout->addWidget(buttonSelect);


    layout->addWidget(new CallButtonLabelBox(
        QString("Print"),
        this,
        [](SetColumnBox* This, QLabel *label){
            label->setText(QString::fromStdString(This->set->output()));
        }
    ));
    layout->addWidget(new CallButtonLabelBox(
        QString("Print~"),
        this,
        [](SetColumnBox* This, QLabel *label){
            label->setText(QString::fromStdString(This->set->operator~().output()));
        }
    ));
    layout->addWidget(new CallButtonLineBox(
        QString("+="),
        this,
        [](SetColumnBox* This, QLineEdit *line){
            QString text = line->text();
            for(auto Qcha : text)
                *(This->set)+=Qcha.toLatin1();
            }
    ));
    layout->addWidget(new CallButtonLineBox(
        QString("-="),
        this,
        [](SetColumnBox* This, QLineEdit *line){
            QString text = line->text();
            for(auto Qcha : text)
                *(This->set)-=Qcha.toLatin1();
        }
    ));
    layout->addWidget(new CallButtonLabelBox(
        QString("set=setSelected"),
        this,
        [](SetColumnBox *This, QLabel *label){
            label->setText(QString::fromStdString(
                (This->set->operator=(*This->setSelected)).output()
            ));
        }
    ));
    layout->addWidget(new CallButtonLabelBox(
        QString("set/setSelected"),
        this,
        [](SetColumnBox *This, QLabel *label){
            label->setText(QString::fromStdString(
                (This->set->operator/(*This->setSelected)).output()
            ));
        }
    ));
    layout->addWidget(new CallButtonLabelBox(
        QString("set/=setSelected"),
        this,
        [](SetColumnBox *This, QLabel *label){
            label->setText(QString::fromStdString(
                (This->set->operator/=(*This->setSelected)).output()
            ));
        }
    ));
    layout->addWidget(new CallButtonLabelBox(
        QString("set&setSelected"),
        this,
        [](SetColumnBox *This, QLabel *label){
            label->setText(QString::fromStdString(
                (This->set->operator&(*This->setSelected)).output()
            ));
        }
    ));
    layout->addWidget(new CallButtonLabelBox(
        QString("set&=setSelected"),
        this,
        [](SetColumnBox *This, QLabel *label){
            label->setText(QString::fromStdString(
                (This->set->operator&=(*This->setSelected)).output()
            ));
        }
    ));
    layout->addWidget(new CallButtonLabelBox(
        QString("set|setSelected"),
        this,
        [](SetColumnBox *This, QLabel *label){
            label->setText(QString::fromStdString(
                (This->set->operator|(*This->setSelected)).output()
            ));
        }
    ));
    layout->addWidget(new CallButtonLabelBox(
        QString("set|=setSelected"),
        this,
        [](SetColumnBox *This, QLabel *label){
            label->setText(QString::fromStdString(
                (This->set->operator|=(*This->setSelected)).output()
            ));
        }
    ));
    layout->addWidget(new callButtonLineLabelBox(
        "Includes",
        this,
        [](SetColumnBox *This, QLineEdit *line, QLabel *label){
            QString text = line->text();
            if (text.size() == 1)
                label->setText(This->set->includes(text[0].toLatin1()) ? "true" : "false");
        }
    ));
    layout->addWidget(new CallButtonLabelBox(
        QString("set==setSelected"),
        this,
        [](SetColumnBox *This, QLabel *label){
            label->setText(
                (This->set->operator==(*This->setSelected)) ? "true" : "false"
            );
        }
    ));
    layout->addWidget(new CallButtonLabelBox(
        QString("set!=setSelected"),
        this,
        [](SetColumnBox *This, QLabel *label){
            label->setText(
                (This->set->operator!=(*This->setSelected)) ? "true" : "false"
            );
        }
    ));
    layout->addWidget(new CallButtonLabelBox(
        QString("Max"),
        this,
        [](SetColumnBox* This, QLabel *label){
            label->setText(QChar::fromLatin1(This->set->max()));
        }
    ));
    layout->addWidget(new CallButtonLabelBox(
        QString("Min"),
        this,
        [](SetColumnBox* This, QLabel *label){
            label->setText(QChar::fromLatin1(This->set->min()));
        }
    ));

    this->setLayout(layout);
}


// slot
void SetColumnBox::newSelected(Set *newSetSelected){
    setSelected = newSetSelected;
    if (newSetSelected == set)
        return;
    buttonSelect->setEnabled(true);
}
