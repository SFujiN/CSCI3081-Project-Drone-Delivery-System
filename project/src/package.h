#ifndef PACKAGE_H_
#define PACKAGE_H_

#include <EntityProject/ANVIL2/package.h>

namespace csci3081 {

/// TODO: Add documentation. You may edit this class including adding members or methods.
/**
 * TODO: Add detailed documentation.
 */
class Package : public entity_project::Package {
 public:
  /// TODO: Add documentation.
  Package() { AddType<Package>(); }
  /// Provides the package weight
  float GetWeight() const override;
};

}  // namespace csci3081
#endif
