#include <QMainWindow>

#include <vector>

class Set;
class SetColumnBox;
class QGridLayout;
class QHBoxLayout;

class MainWindow : public QMainWindow
{
    Q_OBJECT;

    public:

        MainWindow(QWidget* = nullptr);
        ~MainWindow();
        SetColumnBox* createColumn();

    public slots:
        void columnDelete(SetColumnBox *);
        void newSelected(Set *);
    
    signals:
        void select(Set *);

    public:

        QWidget *widget;
        QGridLayout *gridLayout;
        QHBoxLayout *boxLayout;
        std::vector<Set*> sets;
        std::vector<SetColumnBox*> columns;
        // Set* sets[10];
        Set* setSelected;
};