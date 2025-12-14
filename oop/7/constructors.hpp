class MainWindow;
class QLabel;
class QGridLayout;
class QString;
class QLineEdit;

using funcT1 = void(*)(MainWindow*, QLabel*);

void callButtonLabel(QGridLayout *layout, int row, const QString &bText, MainWindow* context, funcT1 &&func);

using funcT2 = void(*)(MainWindow*, QLineEdit*);

void callButtonLine(QGridLayout *layout, int row, const QString &bText, MainWindow* context, funcT2 &&func);

using funcT3 = void(*)(MainWindow*, QLineEdit*, QLabel*);

void callButtonLineLabel(QGridLayout *layout, int row, const QString &bText, MainWindow* context, funcT3 &&func);
