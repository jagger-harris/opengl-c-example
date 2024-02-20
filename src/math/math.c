#include "math.h"

float degs_to_rads(float degrees) {
  return degrees * (PI / 180);
}

float rads_to_degs(float radians) {
  return radians * (180 / PI);
}
