#include "Quad.h"


void Quad::init(
    int FLH, int FRH, int FLL, int FRL, int BLH, int BRH, int BLL, int BRL,
    int trim0, int trim1, int trim2, int trim3, int trim4, int trim5, int trim6, int trim7
) {
    // Map between servos and board pins
    board_pins[0] = FLH; // front left  hip (inner)
    board_pins[1] = FRH; // front right hip (inner)
    board_pins[2] = FLL; // front left  leg (outer)
    board_pins[3] = FRL; // front right leg (outer)
    board_pins[4] = BLH; // back  left  hip (inner)
    board_pins[5] = BRH; // back  right hip (inner)
    board_pins[6] = BLL; // back  left  leg (outer)
    board_pins[7] = BRL; // back  right leg (outer)

    trim[0] = trim0;
    trim[1] = trim1;
    trim[2] = trim2;
    trim[3] = trim3;
    trim[4] = trim4;
    trim[5] = trim5;
    trim[6] = trim6;
    trim[7] = trim7;
    
  // Set reverse movement
  for (int i = 0; i < 8; i++) reverse[i] = false;

  // Init an oscillator for each servo
  for (int i = 0; i < 8; i++) {
    oscillator[i].start();
    servo[i].attach(board_pins[i]);
  }
  zero();
}

void Quad::args_test() {

  float steps = 1;
  int period[] = {1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000};
  int amplitude[] = {0, 0, 0, 0, 0, 0, 0, 20};
  int offset[] = {90, 90, 90, 90, 90, 90, 90, 90};
  int phase[] = {0, 0, 0, 0, 0, 0, 0, 0};

  execute(steps, period, amplitude, offset, phase);
}

void Quad::turnR(float steps, int T) {
  int x_amp = 15;
  int z_amp = 15;
  int ap = 15;
  int hi = 23;
  int period[] = {T, T, T, T, T, T, T, T};
  int amplitude[] = {x_amp, x_amp, z_amp, z_amp, x_amp, x_amp, z_amp, z_amp};
  int offset[] = {90 + ap, 90 - ap, 90 - hi, 90 + hi, 90 - ap, 90 + ap, 90 + hi, 90 - hi };
  int phase[] = {0, 180, 90, 90, 180, 0, 90, 90};

  execute(steps, period, amplitude, offset, phase);
}

void Quad::turnL(float steps, int T) {
  int x_amp = 15;
  int z_amp = 15;
  int ap = 15;
  int hi = 23;
  int period[] = {T, T, T, T, T, T, T, T};
  int amplitude[] = {x_amp, x_amp, z_amp, z_amp, x_amp, x_amp, z_amp, z_amp};
  int offset[] = {90 + ap, 90 - ap, 90 - hi, 90 + hi, 90 - ap, 90 + ap, 90 + hi, 90 - hi };
  int phase[] = {180, 0, 90, 90, 0, 180, 90, 90};

  execute(steps, period, amplitude, offset, phase);
}

void Quad::dance(float steps, int T) {
  int x_amp = 0;
  int z_amp = 40;
  int ap = 30;
  int hi = 40;
  int period[] = {T, T, T, T, T, T, T, T};
  int amplitude[] = {x_amp, x_amp, z_amp, z_amp, x_amp, x_amp, z_amp, z_amp};
  int offset[] = {90 + ap, 90 - ap, 90 - hi, 90 + hi, 90 - ap, 90 + ap, 90 + hi, 90 - hi};
  int phase[] = {0, 0, 0, 270, 0, 0, 90, 180};

  execute(steps, period, amplitude, offset, phase);
}

void Quad::frontBack(float steps, int T) {
  int x_amp = 30;
  int z_amp = 25;
  int ap = 20;
  int hi = 30;
  int period[] = {T, T, T, T, T, T, T, T};
  int amplitude[] = {x_amp, x_amp, z_amp, z_amp, x_amp, x_amp, z_amp, z_amp};
  int offset[] = {90 + ap, 90 - ap, 90 - hi, 90 + hi, 90 - ap, 90 + ap, 90 + hi, 90 - hi};
  int phase[] = {0, 180, 270, 90, 0, 180, 90, 270};

  execute(steps, period, amplitude, offset, phase);
}

