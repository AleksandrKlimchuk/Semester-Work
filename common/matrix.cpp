#include "matrix.hpp"
#include <stdexcept>
#include <memory>

klimchuk::Matrix::Layer::Layer(Shape::ShapePtr* shapePtr, size_t sizeOfLayer):
  sizeOfLayer_{ sizeOfLayer },
  layer_{ shapePtr }
{}

klimchuk::Shape::ShapePtr klimchuk::Matrix::Layer::operator[](size_t index)
{
  if (!layer_)
  {
    throw std::domain_error("Layer: Layer is empty.");
  }
  if (index >= sizeOfLayer_)
  {
    throw std::out_of_range("Layer: Invalid index to access.");
  }
  return layer_[index];
}

klimchuk::Shape::ConstShapePtr klimchuk::Matrix::Layer::operator[](size_t index) const
{
  if (!layer_)
  {
    throw std::domain_error("Layer: Layer is empty.");
  }
  if (index >= sizeOfLayer_)
  {
    throw std::out_of_range("Layer: Invalid index to access.");
  }
  return layer_[index];
}

klimchuk::Matrix::Matrix() :
  sizeOfMatrix_{ 0 },
  numberOfLayers_{ 0 },
  matrix_{ nullptr },
  sizesOfLayers_{ nullptr }
{}

klimchuk::Matrix::Matrix(const Matrix& rhs):
  sizeOfMatrix_{ rhs.sizeOfMatrix_ },
  numberOfLayers_{ rhs.numberOfLayers_ },
  matrix_{ std::make_unique<Shape::ShapePtr[]>(sizeOfMatrix_) },
  sizesOfLayers_{ std::make_unique<size_t[]>(numberOfLayers_) }
{
  for (size_t i = 0; i < sizeOfMatrix_; ++i)
  {
    matrix_[i] = rhs.matrix_[i];
  }
  for (size_t i = 0; i < numberOfLayers_; ++i)
  {
    sizesOfLayers_[i] = rhs.sizesOfLayers_[i];
  }
}

klimchuk::Matrix::Matrix(Matrix&& rhs) noexcept:
  sizeOfMatrix_{ rhs.sizeOfMatrix_ },
  numberOfLayers_{ rhs.numberOfLayers_ },
  matrix_{ std::move(rhs.matrix_) },
  sizesOfLayers_{ std::move(rhs.sizesOfLayers_) }
{}

klimchuk::Matrix& klimchuk::Matrix::operator=(const Matrix& rhs)
{
  if (this == &rhs)
  {
    return *this;
  }
  sizeOfMatrix_ = rhs.sizeOfMatrix_;
  numberOfLayers_ = rhs.numberOfLayers_;
  matrix_ = std::make_unique<Shape::ShapePtr[]>(sizeOfMatrix_);
  for (size_t i = 0; i < sizeOfMatrix_; ++i)
  {
    matrix_[i] = rhs.matrix_[i];
  }
  sizesOfLayers_ = std::make_unique<size_t[]>(numberOfLayers_);
  for (size_t i = 0; i < numberOfLayers_; ++i)
  {
    sizesOfLayers_[i] = rhs.sizesOfLayers_[i];
  }
  return *this;
}

klimchuk::Matrix& klimchuk::Matrix::operator=(Matrix&& rhs) noexcept
{
  if (this == &rhs)
  {
    return *this;
  }
  sizeOfMatrix_ = rhs.sizeOfMatrix_;
  numberOfLayers_ = rhs.numberOfLayers_;
  matrix_ = std::move(rhs.matrix_);
  sizesOfLayers_ = std::move(rhs.sizesOfLayers_);
  return *this;
}

const klimchuk::Matrix::Layer klimchuk::Matrix::operator[](size_t index) const
{
  if (!matrix_)
  {
    throw std::domain_error("Matrix: Matrix is empty.");
  }
  if (index >= numberOfLayers_)
  {
    throw std::out_of_range("Matrix: Invalid index to access.");
  }
  return Layer{ &matrix_[getIndexOfBeginningOfLayer(index)], sizesOfLayers_[index] };
}

klimchuk::Matrix::Layer klimchuk::Matrix::operator[](size_t index)
{
  if (!matrix_)
  {
    throw std::domain_error("Matrix: Matrix is empty.");
  }
  if (index >= numberOfLayers_)
  {
    throw std::out_of_range("Matrix: Invalid index to access.");
  }
  return Layer{ &matrix_[getIndexOfBeginningOfLayer(index)], sizesOfLayers_[index] };
}

