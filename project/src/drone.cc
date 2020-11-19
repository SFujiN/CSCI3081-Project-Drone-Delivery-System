//
// Created by alli on 11/12/20.
//

#include "src/drone.h"
#include "src/route_utils.h"

namespace csci3081 {

Drone::Drone(const picojson::object& initfrom) : Drone() {
  details_ = initfrom;

  name_ = JsonHelper::GetNoFail<std::string>(initfrom, "name", "default name");

  picojson::array arr;
  arr = JsonHelper::GetNoFail<picojson::array>(initfrom, "position", picojson::array{});
  for (int i = 0; i<3; ++i) {
    position_[i] = JsonHelper::ArrayGetNoFail<double>(arr, i, 0);
  }

  std::vector<float> default_direction{1,0,0};
  arr = JsonHelper::GetNoFail<picojson::array>(initfrom, "direction", picojson::array{});
  for (int i = 0; i<3; ++i) {
    direction_[i] = JsonHelper::ArrayGetNoFail<double>(arr, i, default_direction.at(i));
  }

  radius_ = JsonHelper::GetNoFail<double>(initfrom, "radius", 3);
}

void csci3081::Drone::Update(float dt) {
  // TODO Call FollowRoute and manage package lifecycles

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
  return 0;
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

}  // nmespace csci3081
