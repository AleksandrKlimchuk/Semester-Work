#ifndef KLIMCHUK_ABSTRACT_SHAPE
#define KLIMCHUK_ABSTRACT_SHAPE

#include "base-types.hpp"

class Shape
{
public:
  virtual ~Shape() = default;
  virtual double getArea() const = 0;
  virtual rectangle_t getFrameRect() const = 0;
  virtual void move(const point_t& point) = 0;
  virtual void move(double moveAbscissa, double moveOrdinate) = 0;
};

#endif
