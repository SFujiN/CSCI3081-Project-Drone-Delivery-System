#ifndef CUSTOMER_H_
#define CUSTOMER_H_

#include <EntityProject/ANVIL2/customer.h>
#include "src/json_helper.h"

namespace csci3081 {

/// Represents a customer in the drone system.
class Customer : public entity_project::Customer {
 public:
  /// TODO: Add documentation.
  Customer() { AddType<Customer>(); }
  /**
   * @brief Create a Customer from the JSON encoding.
   */
  explicit Customer(const picojson::object&);
};

}  // namespace csci3081

#endif
