//
// Created by alli on 11/12/20.
//

#include "src/drone_simulation.h"
#include "src/drone.h"
#include "src/package.h"

namespace csci3081 {

void DroneSimulation::Update(float dt) {
  for (const auto& entity : entities_) {
    auto drone = entity->AsType<csci3081::Drone>();
    if (drone != nullptr) {
      drone->Update(dt);
    }
    auto package = entity->AsType<csci3081::Package>();
    if (package != nullptr) {
      if (package->ShouldDelete()) {
        entities_.erase(
                std::remove(entities_.begin(), entities_.end(), entity),
                entities_.end());
      }
    }
  }
}

DroneSimulation::~DroneSimulation() {
  for (auto* entity : entities_) {
    delete entity;
  }
}

}  // namespace csci3081
