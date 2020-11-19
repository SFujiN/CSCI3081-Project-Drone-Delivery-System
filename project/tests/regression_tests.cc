#include "gtest/gtest.h"
#include "EntityProject/ANVIL/drone_delivery_system.h"
#include "EntityProject/ANVIL/drone.h"
#include "EntityProject/ANVIL/package.h"
#include "EntityProject/ANVIL/customer.h"
#include <EntityProject/project_settings.h>
#include "src/json_helper.h"


#include <iostream>

namespace csci3081 {

using entity_project::DroneDeliverySystem;
using entity_project::Entity;
using entity_project::Drone;
using entity_project::Package;
using entity_project::Customer;

class DroneSimRegTest : public ::testing::Test {
 protected:
  virtual void SetUp() {
    system = GetDroneDeliverySystem("default");
  }
  virtual void TearDown() {}

  DroneDeliverySystem* system;
  picojson::object obj;
  Entity* entity;
};

/*******************************************************************************
 * Test Cases
 ******************************************************************************/



TEST_F(DroneSimRegTest, EntityCreationRegression) {
  // no type provided
  entity = system->CreateEntity(obj);
  ASSERT_EQ(entity, nullptr);

  // incorrect type provide by json
  obj["type"] = picojson::value(double(45));
  entity = system->CreateEntity(obj);
  ASSERT_EQ(entity, nullptr);

  // only type given
  //Drone
  obj["type"] = picojson::value("drone");

  entity = system->CreateEntity(obj);
  ASSERT_NE(entity, nullptr);
  Drone* drone = entity->AsType<Drone>();
  ASSERT_NE(drone, nullptr);
  EXPECT_FLOAT_EQ(drone->GetPosition()[0],0);
  EXPECT_FLOAT_EQ(drone->GetPosition()[1],0);
  EXPECT_FLOAT_EQ(drone->GetPosition()[2],0);
  EXPECT_FLOAT_EQ(drone->GetDirection()[0],1);
  EXPECT_FLOAT_EQ(drone->GetDirection()[1],0);
  EXPECT_FLOAT_EQ(drone->GetDirection()[2],0);
  EXPECT_NE(drone->GetRadius(),0);

  //Package
  obj["type"] = picojson::value("package");

  entity = system->CreateEntity(obj);
  ASSERT_NE(entity, nullptr);
  Package* package = entity->AsType<Package>();
  ASSERT_NE(package, nullptr);
  EXPECT_FLOAT_EQ(package->GetPosition()[0],0);
  EXPECT_FLOAT_EQ(package->GetPosition()[1],0);
  EXPECT_FLOAT_EQ(package->GetPosition()[2],0);
  EXPECT_FLOAT_EQ(package->GetDirection()[0],1);
  EXPECT_FLOAT_EQ(package->GetDirection()[1],0);
  EXPECT_FLOAT_EQ(package->GetDirection()[2],0);
  EXPECT_NE(package->GetRadius(),0);

  //Customer
  obj["type"] = picojson::value("customer");

  entity = system->CreateEntity(obj);
  ASSERT_NE(entity, nullptr);
  Customer* customer = entity->AsType<Customer>();
  ASSERT_NE(customer, nullptr);
  EXPECT_FLOAT_EQ(customer->GetPosition()[0],0);
  EXPECT_FLOAT_EQ(customer->GetPosition()[1],0);
  EXPECT_FLOAT_EQ(customer->GetPosition()[2],0);
  EXPECT_FLOAT_EQ(customer->GetDirection()[0],1);
  EXPECT_FLOAT_EQ(customer->GetDirection()[1],0);
  EXPECT_FLOAT_EQ(customer->GetDirection()[2],0);
  EXPECT_NE(customer->GetRadius(),0);

  // All attributes given
  // Drone
  obj["type"] = picojson::value("drone");
  obj["position"] = picojson::value(picojson::array(
   {picojson::value(1.0),
   picojson::value(2.0),
   picojson::value(3.0)} ));
  obj["direction"] = picojson::value(picojson::array(
   {picojson::value(-1.0),
   picojson::value(-2.0),
   picojson::value(-3.0)} ));
  obj["radius"] = picojson::value(4.9);

  entity = system->CreateEntity(obj);
  ASSERT_NE(entity, nullptr);
  delete drone;
  drone = entity->AsType<Drone>();
  ASSERT_NE(drone, nullptr);
  EXPECT_FLOAT_EQ(drone->GetPosition()[0],1);
  EXPECT_FLOAT_EQ(drone->GetPosition()[1],2);
  EXPECT_FLOAT_EQ(drone->GetPosition()[2],3);
  EXPECT_FLOAT_EQ(drone->GetDirection()[0],-1);
  EXPECT_FLOAT_EQ(drone->GetDirection()[1],-2);
  EXPECT_FLOAT_EQ(drone->GetDirection()[2],-3);
  EXPECT_FLOAT_EQ(drone->GetRadius(),4.9);

  //Package
  obj["type"] = picojson::value("package");
  obj["position"] = picojson::value(picojson::array(
    {picojson::value(1.0),
    picojson::value(2.0),
    picojson::value(3.0)} ));
  obj["direction"] = picojson::value(picojson::array(
    {picojson::value(-1.0),
    picojson::value(-2.0),
    picojson::value(-3.0)} ));
  obj["radius"] = picojson::value(4.9);

  entity = system->CreateEntity(obj);
  ASSERT_NE(entity, nullptr);
  delete package;
  package = entity->AsType<Package>();
  ASSERT_NE(package, nullptr);
  EXPECT_FLOAT_EQ(package->GetPosition()[0],1);
  EXPECT_FLOAT_EQ(package->GetPosition()[1],2);
  EXPECT_FLOAT_EQ(package->GetPosition()[2],3);
  EXPECT_FLOAT_EQ(package->GetDirection()[0],-1);
  EXPECT_FLOAT_EQ(package->GetDirection()[1],-2);
  EXPECT_FLOAT_EQ(package->GetDirection()[2],-3);
  EXPECT_FLOAT_EQ(package->GetRadius(),4.9);

  //Customer
  obj["type"] = picojson::value("customer");
  obj["position"] = picojson::value(picojson::array(
    {picojson::value(1.0),
    picojson::value(2.0),
    picojson::value(3.0)} ));
  obj["direction"] = picojson::value(picojson::array(
    {picojson::value(-1.0),
    picojson::value(-2.0),
    picojson::value(-3.0)} ));
  obj["radius"] = picojson::value(4.9);

  entity = system->CreateEntity(obj);
  ASSERT_NE(entity, nullptr);
  delete customer;
  customer = entity->AsType<Customer>();
  ASSERT_NE(customer, nullptr);
  EXPECT_FLOAT_EQ(customer->GetPosition()[0],1);
  EXPECT_FLOAT_EQ(customer->GetPosition()[1],2);
  EXPECT_FLOAT_EQ(customer->GetPosition()[2],3);
  EXPECT_FLOAT_EQ(customer->GetDirection()[0],-1);
  EXPECT_FLOAT_EQ(customer->GetDirection()[1],-2);
  EXPECT_FLOAT_EQ(customer->GetDirection()[2],-3);
  EXPECT_FLOAT_EQ(customer->GetRadius(),4.9);
}

TEST_F(DroneSimRegTest, AddEntityToSimulationRegression) {
  picojson::object obj;
  obj["type"] = picojson::value("drone");
  entity = system->CreateEntity(obj);
  ASSERT_NE(entity, nullptr);
  Drone* drone = entity->AsType<Drone>();
  ASSERT_NE(drone, nullptr);
  ASSERT_EQ(system->GetEntities().size(), 0);
  system->AddEntity(drone);
  ASSERT_EQ(system->GetEntities().size(), 1);
  ASSERT_EQ(picojson::value(system->GetEntities()[0]->GetDetails()).serialize(),
      picojson::value(obj).serialize());

  obj["type"] = picojson::value("package");
  entity = system->CreateEntity(obj);
  ASSERT_NE(entity, nullptr);
  Package* package = entity->AsType<Package>();
  ASSERT_NE(package, nullptr);
  ASSERT_EQ(system->GetEntities().size(), 1);
  system->AddEntity(package);
  ASSERT_EQ(system->GetEntities().size(), 2);
  ASSERT_EQ(picojson::value(system->GetEntities()[1]->GetDetails()).serialize(),
      picojson::value(obj).serialize());

  obj["type"] = picojson::value("customer");
  entity = system->CreateEntity(obj);
  ASSERT_NE(entity, nullptr);
  Customer* customer = entity->AsType<Customer>();
  ASSERT_NE(customer, nullptr);
  ASSERT_EQ(system->GetEntities().size(), 2);
  system->AddEntity(customer);
  ASSERT_EQ(system->GetEntities().size(), 3);
  ASSERT_EQ(picojson::value(system->GetEntities()[2]->GetDetails()).serialize(),
      picojson::value(obj).serialize());
}

TEST_F(DroneSimRegTest, ScheduleDeliveryRegression) {
  std::vector<float> drone_start_position{100.0, 2.0, 3.0};
  picojson::object droneobj;
  picojson::object custobj;
  picojson::object packobj;
  picojson::object dummyobj;
  int steps;

  droneobj["type"] = picojson::value("drone");
  custobj["type"] = picojson::value("customer");
  packobj["type"] = picojson::value("package");

  droneobj["position"] = picojson::value(picojson::array(
    {picojson::value(drone_start_position[0]),
    picojson::value(drone_start_position[1]),
    picojson::value(drone_start_position[2])} ));
  packobj["position"] = picojson::value(picojson::array(
    {picojson::value(1.0),
    picojson::value(200.0),
    picojson::value(3.0)} ));
  custobj["position"] = picojson::value(picojson::array(
    {picojson::value(1.0),
    picojson::value(2.0),
    picojson::value(300.0)} ));

  entity = system->CreateEntity(droneobj);
  Drone* drone = entity->AsType<Drone>();
  entity = system->CreateEntity(custobj);
  Customer* customer = entity->AsType<Customer>();
  entity = system->CreateEntity(packobj);
  Package* package = entity->AsType<Package>();
  system->AddEntity(drone);
  system->AddEntity(customer);
  system->AddEntity(package);

  // make sure drone is at its starting position
  for (int i = 0; i < 3; i++) {
    ASSERT_FLOAT_EQ(drone->GetPosition()[i],drone_start_position[i]);
  }

  steps = 10;
  for (int i = 0; i < steps; i++) {
    system->Update(0.1);
  }

  // make sure drone has not moved
  for (int i = 0; i < 3; i++) {
    EXPECT_FLOAT_EQ(drone->GetPosition()[i],drone_start_position[i]);
  }

  system->ScheduleDelivery(package,customer,dummyobj);
  steps = 50;
  for (int i = 0; i < steps; i++) {
    system->Update(0.1);
  }

  // check that drone is moving in response to ScheduleDelivery
  for (int i = 0; i < 3; i++) {
    EXPECT_NE(drone->GetPosition()[i],drone_start_position[i]);
  }
}

} // namespace csci3081
