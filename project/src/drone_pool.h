#ifndef DRONE_POOL_H_
#define DRONE_POOL_H_

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <vector>

namespace csci3081 {

struct droneSpecs {
  std::string model_;
  float mass_;
  float max_speed_;
  float base_acc_;
  float weight_cap_;
  float base_bat_cap_;

  droneSpecs(std::string model = "Q-36-01",
             float mass = 50.0,
             float speed = 60.0,
             float acc = 4.0,
             float weight = 10.0,
             float battery = 300)
      : model_(model),
        mass_(mass),
        max_speed_(speed),
        base_acc_(acc),
        weight_cap_(weight),
        base_bat_cap_(battery) {}
};

std::unordered_map<std::string, droneSpecs> createDroneModelList(std::string filename);
// NOTICE: commented out because unused and passes by mutable reference, failing cpplint.
// void updateDroneModelList(std::unordered_map<std::string, droneSpecs>* list,
//                           std::string filename);
bool isModelListed(std::unordered_map<std::string, csci3081::droneSpecs> list, std::string model);
std::ostream& operator<<(std::ostream& out, const droneSpecs& d);

}  // namespace csci3081

#endif
