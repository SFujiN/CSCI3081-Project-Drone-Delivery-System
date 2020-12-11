#include <EntityProject/osm_graph_parser.h>
#include <EntityProject/project_settings.h>

#include <iostream>

#include "EntityProject/ANVIL/drone_delivery_system.h"
#include "gtest/gtest.h"
#include "src/customer.h"
#include "src/drone.h"
#include "src/json_helper.h"
#include "src/package.h"
#include "src/statistics.h"

namespace csci3081 {

using entity_project::DroneDeliverySystem;
using entity_project::Entity;

class TestStatistics : public csci3081::Statistics {
 public:
  //   std::unordered_map<int, PackData>GetPackageData() { return package_data;
  //   } std::unordered_map<int, DroneData>GetDroneData() { return drone_data; }
  //   float GetSimTime() { return simulation_time; }
  //   FRIENDTEST(StatisticsIntegration, PackageTest);
  //   FRIENDTEST(StatisticsIntegration, DroneTest);
};

class StatisticsIntegration : public ::testing::Test {
 protected:
  virtual void SetUp() {
    system = GetDroneDeliverySystem("default");
    entity_project::OSMGraphParser parser;
    const entity_project::IGraph* graph =
        parser.CreateGraph("data/umn.osm", "data/umn-height.csv");
    system->SetGraph(graph);

    p_obj["type"] = picojson::value("package");
    p_obj["name"] = picojson::value("TEST PACKAGE 1");
    p_obj["position"] = picojson::value(picojson::array(
        {picojson::value(0.0), picojson::value(0.0), picojson::value(0.0)}));
    package = system->CreateEntity(p_obj)->AsType<Package>();
    system->AddEntity(package);

    d_obj["type"] = picojson::value("drone");
    d_obj["name"] = picojson::value("TEST DRONE 1");
    d_obj["position"] = picojson::value(picojson::array(
        {picojson::value(0.0), picojson::value(0.0), picojson::value(0.0)}));
    drone = system->CreateEntity(d_obj)->AsType<Drone>();
    system->AddEntity(drone);
  }

  virtual void TearDown() { delete system; }

  DroneDeliverySystem* system;
  picojson::object p_obj;
  picojson::object d_obj;
  Package* package;
  Drone* drone;
};

TEST_F(StatisticsIntegration, SimulationTime) {
  EXPECT_NE(Statistics::GetInstance()->GetSimTime(), 0);
  Statistics::GetInstance()->Update(30);
  EXPECT_NE(Statistics::GetInstance()->GetSimTime(), 0);
}

TEST_F(StatisticsIntegration, PackageTest) {
  system->AddObserver(package, Statistics::GetInstance());
  EXPECT_FLOAT_EQ(Statistics::GetInstance()
                      ->GetPackageData()[package->GetId()]
                      .time_scheduled,
                  0.0);
  EXPECT_FLOAT_EQ(Statistics::GetInstance()
                      ->GetPackageData()[package->GetId()]
                      .time_enroute,
                  0.0);
  EXPECT_FLOAT_EQ(Statistics::GetInstance()
                      ->GetPackageData()[package->GetId()]
                      .time_delivered,
                  0.0);
}

TEST_F(StatisticsIntegration, DroneTest) {
  system->AddObserver(drone, Statistics::GetInstance());
  EXPECT_FLOAT_EQ(
      Statistics::GetInstance()->GetDroneData()[drone->GetId()].time_elapsed,
      0.0);
  EXPECT_FLOAT_EQ(
      Statistics::GetInstance()->GetDroneData()[drone->GetId()].deliveries_made,
      0.0);
  EXPECT_FLOAT_EQ(
      Statistics::GetInstance()->GetDroneData()[drone->GetId()].time_moving,
      0.0);
  EXPECT_FLOAT_EQ(
      Statistics::GetInstance()->GetDroneData()[drone->GetId()].time_delivering,
      0.0);
  EXPECT_FLOAT_EQ(
      Statistics::GetInstance()->GetDroneData()[drone->GetId()].time_idle, 0.0);
  EXPECT_FLOAT_EQ(Statistics::GetInstance()
                      ->GetDroneData()[drone->GetId()]
                      .distance_traveled,
                  0.0);
  EXPECT_FLOAT_EQ(Statistics::GetInstance()
                      ->GetDroneData()[drone->GetId()]
                      .distance_traveled2,
                  0.0);
  EXPECT_FALSE(
      Statistics::GetInstance()->GetDroneData()[drone->GetId()].is_idled);
  EXPECT_FALSE(
      Statistics::GetInstance()->GetDroneData()[drone->GetId()].is_moving);
}

}  // namespace csci3081
