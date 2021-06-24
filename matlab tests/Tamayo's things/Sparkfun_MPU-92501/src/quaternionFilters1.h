#ifndef _QUATERNIONFILTERS_H_1
#define _QUATERNIONFILTERS_H_1

#include <Arduino.h>

void MadgwickQuaternionUpdate1(float ax, float ay, float az, float gx, float gy,
                              float gz, float mx, float my, float mz,
                              float deltat);
void MahonyQuaternionUpdate1(float ax, float ay, float az, float gx, float gy,
                            float gz, float mx, float my, float mz,
                            float deltat);
const float * getQ1();
const float getQuaW1 ();
const float getQuaX1 ();
const float getQuaY1 ();
const float getQuaZ1 ();
#endif // _QUATERNIONFILTERS_H_
