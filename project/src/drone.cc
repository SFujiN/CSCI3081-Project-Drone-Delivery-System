//
// Created by alli on 11/12/20.
//

#include "src/drone.h"
//#include "src/route_utils.h"

namespace csci3081 {

Drone::Drone(const picojson::object& initfrom) : Drone() {
  details_ = initfrom;

  droneObservable.SetEntity(this);
  NotifyIdled();

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
  if (details_.find("model") != details_.end()) {
    modelNum = details_["model"].get<std::string>();
  } else {
    modelNum = "Q-36-01";
  }
  // SetDroneSpecs(models_);
  SetDroneSpecs(csci3081::createDroneModelList("data/planet-x.csv"));
  //std::cout << "\ndroneList: \n" << spec_ << "\n";

  radius_ = JsonHelper::GetNoFail<double>(initfrom, "radius", 3);
}

void csci3081::Drone::Update(float dt) {
  // TODO Call FollowRoute and manage package lifecycles
  if (!IsDelivering()) return;
  bool completed = FollowRoute(dt);
  CarryPackages();
  if (!completed) return;
  if (!hasPickedUpPackage_) {
    hasPickedUpPackage_ = true;
    CarryPackages();
    package->NotifyPickedUp();
    RouteTo(package->GetDestination());
  } else {
    package->NotifyDelivered();
    NotifyIdled();
    hasPickedUpPackage_ = false;
    package = nullptr;
  }
  
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
  return route_by_node_name;
}

float csci3081::Drone::GetRemainingBattery() const {
  // TODO
  return battery;
}

float csci3081::Drone::GetCurrentSpeed() const {
  // TODO
  return speed;
}

float csci3081::Drone::GetMaxCapacity() const {
  // TODO
  return spec_.weight_cap_;
}

float csci3081::Drone::GetRemainingCapacity() const {
  // TODO
  return spec_.weight_cap_ - currLoadWeight;
}

float csci3081::Drone::GetBaseAcceleration() const {
  // TODO
  return spec_.base_acc_;
}

void Drone::SetDeliveryPlan(csci3081::Package* package_, csci3081::Customer* customer, RouteManager rm) {
  package = package_;
  package->SetDestination(customer);
  routemanager = rm;
  RouteTo(package);
}

void Drone::RouteTo(entity_project::Entity* dest) {
  SetRoute(routemanager.GetRoute(
      routemanager.GetRoutePointFor(this),
      routemanager.GetRoutePointFor(dest)));
}
void Drone::SetRoute(std::vector<entity_project::IGraphNode*> newRoute) {
  std::queue<entity_project::IGraphNode*> newRouteQueue;
  route_by_node_name.clear();
  for (auto node : newRoute) {
    newRouteQueue.push(node);
    route_by_node_name.push_back(node->GetName());
    std::cout << node->GetPosition()[0] << ' '<< node->GetPosition()[1] << ' '<< node->GetPosition()[2] << std::endl;
  }
  route = newRouteQueue;
  NotifyMoving();
}

void Drone::CarryPackages() {
  if (hasPickedUpPackage_) {
    std::cout << "movin the package" << std::endl;
    package->SetVecPos(this->GetVecPos() - Vector3d(0, 0.5, 0));
  }
}

void Drone::UpdatePackages() {
    if (/*package.AtDestination()*/ false) {
      // Drop off package
      package->NotifyDelivered();
    } else if (/*Touching(package)*/ true) {
      package->DronePickUp();
    }
}

void csci3081::Drone::SetDroneSpecs(const std::unordered_map<std::string,csci3081::droneSpecs> list) {
    if (csci3081::isModelListed(list, modelNum)) {
      spec_ = list.at(modelNum);
    }

    battery = spec_.base_bat_cap_;
}

void Drone::NotifyIdled() {
  picojson::object obj;
  obj["type"] = picojson::value("notify");
  obj["value"] = picojson::value("idle");
  const picojson::value& event = picojson::value(obj);
  droneObservable.Notify(event);
}

void Drone::NotifyMoving() {
  picojson::object obj;
  obj["type"] = picojson::value("notify");
  obj["value"] = picojson::value("moving");
  
  std::queue<entity_project::IGraphNode*> routeCopy = route;
  
  std::vector<std::vector<float>> arr;
  while (!routeCopy.empty()) {
    std::vector<float> temp = routeCopy.front()->GetPosition();
    arr.push_back(temp);
    routeCopy.pop();
  }
  obj["path"] = JsonHelper::EncodeArray(arr);
  
  const picojson::value& event = picojson::value(obj);
  
  droneObservable.Notify(event);
}

}  // namespace csci3081
