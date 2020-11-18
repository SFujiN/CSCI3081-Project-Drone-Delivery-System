//
// Created by alli on 11/12/20.
//

#include "src/drone.h"
#include "src/route_utils.h"

namespace csci3081 {

Drone::Drone(const picojson::object& initfrom) : Drone() {
  details_ = initfrom;
  if (details_.find("position") != details_.end()) {
    int len = details_["position"].get<picojson::array>().size();
    for (int i = 0; i < len && i < 3; i++) {
      position_[i] = details_["position"].get<picojson::array>()[i].get<double>();
    }
  }
}

void csci3081::Drone::Update(float dt) {
  // TODO Call FollowRoute and manage package lifecycles
  FollowRoute(dt);
  /* old code:
    if (!IsDispatched()) return;
    bool completed = FollowRoute(dt);
    CarryPackage();
    if (!completed) return;
    if (!hasPickedPackage) {
      hasPickedPackage = true;
      RouteTo(destination);
    } else {
      hasPickedPackage = false;
      destination = nullptr;
      pickup = nullptr;
    }
   */
}

bool Drone::FollowRoute(float dt) {
  auto pos = GetVecPos();
  float remainingDistance = GetCurrentSpeed() * dt;
  while (remainingDistance > 0) {
    if (route.empty()) {
      SetVecPos(pos);
      return true;
    }

    auto point = RouteManager::AsVec(route.front());
    float dist = pos.distanceTo(point);
    if (dist < remainingDistance) {
      pos = point;
      remainingDistance -= dist;
      route.pop();
    } else {
      pos = pos + (pos.directionTo(point) * remainingDistance);
      remainingDistance = 0;
    }
  }
  SetVecPos(pos);
  return false;
}

Vector3d csci3081::Drone::GetVecPos() {
  return {position_[0], position_[1], position_[2]};
}

void csci3081::Drone::SetVecPos(Vector3d vec) {
  position_[0] = vec.x;
  position_[1] = vec.y;
  position_[2] = vec.z;
}

const std::vector<std::string>& Drone::GetCurrentRoute() const {
  return *((std::vector<std::string>*) nullptr);
}

float csci3081::Drone::GetRemainingBattery() const {
  // TODO
  return 0;
}

float csci3081::Drone::GetCurrentSpeed() const {
  // TODO
  return 30;
}

float csci3081::Drone::GetMaxCapacity() const {
  // TODO
  return 0;
}

float csci3081::Drone::GetRemainingCapacity() const {
  // TODO
  return 0;
}

float csci3081::Drone::GetBaseAcceleration() const {
  // TODO
  return 0;
}

void Drone::SetDeliveryPlan(csci3081::Package* package, csci3081::Customer* customer, RouteManager rm) {
  package->SetDestination(customer);
  packages.push_back(package);
  routemanager = rm;
  RecalculateRoute();
}

void Drone::RecalculateRoute() {
  if (packages.empty()) { return; }
  if (packages.front()->PickedUp()) {
    RouteTo(packages.front()->GetDestination());
  } else {
    RouteTo(packages.front());
  }
}
void Drone::RouteTo(entity_project::Entity* dest) {
  SetRoute(routemanager.GetRoute(
      routemanager.GetRoutePointFor(this),
      routemanager.GetRoutePointFor(dest)));
}
void Drone::SetRoute(std::vector<entity_project::IGraphNode*> newRoute) {
  std::queue<entity_project::IGraphNode*> newRouteQueue;
  for (auto node : newRoute) {
    newRouteQueue.push(node);
    std::cout << node->GetPosition()[0] << ' '<< node->GetPosition()[1] << ' '<< node->GetPosition()[2] << std::endl;
  }
  route = newRouteQueue;
  // TODO
}

}  // nmespace csci3081
