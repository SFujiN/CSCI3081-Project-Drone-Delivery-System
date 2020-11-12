#ifndef DRONE_H_
#define DRONE_H_

#include <EntityProject/ANVIL2/drone.h>

namespace csci3081 {

/// TODO: Add documentation. You may edit this class including adding members or methods.
/**
 * TODO: Add detailed documentation.
 */
class Drone : public entity_project::Drone {
 public:
  /// TODO: Add documentation.
  Drone() { AddType<Drone>(); }
  /// Gets the current route
  const std::vector<std::string>& GetCurrentRoute() const override;
  /// Gets the remaining battery life
  float GetRemainingBattery() const override;
  /// Gets the current speed
  float GetCurrentSpeed() const override;
  /// Gets the max carrying capacity
  float GetMaxCapacity() const override;
  /// Gets the remaining capacity
  float GetRemainingCapacity() const override;
  /// Gets the base acceleration
  float GetBaseAcceleration() const override;
};

}  // namespace csci3081
#endif
