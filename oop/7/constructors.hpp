#include <QWidget>

class SetColumnBox;
class QLabel;
class QString;
class QLineEdit;
class QHBoxLayout;
class QPushButton;

using funcT1 = void (*)(SetColumnBox*, QLabel*);

using funcT2 = void (*)(SetColumnBox*, QLineEdit*);

using funcT3 = void (*)(SetColumnBox*, QLineEdit*, QLabel*);

class CallButtonLabelBox : public QWidget {
    Q_OBJECT;

  public:
    CallButtonLabelBox(const QString& bText, SetColumnBox* context, funcT1&& func);

  public:
    QPushButton* button;
    QHBoxLayout* layout;
    QLabel* label;
    funcT1 func1;
};

class CallButtonLineBox : public QWidget {
    Q_OBJECT;

  public:
    CallButtonLineBox(const QString& bText, SetColumnBox* context, funcT2&& func);

  public:
    QPushButton* button;
    QHBoxLayout* layout;
    QLineEdit* line;
    funcT2 func2;
};

class callButtonLineLabelBox : public QWidget {
    Q_OBJECT;

  public:
    callButtonLineLabelBox(const QString& bText, SetColumnBox* context, funcT3&& func);

  public:
    QHBoxLayout* layout;
    QPushButton* button;
    QLabel* label;
    QLineEdit* line;
    funcT3 func3;
};