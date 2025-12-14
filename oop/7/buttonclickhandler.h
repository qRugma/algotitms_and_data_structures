#include <QObject>


class QLabel;
class QPushButton;
class Set;

class ButtonClickHandler : public QObject
{
    Q_OBJECT;

    public:

        ButtonClickHandler() = default;
        ButtonClickHandler(Set*, QLabel*, const int);

    public slots:

        void onButtonClicked(bool);

    private:

        QLabel *label_;
        Set* set_;
        int index_;
};

