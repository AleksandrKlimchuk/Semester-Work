#ifndef KLIMCHUK_MATRIX
#define KLIMCHUK_MATRIX

#include <memory>
#include "shape.hpp"

namespace klimchuk
{
  class Matrix
  {
  public:
    class Layer
    {
    public:
      Shape::ShapePtr operator[](size_t index);
      Shape::ConstShapePtr operator[](size_t index) const;
    private:
      friend class Matrix;
      size_t sizeOfLayer_;
      Shape::ShapePtr* layer_;
      Layer(Shape::ShapePtr* shapePtr, size_t sizeOfLayer);
    };

    Matrix();

    Matrix(const Matrix& rhs);
    Matrix(Matrix&& rhs) noexcept;

    Matrix& operator=(const Matrix& rhs);
    Matrix& operator=(Matrix&& rhs) noexcept;
    const Layer operator[](size_t index) const;
    Layer operator[](size_t index);

    void add(const Shape::ShapePtr& shape);

    size_t getIndexOfBeginningOfLayer(size_t indexOfLayer) const;
    size_t getIndexOfLayerToAdd(const Shape::ShapePtr& shape) const;
    size_t getIndexOfLayerForShape(size_t indexOfFigure) const;
    size_t getIndexInMatrixForShape(size_t indexOfLayer) const;

    size_t getSizeOfMatrix() const;
    size_t getNumberOFLayers() const;
    size_t getSizeOfLayer(size_t indexOfLayer) const;
  private:
    size_t sizeOfMatrix_;
    size_t numberOfLayers_;
    std::unique_ptr<Shape::ShapePtr[]> matrix_;
    std::unique_ptr<size_t[]> sizesOfLayers_;
  };
}

#endif
