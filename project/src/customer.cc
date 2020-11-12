//
// Created by alli on 11/12/20.
//

#include "src/customer.h"

namespace csci3081 {

Customer::Customer(const picojson::object& initfrom) : Customer() {
  details_ = initfrom;
  if (details_.find("position") != details_.end()) {
    int len = details_["position"].get<picojson::array>().size();
    for (int i = 0; i < len && i < 3; i++) {
      position_[i] = details_["position"].get<picojson::array>()[i].get<double>();
    }
  }
}

}  // namespace csci3081
