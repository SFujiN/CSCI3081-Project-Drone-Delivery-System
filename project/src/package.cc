//
// Created by alli on 11/12/20.
//

#include "src/package.h"
#include <vector>
#include <algorithm>

namespace csci3081 {

Package::Package(const picojson::object& initfrom) : Package() {
  details_ = initfrom;
  packageObservable.SetEntity(this);
  if (details_.find("position") != details_.end()) {
    int len = details_["position"].get<picojson::array>().size();
    for (int i = 0; i < len && i < 3; i++) {
      position_[i] = details_["position"].get<picojson::array>()[i].get<double>();
    }
  }
}

float Package::GetWeight() const {
  return 0;
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
}  // namespace csci3081
