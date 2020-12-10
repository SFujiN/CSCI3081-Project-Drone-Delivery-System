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
      SetFalse(id);
      // drone is idle
      // set a boolean value here to be used in Update()
      drone_data[id].is_idled = true;
      drone_data[id].deliveries_made += 1;
    }
    if (value == "moving") {
      SetFalse(id);
      // drone is moving
      drone_data[id].is_moving = true;
      OnEventDroneMoving(event, entity);
    }
  }
}

void Statistics::OnEventDroneMoving(const picojson::value& event, const entity_project::Entity& entity) {
  // do things
}

void Statistics::Update(float dt) {
  simulation_time += dt;
}

void Statistics::AddTime(float dt, int droneID) {
  // std::cout << "Added " << dt << " time to Drone " << droneID << std::endl;
  drone_data[droneID].time_elapsed += dt;

  if (drone_data[droneID].is_idled) {
    drone_data[droneID].time_idle += dt;
    // Debug: std::cout << drone_data[droneID].time_idle << std::endl;
  }
  if (drone_data[droneID].is_moving) {
    drone_data[droneID].time_moving += dt;
    // Debug: std::cout << drone_data[droneID].time_moving << std::endl;
  }
}

void Statistics::SetFalse(int droneID) {
  drone_data[droneID].is_idled = false;
  drone_data[droneID].is_moving = false;
}

void Statistics::AddRouteDistance(float dist, int droneID) {
  drone_data[droneID].distance_traveled += dist;
  std::cout << "drone_data's distance_traveled is " <<
    drone_data[droneID].distance_traveled << " for drone " << droneID << std::endl;
}

void Statistics::AddTimeDelivering(float dt, int droneID) {
  drone_data[droneID].time_delivering += dt;
  std::cout << "Adding dt: " << dt << std::endl;
}


}  // namespace csci3081