void Quad::run(float steps, int T) {
  int x_amp = 15;
  int z_amp = 15;
  int ap = 15;
  int hi = 35;
  int front_x = 6;
  int period[] = {T, T, T, T, T, T, T, T};
  int amplitude[] = {x_amp, x_amp, z_amp, z_amp, x_amp, x_amp, z_amp, z_amp};
  int offset[] = {    90 + ap - front_x,
                      90 - ap + front_x,
                      90 - hi,
                      90 + hi,
                      90 - ap - front_x,
                      90 + ap + front_x,
                      90 + hi,
                      90 - hi
                 };
  int phase[] = {0, 0, 90, 90, 180, 180, 90, 90};

  execute(steps, period, amplitude, offset, phase);
}

void Quad::omniWalk(float steps, int T, bool side, float turn_factor) {
  int x_amp = 15;
  int z_amp = 15;
  int ap = 15;
  int hi = 23;
  int front_x = 6 * (1 - pow(turn_factor, 2));
  int period[] = {T, T, T, T, T, T, T, T};
  int amplitude[] = {x_amp, x_amp, z_amp, z_amp, x_amp, x_amp, z_amp, z_amp};
  int offset[] = {    90 + ap - front_x,
                      90 - ap + front_x,
                      90 - hi,
                      90 + hi,
                      90 - ap - front_x,
                      90 + ap + front_x,
                      90 + hi,
                      90 - hi
                 };

  int phase[8];
  if (side) {
    int phase1[] =  {0,   0,   90,  90,  180, 180, 90,  90};
    int phase2R[] = {0,   180, 90,  90,  180, 0,   90,  90};
    for (int i = 0; i < 8; i++)
      phase[i] = phase1[i] * (1 - turn_factor) + phase2R[i] * turn_factor;
  }
  else {
    int phase1[] =  {0,   0,   90,  90,  180, 180, 90,  90};
    int phase2L[] = {180, 0,   90,  90,  0,   180, 90,  90};
    for (int i = 0; i < 8; i++)
      phase[i] = phase1[i] * (1 - turn_factor) + phase2L[i] * turn_factor + oscillator[i].getPhaseProgress();
  }

  execute(steps, period, amplitude, offset, phase);
}

 
void Quad::moonwalkL(float steps, int T) {
  int z_amp = 50;
  int o = 10;
  int period[] = {T, T, T, T, T, T, T, T};
  int amplitude[] = {0, 0, z_amp, z_amp, 0, 0, z_amp, z_amp};
  int offset[] = {90, 90, 90-z_amp-0, 90+z_amp+o, 90, 90, 90+z_amp+o, 90-z_amp-o};
  //int phase[] = {0, 0, 0, 120, 0, 0, 180, 290};
  int phase[] = {0, 0, 0, 80, 0, 0, 160, 290};
  //int phase[] = {0, 0, 0, 45, 0, 0, 90, 135};

  execute(steps, period, amplitude, offset, phase);
}

