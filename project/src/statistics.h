#ifndef STATISTICS_H_
#define STATISTICS_H_

#include <EntityProject/entity_observer.h>

#include <fstream>
#include <string>
#include <unordered_map>

#include "src/json_helper.h"

namespace csci3081 {

/**
 * @brief Statistics class
 *
 * This class
 */
class Statistics : public entity_project::EntityObserver {
 private:
  /// private constructor because this is Singleton
  Statistics();
  /// single instance of this class
  static Statistics* instance;

 public:
  /// returns the same instance each time
  static Statistics* GetInstance() {
    if (!instance) {
      instance = new Statistics;
    }
    return instance;
  }
  /// Destructor
  ~Statistics();
  /// called when an event occurs
  void OnEvent(const picojson::value& event,
               const entity_project::Entity& entity);
  /// called when a drone movement event is received
  void OnEventDroneMoving(const picojson::value& event,
                          const entity_project::Entity& entity);
  /// called every update, used to keep track of in-simulation runtime
  void Update(float dt);
  /// called by every drone, used to keep track of drone times
  void AddTime(float dt, int droneID);
  /// sets private boolean variables to false, to track drone status
  void SetFalse(int droneID);
  /// adds the distance of a new route to the drone distance accumulator
  void AddRouteDistance(float dist, int droneID);
  /// adds the time a drone spends delivering to time accumulator
  void AddTimeDelivering(float dt, int droneID);
  /// writes drone_data to "data/DroneData.csv"
  void WriteStats();
  /// alternative distance traveled function
  void AddRouteDist2(float dist, int droneID);

 protected:
  struct PackData {
    float time_scheduled = 0;
    float time_enroute = 0;
    float time_delivered = 0;
  };
  struct DroneData {
    float time_elapsed = 0;
    float deliveries_made = 0;
    float time_moving = 0;
    float time_delivering = 0;
    float time_idle = 0;
    float distance_traveled = 0;
    float distance_traveled2 = 0;
    bool is_idled = false;
    bool is_moving = false;
  };
  /// maps from the Entity id to their associated data
  std::unordered_map<int, PackData> package_data;
  std::unordered_map<int, DroneData> drone_data;

  float simulation_time = 0;

 public:
  std::unordered_map<int, PackData> GetPackageData() { return package_data; }
  std::unordered_map<int, DroneData> GetDroneData() { return drone_data; }
  float GetSimTime() { return simulation_time; }
};

}  // namespace csci3081

#endif
