#include "src/statistics.h"

namespace csci3081 {

Statistics* Statistics::instance = nullptr;

Statistics::Statistics() {
  // nothing yet
}

Statistics::~Statistics() {
  // nothing yet
}

void Statistics::OnEvent(const picojson::value& event, const entity_project::Entity& entity) {
  picojson::object eventobj;
  if (event.is<picojson::object>()) {
    eventobj = event.get<picojson::object>();
  } else { return; }

  std::string type = JsonHelper::GetNoFail<std::string>(eventobj, "type", "no type");
  std::string value = JsonHelper::GetNoFail<std::string>(eventobj, "value", "no value");
  //std::string name = entity.GetName();
  int id = entity.GetId();

  if (type == "notify") {
    if (value == "scheduled") {
      SetFalse();
      is_moving = true;
      // package was scheduled
    }
    if (value == "en route") {
      SetFalse();
      is_delivering = true;
      // package is enroute
    }
    if (value == "delivered") {
      SetFalse();
      // package was delivered
    }
    if (value == "idle") {
      SetFalse();
      is_idled = true;
      // drone is idle
    }
    if (value == "moving") {
      // drone is moving
      OnEventDroneMoving(event, entity);
    }
  }

}

void Statistics::OnEventDroneMoving(const picojson::value& event, const entity_project::Entity& entity) {
  // do things
}

void Statistics::AddTime(float dt, int droneID) {
  // std::cout << "Added " << dt << " time to Drone " << droneID << std::endl;
  time_elapsed += dt;
  if (is_delivering) {
    if (drone_data.find(droneID) != drone_data.end()) {
      drone_data[droneID].time_delivering += dt;
    } else {
      struct DroneData drone;
      drone_data[droneID] = drone;
      drone_data[droneID].time_delivering = 0;
      drone_data[droneID].time_delivering += dt;
    }

  }
}

void Statistics::SetFalse() {
  is_idled = false;
  is_moving = false;
  is_delivering = false;
}

void Statistics::AddCurrentRoute(float dist, int droneID) {
  
}

}  // namespace csci3081
