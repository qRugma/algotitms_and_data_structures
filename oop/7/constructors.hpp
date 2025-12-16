class SetColumnBox;
class QLabel;
class QGridLayout;
class QString;
class QLineEdit;

#include <QWidget>
class QHBoxLayout;
class QPushButton;



using funcT1 = void(*)(SetColumnBox*, QLabel*);

void callButtonLabel(QGridLayout *layout, int row, const QString &bText, SetColumnBox* context, funcT1 &&func);

using funcT2 = void(*)(SetColumnBox*, QLineEdit*);

void callButtonLine(QGridLayout *layout, int row, const QString &bText, SetColumnBox* context, funcT2 &&func);

using funcT3 = void(*)(SetColumnBox*, QLineEdit*, QLabel*);

void callButtonLineLabel(QGridLayout *layout, int row, const QString &bText, SetColumnBox* context, funcT3 &&func);



class CallButtonLabelBox : public QWidget{
    Q_OBJECT;

    public:

    CallButtonLabelBox(const QString &bText, SetColumnBox* context, funcT1 &&func);

    public:

    QPushButton *button;
    QHBoxLayout *layout;
    QLabel *label;
    funcT1 func1;

};


class CallButtonLineBox : public QWidget{
    Q_OBJECT;

    public:

    CallButtonLineBox(const QString &bText, SetColumnBox* context, funcT2 &&func);
    
    public:

    QPushButton *button;
    QHBoxLayout *layout;
    QLineEdit *line;
    funcT2 func2;

};


class callButtonLineLabelBox : public QWidget{
    Q_OBJECT;

    public:

    callButtonLineLabelBox(const QString &bText, SetColumnBox* context, funcT3 &&func);

    public:
    QHBoxLayout *layout;
    QPushButton *button;
    QLabel *label;
    QLineEdit *line;
    funcT3 func3;
};