size_t klimchuk::Matrix::getIndexOfBeginningOfLayer(size_t indexOfLayer) const
{
  if (indexOfLayer >= numberOfLayers_)
  {
    throw std::out_of_range("Matrix: Invalid index to access.");
  }
  size_t beginningIndex = 0;
  for (size_t i = 0; i < indexOfLayer; ++i)
  {
    beginningIndex += sizesOfLayers_[i];
  }
  return beginningIndex;
}

void klimchuk::Matrix::add(const Shape::ShapePtr& shape)
{
  if (!shape)
  {
    throw std::invalid_argument("Matrix: invalid argument to add");
  }
  size_t indexOfLayer = getIndexOfLayerToAdd(shape);
  if (indexOfLayer < numberOfLayers_)
  {
    size_t indexForAdd = getIndexInMatrixForShape(indexOfLayer);
    ++sizeOfMatrix_;
    ++sizesOfLayers_[indexOfLayer];
    std::unique_ptr<Shape::ShapePtr[]> tempMatrix = std::make_unique<Shape::ShapePtr[]>(sizeOfMatrix_);
    for (size_t i = 0; i < indexForAdd; ++i)
    {
      tempMatrix[i] = matrix_[i];
    }
    tempMatrix[indexForAdd] = shape;
    for (size_t i = indexForAdd + 1; i < sizeOfMatrix_; ++i)
    {
      tempMatrix[i] = matrix_[i - 1];
    }
    matrix_.swap(tempMatrix);
  }
  else
  {
    ++numberOfLayers_;
    std::unique_ptr<size_t[]> tempSizesOfLayers = std::make_unique<size_t[]>(numberOfLayers_);
    for (size_t i = 0; i < numberOfLayers_ - 1; ++i)
    {
      tempSizesOfLayers[i] = sizesOfLayers_[i];
    }
    tempSizesOfLayers[numberOfLayers_ - 1] = 1;
    sizesOfLayers_.swap(tempSizesOfLayers);
    ++sizeOfMatrix_;
    std::unique_ptr<Shape::ShapePtr[]> tempMatrix = std::make_unique<Shape::ShapePtr[]>(sizeOfMatrix_);
    for (size_t i = 0; i < sizeOfMatrix_ - 1; ++i)
    {
      tempMatrix[i] = matrix_[i];
    }
    tempMatrix[sizeOfMatrix_ - 1] = shape;
    matrix_.swap(tempMatrix);
  }
}

size_t klimchuk::Matrix::getIndexOfLayerToAdd(const Shape::ShapePtr& shape) const
{
  if (!shape)
  {
    throw std::invalid_argument("Matrix: ivalid argument to compute index");
  }
  size_t index = 0;
  bool isFind = false;
  for (size_t i = 0; i < sizeOfMatrix_ && !isFind; ++i)
  {
    if (areShapesIntersect(matrix_[i]->getFrameRect(), shape->getFrameRect()))
    {
      index = getIndexOfLayerForShape(i) + 1;
    }
    else
    {
      index = getIndexOfLayerForShape(i);
      isFind = true;
    }
  }
  return index;
}

size_t klimchuk::Matrix::getIndexOfLayerForShape(size_t indexOfFigure) const
{
  if (indexOfFigure >= sizeOfMatrix_)
  {
    throw std::out_of_range("Matrix: ivalid index to access");
  }
  size_t j = 0;
  size_t countOfShapes = 0;
  while (indexOfFigure >= countOfShapes)
  {
    countOfShapes += sizesOfLayers_[j++];
  }
  return --j;
}

size_t klimchuk::Matrix::getIndexInMatrixForShape(size_t indexOfLayer) const
{
  if (indexOfLayer >= numberOfLayers_)
  {
    throw std::out_of_range("Matrix: invalid index to access");
  }
  size_t index = 0;
  for (size_t i = 0; i <= indexOfLayer; ++i)
  {
    index += sizesOfLayers_[i];
  }
  return index;
}

size_t klimchuk::Matrix::getSizeOfMatrix() const
{
  return sizeOfMatrix_;
}

size_t klimchuk::Matrix::getNumberOFLayers() const
{
  return numberOfLayers_;
}

size_t klimchuk::Matrix::getSizeOfLayer(size_t indexOfLayer) const
{
  if (indexOfLayer >= numberOfLayers_)
  {
    std::out_of_range("Matrix: Invalid index to access");
  }
  return sizesOfLayers_[indexOfLayer];
}
