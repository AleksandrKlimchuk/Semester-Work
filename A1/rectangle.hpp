#ifndef KLIMCHUK_RECTANGLE
#define KLIMCHUK_RECTANGLE

#include "shape.hpp"

class Rectangle : public Shape
{
public:
  Rectangle(double width, double height, double posX, double posY);
  double getArea() const override;
  rectangle_t getFrameRect() const override;
  void move(const point_t& point) override;
  void move(double moveAbscissa, double moveOrdinate) override;
  point_t getCentre() const;
private:
  rectangle_t rectangle_;
};

#endif
