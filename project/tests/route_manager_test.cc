#include "gtest/gtest.h"
#include "src/route_utils.h"
#include <EntityProject/project_settings.h>

#include <iostream>

namespace csci3081 {

class RouteManagerTest : public ::testing::Test {
 protected:
  virtual void SetUp() {}
  virtual void TearDown() {}

};

class TestGraph : public entity_project::IGraph {
public:
  const entity_project::IGraphNode* GetNode(const std::string& name) const override {
    return nodesmap.at(name);
  }
  const std::vector<entity_project::IGraphNode*>& GetNodes() const override {
    return nodesvec;
  }
  void AddNode(entity_project::IGraphNode* node) {
    nodesvec.push_back(node);
    nodesmap[node->GetName()] = node;
  }
  void AddNodes(std::vector<entity_project::IGraphNode*> nodes) {
    for (auto i = nodes.begin(); i != nodes.end(); ++i) {
      AddNode(*i);
    }
  }
private:
  std::unordered_map<std::string,entity_project::IGraphNode*> nodesmap;
  std::vector<entity_project::IGraphNode*> nodesvec;
};

class TestNode : public entity_project::IGraphNode {
public:
  TestNode(std::string newName, float x, float y, float z) {
    name = newName;
    position = {x,y,z};
  }
  const std::string& GetName() const override {return name;}
  const std::vector<entity_project::IGraphNode*>& GetNeighbors() const override {return neighbors;}
  const std::vector<float> GetPosition() const override {return position;}
  void SetPosition(float x, float y, float z) {position = {x,y,z};}
  void AddNeighbor(entity_project::IGraphNode* node) {neighbors.push_back(node);}
  void SetNeighbors(std::vector<entity_project::IGraphNode*> nodes) {neighbors = nodes;}
private:
  std::string name;
  std::vector<float> position;
  std::vector<entity_project::IGraphNode*> neighbors;
};

float RouteLength(std::vector<entity_project::IGraphNode*> route) {
  RouteManager rm;
  float acc = 0;
  for( auto i = route.begin() + 1; i != route.end(); ++i ) {
    acc += rm.GetRouteDistanceBetween(*i, *(i-1));
  }
  return acc;
}

/*******************************************************************************
 * Test Cases
 ******************************************************************************/

TEST_F(RouteManagerTest, RouteDistanceBetween) {
  RouteManager rm;
  TestNode a("A", 0,0,0);
  TestNode b("B", 0,0,0);

  ASSERT_FLOAT_EQ(rm.GetRouteDistanceBetween(&a,&b),0);

  a.SetPosition(1,4,8);
  b.SetPosition(0,0,0);
  ASSERT_FLOAT_EQ(rm.GetRouteDistanceBetween(&a,&b),9);

  a.SetPosition(0,0,0);
  b.SetPosition(-1,4,8);
  ASSERT_FLOAT_EQ(rm.GetRouteDistanceBetween(&a,&b),9);

  a.SetPosition(2,-1,-5);
  b.SetPosition(2-14,-1+3,-5-18);
  ASSERT_FLOAT_EQ(rm.GetRouteDistanceBetween(&a,&b),23);

  a.SetPosition(-49.32,32.515,-60.005);
  b.SetPosition(-49.32+30,32.515-240,-60.005+160);
  ASSERT_FLOAT_EQ(rm.GetRouteDistanceBetween(&a,&b),290);
}

TEST_F(RouteManagerTest, BasicRoute) {
  RouteManager rm;
  TestNode n0("0", 0,0,0);
  TestNode n1("1", 1,0,0);
  TestNode n2("2", 2,0,0);
  TestNode n3("3", 0,1,0);
  TestNode n4("4", 1,1,0);
  TestNode n5("5", 2,1,0);
  TestNode n6("6", 0,2,0);
  TestNode n7("7", 1,2,0);
  TestNode n8("8", 2,2,0);
  TestGraph g;

  n0.SetNeighbors(std::vector<entity_project::IGraphNode*>{&n1,&n3});
  n2.SetNeighbors(std::vector<entity_project::IGraphNode*>{&n1,&n5});
  n6.SetNeighbors(std::vector<entity_project::IGraphNode*>{&n3,&n7});
  n8.SetNeighbors(std::vector<entity_project::IGraphNode*>{&n7,&n5});
  n1.SetNeighbors(std::vector<entity_project::IGraphNode*>{&n0,&n4,&n2});
  n3.SetNeighbors(std::vector<entity_project::IGraphNode*>{&n0,&n4,&n6});
  n5.SetNeighbors(std::vector<entity_project::IGraphNode*>{&n8,&n4,&n2});
  n7.SetNeighbors(std::vector<entity_project::IGraphNode*>{&n6,&n4,&n8});
  n4.SetNeighbors(std::vector<entity_project::IGraphNode*>{&n1,&n3,&n5,&n7});

  g.AddNodes(std::vector<entity_project::IGraphNode*>{&n0,&n1,&n2,&n3,&n4,&n5,&n6,&n7,&n8});

  rm.SetGraph(&g);
  std::vector<entity_project::IGraphNode*> route = rm.GetRoute(&n0,&n8);

  for(auto i = route.begin(); i != route.end(); ++i) {
    std::cout << (*i)->GetName() << std::endl;
  }
  ASSERT_FLOAT_EQ(RouteLength(route),4);
}

TEST_F(RouteManagerTest, SpecificRoute) {
  RouteManager rm;
  TestNode n0("0", 0,0,0);
  TestNode n1("1", 1,0,0);
  TestNode n2("2", 2,0,0);
  TestNode n3("3", 0,1,0);
  TestNode n4("4", 1,1,0);
  TestNode n5("5", 2,1,0);
  TestNode n6("6", 0,2,0);
  TestNode n7("7", 1,2,0);
  TestNode n8("8", 1.5,5,0);
  TestGraph g;

  n0.SetNeighbors(std::vector<entity_project::IGraphNode*>{&n1,&n3,&n4});
  n2.SetNeighbors(std::vector<entity_project::IGraphNode*>{&n1,&n5});
  n6.SetNeighbors(std::vector<entity_project::IGraphNode*>{&n3,&n7});
  n8.SetNeighbors(std::vector<entity_project::IGraphNode*>{&n7,&n5});
  n1.SetNeighbors(std::vector<entity_project::IGraphNode*>{&n0,&n4,&n2});
  n3.SetNeighbors(std::vector<entity_project::IGraphNode*>{&n0,&n4,&n6});
  n5.SetNeighbors(std::vector<entity_project::IGraphNode*>{&n8,&n4,&n2});
  n7.SetNeighbors(std::vector<entity_project::IGraphNode*>{&n6,&n4,&n8});
  n4.SetNeighbors(std::vector<entity_project::IGraphNode*>{&n1,&n3,&n5,&n7,&n0});

  g.AddNodes(std::vector<entity_project::IGraphNode*>{&n0,&n1,&n2,&n3,&n4,&n5,&n6,&n7,&n8});

  rm.SetGraph(&g);
  std::vector<entity_project::IGraphNode*> route = rm.GetRoute(&n0,&n8);

  std::string routeNames = "";
  for(auto i = route.begin(); i != route.end(); ++i) {
    std::cout << (*i)->GetName() << std::endl;
    routeNames += (*i)->GetName();
  }
  ASSERT_EQ(routeNames,"0478");
}

TEST_F(RouteManagerTest, NoRoute) {
  RouteManager rm;
  TestNode n0("0", 0,0,0);
  TestNode n1("1", 1,0,0);
  TestNode n2("2", 2,0,0);
  TestNode n3("3", 0,1,0);
  TestNode n4("4", 1,1,0);
  TestNode n5("5", 2,1,0);
  TestNode n6("6", 0,2,0);
  TestNode n7("7", 1,2,0);
  TestNode n8("8", 1.5,5,0);
  TestGraph g;

  n0.SetNeighbors(std::vector<entity_project::IGraphNode*>{&n1,&n3,&n4});
  n2.SetNeighbors(std::vector<entity_project::IGraphNode*>{&n1,&n5});
  n6.SetNeighbors(std::vector<entity_project::IGraphNode*>{&n3,&n7});
  n8.SetNeighbors(std::vector<entity_project::IGraphNode*>{&n8});
  n1.SetNeighbors(std::vector<entity_project::IGraphNode*>{&n0,&n4,&n2});
  n3.SetNeighbors(std::vector<entity_project::IGraphNode*>{&n0,&n4,&n6});
  n5.SetNeighbors(std::vector<entity_project::IGraphNode*>{&n8,&n4,&n2});
  n7.SetNeighbors(std::vector<entity_project::IGraphNode*>{&n6,&n4,&n8});
  n4.SetNeighbors(std::vector<entity_project::IGraphNode*>{&n1,&n3,&n5,&n7,&n0});

  g.AddNodes(std::vector<entity_project::IGraphNode*>{&n0,&n1,&n2,&n3,&n4,&n5,&n6,&n7,&n8});

  rm.SetGraph(&g);
  std::vector<entity_project::IGraphNode*> route = rm.GetRoute(&n0,&n8);

  std::string routeNames = "";
  for(auto i = route.begin(); i != route.end(); ++i) {
    std::cout << (*i)->GetName() << std::endl;
    routeNames += (*i)->GetName();
  }
  ASSERT_EQ(routeNames,"08");
}

}  // namespace csci3081
