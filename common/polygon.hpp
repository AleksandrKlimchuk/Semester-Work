#ifndef KLIMCHUK_POLYGON
#define KLIMcHUK_POLYGON

#include <initializer_list>
#include "shape.hpp"

namespace klimchuk
{
  class Polygon : public Shape
  {
  public:
    Polygon(const std::initializer_list<point_t> points);
    const point_t operator[](size_t index) const;
    point_t operator[](size_t index);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t& point) override;
    void move(double moveAbscissa, double moveOrdinate) override;
    void scale(double coefficient) override;
    point_t getCentre() const override;
    void rotate(double angle) override;
    size_t getSize() const;
  private:
    size_t size_;
    std::unique_ptr<point_t[]> points_;
  };
}

#endif
