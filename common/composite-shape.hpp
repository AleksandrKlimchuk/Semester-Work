#ifndef KLIMCHUK_COMPOSITE_SHAPE
#define KLIMCHUK_COMPOSITE_SHAPE

#include <memory>
#include <initializer_list>
#include "shape.hpp"

namespace klimchuk
{
  class CompositeShape : public Shape
  {
  public:
    CompositeShape(const ShapePtr& shape);
    CompositeShape(const CompositeShape& rhs);
    CompositeShape(CompositeShape&& rhs) noexcept;
    CompositeShape& operator=(const CompositeShape& rhs);
    CompositeShape& operator=(CompositeShape&& rhs) noexcept;

    ShapePtr operator[](size_t index);
    ConstShapePtr operator[](size_t index) const;

    void add(const ShapePtr& shape);
    void remove(size_t index);
    size_t getSize() const;

    virtual double getArea() const override;
    virtual rectangle_t getFrameRect() const override;
    virtual void move(const point_t& point) override;
    virtual void move(double moveAbscissa, double moveOrdinate);
    virtual void scale(double coefficient) override;
    virtual point_t getCentre() const override;
    virtual void rotate(double angle) override;
  private:
    size_t size_;
    std::unique_ptr<ShapePtr[]> arrayOfShapes_;
  };
}

#endif
