// -----
// pleaseWait.h - Library for a working, waiting, loading pattern on the LEDs
// This class is implemented for use with the Arduino environment.
// Copyright (c) by Dan Malone
// This work is licensed under a BSD style license.
// More information on:
// -----
// 12/16/2018 Initial code
// -----

#include "pleaseWait.h"

//bool debug = true;

void pleaseWait::computeInternals() {
  float segments;
  secondsScrollDuration = secondsTotalDuration - secondsGapDuration;
  secondsHalfScrollDuration = secondsScrollDuration / 2;
  travelLeds = numLeds - floor((float)(numLeds - numBlips) / 2);
  segments = (numBlips * (1 - blipOverlapPercent)) + blipOverlapPercent;
  secondsBlipTravelHalfDuration = secondsHalfScrollDuration / segments;
  acceleration = travelLeds * 2 / pow(secondsBlipTravelHalfDuration, 2);
  //        Serial.println("computeInternals");
  //        Serial.println(secondsScrollDuration);
  //        Serial.println(secondsHalfScrollDuration);
  //        Serial.println(travelLeds);
  //        Serial.println(segments);
  //        Serial.println(secondsBlipTravelHalfDuration);
  //        Serial.println(acceleration);
}


pleaseWait::pleaseWait(struct CRGB *_leds,
                       unsigned int _numLeds,
                       unsigned int _numBlips,
                       float _blipOverlapPercent,
                       float _secondsTotalDuration,
                       float _secondsGapDuration,
                       CRGB _color)
{
  leds = _leds;
  numLeds = _numLeds;
  numBlips = _numBlips;
  blipOverlapPercent = _blipOverlapPercent;
  secondsTotalDuration = _secondsTotalDuration;
  secondsGapDuration = _secondsGapDuration;
  color = _color;

  computeInternals();
}


// ----- Set runtime parameters -----
void pleaseWait::setNumBlips(unsigned int _numBlips) {
  numBlips = _numBlips;
  computeInternals();
}

void pleaseWait::setBlipOverlapPercent(float _blipOverlapPercent) {
  blipOverlapPercent = _blipOverlapPercent;
  computeInternals();
}

void pleaseWait::setTotalDuration(float _secondsTotalDuration) {
  secondsTotalDuration = _secondsTotalDuration;
  computeInternals();
}

void pleaseWait::setGapDuration(float _secondsGapDuration) {
  secondsGapDuration = _secondsGapDuration;
  computeInternals();
}

void pleaseWait::setColor(CRGB _color) {
  color = _color;
  computeInternals();
}

// ----- State functions -----
void pleaseWait::start() {
  state = 1;
  millisLastStart = millis();
}

void pleaseWait::stop() {
  state = 0;
}

void pleaseWait::restart() {
  stop();
  start();
}

void pleaseWait::clear() {
  unsigned char counter;
  for (counter = 0; counter < numLeds; counter++) {
    leds[counter] = 0x000000;
  }
}

void pleaseWait::displayBlip(float blipPosition) {
  int fullBlipPosition;
  int partialBlipPosition;
  float partialBlipPercent;
  CRGB dimColor;

  fullBlipPosition = round(blipPosition);
  partialBlipPercent = abs(blipPosition - fullBlipPosition) * 2.0;
  dimColor = color;
  dimColor.fadeLightBy(255 - int(255 * partialBlipPercent));

  if (fullBlipPosition > blipPosition) {
    partialBlipPosition = fullBlipPosition - 1;
  } else {
    partialBlipPosition = fullBlipPosition + 1;
  }

  if ((fullBlipPosition >= 0) && (fullBlipPosition < numLeds)) {
    leds[fullBlipPosition] += color;
  }
//  if ((partialBlipPosition >= 0) && (partialBlipPosition < numLeds)) {
//    leds[partialBlipPosition] += dimColor;
//  }
}

