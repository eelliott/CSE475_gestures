#include "Creature.h"
#include "State.h"

State::State(Creature& creature, char* const name, const uint8_t id) : _creature(creature), _id(id) {
  strncpy(_name, name, MAX_NAME_LEN);
  _name[MAX_NAME_LEN] = 0;
};

uint8_t State::getId() {
  return _id;
}

char* State::getName() {
  return _name;
}

void State::playSound(uint8_t sound_idx) {
  // TODO: implement
}

void State::playEffect(uint8_t effect_idx) {
  // TODO: implement
}

bool State::rxPlaySound(uint8_t len, uint8_t* payload) {
  // TODO: implement
}

bool State::rxPlayEffect(uint8_t len, uint8_t* payload) {
  // TODO: implement
}

bool State::rxStartle(int8_t rssi, uint8_t len, uint8_t* payload) {
  uint8_t strength = payload[0];
  uint8_t id = payload[1];
  // strength is greater than startle_factor * creature_threshold 
  if (strength > this->getStartleFactor()*this->_creature.getStartleThreshold()) {
    this->startled(); // startled
  }  
}

void State::txStartle(uint8_t strength, uint8_t id) {
  uint8_t* startlePayload [] = {strength, id};
  this->_creature->tx(PID_STARTLE, 0xFF, 2, startlePayload);
}

State* State::transition() {
  // TODO: implement
  // generate 0~1
  // assign each state to some part of the range
  /*
   * Computes probability distribution for state transitions, generates a random
   * number, and uses this to produce the next state we should transition into.
   *
   * @returns State object for next state to transition into.
  */
}

void State::PIR() {
  // TODO: implement
}

void State::startled(uint8_t strength, uint8_t id) {
  // TODO: implement
  dprintln("Startled");
}

int8_t* State::getGlobalWeights() {
  return _globalWeights;
}
