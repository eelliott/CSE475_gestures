#include "Active1.h"
#include "Neopixel.h"
#include "Debug.h"

constexpr uint8_t Active1::_localWeights[];

uint8_t Active1::getNumRepeats() {
 return 32;
}

void Active1::loop(uint32_t dt) {
//  dprintln(F("Waiting..."));
}

const uint8_t* Active1::getLocalWeights() {
  return this->_localWeights;
}

float Active1::getStartleFactor() {
  return 0000100000; // ?
}

void Active1::PIR() {
  dprintln("PIR triggered!");
}

void Active1::startled(uint8_t strength, uint8_t id) {}
