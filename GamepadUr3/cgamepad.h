#ifndef CGAMEPAD_H
#define CGAMEPAD_H

#include <QGamepad>
//#include <UR3Intermediator.h>

#include <QDebug>

class cGamepad : public QGamepad
{
public:
    cGamepad();

signals:

private:
    QGamepad *m_gamepad;

};

#endif // CGAMEPAD_H
