#ifndef Quad_h
#define Quad_h
#define MIN_PULSE_WIDTH 544  // the shortest pulse sent to a servo
#define MAX_PULSE_WIDTH 2400 // the longest pulse sent to a servo
#define DEFAULT_PULSE_WIDTH 1500

#include <ESP32Servo.h>
#include "Octosnake.h"

class Quad
{
public:
    void init(int FRH, int FLH, int FRL, int FLL, int BRH, int BLH, int BRL, int BLL);
    void args_test();
    void home();
    void zero();
    void hello();
    void walk(int dir = 1, float steps = 4, int period = 1000);
    void omniWalk(float steps = 4, int T = 1000, bool side = true, float turn_factor = 2);
    void run(float steps = 4, int period = 600);
    // void backward(float steps, int period);
    void turnL(float steps = 2, int period = 800);
    void turnR(float steps = 2, int period = 800);
    void moonwalkL(float steps = 4, int period = 2000);
    void dance(float steps = 2, int period = 2000);
    void upDown(float steps = 3, int period = 500);
    void pushUp(float steps = 2, int period = 3000);
    void frontBack(float steps = 2, int period = 1000);

    // copy from otto quad
    void waveHand(float steps = 5, int period = 700);
    void hide(float steps = 1, int period = 2000);
    void scared();

    void setServo(int id, float target);
    void reverseServo(int id);
    float getServo(int id);
    void moveServos(int time, float target[8]);

private:
    Oscillator oscillator[8];
    Servo servo[8];
    int board_pins[8];
    int trim[8];
    bool reverse[8];
    unsigned long _init_time;
    unsigned long _final_time;
    unsigned long _partial_time;
    float _increment[8];
    float _servo_position[8];

    int angToUsec(float value);
    void execute(float steps, int period[8], int amplitude[8], int offset[8], int phase[8]);
};

#endif
