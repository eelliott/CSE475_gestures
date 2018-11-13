#include "Ambient1.h"
#include "Neopixel.h"
#include "Debug.h"

constexpr uint8_t Ambient1::_localWeights[];

uint8_t Ambient1::getNumRepeats() {
 return 32;
}

void Ambient1::loop(uint32_t dt) {
//  dprintln(F("Waiting..."));
}

const uint8_t* Ambient1::getLocalWeights() {
  return this->_localWeights;
}

float Ambient1::getStartleFactor() {
  return 0000050000; // ?
}

void Ambient1::PIR() {
  dprintln("PIR triggered!");
}

void Ambient1::startled(uint8_t strength, uint8_t id) {}
