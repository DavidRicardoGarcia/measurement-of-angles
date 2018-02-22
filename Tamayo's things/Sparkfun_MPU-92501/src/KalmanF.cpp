#include "KalmanF.h"

float KalmanF::getAngle(float newAngle, float  newRate, float  dt)
{       
        rate = newRate - bias;
        angle += dt * rate;

        P00 += dt * (dt*P11 - P01 - P10 + Q_angle);
        P01 -= dt * P11;
        P10 -= dt * P11;
        P11 += Q_bias * dt;

        S = P00 + R_measure ;
        K0 = P00 / S;
        K1 = P10 / S;

        y = newAngle - angle;
        
        angle += K0 * y;
        bias += K1 * y;

        P00_temp = P00;
        P01_temp = P01;

        P00 -= K0 * P00_temp;
        P01 -= K0 * P01_temp;
        P10 -= K1 * P00_temp;
        P11 -= K1 * P01_temp;

        return angle;
}    
        
void KalmanF::setAngle(float newAngle) 
{
       angle = newAngle;
}

float KalmanF::getRate()
{
        return rate;
}

void KalmanF::setQangle(float  newQ_angle)
{
        Q_angle = newQ_angle;
}

void KalmanF::setQbias(float  newQ_bias)
{
        Q_bias = newQ_bias;
}
void KalmanF::setRmeasure(float newR_measure)
{
        R_measure = newR_measure;
}
float KalmanF::getQangle()
{
        return Q_angle;
}
float KalmanF::getQbias()
{
        return Q_bias;
}
float KalmanF::getRmeasure()
{
       return R_measure;
}