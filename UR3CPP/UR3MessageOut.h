#ifndef UR3MESSAGEOUT_H
#define UR3MESSAGEOUT_H
#pragma once
#include <vector>


using namespace std;
/**
 * @brief The UR3MessageOut class
 *
 *
 */
class UR3MessageOut
{
public:

    vector<double> JointsPositions;
    double Acceleration;
    double Speed;
    double BlendRadius;
    double Time;//< czas w [s]

    UR3MessageOut();
    /**
     * @brief konstruktor dla klasy
     * @param jointsPositionsList - orientacja w poszczególnych przegubach [rad]
     * @param acceleration
     * @param speed
     * @param blendRadius
     * @param time
     */
    UR3MessageOut(const vector<double> jointsPositionsList, double acceleration, double speed, double blendRadius, double time);
    ~UR3MessageOut();
};



#endif // UR3MESSAGEOUT_H
