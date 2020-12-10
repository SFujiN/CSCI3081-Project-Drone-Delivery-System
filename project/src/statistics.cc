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
      // package was scheduled
    }
    if (value == "en route") {
      // package is enroute
    }
    if (value == "delivered") {
      // package was delivered
    }
    if (value == "idle") {
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
}

void Statistics::SetFalse() {
  is_idled = false;
  is_moving = false;
  is_delivering = false;
}

}  // namespace csci3081
