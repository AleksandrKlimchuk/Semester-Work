#ifndef KLIMCHUK_BASE_TYPES
#define KLIMCHUK_BASE_TYPES

namespace klimchuk
{

  struct point_t
  {
    double x;
    double y;
  };

  struct rectangle_t
  {
    double width;
    double height;
    point_t pos;
  };

  bool areShapesIntersect(const rectangle_t& rectangle1, const rectangle_t& rectangle2);
}
#endif
