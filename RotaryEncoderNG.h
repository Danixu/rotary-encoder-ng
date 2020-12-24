// -----
// RotaryEncoderNG.cpp - Library for using rotary encoders.
// This class is implemented for use with the Arduino environment.
// Copyright (c) by Daniel Carrasco, https://www.electrosoftcloud.com/
// This work is licensed under a GPL style license. See the included LICENSE file
// -----
// 24.12.2020 first version
// -----

#ifndef RotaryEncoder_h
#define RotaryEncoder_h

#include "Arduino.h"

class RotaryEncoder
{
public:
  enum class Direction { NOROTATION = 0, CLOCKWISE = 1, COUNTERCLOCKWISE = -1};
  Direction direction = Direction::NOROTATION;
  Direction lastDirection = Direction::NOROTATION;

  // ----- Constructor -----
  // directionDebounce avoid the short changes in direction. Make it needs at least two ticks to change the direction.
  RotaryEncoder(int pin1, int pin2, bool directionDebounce = false);
  
  // retrieve the current position
  long getPosition() const { return _position; };

  // adjust the current position
  void setPosition(long newPosition) { _position = newPosition; };
  
  // simple retrieve of the direction the knob was rotated at. 0 = No rotation, 1 = Clockwise, -1 = Counter Clockwise
  Direction getDirection() const { return direction; };

  // call this function every some milliseconds or by using an interrupt for handling state changes of the rotary encoder.
  void tick(void);

  // Set the acceleration of the encoder
  void setAcceleration(float m, float c, uint16_t shortCutoff = 4, uint16_t longCutoff = 200);

  // Returns the time in milliseconds between the current observed 
  unsigned long getMillisBetweenRotations() const { return _positionTime - _positionTimePrev; };

private:
  int _pin1, _pin2; // Arduino pins used for the encoder.
  int _pin1LastState = 0; // To keep the last pin state

  long _position = 0;
  long _positionTime = 0;
  long _positionTimePrev = 0;
  bool _directionDebounce;

  // Acceleration
  float _m = 0;
  float _c = 0;
  uint16_t _shortCutoff = 4;
  uint16_t _longCutoff = 200;
};

#endif
// End