#include "base-types.hpp"
#include <cmath>

bool klimchuk::areShapesIntersect(const rectangle_t& rectangle1, const rectangle_t& rectangle2)
{
  return (abs(rectangle1.pos.x - rectangle2.pos.x) <= ((rectangle1.width / 2) + (rectangle2.width / 2))
    && (abs(rectangle1.pos.y - rectangle2.pos.y) <= ((rectangle1.height / 2) + (rectangle2.height / 2))));
}