void Quad::walk(int dir, float steps, int T) {
  int x_amp = 15;
  int z_amp = 20;
  int ap = 20;
  int hi = 25;
  int front_x = 12;
  int period[] = {T, T, T / 2, T / 2, T, T, T / 2, T / 2};
  int amplitude[] = {x_amp, x_amp, z_amp, z_amp, x_amp, x_amp, z_amp, z_amp};
  int offset[] = {   90 + ap - front_x,
                     90 - ap + front_x,
                     90 - hi,
                     90 + hi,
                     90 - ap - front_x,
                     90 + ap + front_x,
                     90 + hi,
                     90 - hi
                 };
  int  phase[] = {90, 90, 270, 90, 270, 270, 90, 270};

  if (dir == 0) { //backward
    phase[0] = phase[1] = 270;
    phase[4] = phase[5] = 90;
  }

  for (int i = 0; i < 8; i++) {
    oscillator[i].reset();
    oscillator[i].setPeriod(period[i]);
    oscillator[i].setAmplitude(amplitude[i]);
    oscillator[i].setPhase(phase[i]);
    oscillator[i].setOffset(offset[i]);
  }

  _final_time = millis() + period[0] * steps;
  _init_time = millis();
  bool side;
  while (millis() < _final_time) {
    side = (int)((millis() - _init_time) / (period[0] / 2)) % 2;
    setServo(0, oscillator[0].refresh());
    setServo(1, oscillator[1].refresh());
    setServo(4, oscillator[4].refresh());
    setServo(5, oscillator[5].refresh());

    if (side == 0) {
      setServo(3, oscillator[3].refresh());
      setServo(6, oscillator[6].refresh());
    }
    else {
      setServo(2, oscillator[2].refresh());
      setServo(7, oscillator[7].refresh());
    }
    delay(1);
  }
}


void Quad::upDown(float steps, int T) {
  int x_amp = 0;
  int z_amp = 35;
  int ap = 20;
  int hi = 35;
  int front_x = 0;
  int period[] = {T, T, T, T, T, T, T, T};
  int amplitude[] = {x_amp, x_amp, z_amp, z_amp, x_amp, x_amp, z_amp, z_amp};
  int offset[] = {    90 + ap - front_x,
                      90 - ap + front_x,
                      90 - hi,
                      90 + hi,
                      90 - ap - front_x,
                      90 + ap + front_x,
                      90 + hi,
                      90 - hi
                 };
  int phase[] = {0, 0, 90, 270, 180, 180, 270, 90};

  execute(steps, period, amplitude, offset, phase);
}


void Quad::pushUp(float steps, int T) {
  int z_amp = 40;
  int x_amp = 65;
  int hi = 50;
  int period[] = {T, T, T, T, T, T, T, T};
  int amplitude[] = {0, 0, z_amp, z_amp, 0, 0, 0, 0};
  //int offset[] = {90, 90, 90 - hi, 90 + hi, 90 - x_amp, 90 + x_amp, 90 + hi, 90 - hi};
  int offset[] = {90, 90, 90 - hi, 90 + hi, 5, 175, 90, 90};
  int phase[] = {0, 0, 0, 180, 0, 0, 0, 170};

  execute(steps, period, amplitude, offset, phase);
}

void Quad::hello() {
  float sentado[] = {90 + 15, 90 - 15, 90 - 65, 90 + 65, 90 + 20, 90 - 20, 90 + 10, 90 - 10};
  moveServos(150, sentado);
  delay(300);

  int z_amp = 40;
  int x_amp = 60;
  int T = 550;
  int period[] = {T, T, T, T, T, T, T, T};
  int amplitude[] = {0, 50, 0, 50, 0, 0, 0, 0};
  int offset[] = {90 + 15, 40, 90 - 65, 90, 90 + 20, 90 - 20, 90 + 10, 90 - 10};
  int phase[] = {0, 0, 0, 90, 0, 0, 0, 0};

  execute(4, period, amplitude, offset, phase);

  float goingUp[] = {160, 20, 90, 90, 90 - 20, 90 + 20, 90 + 10, 90 - 10};
  moveServos(500, goingUp);
  delay(200);

}

// copy from otto quad
void Quad::waveHand(float steps, int T) {

  int z_amp = 40;
  int x_amp = 65;
  int hi = 0;
 // (left front hip, right front hip, left front foot, right front foot,left rear hip, right rear hip, left rear foot, right rear foot)
  int period[] = {T, T, T, T, T, T, T, T};
  // int amplitude[] = {0, 0, -20, 0, 0, 0, 0, 0};
  int amplitude[] = {10, 0, 0, -20, 0, 0, 0, 0};
  // int offset[] = {90, 90, 30, 60 + hi, 90 - x_amp, 110 + x_amp, 90 + hi, 90 - hi};
  int offset[] = {90, 90, 45, 30, 90, 90, 90, 90};
  int phase[] = {0, 0, 0, 0, 0, 0, 0, 0};

  execute(steps, period, amplitude, offset, phase);
}

