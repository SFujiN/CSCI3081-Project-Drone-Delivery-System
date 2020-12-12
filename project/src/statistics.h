#ifndef STATISTICS_H_
#define STATISTICS_H_

#include <EntityProject/entity_observer.h>

#include <fstream>
#include <string>
#include <unordered_map>

#include "src/json_helper.h"

namespace csci3081 {

/**
 * @brief Statistics class, which tracks drone statistics
 *
 * Statistics class is a Singleton class and is an EntityObserver.
 * Statistics implements the strategy to keep track of useful information on
 * drones. This is done by mapping individual drones by ID to stats:\n
 * time_elapsed, total time elapsed since drone was created\n
 * deliveries_made, deliveries made by drone\n
 * time_moving, drone's total time spent moving\n
 * time_delivering, drone's time spent delivering\n
 * time_idle, drone's time idle\n
 * planned_distance, total planned distance of drone's route\n
 * traveled_distance, total distance traveled by the drone\n
 */
class Statistics : public entity_project::EntityObserver {
 private:
  /**
   * @brief Default private constructor
   * @details Constructor is private to avoid more than
   * one instance
   */
  Statistics();
  static Statistics* instance;  ///< single instance of this class

 public:
  /**
   * @brief Returns the same instance of the class each time.
   *
   * @return instance a private static member instance of Statistics
   */
  static Statistics* GetInstance() {
    if (!instance) {
      instance = new Statistics;
    }
    return instance;
  }
  /**
   * @brief Statistics destructor
   */
  ~Statistics();
  /**
   * @brief Determines what statistics to update given state of an Entity
   *
   * @param event picojson::value& reference detailing the state of an Entity
   * @param entity the Entity reference, used to get an Id for stats collecting
   *
   * @post Overrides the OnEvent(..) function of EntityObserver. It determines
   * what state an Entity is in, and it will collect stats or set boolean
   * variables that determine which stats need to be updated in other functions.
   */
  void OnEvent(const picojson::value& event,
               const entity_project::Entity& entity);
  /**
   * @brief Called when there is a drone movement event
   *
   * @param event picojson::value& reference detailing the state of an Entity
   * @param entity the Entity reference, used to get an Id for stats collecting
   *
   * @post Will collect stats from the a Drone movement state
   */
  void OnEventDroneMoving(const picojson::value& event,
                          const entity_project::Entity& entity);
  /**
   * @brief Called every update, used to keep track of in-simulation runtime
   *
   * @param dt float value that is used in incrementing simulation time
   *
   * @post Updates simulation_time incrementally
   */
  void Update(float dt);
  /**
   * @brief Updates time statistics for unique Drone
   *
   * Called by every drone, used to keep track of drone times whether they
   * are idled or moving
   *
   * @param dt float value that is used in incrementing simulation time
   * @param droneID int value that holds the id of the Entity that needs stats
   * update
   *
   * @post Updates a specific time based statisitic for a unique drone
   */
  void AddTime(float dt, int droneID);
  /**
   * @brief Manages Drone statistic update state
   *
   * @param droneID int value that pertains to unique id of a drone
   *
   * @post Sets private boolean variables to false, to track drone status
   * and ensure drone is in correct state for stats collecting
   */
  void SetFalse(int droneID);
  /**
   * @brief Adds the entire distance of a new route to the drone distance
   * accumulator
   *
   * @param dist float value that pertains to distance stat
   * @param droneID int value that pertains to unique id of a drone
   *
   * @post Updates planned_distance statistic of DroneData using dist
   */
  void AddPlannedRouteDistance(float dist, int droneID);
  /**
   * @brief Adds the time a drone spends delivering to time accumulator
   *
   * @param droneID int value that pertains to unique id of a drone
   * @param dt float value that pertains to incremental simulation time
   */
  void AddTimeDelivering(float dt, int droneID);
  /**
   * @brief Writes Statistics to an outfile
   *
   * @post Writes simulation statistics to data/DroneData.csv outfile.
   * Runs at the end of the simulation.
   */
  void WriteStats();
  /**
   * @brief Used to keep track of drone traveled distance per Update
   *
   * @param droneID int value that pertains to unique id of a drone
   * @param dt float value that pertains to incremental simulation time
   *
   * @post Updates traveled_distance statistic of DroneData using dist
   */
  void AddDroneTraveledDistance(float dist, int droneID);

 protected:
  /**
   *  @struct PackData
   *
   *  @brief This structure contains members used for holding
   * Package related statistics that will later be written to a
   * CSV file
   */
  struct PackData {
    float time_scheduled = 0;  ///< time_scheduled float contains the time it
                               ///< has been scheduled for
    float time_enroute =
        0;  ///< time_enroute float contains the time is has been enroute
    float time_delivered =
        0;  ///< time_deliverd float contains the time is has been delivered for
  };
  /**
   *  @struct DroneData
   *
   *  @brief This structure contains members used for holding
   * Drone related statistics that will later be written to a
   * CSV file
   */
  struct DroneData {
    float time_elapsed = 0;  ///< time_delivered float contains total elapsed
                             ///< time of it's existence
    float deliveries_made =
        0;  ///< deliveries_made float numbers the total delivieries of a drone
    float time_moving =
        0;  ///< time_moving float contains total time spent moving
    float time_delivering =
        0;  ///< time_delivering float contains total time delivering
    float time_idle = 0;         ///< time_idle float contains total time idling
    float planned_distance = 0;  ///< total route lengths planned by drone
    float traveled_distance =
        0;  ///< total distance traveled in simulation by drone
    bool is_idled =
        false;  ///< is_idled bool tracks if the drone is idled or not
    bool is_moving =
        false;  ///< is_moving bool tracks if the drone is moving or not
  };
  /// maps from the Package id to its associated data
  std::unordered_map<int, PackData> package_data;
  /// maps from the Drone id to its associated data
  std::unordered_map<int, DroneData> drone_data;

  /// simulation_time float tracks total simulation time at the end
  float simulation_time = 0;

 public:
  /**
   * @brief Getter for package_data
   *
   * @return protected package_data member variable
   */
  std::unordered_map<int, PackData> GetPackageData() { return package_data; }
  /**
   * @brief Getter for drone_data
   *
   * @return protected drone_data member variable
   */
  std::unordered_map<int, DroneData> GetDroneData() { return drone_data; }
  /**
   * @brief Getter for simulation_time
   *
   * @return float simulation_time
   */
  float GetSimTime() { return simulation_time; }
};

}  // namespace csci3081

#endif
