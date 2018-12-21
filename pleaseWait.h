// -----
// pleaseWait.h - Library for a working, waiting, loading pattern on the LEDs
// This class is implemented for use with the Arduino environment.
// Copyright (c) by Dan Malone
// This work is licensed under a BSD style license.
// More information on:
// -----
// 12/16/2018 Initial code
// -----

#ifndef pleaseWait_h
#define pleaseWait_h

#include "Arduino.h"

// This supresses the pragma version warning FASTLED produces
#define FASTLED_INTERNAL
#include <FastLED.h>

class pleaseWait
{
  public:
    // ----- Constructor -----
    pleaseWait(struct CRGB *_leds,
               unsigned int _numLeds,
               unsigned int _numBlips,
               float _blipOverlapPercent,
               float _secondsTotalDuration,
               float _secondsGapDuration,
               CRGB _color);

    // ----- Set runtime parameters -----
    void setNumBlips(unsigned int _numBlips);
    void setBlipOverlapPercent(float _blipOverlapPercent);
    void setTotalDuration(float _secondsTotalDuration);
    void setGapDuration(float _secondsGapDuration);
    void setColor(CRGB _color);

    // ----- State functions -----
    void start();
    void restart();
    void stop();
    void clear();

    // call this function every some milliseconds for handling color changes/dims.
    void loop(void);

  private:
    //
    CRGB *leds;
    unsigned int numLeds = 0;
    unsigned int numBlips = 0;
    float blipOverlapPercent = 0.0;
    float secondsTotalDuration = 0;
    float secondsGapDuration = 0;
    CRGB color;

    float secondsScrollDuration = 0;
    float secondsHalfScrollDuration = 0;
    unsigned int travelLeds = 0;
    float secondsBlipTravelHalfDuration = 0;
    float acceleration = 0.0;

    // State
    unsigned char state = 0;
    unsigned long millisLastStart = 0;

    void computeInternals();
    void displayBlip(float blipPosition);
};

#endif
