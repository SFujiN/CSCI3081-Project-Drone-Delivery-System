//
// Created by alli on 10/18/20.
//

#ifndef SRC_VECTOR_3D_H
#define SRC_VECTOR_3D_H

/**
 * @brief A class that allows usage of arithmetic operators for points and vectors in 3d space
 *
 * This is a constant data structure, all functions are marked const and all returned Vector3d's are
 * new. Everything is passed by const reference and returned by value for speed, and ease of typing.
 * All functions behave as their mathematical equivalents.
 */
struct Vector3d {
  Vector3d(float x, float y, float z) : x(x), y(y), z(z) {}
  Vector3d operator+(const Vector3d&) const;
  Vector3d operator-() const;
  Vector3d operator-(const Vector3d&) const;
  Vector3d operator*(const float&) const;
  Vector3d operator/(const float&) const;
  float getMagnitude() const;
  Vector3d normalized() const;
  float distanceTo(const Vector3d&) const;
  Vector3d directionTo(const Vector3d&) const;
  float x, y, z;
};


#endif  // SRC_VECTOR_3D_H
