//
// Created by alli on 11/12/20.
//

#include "src/drone.h"

namespace csci3081 {

const std::vector<std::string>& Drone::GetCurrentRoute() const {
  return *((std::vector<std::string>*) nullptr);
}

float csci3081::Drone::GetRemainingBattery() const {
  return 0;
}

float csci3081::Drone::GetCurrentSpeed() const {
  return 0;
}

float csci3081::Drone::GetMaxCapacity() const {
  return 0;
}

float csci3081::Drone::GetRemainingCapacity() const {
  return 0;
}

float csci3081::Drone::GetBaseAcceleration() const {
  return 0;
}

}  // nmespace csci3081
