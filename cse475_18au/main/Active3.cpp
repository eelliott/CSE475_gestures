#include "Active3.h"
#include "Neopixel.h"
#include "Debug.h"

constexpr uint8_t Active3::_localWeights[];

uint8_t Active3::getNumRepeats() {
 return 32;
}

void Active3::loop(uint32_t dt) {
//  dprintln(F("Waiting..."));
}

const uint8_t* Active3::getLocalWeights() {
  return this->_localWeights;
}

float Active3::getStartleFactor() {
  return 0000100000; // ?
}

void Active3::PIR() {
  dprintln("PIR triggered!");
}

void Active3::startled(uint8_t strength, uint8_t id) {}
