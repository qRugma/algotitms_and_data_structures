#include <QMainWindow>

#include "set.hpp"

class ButtonClickHandler;

class QGridLayout;

class MainWindow : public QMainWindow
{
    Q_OBJECT;

    public:

        MainWindow(QWidget* = nullptr);
        ~MainWindow();

        void setAppendValue(char value){
            appendValue = value;
        }

    public:

        QWidget *widget;
        QGridLayout *gridLayout;
        ButtonClickHandler *buttonClickHandlers[10];
        Set set;
        char appendValue;
        char popValue;
};