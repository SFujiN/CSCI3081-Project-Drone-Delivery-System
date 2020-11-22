#include "gtest/gtest.h"
#include "EntityProject/ANVIL/drone_delivery_system.h"
#include "src/drone.h"
#include "src/package.h"
#include "src/customer.h"
#include <EntityProject/project_settings.h>
#include "src/json_helper.h"
#include <EntityProject/osm_graph_parser.h>
#include "src/test_observer.h"

#include <iostream>

namespace csci3081 {

using entity_project::DroneDeliverySystem;
using entity_project::Entity;

class ObservableDroneIntegration : public ::testing::Test {
 protected:
  virtual void SetUp() {
    system = GetDroneDeliverySystem("default");
    // Create and set the graph
    entity_project::OSMGraphParser parser;
    const entity_project::IGraph* graph = parser.CreateGraph("data/umn.osm", "data/umn-height.csv");
    system->SetGraph(graph);

    obj["type"] = picojson::value("package");
    obj["name"] = picojson::value("TEST PACKAGE 1");
    obj["position"] = picojson::value(picojson::array(
     {picojson::value(505.303),
     picojson::value(264.0),
     picojson::value(-283.616)} ));
    package = system->CreateEntity(obj)->AsType<Package>();
    system->AddEntity(package);

    obj["type"] = picojson::value("drone");
    obj["name"] = picojson::value("TEST DRONE 1");
    obj["position"] = picojson::value(picojson::array(
     {picojson::value(505.303),
     picojson::value(264.0),
     picojson::value(-283.616)} ));
    drone = system->CreateEntity(obj)->AsType<Drone>();
    system->AddEntity(drone);

    obj["type"] = picojson::value("customer");
    obj["name"] = picojson::value("TEST CUSTOMER 1");
    obj["position"] = picojson::value(picojson::array(
     {picojson::value(505.303),
     picojson::value(264.0),
     picojson::value(-283.616)} ));
    customer = system->CreateEntity(obj)->AsType<Customer>();
    system->AddEntity(customer);

    obs = new TestObserver();
    system->AddObserver(package,obs);
  }
  virtual void TearDown() {
    delete obs;
    delete system;
  }

  DroneDeliverySystem* system;
  picojson::object obj;
  Package* package;
  Drone* drone;
  Customer* customer;
  TestObserver* obs;
};

/*******************************************************************************
 * Test Cases
 ******************************************************************************/



TEST_F(ObservableDroneIntegration, PackageObservationWithDrone) {
  picojson::object dummyobj;
  system->ScheduleDelivery(package,customer,dummyobj);
  EXPECT_TRUE(obs->notifiedScheduled);
  EXPECT_FALSE(obs->notifiedPickedUp);
  EXPECT_FALSE(obs->notifiedDelivered);
  EXPECT_EQ(obs->name,"TEST PACKAGE 1");

  for (int i = 0; i < 5; i++) { system->Update(0.2); }
  EXPECT_TRUE(obs->notifiedScheduled);
  EXPECT_TRUE(obs->notifiedPickedUp);
  EXPECT_TRUE(obs->notifiedDelivered);
  EXPECT_EQ(obs->name,"TEST PACKAGE 1");
}

} // namespace csci3081
