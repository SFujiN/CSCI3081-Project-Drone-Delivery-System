#ifndef SRC_ROUTING_SCHEDULER_H
#define SRC_ROUTING_SCHEDULER_H

#include "src/drone.h"
#include "src/package.h"
#include "src/customer.h"
#include "src/route_utils.h"
#include <EntityProject/entity.h>
#include <vector>

namespace csci3081 {

/**
 * @brief Entry point to the routing system.
 * Currently, has nothing more than a single function, but is expected to need to store more complex
 * state to account for multiple drones, packages, or customers.
 */
class RoutingScheduler {
 public:
  /**
   * @brief Find the drone that can deliver the Package to the Customer the fastest, and dispatch.
   *
   * Contains the logic for deciding which drone to assign a delivery to. Called by
   * DroneSimulation to handle deliveries. Also contains the RouteManager which all
   * drones will use to make their route calculations.
   */
  void ScheduleDelivery(Package*, Customer*, const std::vector<entity_project::Entity*>&,
      const picojson::object&);

  void SetGraph(const entity_project::IGraph* graph) { routemanager.SetGraph(graph); }

 private:
  RouteManager routemanager;

  /**
   * @brief Get the right drone to deliver the package to the customer
   * @return Null if no drones are available, otherwise the closest drone.
   */
  Drone* findAppropriateDrone(
      Package* package, Customer* customer,
      const std::vector<entity_project::Entity*>& entities);
};

}  // namespace csci3081


#endif  // SRC_ROUTING_SCHEDULER_H
