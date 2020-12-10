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
  // std::string name = entity.GetName();
  int id = entity.GetId();
  is_idled = false;
  is_moving = false;

  if (type == "notify") {
    if (value == "scheduled") {
      // package was scheduled
      is_moving = true;
    }
    if (value == "en route") {
      // package is enroute
    }
    if (value == "delivered") {
      // package was delivered
    }
    if (value == "idle") {
      // drone is idle
      // set a boolean value here to be used in Update()
      is_idled = true;
    }
    if (value == "moving") {
      // drone is moving
      is_moving = true;
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

  if (is_idled) {
    // drone_data[id].time_idle += dt;
    std::cout << "IS IDLED BEING ADDED" << std::endl;
  } 
  if (is_moving) {
    // drone_data[id].time_moving += dt;
    std::cout << "IS MOVING BEING ADDED" << std::endl;
  }
}

void Statistics::SetFalse() {
  is_idled = false;
  is_moving = false;
  is_delivering = false;
}

}  // namespace csci3081
