#ifndef KLIMCHUK_RECTANGLE
#define KLIMCHUK_RECTANGLE

#include "shape.hpp"

namespace klimchuk
{
  class Rectangle : public Shape
  {
  public:
    Rectangle(double width, double height, double posX, double posY);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t& point) override;
    void move(double moveAbscissa, double moveOrdinate) override;
    point_t getCentre() const override;
    void scale(double coefficient) override;
    double getHeight() const;
    double getWidth() const;
    void rotate(double angle) override;
  private:
    point_t corners_[4];
  };
}

#endif
