#ifndef STATISTICS_H_
#define STATISTICS_H_

#include <EntityProject/entity_observer.h>
#include <string>
#include <unordered_map>
#include <fstream>
#include "src/json_helper.h"

namespace csci3081 {

/**
 * @brief Statistics class
 *
 * Statistics class is a Singleton class and is an EntityObserver. 
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
    * Returns the same instance of the class each time.
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
   * Statistics destructor
   */
  ~Statistics();
  /**
    * Overrides the OnEvent(..) function of EntityObserver. It determines what
    * state an Entity is in, and it will collect stats or set boolean variables
    * that determine which stats need to be updated in other functions. 
    *
    * @param event picojson::value& reference detailing the state of an Entity
    * @param entity the Entity reference, used to get an Id for stats collecting
    */
  void OnEvent(const picojson::value& event, const entity_project::Entity& entity);
  /**
    * Called when there is a drone movement event
    *
    * @param event picojson::value& reference detailing the state of an Entity
    * @param entity the Entity reference, used to get an Id for stats collecting
    */
  void OnEventDroneMoving(const picojson::value& event, const entity_project::Entity& entity);
  /**
    * Called every update, used to keep track of in-simulation runtime
    *
    * @param dt float value that is used in incrementing simulation time
    */
  void Update(float dt); 
  /**
    * Called by every drone, used to keep track of drone times whether they
    * are idled or moving
    *
    * @param dt float value that is used in incrementing simulation time
    * @param droneID int value that holds the id of the Entity that needs stats update
    */
  void AddTime(float dt, int droneID);
  /**
    * Sets private boolean variables to false, to track drone status
    * and ensure drone is in correct state for stats collecting
    *
    * @param droneID int value that pertains to unique id of a drone
    */
  void SetFalse(int droneID);
  /**
    * Adds the distance of a new route to the drone distance accumulator
    *
    * @param dist float value that pertains to distance stat
    * @param droneID int value that pertains to unique id of a drone
    */
  void AddRouteDistance(float dist, int droneID); 
  /**
    * Adds the time a drone spends delivering to time accumulator
    * 
    * @param droneID int value that pertains to unique id of a drone
    * @param dt float value that pertains to incremental simulation time
    */
  void AddTimeDelivering(float dt, int droneID);
  /**
    * Writes drone_data to "data/DroneData.csv"
    * 
    */
  void WriteStats();
  /// alternative distance traveled function
  void AddRouteDist2(float dist, int droneID);

protected:
 /** @struct PackData
  *  @brief This structure contains members used for holding
  * Package related statistics that will later be written to a 
  * CSV file
  */
  struct PackData {
    float time_scheduled = 0;  ///< time_scheduled float contains the time it has been scheduled for
    float time_enroute = 0;  ///< time_enroute float contains the time is has been enroute
    float time_delivered = 0;  ///< time_deliverd float contains the time is has been delivered for
  };
 /** @struct DroneData
  *  @brief This structure contains members used for holding
  * Drone related statistics that will later be written to a 
  * CSV file
  */
  struct DroneData {
    float time_elapsed = 0;  ///< time_delivered float contains total elapsed time of it's existence
    float deliveries_made = 0;  ///< deliveries_made float numbers the total delivieries of a drone
    float time_moving = 0;  ///< time_moving float contains total time spent moving
    float time_delivering = 0;  ///< time_delivering float contains total time delivering
    float time_idle = 0;  ///< time_idle float contains total time idling
    float distance_traveled = 0;  ///< total distance traveled in simulation
    float distance_traveled2 = 0;  ///< total distance traveled in simulation
    bool is_idled = false;  ///< is_idled bool tracks if the drone is idled or not
    bool is_moving = false;  ///< is_moving bool tracks if the drone is moving or not
  };
  /// maps from the Entity id to their associated data
  std::unordered_map<int, PackData> package_data;  ///< For Package Entity statistics
  std::unordered_map<int, DroneData> drone_data;  ///< For Drone Entity statistics

  float simulation_time = 0;  ///< simulation_time float tracks total simulation time at the end
};

}  // namespace csci3081

#endif
