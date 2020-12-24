// -----
// RotaryEncoderNG.cpp - Library for using rotary encoders.
// This class is implemented for use with the Arduino environment.
// Copyright (c) by Daniel Carrasco, https://www.electrosoftcloud.com/
// This work is licensed under a GPL style license. See the included LICENSE file
// -----
// 24.12.2020 first version
// -----

#include "Arduino.h"
#include "RotaryEncoderNG.h"

RotaryEncoder::RotaryEncoder(int pin1, int pin2, bool directionDebounce) {
  
  // Remember Hardware Setup
  _pin1 = pin1;
  _pin2 = pin2;

  // Debounce?
  _directionDebounce = directionDebounce;
  
  // Setup the input pins and turn on pullup resistor
  pinMode(pin1, INPUT_PULLUP);
  pinMode(pin2, INPUT_PULLUP);

  // Set current state as last state to avoid on init tick
  _pin1LastState = digitalRead(_pin1);
} // RotaryEncoder()

void RotaryEncoder::tick(void)
{
  int sig1 = digitalRead(_pin1);
  int sig2 = digitalRead(_pin2);
  _positionTime = millis();
  
  if (sig1 != _pin1LastState) {
    Direction newDirection = Direction::NOROTATION;
    uint16_t ticks = 1;
    if (sig1 != _pin1LastState) {
      if (sig1 != sig2) {
        newDirection = Direction::CLOCKWISE;
      } else {
        newDirection = Direction::COUNTERCLOCKWISE;
      }
    }

    if (_directionDebounce && lastDirection != newDirection) {
      lastDirection = newDirection;
    } else {
      direction = newDirection;
    }

    if (direction == newDirection) {
      unsigned long deltat = getMillisBetweenRotations();

      if (deltat < _longCutoff && _m != 0) {
        if (deltat < _shortCutoff) {
          // limit to maximum acceleration
          deltat = _shortCutoff;
        }

        float ticksActual_float = _m * deltat + _c;
        ticks = (uint16_t)ticksActual_float;
      }

      if (direction == Direction::CLOCKWISE){
        _position -= ticks;
      } else  {
        _position += ticks;
      }
    }

    _pin1LastState = sig1;
    _positionTimePrev = _positionTime;
  }
}

void RotaryEncoder::setAcceleration(float m, float c, uint16_t shortCutoff, uint16_t longCutoff) {
  _m = m;
  _c = c;
  _shortCutoff = shortCutoff;
  _longCutoff = longCutoff;
}
// End