#include "src/routing_scheduler.h"
#include "src/route_utils.h"
#include <vector>

namespace csci3081 {

void csci3081::RoutingScheduler::ScheduleDelivery(
    csci3081::Package* package, csci3081::Customer* customer,
    const std::vector<entity_project::Entity*>& entities,
    const picojson::object& details
) {
  if(package->IsDynamic()) return;
  package->NotifyScheduled();
  Drone* to_dispatch = findAppropriateDrone(
      package, customer, entities);
  if (to_dispatch == nullptr) {
    std::cerr << "No drone was a available for this delivery! Try again later!" << std::endl;
    return;
  }
  package->SetDeliveryInfo(DeliveryInfo(details));
  to_dispatch->SetDeliveryPlan(package, customer, routemanager);
}

Drone* RoutingScheduler::findAppropriateDrone(
    Package* package, Customer* customer,
    const std::vector<entity_project::Entity*>& vector) {
  for (auto* entity : vector) {
    auto drone = entity->AsType<csci3081::Drone>();
    if (drone != nullptr && !drone->IsDelivering()) {
      return drone;
    }
  }
  return nullptr;
}

}  // namespace csci3081