void Quad::hide(float steps, int T) {

  int z_amp = 40;
  int x_amp = 65;
  int hi = 0;
  int h = 80;
  // 0 - 90 mid pos - 180
 // (left front hip, right front hip, left front foot, right front foot,left rear hip, right rear hip, left rear foot, right rear foot)
  int period[] = {T, T, T, T, T, T, T, T};
  int amplitude[] = {0, 0, 0, 0, 0, 0, 0, 0};
  int offset[] = {90 - h, 90 + h, 170, 10, 90 + h, 90 - h, 10, 170};
  int phase[] = {0, 0, 0, 0, 0, 0, 0, 0};

  execute(steps, period, amplitude, offset, phase);
}

void Quad::scared() {

  int ap = 20;
  int hi = 35;

  float sentado[] = {90 - 15, 90 + 15, 150, 30,  90 - 20, 90 + 20, 30, 150};
  float salto[] = {90 - ap, 90 + ap, 10, 170, 90 + ap * 3, 90 - ap * 3, 170, 10};
  
  // zero();
  moveServos(600, sentado);
  moveServos(1000, salto);
  delay(1000);
  
  // home();
}

void Quad::home() {
  int ap = 20;
  int hi = 80;
  int position[] = {90 + ap, 90 - ap, 90 - hi, 90 + hi, 90 - ap, 90 + ap, 90 + hi, 90 - hi};
  for (int i = 0; i < 8; i++) setServo(i, position[i]);
}

void Quad::zero() {
  for (int i = 0; i < 8; i++) setServo(i, 90);
}

void Quad::reverseServo(int id) {
  if (reverse[id])
    reverse[id] = 0;
  else
    reverse[id] = 1;
}


void Quad::setServo(int id, float target) {
  if (!reverse[id])
    servo[id].writeMicroseconds(angToUsec(target + trim[id]));
  else
    servo[id].writeMicroseconds(angToUsec(180 - (target + trim[id])));
  _servo_position[id] = target;
}

float Quad::getServo(int id) {
  return _servo_position[id];
}


void Quad::moveServos(int time, float target[8]) {
  if (time > 10) {
    for (int i = 0; i < 8; i++)	_increment[i] = (target[i] - _servo_position[i]) / (time / 10.0);
    _final_time =  millis() + time;

    while (millis() < _final_time) {
      _partial_time = millis() + 10;
      for (int i = 0; i < 8; i++) setServo(i, _servo_position[i] + _increment[i]);
      while (millis() < _partial_time); //pause
    }
  }
  else {
    for (int i = 0; i < 8; i++) setServo(i, target[i]);
  }
  for (int i = 0; i < 8; i++) _servo_position[i] = target[i];
}

void Quad::execute(float steps, int period[8], int amplitude[8], int offset[8], int phase[8]) {

  for (int i = 0; i < 8; i++) {
    oscillator[i].setPeriod(period[i]);
    oscillator[i].setAmplitude(amplitude[i]);
    oscillator[i].setPhase(phase[i]);
    oscillator[i].setOffset(offset[i]);
  }

  unsigned long global_time = millis();

  for (int i = 0; i < 8; i++) oscillator[i].setTime(global_time);

  _final_time = millis() + period[0] * steps;
  while (millis() < _final_time) {
    for (int i = 0; i < 8; i++) {
      setServo(i, oscillator[i].refresh());
    }
    yield();
  }
}

int Quad::angToUsec(float value) {
  return value / 180 * (MAX_PULSE_WIDTH - MIN_PULSE_WIDTH) + MIN_PULSE_WIDTH;
}
