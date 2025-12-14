#include <QMainWindow>

// #include "set.hpp"

class Set;


class QGridLayout;

class MainWindow : public QMainWindow
{
    Q_OBJECT;

    public:

        MainWindow(QWidget* = nullptr);
        ~MainWindow();

    public:

        QWidget *widget;
        QGridLayout *gridLayout;
        Set* set;
        Set* set2;
        Set* setSelected;
};