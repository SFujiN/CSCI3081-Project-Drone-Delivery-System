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
	int base_bat_cap_;

	droneSpecs(std::string model,
               float mass,
               float speed,
               float acc, float weight,
               int battery)
               : model_(model),
                 mass_(mass),
                 max_speed_(speed),
                 base_acc_(acc),
                 weight_cap_(weight),
                 base_bat_cap_(battery) {}
};

std::vector<droneSpecs> createDroneModelList(std::string filename);
std::ostream& operator<<(std::ostream& out, const droneSpecs& d);

} // namespace csci3081

#endif
