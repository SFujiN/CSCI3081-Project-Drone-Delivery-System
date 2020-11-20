//
// Created by alli on 11/12/20.
//

#include "src/package.h"
#include "src/vector_3d.h"
#include <vector>
#include <algorithm>

namespace csci3081 {

Package::Package(const picojson::object& initfrom) : Package() {
  details_ = initfrom;
  packageObservable.SetEntity(this);

  name_ = JsonHelper::GetNoFail<std::string>(initfrom, "name", "default name");

  picojson::array arr;
  arr = JsonHelper::GetNoFail<picojson::array>(initfrom, "position", picojson::array{});
  for (int i = 0; i<3; ++i) {
    position_[i] = JsonHelper::ArrayGetNoFail<double>(arr, i, 0);
  }

  std::vector<float> default_direction{1,0,0};
  arr = JsonHelper::GetNoFail<picojson::array>(initfrom, "direction", picojson::array{});
  for (int i = 0; i<3; ++i) {
    direction_[i] = JsonHelper::ArrayGetNoFail<double>(arr, i, default_direction.at(i));
  }

  radius_ = JsonHelper::GetNoFail<double>(initfrom, "radius", 3);
}

float Package::GetWeight() const {
  return 0;
}

Vector3d csci3081::Package::GetVecPos() {
  return {position_[0], position_[1], position_[2]};
}

void csci3081::Package::SetVecPos(Vector3d vec) {
  position_[0] = vec.x;
  position_[1] = vec.y;
  position_[2] = vec.z;
}

void Package::NotifyScheduled() {
  HasBeenScheduled = true;
  picojson::object obj;
  obj["type"] = picojson::value("notify");
  obj["value"] = picojson::value("scheduled");
  const picojson::value& event = picojson::value(obj);
  packageObservable.Notify(event);
}

void Package::NotifyDelivered() {
  HasBeenDelivered = true;
  picojson::object obj;
  obj["type"] = picojson::value("notify");
  obj["value"] = picojson::value("delivered");
  const picojson::value& event = picojson::value(obj);
  packageObservable.Notify(event);
}

void Package::NotifyPickedUp() {
  picojson::object obj;
  obj["type"] = picojson::value("notify");
  obj["value"] = picojson::value("en route");
  const picojson::value& event = picojson::value(obj);
  packageObservable.Notify(event);
}


}  // namespace csci3081
