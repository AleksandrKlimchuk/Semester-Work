#ifndef KLIMCHUK_CIRCLE
#define KLIMCHUK_CIRCLE
#include "shape.hpp"

namespace klimchuk
{
  class Circle : public Shape
  {
  public:
    Circle(double posX, double posY, double radius);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t& point) override;
    void move(double moveAbscissa, double moveOrdinate) override;
    point_t getCentre() const override;
    void scale(double coefficient) override;
    double getRadius() const;
    void rotate(double) override;
  private:
    double radius_;
    point_t centre_;
  };
}

#endif
