#include "Active2.h"
#include "Neopixel.h"
#include "Debug.h"

constexpr uint8_t Active2::_localWeights[];

uint8_t Active2::getNumRepeats() {
 return 32;
}

void Active2::loop(uint32_t dt) {
//  dprintln(F("Waiting..."));
}

const uint8_t* Active2::getLocalWeights() {
  return this->_localWeights;
}

float Active2::getStartleFactor() {
  return 0000100000; // ?
}

void Active2::PIR() {
  dprintln("PIR triggered!");
}

void Active2::startled(uint8_t strength, uint8_t id) {}
