#ifndef DRONE_H_
#define DRONE_H_

#include <EntityProject/ANVIL2/drone.h>
#include <queue>
#include <EntityProject/graph.h>
#include "src/vector_3d.h"
#include "src/package.h"
#include "src/route_utils.h"
#include "src/json_helper.h"
#include "src/drone_pool.h"
#include <unordered_map>
#include <vector>
#include <string>

namespace csci3081 {

static std::unordered_map<std::string, csci3081::droneSpecs>
    models_ = csci3081::createDroneModelList("data/planet-x.csv");


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
  /// Update the deliveries assigned to this drone
  void SetDeliveryPlan(csci3081::Package* package, csci3081::Customer* customer, RouteManager rm);
  /// Update the drone's route based on current state
  void RecalculateRoute();
  /// Sets route to a destination
  void RouteTo(entity_project::Entity* dest);
  /// Sets route from a vector of IGraphNodes
  void SetRoute(std::vector<entity_project::IGraphNode*> newRoute);

  /// Updates package positions
  void CarryPackages();
  /// Updates package PickedUp states
  /**
   * Drops off any packages touching their destination, then picks up any packages
   * the drone is touching.
   */
  void UpdatePackages();

  /**
  * Retrieves a Drone's Observable reference to call functions
  * related to the subject of an observer pattern.
  *
  * @return Observable object reference. Returns droneObservable
  */
  Observable& GetObservable() { return droneObservable; }

  /**
  * Notify observers that the drone is idle.
  */
  void NotifyIdled();

  /**
  * Notify observers that the drone is moving.
  * 
  */
  void NotifyMoving();

  /// Returns true if the drone has incomplete deliveries
  bool IsDelivering() { return package != nullptr; }

  void SetDroneSpecs(const std::unordered_map<std::string, droneSpecs> list);

  void PhysicsUpdate(float dt);

 private:
  std::queue<entity_project::IGraphNode*> route;
  csci3081::Package* package = nullptr;
  bool hasPickedUpPackage_ = false;
  std::vector<std::string> route_by_node_name;
  RouteManager routemanager;
  Observable droneObservable;
  /// The speed at which the drone moves, in simulation-units per second
  float speed = 100;
  float battery;
  float currLoadWeight = 0;
  std::string modelNum;
  droneSpecs spec_;
  std::string physicsModel = "velocity";
};

}  // namespace csci3081
#endif
