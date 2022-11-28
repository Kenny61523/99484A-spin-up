#include <iostream>
#include <vector>
#include "vex.h"
#include <cmath>

int auton_counter = 1;

template <typename MOTOR>

void spin (MOTOR name, int power = 100) {
  name.spin(directionType::fwd, power, velocityUnits::pct);
}

void spinRoller(int power, int time) {
  spin(intake_roller, power);
  task::sleep(time);
  intake_roller.stop();
}

void lowerCatapult() {
  do {
    spin(catapult);
  } while(!catapult_limit.pressing());
  catapult.stop();
  catapult.setBrake(brakeType::hold);
}

void move(int power, int time, int roller_power = 0) {
  spin(chassis_left, power);
  spin(chassis_right, power);
  spin(intake_roller, roller_power);
  task::sleep(time);
  chassis_left.stop();
  chassis_right.stop();
  intake_roller.stop();
}

void turn(int power, int time, int roller_power = 0) {
  spin(chassis_left, power);
  spin(chassis_right, -power);
  spin(intake_roller, roller_power);
  task::sleep(time);
  chassis_left.stop();
  chassis_right.stop();
  intake_roller.stop();
}

void catapultShoot() {
  catapult.resetRotation();
  do {
    spin(catapult);
  } while (catapult.rotation(rotationUnits::deg) < 100 || !catapult_limit.pressing());
  catapult.stop();
  catapult.setBrake(brakeType::hold);
}

void stringMech() {
  string_mech.open();
}

void skill() {

}

void bottomAuton() {
  lowerCatapult();
  move(30, 200, -100);
  move(-30, 200);
  turn(30, 650);
  move(20, 350, 100);
  spinRoller(100, 500);
  move(-20, 350, 100);
  turn(-30, 200);
  task::sleep(100);
  move(-30, 200);
  turn(-30, 100);
  catapultShoot();
  move(-30, 1000);
  task::sleep(100);
  turn(30, 450);
  move(-20, 550);
  task::sleep(100);
  lowerCatapult();
  task::sleep(2000);
  move(30, 300);
  turn(-30, 500);
  catapultShoot();
  turn(30, 300);
  move(-30, 500);
  lowerCatapult();
  spinRoller(100, 500);
  move(30, 300);
  turn(-30, 500);
  
  catapultShoot();
}

void sideAuton() {

}

void auton_ctrl() {
  chassis_left.resetRotation();
  chassis_right.resetRotation();
  intake_roller.resetRotation();
  switch (auton_counter) {
    case 0: skill(); break;
    case 1: bottomAuton(); break;
    case 2: sideAuton(); break;
  }
}