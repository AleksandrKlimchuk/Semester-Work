#include <stdexcept>
#include "boost/test/unit_test.hpp"
#include "matrix.hpp"
#include "circle.hpp"
#include "rectangle.hpp"
#include "triangle.hpp"
#include "composite-shape.hpp"

const int EPSILON = 0.000001;

BOOST_AUTO_TEST_SUITE(Matrix_copy_constructor_and_assignment)

BOOST_AUTO_TEST_CASE(Matrix_copy_constructor)
{
  std::shared_ptr<klimchuk::Circle> circle = std::make_shared<klimchuk::Circle>(2.0, 2.0, 2);
  std::shared_ptr<klimchuk::Rectangle> rectangle = std::make_shared<klimchuk::Rectangle>(10.0, 6.0, 1.0, 3.0);
  std::shared_ptr<klimchuk::Triangle> triangle = std::make_shared<klimchuk::Triangle>(klimchuk::point_t{ -5.0, 1.0 },
    klimchuk::point_t{ -2, 3 }, klimchuk::point_t{ -2, -2 });
  klimchuk::Matrix matrix;
  matrix.add(circle);
  matrix.add(rectangle);
  matrix.add(triangle);
  klimchuk::Matrix copyOfMatrix(matrix);
  BOOST_CHECK_EQUAL(matrix.getSizeOfMatrix(), copyOfMatrix.getSizeOfMatrix());
  BOOST_CHECK_EQUAL(matrix.getNumberOFLayers(), copyOfMatrix.getNumberOFLayers());
  BOOST_CHECK_CLOSE(copyOfMatrix[0][0]->getArea(), matrix[0][0]->getArea(), EPSILON);
  BOOST_CHECK_CLOSE(copyOfMatrix[0][1]->getArea(), matrix[0][1]->getArea(), EPSILON);
  BOOST_CHECK_CLOSE(copyOfMatrix[1][0]->getArea(), matrix[1][0]->getArea(), EPSILON);
}

BOOST_AUTO_TEST_CASE(Matrix_copy_assignment)
{
  std::shared_ptr<klimchuk::Circle> circle = std::make_shared<klimchuk::Circle>(2.0, 2.0, 3);
  std::shared_ptr<klimchuk::Rectangle> rectangle = std::make_shared<klimchuk::Rectangle>(10.0, 6.0, 1.0, 3.0);
  std::shared_ptr<klimchuk::Triangle> triangle = std::make_shared<klimchuk::Triangle>(klimchuk::point_t{ -5.0, 1.0 },
    klimchuk::point_t{ -2, 3 }, klimchuk::point_t{ -2, -2 });
  klimchuk::Matrix matrix;
  matrix.add(circle);
  matrix.add(rectangle);
  matrix.add(triangle);
  klimchuk::Matrix copyOfMatrix;
  copyOfMatrix = matrix;
  BOOST_CHECK_EQUAL(matrix.getSizeOfMatrix(), copyOfMatrix.getSizeOfMatrix());
  BOOST_CHECK_EQUAL(matrix.getNumberOFLayers(), copyOfMatrix.getNumberOFLayers());
  BOOST_CHECK_CLOSE(copyOfMatrix[0][0]->getArea(), matrix[0][0]->getArea(), EPSILON);
  BOOST_CHECK_CLOSE(copyOfMatrix[0][1]->getArea(), matrix[0][1]->getArea(), EPSILON);
  BOOST_CHECK_CLOSE(copyOfMatrix[1][0]->getArea(), matrix[1][0]->getArea(), EPSILON);
}

BOOST_AUTO_TEST_SUITE_END()

klimchuk::Matrix function(std::shared_ptr<klimchuk::Circle> circle,
  std::shared_ptr<klimchuk::Rectangle> rectangle,
  std::shared_ptr<klimchuk::Triangle> triangle)
{
  klimchuk::Matrix matrix;
  matrix.add(circle);
  matrix.add(rectangle);
  matrix.add(triangle);
  return matrix;
}

BOOST_AUTO_TEST_SUITE(Matrix_move_constructor_and_assignment)

BOOST_AUTO_TEST_CASE(Matrix_move_constructor)
{
  std::shared_ptr<klimchuk::Circle> circle = std::make_shared<klimchuk::Circle>(2.0, 2.0, 2);
  std::shared_ptr<klimchuk::Rectangle> rectangle = std::make_shared<klimchuk::Rectangle>(10.0, 6.0, 1.0, 3.0);
  std::shared_ptr<klimchuk::Triangle> triangle = std::make_shared<klimchuk::Triangle>(klimchuk::point_t{ -5.0, 1.0 },
    klimchuk::point_t{ -2, 3 }, klimchuk::point_t{ -2, -2 });
  klimchuk::Matrix matrix = function(circle, rectangle, triangle);
  BOOST_CHECK_EQUAL(matrix.getSizeOfMatrix(), 3);
  BOOST_CHECK_EQUAL(matrix.getNumberOFLayers(), 2);
  BOOST_CHECK_EQUAL(matrix[0][0], circle);
  BOOST_CHECK_EQUAL(matrix[0][1], triangle);
  BOOST_CHECK_EQUAL(matrix[1][0], rectangle);
}

