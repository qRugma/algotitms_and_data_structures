#include "buttonclickhandler.h"
#include "set.hpp"

#include <iostream>
#include <QMessageBox>
#include <QLabel>
#include <QPushButton>

ButtonClickHandler::ButtonClickHandler(Set* set, QLabel* label, const int index) : set_(set), label_(label), index_(index) {}

void ButtonClickHandler::onButtonClicked(bool){
    // label_->setText(QString("Button ") + QString::number(index_) + QString(" was clicked!"));
    label_->setText(QString::fromStdString(set_->output()));
}
