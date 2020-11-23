#ifndef DRONE_POOL_H_
#define DRONE_POOL_H_

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <vector>

namespace csci3081 {

/// struct to hold specifications for different drone models.
struct droneSpecs {
  std::string model_;
  float mass_;
  float max_speed_;
  float base_acc_;
  float weight_cap_;
  float base_bat_cap_;

  // Constructor to initialize a drone's specifications based off model number.
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

/**
 * Creates a map holding drone model specs, key value pair being <model, droneSpecs>
 * 
 * @param filename is the file to read drone specs from.
 * @return drone_model_list is the map holding the differenct model specs.
 */
std::unordered_map<std::string, droneSpecs> createDroneModelList(std::string filename);
// NOTICE: commented out because unused and passes by mutable reference, failing cpplint.
// void updateDroneModelList(std::unordered_map<std::string, droneSpecs>* list,
//                           std::string filename);
/**
 * Check if model is listed in the drone spec list.
 * 
 * @param list is the map to check if model is in.
 * @param model is the model name to be checked.
 */
bool isModelListed(std::unordered_map<std::string, csci3081::droneSpecs> list, std::string model);
// Overloaded operator for testing purposes.
std::ostream& operator<<(std::ostream& out, const droneSpecs& d);

}  // namespace csci3081

#endif