BOOST_AUTO_TEST_CASE(Matrix_move_assignment)
{
  std::shared_ptr<klimchuk::Circle> circle = std::make_shared<klimchuk::Circle>(2.0, 2.0, 3);
  std::shared_ptr<klimchuk::Rectangle> rectangle = std::make_shared<klimchuk::Rectangle>(10.0, 6.0, 1.0, 3.0);
  std::shared_ptr<klimchuk::Triangle> triangle = std::make_shared<klimchuk::Triangle>(klimchuk::point_t{ -5.0, 1.0 },
    klimchuk::point_t{ -2, 3 }, klimchuk::point_t{ -2, -2 });
  klimchuk::Matrix matrix;
  matrix = function(circle, rectangle, triangle);
  BOOST_CHECK_EQUAL(matrix.getSizeOfMatrix(), 3);
  BOOST_CHECK_EQUAL(matrix.getNumberOFLayers(), 2);
  BOOST_CHECK_EQUAL(matrix[0][0], circle);
  BOOST_CHECK_EQUAL(matrix[0][1], triangle);
  BOOST_CHECK_EQUAL(matrix[1][0], rectangle);
}

BOOST_AUTO_TEST_SUITE_END()
  
BOOST_AUTO_TEST_SUITE(Matrix_check_correctness_of_index)

BOOST_AUTO_TEST_CASE(Matrix_valid_index)
{
  std::shared_ptr<klimchuk::Circle> circle = std::make_shared<klimchuk::Circle>(2.0, 2.0, 3);
  std::shared_ptr<klimchuk::Rectangle> rectangle = std::make_shared<klimchuk::Rectangle>(10.0, 6.0, 1.0, 3.0);
  std::shared_ptr<klimchuk::Triangle> triangle = std::make_shared<klimchuk::Triangle>(klimchuk::point_t{ -5.0, 1.0 },
    klimchuk::point_t{ -2, 3 }, klimchuk::point_t{ -2, -2 });
  klimchuk::Matrix matrix;
  matrix.add(circle);
  matrix.add(rectangle);
  matrix.add(triangle);
  BOOST_CHECK_NO_THROW(matrix[0]);
  BOOST_CHECK_NO_THROW(matrix[0][0]);
}

BOOST_AUTO_TEST_CASE(Matrix_invalid_index)
{
  std::shared_ptr<klimchuk::Circle> circle = std::make_shared<klimchuk::Circle>(2.0, 2.0, 3);
  std::shared_ptr<klimchuk::Rectangle> rectangle = std::make_shared<klimchuk::Rectangle>(10.0, 6.0, 1.0, 3.0);
  std::shared_ptr<klimchuk::Triangle> triangle = std::make_shared<klimchuk::Triangle>(klimchuk::point_t{ -5.0, 1.0 },
    klimchuk::point_t{ -2, 3 }, klimchuk::point_t{ -2, -2 });
  klimchuk::Matrix matrix;
  BOOST_CHECK_THROW(matrix[1], std::domain_error);
  matrix.add(circle);
  matrix.add(rectangle);
  matrix.add(triangle);
  BOOST_CHECK_THROW(matrix[10], std::out_of_range);
  BOOST_CHECK_THROW(matrix[0][12], std::out_of_range);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(Matrix_check_correctness_adding)

BOOST_AUTO_TEST_CASE(Matrix_adding_invalid_shape)
{
  klimchuk::Matrix matrix;
  BOOST_CHECK_THROW(matrix.add(nullptr), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(Matrix_addding_new_shape_at_new_collumn)
{
  std::shared_ptr<klimchuk::Circle> circle = std::make_shared<klimchuk::Circle>(2.0, 2.0, 3);
  std::shared_ptr<klimchuk::Triangle> triangle = std::make_shared<klimchuk::Triangle>(klimchuk::point_t{ -5.0, 1.0 },
    klimchuk::point_t{ -2, 3 }, klimchuk::point_t{ -2, -2 });
  klimchuk::Matrix matrix;
  matrix.add(circle);
  BOOST_CHECK_EQUAL(matrix.getSizeOfLayer(0), 1);
  BOOST_CHECK_EQUAL(matrix[0][0], circle);
  matrix.add(triangle);
  BOOST_CHECK_EQUAL(matrix.getSizeOfLayer(0), 2);
  BOOST_CHECK_EQUAL(matrix[0][1], triangle);
}

BOOST_AUTO_TEST_CASE(Matrix_adding_new_shape_at_new_raw)
{
  std::shared_ptr<klimchuk::Circle> circle = std::make_shared<klimchuk::Circle>(2.0, 2.0, 3);
  std::shared_ptr<klimchuk::Rectangle> rectangle = std::make_shared<klimchuk::Rectangle>(10.0, 6.0, 1.0, 3.0);
  klimchuk::Matrix matrix;
  matrix.add(circle);
  BOOST_CHECK_EQUAL(matrix.getNumberOFLayers(), 1);
  BOOST_CHECK_EQUAL(matrix[0][0], circle);
  matrix.add(rectangle);
  BOOST_CHECK_EQUAL(matrix.getNumberOFLayers(), 2);
  BOOST_CHECK_EQUAL(matrix[1][0], rectangle);
}

BOOST_AUTO_TEST_SUITE_END()
