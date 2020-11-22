//
// Created by alli on 11/12/20.
//

#include "src/customer.h"
#include <string>
#include <vector>

namespace csci3081 {

Customer::Customer(const picojson::object& initfrom) : Customer() {
  details_ = initfrom;

  name_ = JsonHelper::GetNoFail<std::string>(initfrom, "name", "default name");

  picojson::array arr;
  arr = JsonHelper::GetNoFail<picojson::array>(initfrom, "position", picojson::array{});
  for (int i = 0; i < 3; ++i) {
    position_[i] = JsonHelper::ArrayGetNoFail<double>(arr, i, 0);
  }

  std::vector<float> default_direction{1, 0, 0};
  arr = JsonHelper::GetNoFail<picojson::array>(initfrom, "direction", picojson::array{});
  for (int i = 0; i < 3; ++i) {
    direction_[i] = JsonHelper::ArrayGetNoFail<double>(arr, i, default_direction.at(i));
  }

  radius_ = JsonHelper::GetNoFail<double>(initfrom, "radius", 3);
}

}  // namespace csci3081
