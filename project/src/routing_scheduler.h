#ifndef SRC_ROUTING_SCHEDULER_H
#define SRC_ROUTING_SCHEDULER_H

#include "src/drone.h"
#include "src/package.h"
#include "src/customer.h"
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
   * @brief Find the drone that can deliver the Package to the Customer the fastest, and dispatch it
   *
   * This ends up being the closest drone to the package that is not already en-route to a package or delivery point.
   */
  void ScheduleDelivery(Package*, Customer*, const std::vector<entity_project::Entity*>&);

 private:

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
