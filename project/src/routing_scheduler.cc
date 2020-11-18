#include "src/routing_scheduler.h"
#include "src/route_utils.h"
#include <vector>
#include <limits>

namespace csci3081 {

void csci3081::RoutingScheduler::ScheduleDelivery(
        csci3081::Package* package, csci3081::Customer* customer,
        const std::vector<entity_project::Entity*>& entities
) {
  package->NotifyScheduled();
  Drone* to_dispatch = findAppropriateDrone(
          package, customer, entities);
  if (to_dispatch == nullptr) {
    std::cerr << "No drone was a available for this delivery! Try again later!" << std::endl;
    return;
  }
  // TODO: Tell the drone where to go
  //to_dispatch->SetDeliveryPlan(package, customer);
}

Drone* RoutingScheduler::findAppropriateDrone(
        Package* package, Customer* customer,
        const std::vector<entity_project::Entity*>& vector) {
  // TODO: this should more intelligently choose a drone
  for (auto i = vector.begin(); i != vector.end(); ++i) {
    auto drone = (*i)->AsType<csci3081::Drone>();
    if (drone != nullptr) {
      return drone;
    }
  }
  return nullptr;
}

}  // namespace csci3081
