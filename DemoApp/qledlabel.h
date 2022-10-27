#ifndef QLEDLABEL_H
#define QLEDLABEL_H

#include <QWidget>

enum State {
    StateOk,
    StateOkBlue,
    StateWarning,
    StateError
};

class QLedLabel : public QWidget
{
    Q_OBJECT
public:
    explicit QLedLabel(QWidget *parent = nullptr);

signals:
    void setLedState(State state);
};

#endif // QLEDLABEL_H
