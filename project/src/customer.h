#ifndef CUSTOMER_H_
#define CUSTOMER_H_

#include <EntityProject/ANVIL2/customer.h>

namespace csci3081 {
/// TODO: Add documentation. You may edit this class including adding members or methods.
/**
 * TODO: Add detailed documentation.
 */
class Customer : public entity_project::Customer {
 public:
    /// TODO: Add documentation.
    Customer() { AddType<Customer>(); }
};

}  // namespace csci3081

#endif
