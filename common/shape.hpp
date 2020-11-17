#ifndef KLIMCHUK_ABSTRACT_SHAPE
#define KLIMCHUK_ABSTRACT_SHAPE

#include <memory>
#include "base-types.hpp"

namespace klimchuk
{
  class Shape
  {
  public:
    typedef std::shared_ptr<Shape> ShapePtr;
    typedef std::shared_ptr<const Shape> ConstShapePtr;

    virtual ~Shape() = default;
    virtual double getArea() const = 0;
    virtual rectangle_t getFrameRect() const = 0;
    virtual void move(const point_t& point) = 0;
    virtual void move(double moveAbscissa, double moveOrdinate) = 0;
    virtual void scale(double coefficient) = 0;
    virtual point_t getCentre() const = 0;
    virtual void rotate(double angle) = 0;
  };
}

#endif
