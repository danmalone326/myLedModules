// -----
// larsonScanner.cpp - Library for displaying a Larson Scanner
// This class is implemented for use with the Arduino environment.
// Copyright (c) by Dan Malone
// This work is licensed under a BSD style license.
// More information on:
// -----
// 01/20/2019 Initial code
// -----

#include "larsonScanner.h"

CRGB larsonScanner::lerpColor(CRGB fromColor, CRGB toColor, float percent) {
  CRGB result;
  unsigned char fract8 = (int)(255 * percent);

  result.r = lerp8by8(fromColor.r, toColor.r, fract8);
  result.g = lerp8by8(fromColor.g, toColor.g, fract8);
  result.b = lerp8by8(fromColor.b, toColor.b, fract8);

  return result;
}

larsonScanner::larsonScanner (struct CRGB *_leds,
                              unsigned int _numLeds,
                              CRGB _color,
                              unsigned long _millisPerScan = 2000,
                              unsigned char _scanWidth = 3) {
  leds = _leds;
  numLeds = _numLeds;
  color = _color;
  millisPerScan = _millisPerScan;
  scanWidth = _scanWidth;
}

void larsonScanner::restartScan (unsigned long _startOfScanMillis = millis()) {
  startOfScanMillis = _startOfScanMillis;
  endOfScanMillis = _startOfScanMillis + millisPerScan;
}

void larsonScanner::clear() {
  unsigned char counter;
  for (counter = 0; counter < numLeds; counter++) {
    leds[counter] = 0x000000;
  }
}

void larsonScanner::loop() {
  unsigned long millisThisLoop = millis();
  float thisScanPosition;
  float thisLedDistance;
  float fade;
  int low;
  int high;
  unsigned char index;
  CRGB tempColor;

  if (millisThisLoop >= endOfScanMillis) {
    restartScan(endOfScanMillis);
  }

  thisScanPosition = numLeds * (abs((float)(millisThisLoop - startOfScanMillis) - (millisPerScan / 2)) * 2) / millisPerScan;

  low = floor(thisScanPosition - scanWidth);
  if (low  < 0 ) {
    low = 0;
  }

  high = ceil(thisScanPosition + scanWidth);
  if (high > numLeds) {
    high = numLeds;
  }

  for (index = low; index < high; index++) {
    thisLedDistance = abs(index - thisScanPosition);
    fade = 1 / (pow(2, thisLedDistance));
    tempColor = lerpColor(leds[index],
                          color,
                          fade);
    leds[index] = tempColor;
  }
}
