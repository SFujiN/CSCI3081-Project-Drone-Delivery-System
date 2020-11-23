//
// Created by alli on 11/22/20.
//

#include <string>
#include <picojson.h>

#ifndef PROJECT_SRC_DELIVERY_INFO_H_
#define PROJECT_SRC_DELIVERY_INFO_H_

namespace csci3081 {

/**
 * @brief Stores information about a delivery's scheduling status
 * Currently, this data is only stored and not used.
 */
class DeliveryInfo {
 public:
  DeliveryInfo() = default;
  explicit DeliveryInfo(const picojson::object&);
  std::string GetPriority() const { return priority; }
  float GetMinTime() const { return minTime; }
 private:
  std::string priority;
  float minTime = 0;
};


}  // namespace csci3081

#endif  // PROJECT_SRC_DELIVERY_INFO_H_
