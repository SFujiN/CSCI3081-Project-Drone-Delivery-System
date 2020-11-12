#ifndef DRONE_H_
#define DRONE_H_

#include <EntityProject/ANVIL2/drone.h>
#include <queue>
#include <EntityProject/graph.h>
#include "vector_3d.h"

namespace csci3081 {

/// TODO: Add documentation. You may edit this class including adding members or methods.
/**
 * TODO: Add detailed documentation.
 */
class Drone : public entity_project::Drone {
 public:
  /// TODO: Add documentation.
  Drone() { AddType<Drone>(); }
  /**
   * @brief Create a Drone from the JSON encoding.
   */
  explicit Drone(const picojson::object&);
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

  void Update(float dt);

  /**
   * @brief Move the drone speed*dt distance along its current route
   * @return true if the route end has been reached, otherwise false
   */
  bool FollowRoute(float dt);
  /// Get the current position in the form of a Vector3d
  Vector3d GetVecPos();
  /// Move to the location of the Vector3d
  void SetVecPos(Vector3d);

 private:
  std::queue<entity_project::IGraphNode*> route;
};

}  // namespace csci3081
#endif
