//
// Created by alli on 11/22/20.
//

#include "src/delivery_info.h"
#include "src/json_helper.h"

namespace csci3081 {

DeliveryInfo::DeliveryInfo(const picojson::object& val) {
  priority = JsonHelper::GetNoFail<std::string>(val, "priority", "medium");
  minTime = JsonHelper::GetNoFail<double>(val, "minDeliveryTime", 0);
}

}  // namespace csci3081