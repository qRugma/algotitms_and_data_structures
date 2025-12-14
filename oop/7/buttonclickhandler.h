#include <QObject>


class QLabel;
class QPushButton;
class QString;
class Set;

class ButtonClickHandler : public QObject
{
    Q_OBJECT;

    public:

        ButtonClickHandler() = default;
        ButtonClickHandler(Set*, QLabel*, const int);

    public slots:

        void onButtonClicked(bool);

    signals:

        void clicked(QString);

    private:

        QLabel *label_;
        Set* set_;
        int index_;
};

