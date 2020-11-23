//
// Created by alli on 10/18/20.
//

#include "src/vector_3d.h"
#include <math.h>

Vector3d Vector3d::operator+(const Vector3d& other) const {
  return {x + other.x, y + other.y, z + other.z};
}

Vector3d Vector3d::operator-() const {
  return {-x, -y, -z};
}

Vector3d Vector3d::operator-(const Vector3d& other) const {
  return {x - other.x, y - other.y, z - other.z};
}

Vector3d Vector3d::operator*(const float& sc) const {
  return {x * sc, y * sc, z * sc};
}

Vector3d Vector3d::operator/(const float& sc) const {
  return {x / sc, y / sc, z / sc};
}

float Vector3d::getMagnitude() const {
  return sqrt(x * x + y * y + z * z);
}

Vector3d Vector3d::normalized() const {
  return (*this) * 1.0f / getMagnitude();
}

float Vector3d::distanceTo(const Vector3d& other) const {
  return (other - *this).getMagnitude();
}

Vector3d Vector3d::directionTo(const Vector3d& other) const {
  return (other - *this).normalized();
}
