//
// Created by alli on 11/12/20.
//

#include "src/drone.h"

namespace csci3081 {

Drone::Drone(const picojson::object& initfrom) : Drone() {
  details_ = initfrom;
  if (details_.find("position") != details_.end()) {
    int len = details_["position"].get<picojson::array>().size();
    for (int i = 0; i < len && i < 3; i++) {
      position_[i] = details_["position"].get<picojson::array>()[i].get<double>();
    }
  }
}

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
