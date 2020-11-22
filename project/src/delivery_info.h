//
// Created by alli on 11/22/20.
//

#include <string>
#include <picojson.h>

#ifndef PROJECT_SRC_DELIVERY_INFO_H_
#define PROJECT_SRC_DELIVERY_INFO_H_

namespace csci3081 {

class DeliveryInfo {
 public:
  DeliveryInfo(const picojson::object&);
  std::string GetPriority() const { return priority; }
  float GetMinTime() const { return minTime; }
 private:
  std::string priority;
  float minTime;
};


}  // namespace csci3081

#endif //PROJECT_SRC_DELIVERY_INFO_H_
