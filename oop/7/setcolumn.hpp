#include <QWidget>

class Set;
class QVBoxLayout;
class QPushButton;

class SetColumnBox: public QWidget {
    Q_OBJECT;

    public:

    SetColumnBox(Set *set, Set *setSelected);

    public slots:
        void newSelected(Set *newSetSelected);
    
    signals:
        void SelectedChange(Set *newSetSelected);
        void deleted(SetColumnBox *);

    public:
    Set *set;
    Set *setSelected;
    QVBoxLayout *layout;
    QPushButton *buttonSelect;


};