void pleaseWait::loop(void) {
  float secondsSinceLastStart = (float)(millis() - millisLastStart) / 1000;
  float secondsBlipStart;
  float secondsBlipEnd;

  int blipStartLed;
  int blipMidLed;
  int blipEndLed;

  float blipPosition;

  if (state == 1) {
    if (secondsSinceLastStart > secondsTotalDuration) {
      restart();

      // incoming blips
    } else if (secondsSinceLastStart < secondsHalfScrollDuration) {
      for (unsigned int blip = 0; blip < numBlips; blip++) {
        blipMidLed = numLeds - ceil((float)(numLeds - numBlips) / 2) - 1 - blip;
        blipStartLed = blipMidLed - travelLeds;
        secondsBlipStart = blip * (secondsBlipTravelHalfDuration * (1.0 - blipOverlapPercent));
        secondsBlipEnd = secondsBlipStart + secondsBlipTravelHalfDuration;

        blipPosition = (float)blipMidLed - (acceleration * (pow((secondsBlipEnd - secondsSinceLastStart), 2)) / 2);
        if (secondsSinceLastStart < secondsBlipStart) {
          blipPosition = blipStartLed;
        } else if (secondsSinceLastStart > secondsBlipEnd) {
          blipPosition = blipMidLed;
        }
        displayBlip(blipPosition);
      }

      // outgoing blips
    } else if (secondsSinceLastStart < secondsScrollDuration) {
      //                Serial.print(secondsSinceLastStart);
      //                Serial.print(": ");
      for (unsigned int blip = 0; blip < numBlips; blip++) {
        blipMidLed = numLeds - ceil((float)(numLeds - numBlips) / 2) - 1 - blip;
        blipEndLed = blipMidLed + travelLeds;
        secondsBlipStart = blip * (secondsBlipTravelHalfDuration * (1.0 - blipOverlapPercent)) + secondsHalfScrollDuration;
        secondsBlipEnd = secondsBlipStart + secondsBlipTravelHalfDuration + secondsHalfScrollDuration;

        blipPosition = (float)blipMidLed + (acceleration * (pow((secondsSinceLastStart - secondsBlipStart), 2)) / 2);
        if (secondsSinceLastStart < secondsBlipStart) {
          blipPosition = blipMidLed;
        } else if (secondsSinceLastStart > secondsBlipEnd) {
          blipPosition = blipEndLed;
        }
        displayBlip(blipPosition);
        //        if (debug) {
        //        Serial.print("blip: ");
        //        Serial.print(blip);
        //        Serial.print(", pos: ");
        //                Serial.print(blipPosition);
        //                Serial.print(", ");
        //        Serial.println(blipMidLed);
        //        Serial.println(blipStartLed);
        //        Serial.println(secondsBlipStart);
        //        Serial.println(secondsBlipEnd);
        //        Serial.println(acceleration);

        //        Serial.println(secondsBlipEnd - secondsSinceLastStart);
        //        Serial.println(pow((secondsBlipEnd - secondsSinceLastStart), 2)) ;
        //        Serial.println( (pow((secondsBlipEnd - secondsSinceLastStart), 2)) / 2);
        //        Serial.println((acceleration * (pow((secondsBlipEnd - secondsSinceLastStart), 2)) / 2));
        //        Serial.println((float)blipMidLed - (acceleration * (pow((secondsBlipEnd - secondsSinceLastStart), 2)) / 2));

        //        }
      }
      //              Serial.println("");
      //            delay(124);
    }
  }
}


//    unsigned int numLeds = 0;
//    unsigned int numBlips = 0;
//    float blipOverlapPercent = 0.0;
//    unsigned long millisTotalDuration = 0;
//    unsigned long millisGapDuration = 0;
//    CRGB color;
//
//    unsigned long millisScrollDuration = 0;
//    unsigned long millisHalfScrollDuration = 0;
//    unsigned int travelLeds = 0;
//    unsigned long millisBlipTravelHalfDuration = 0;
//    float acceleration = 0.0;
//
//    // State
//    unsigned char state = 0;
//    unsigned long millisLastStart = 0;
