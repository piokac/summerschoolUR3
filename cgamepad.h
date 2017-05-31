#ifndef CGAMEPAD_H
#define CGAMEPAD_H

#include <QGamepad>

#include <QDebug>

class cGamepad : public QGamepad
{
public:
    cGamepad();

signals:
    void axisLeftXChanged(double value);
    void axisLeftYChanged(double value);
    void axisRightXChanged(double value);
    void axisRightYChanged(double value);

private:
    QGamepad *m_gamepad;

};

#endif // CGAMEPAD_H
