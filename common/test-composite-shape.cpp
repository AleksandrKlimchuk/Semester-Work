#include <stdexcept>
#include "boost/test/unit_test.hpp"
#include "composite-shape.hpp"
#include "circle.hpp"
#include "rectangle.hpp"
#include "triangle.hpp"

const double EPSILON = 0.000001;

BOOST_AUTO_TEST_SUITE(CompositeShape_constructors)

BOOST_AUTO_TEST_CASE(CompositeShape_constructor_valid)
{
  klimchuk::CompositeShape compositeShape(std::make_shared<klimchuk::Circle>(12.0, 14.6, 10.0));
  BOOST_CHECK_EQUAL(compositeShape.getSize(), 1);
  BOOST_CHECK_CLOSE(compositeShape.getCentre().x, 12.0, EPSILON);
  BOOST_CHECK_CLOSE(compositeShape.getCentre().y, 14.6, EPSILON);
}

BOOST_AUTO_TEST_CASE(CompositeShape_constructor_invalid)
{
  BOOST_CHECK_THROW(klimchuk::CompositeShape(nullptr), std::invalid_argument);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(CompositeShape_copy_constructor_and_assignment)

BOOST_AUTO_TEST_CASE(CompositeShape_copy_constructor)
{
  klimchuk::CompositeShape compositeShape(std::make_shared<klimchuk::Circle>(12.0, 14.6, 10.0));
  klimchuk::CompositeShape copyOfCompositeShape = compositeShape;
  BOOST_CHECK_EQUAL(copyOfCompositeShape.getSize(), 1);
  BOOST_CHECK_CLOSE(copyOfCompositeShape.getCentre().x, 12.0, EPSILON);
  BOOST_CHECK_CLOSE(copyOfCompositeShape.getCentre().y, 14.6, EPSILON);
}

BOOST_AUTO_TEST_CASE(CompositeShape_copy_assignment)
{
  klimchuk::CompositeShape compositeShape(std::make_shared<klimchuk::Circle>(0.0, 0.0, 1.0));
  klimchuk::CompositeShape rhs(std::make_shared<klimchuk::Circle>(12.0, 14.6, 10.0));
  compositeShape = rhs;
  BOOST_CHECK_EQUAL(compositeShape.getSize(), 1);
  BOOST_CHECK_CLOSE(compositeShape.getCentre().x, 12.0, EPSILON);
  BOOST_CHECK_CLOSE(compositeShape.getCentre().y, 14.6, EPSILON);
}

BOOST_AUTO_TEST_SUITE_END()

klimchuk::CompositeShape function(double x, double y, double radius)
{
  klimchuk::CompositeShape compositeShape(std::make_shared<klimchuk::Circle>(x, y, radius));
  return compositeShape;
}

BOOST_AUTO_TEST_SUITE(CompositeShape_move_constructor_and_assignment)

BOOST_AUTO_TEST_CASE(CompositeShape_move_constructor)
{
  klimchuk::CompositeShape compositeShape(std::make_shared<klimchuk::CompositeShape>(function(12.0, 14.6, 10.0)));
  BOOST_CHECK_EQUAL(compositeShape.getSize(), 1);
  BOOST_CHECK_CLOSE(compositeShape.getCentre().x, 12.0, EPSILON);
  BOOST_CHECK_CLOSE(compositeShape.getCentre().y, 14.6, EPSILON);
}

BOOST_AUTO_TEST_CASE(CompositeShape_move_assignmet)
{
  klimchuk::CompositeShape compositeShape(std::make_shared<klimchuk::Circle>(0.0, 0.0, 1.0));
  compositeShape = function(12.0, 14.6, 10.0);
  BOOST_CHECK_EQUAL(compositeShape.getSize(), 1);
  BOOST_CHECK_CLOSE(compositeShape.getCentre().x, 12.0, EPSILON);
  BOOST_CHECK_CLOSE(compositeShape.getCentre().y, 14.6, EPSILON);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(CompositeShape_moving)

BOOST_AUTO_TEST_CASE(CompositeShape_moving_to_point)
{
  klimchuk::point_t newCentre{ 6, -1 };
  klimchuk::CompositeShape compositeShape(std::make_shared<klimchuk::Circle>(5.0, 1.0, 7.0));
  compositeShape.add(std::make_shared<klimchuk::Rectangle>(8.0, 4.0, 1.0, 5.0));
  compositeShape.add(std::make_shared<klimchuk::Triangle>(klimchuk::point_t{ 1.0, 2.0 }, klimchuk::point_t{ 3.0, -1.0 }, 
    klimchuk::point_t{ 2.0, 5.0 }));
  compositeShape.move(newCentre);
  BOOST_CHECK_CLOSE(newCentre.x, compositeShape.getCentre().x, EPSILON);
  BOOST_CHECK_CLOSE(newCentre.y, compositeShape.getCentre().y, EPSILON);
}

BOOST_AUTO_TEST_CASE(CompositeShape_moving_to_point_check_const_area)
{
  klimchuk::point_t newCentre{ 6, -1 };
  klimchuk::CompositeShape compositeShape(std::make_shared<klimchuk::Circle>(5.0, 1.0, 7.0));
  compositeShape.add(std::make_shared<klimchuk::Rectangle>(8.0, 4.0, 1.0, 5.0));
  compositeShape.add(std::make_shared<klimchuk::Triangle>(klimchuk::point_t{ 1.0, 2.0 }, klimchuk::point_t{ 3.0, -1.0 },
    klimchuk::point_t{ 2.0, 5.0 }));
  double areaBeforeMoving = compositeShape.getArea();
  compositeShape.move(newCentre);
  BOOST_CHECK_CLOSE(areaBeforeMoving, compositeShape.getArea(), EPSILON);
}

BOOST_AUTO_TEST_CASE(CompositeShape_moving_to_point_check_const_frame_rectangle)
{
  klimchuk::point_t newCentre{ 6, -1 };
  klimchuk::CompositeShape compositeShape(std::make_shared<klimchuk::Circle>(5.0, 1.0, 7.0));
  compositeShape.add(std::make_shared<klimchuk::Rectangle>(8.0, 4.0, 1.0, 5.0));
  compositeShape.add(std::make_shared<klimchuk::Triangle>(klimchuk::point_t{ 1.0, 2.0 }, klimchuk::point_t{ 3.0, -1.0 },
    klimchuk::point_t{ 2.0, 5.0 }));
  klimchuk::rectangle_t frameRectangle = compositeShape.getFrameRect();
  compositeShape.move(newCentre);
  BOOST_CHECK_CLOSE(frameRectangle.width, compositeShape.getFrameRect().width, EPSILON);
  BOOST_CHECK_CLOSE(frameRectangle.height, compositeShape.getFrameRect().height, EPSILON);
}

BOOST_AUTO_TEST_CASE(CompositeShape_moving_add_abscissa_ordinate)
{
  klimchuk::CompositeShape compositeShape(std::make_shared<klimchuk::Circle>(5.0, 1.0, 7.0));
  compositeShape.add(std::make_shared<klimchuk::Rectangle>(8.0, 4.0, 1.0, 5.0));
  compositeShape.add(std::make_shared<klimchuk::Triangle>(klimchuk::point_t{ 1.0, 2.0 }, klimchuk::point_t{ 3.0, -1.0 },
    klimchuk::point_t{ 2.0, 5.0 }));
  const double moveAbscissa = 3.0;
  const double moveOrdinate = 8.0;
  klimchuk::point_t centreBeforeMoving = compositeShape.getCentre();
  compositeShape.move(moveAbscissa, moveOrdinate);
  BOOST_CHECK_CLOSE(compositeShape.getCentre().x, centreBeforeMoving.x + moveAbscissa, EPSILON);
  BOOST_CHECK_CLOSE(compositeShape.getCentre().y, centreBeforeMoving.y + moveOrdinate, EPSILON);
}

BOOST_AUTO_TEST_CASE(CompositeShape_moving_add_abscissa_ordinate_check_const_area)
{
  klimchuk::CompositeShape compositeShape(std::make_shared<klimchuk::Circle>(5.0, 1.0, 7.0));
  compositeShape.add(std::make_shared<klimchuk::Rectangle>(8.0, 4.0, 1.0, 5.0));
  compositeShape.add(std::make_shared<klimchuk::Triangle>(klimchuk::point_t{ 1.0, 2.0 }, klimchuk::point_t{ 3.0, -1.0 },
    klimchuk::point_t{ 2.0, 5.0 }));
  const double moveAbscissa = 3.0;
  const double moveOrdinate = 8.0;
  double areaBeforeMoving = compositeShape.getArea();
  compositeShape.move(moveAbscissa, moveOrdinate);
  BOOST_CHECK_CLOSE(areaBeforeMoving, compositeShape.getArea(), EPSILON);
}

BOOST_AUTO_TEST_CASE(CompositeShape_moving_add_abscissa_ordinate_check_const_frame_rectangle)
{
  klimchuk::CompositeShape compositeShape(std::make_shared<klimchuk::Circle>(5.0, 1.0, 7.0));
  compositeShape.add(std::make_shared<klimchuk::Rectangle>(8.0, 4.0, 1.0, 5.0));
  compositeShape.add(std::make_shared<klimchuk::Triangle>(klimchuk::point_t{ 1.0, 2.0 }, klimchuk::point_t{ 3.0, -1.0 },
    klimchuk::point_t{ 2.0, 5.0 }));
  klimchuk::rectangle_t frameRectangle = compositeShape.getFrameRect();
  const double moveAbscissa = 3.0;
  const double moveOrdinate = 8.0;
  compositeShape.move(moveAbscissa, moveOrdinate);
  BOOST_CHECK_CLOSE(frameRectangle.width, compositeShape.getFrameRect().width, EPSILON);
  BOOST_CHECK_CLOSE(frameRectangle.height, compositeShape.getFrameRect().height, EPSILON);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(CompositeShape_scaling)

BOOST_AUTO_TEST_CASE(CompositeShape_scaling_valid_coefficient)
{
  klimchuk::CompositeShape compositeShape(std::make_shared<klimchuk::Circle>(4.0, 13.0, 5.0));
  compositeShape.add(std::make_shared<klimchuk::Rectangle>(3.0, 9.0, 7.0, 14.0));
  compositeShape.add(std::make_shared<klimchuk::Triangle>(klimchuk::point_t{ 1.0, 2.0 }, klimchuk::point_t{ 3.0, -1.0 },
    klimchuk::point_t{ 2.0, 5.0 }));
  klimchuk::rectangle_t frameRectangleForShape1 = compositeShape[0]->getFrameRect();
  klimchuk::rectangle_t frameRectangleForShape2 = compositeShape[1]->getFrameRect();
  klimchuk::rectangle_t frameRectangleForShape3 = compositeShape[2]->getFrameRect();
  double areaOfShape1 = compositeShape[0]->getArea();
  double areaOfShape2 = compositeShape[1]->getArea();
  double areaOfShape3 = compositeShape[2]->getArea();
  const double coefficient = 2.0;
  compositeShape.scale(coefficient);
  BOOST_CHECK_CLOSE(frameRectangleForShape1.width * coefficient, compositeShape[0]->getFrameRect().width, EPSILON);
  BOOST_CHECK_CLOSE(frameRectangleForShape1.height * coefficient, compositeShape[0]->getFrameRect().height, EPSILON);
  BOOST_CHECK_CLOSE(frameRectangleForShape2.width * coefficient, compositeShape[1]->getFrameRect().width, EPSILON);
  BOOST_CHECK_CLOSE(frameRectangleForShape2.height * coefficient, compositeShape[1]->getFrameRect().height, EPSILON);
  BOOST_CHECK_CLOSE(frameRectangleForShape3.width * coefficient, compositeShape[2]->getFrameRect().width, EPSILON);
  BOOST_CHECK_CLOSE(frameRectangleForShape3.height * coefficient, compositeShape[2]->getFrameRect().height, EPSILON);
  BOOST_CHECK_CLOSE(areaOfShape1 * coefficient * coefficient, compositeShape[0]->getArea(), EPSILON);
  BOOST_CHECK_CLOSE(areaOfShape2 * coefficient * coefficient, compositeShape[1]->getArea(), EPSILON);
  BOOST_CHECK_CLOSE(areaOfShape3 * coefficient * coefficient, compositeShape[2]->getArea(), EPSILON);
}

BOOST_AUTO_TEST_CASE(CompositeShape_scaling_invalid_coefficient)
{
  klimchuk::CompositeShape compositeShape(std::make_shared<klimchuk::Circle>(4.0, 13.0, 5.0));
  BOOST_CHECK_THROW(compositeShape.scale(0.0), std::invalid_argument);
  BOOST_CHECK_THROW(compositeShape.scale(-2.0), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(CompositeShape_scaling_correct_frame_rectangle)
{
  klimchuk::CompositeShape compositeShape(std::make_shared<klimchuk::Circle>(4.0, 13.0, 5.0));
  compositeShape.add(std::make_shared<klimchuk::Rectangle>(3.0, 9.0, 7.0, 14.0));
  compositeShape.add(std::make_shared<klimchuk::Triangle>(klimchuk::point_t{ 1.0, 2.0 }, klimchuk::point_t{ 3.0, -1.0 },
    klimchuk::point_t{ 2.0, 5.0 }));
  klimchuk::rectangle_t frameRectangle = compositeShape.getFrameRect();
  const double coefficient = 2.0;
  compositeShape.scale(coefficient);
  BOOST_CHECK_CLOSE(frameRectangle.width * coefficient, compositeShape.getFrameRect().width, EPSILON);
  BOOST_CHECK_CLOSE(frameRectangle.height * coefficient, compositeShape.getFrameRect().height, EPSILON);
}

BOOST_AUTO_TEST_CASE(CompositeShape_scaling_correct_area)
{
  klimchuk::CompositeShape compositeShape(std::make_shared<klimchuk::Circle>(4.0, 13.0, 5.0));
  compositeShape.add(std::make_shared<klimchuk::Rectangle>(3.0, 9.0, 7.0, 14.0));
  compositeShape.add(std::make_shared<klimchuk::Triangle>(klimchuk::point_t{ 1.0, 2.0 }, klimchuk::point_t{ 3.0, -1.0 },
    klimchuk::point_t{ 2.0, 5.0 }));
  double areaOfShape1 = compositeShape[0]->getArea();
  double areaOfShape2 = compositeShape[1]->getArea();
  double areaOfShape3 = compositeShape[2]->getArea();
  const double coefficient = 2.0;
  double sumArea = (areaOfShape1 + areaOfShape2 + areaOfShape3) * coefficient * coefficient;
  compositeShape.scale(coefficient);
  BOOST_CHECK_CLOSE(sumArea, compositeShape.getArea(), EPSILON);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(CompositeShape_adding_shapes)

BOOST_AUTO_TEST_CASE(CompositeShape_adding_shapes_check_correct_index_and_size)
{
  std::shared_ptr<klimchuk::Shape> circle = std::make_shared<klimchuk::Circle>(5.0, 1.0, 6.0);
  std::shared_ptr<klimchuk::Shape> rectangle = std::make_shared<klimchuk::Rectangle>(7.0, 1.0, 8.0, 13.0);
  std::shared_ptr<klimchuk::Shape> triangle = std::make_shared<klimchuk::Triangle>(klimchuk::point_t{ 1.0, 2.0 }, 
    klimchuk::point_t{ 3.0, -1.0 }, klimchuk::point_t{ 2.0, 5.0 });
  klimchuk::CompositeShape compositeShape(circle);
  compositeShape.add(rectangle);
  compositeShape.add(triangle);
  BOOST_CHECK_EQUAL(compositeShape.getSize(), 3);
  BOOST_CHECK_EQUAL(compositeShape[0], circle);
  BOOST_CHECK_EQUAL(compositeShape[1], rectangle);
  BOOST_CHECK_EQUAL(compositeShape[2], triangle);
}

BOOST_AUTO_TEST_CASE(CompositeShape_adding_null_shape)
{
  klimchuk::CompositeShape compositeShape(std::make_shared<klimchuk::Circle>(5.0, 1.0, 6.0));
  BOOST_CHECK_THROW(compositeShape.add(nullptr), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(CompositeShape_adding_shapes_changing_of_area)
{
  klimchuk::CompositeShape compositeShape(std::make_shared<klimchuk::Circle>(5.0, 1.0, 6.0));
  double areaAfterFirstAdding = compositeShape.getArea();
  std::shared_ptr<klimchuk::Shape> rectangle = std::make_shared<klimchuk::Rectangle>(7.0, 1.0, 8.0, 13.0);
  double areaOfRectangle = rectangle->getArea();
  std::shared_ptr<klimchuk::Shape> triangle = std::make_shared<klimchuk::Triangle>(klimchuk::point_t{ 1.0, 2.0 },
    klimchuk::point_t{ 3.0, -1.0 }, klimchuk::point_t{ 2.0, 5.0 });
  double areaOfTriangle = triangle->getArea();
  compositeShape.add(rectangle);
  compositeShape.add(triangle);
  BOOST_CHECK_CLOSE(compositeShape.getArea(), areaAfterFirstAdding + areaOfRectangle + areaOfTriangle, EPSILON);
}

BOOST_AUTO_TEST_CASE(CompositeShape_adding_shapes_changing_of_frame_rectangle)
{
  klimchuk::CompositeShape compositeShape(std::make_shared<klimchuk::Circle>(5.0, 1.0, 6.0));
  klimchuk::rectangle_t frameRectangle = compositeShape.getFrameRect();
  compositeShape.add(std::make_shared<klimchuk::Rectangle>(14.0, 2.0, 5.0, 1.0));
  BOOST_CHECK_CLOSE(frameRectangle.width + 2.0, compositeShape.getFrameRect().width, EPSILON);
  BOOST_CHECK_CLOSE(frameRectangle.height, compositeShape.getFrameRect().height, EPSILON);
  BOOST_CHECK_CLOSE(frameRectangle.pos.x, compositeShape.getFrameRect().pos.x, EPSILON);
  BOOST_CHECK_CLOSE(frameRectangle.pos.y, compositeShape.getFrameRect().pos.y, EPSILON);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(CompositeShape_removing_shapes)

BOOST_AUTO_TEST_CASE(CompositeShape_removing_shapes_check_correct_size_and_index)
{
  std::shared_ptr<klimchuk::Shape> circle = std::make_shared<klimchuk::Circle>(5.0, 1.0, 6.0);
  std::shared_ptr<klimchuk::Shape> rectangle = std::make_shared<klimchuk::Rectangle>(7.0, 1.0, 8.0, 13.0);
  std::shared_ptr<klimchuk::Shape> triangle = std::make_shared<klimchuk::Triangle>(klimchuk::point_t{ 1.0, 2.0 },
    klimchuk::point_t{ 3.0, -1.0 }, klimchuk::point_t{ 2.0, 5.0 });
  klimchuk::CompositeShape compositeShape(circle);
  compositeShape.add(rectangle);
  compositeShape.add(triangle);
  compositeShape.remove(0);
  BOOST_CHECK_EQUAL(compositeShape.getSize(), 2);
  BOOST_CHECK_EQUAL(compositeShape[0], rectangle);
  compositeShape.remove(0);
  BOOST_CHECK_EQUAL(compositeShape.getSize(), 1);
  BOOST_CHECK_EQUAL(compositeShape[0], triangle);
}

BOOST_AUTO_TEST_CASE(CompositeShape_removing_shape_by_invalid_index)
{
  klimchuk::CompositeShape compositeShape(std::make_shared<klimchuk::Circle>(5.0, 1.0, 6.0));
  BOOST_CHECK_THROW(compositeShape.remove(10), std::out_of_range);
}

BOOST_AUTO_TEST_CASE(CompositeShape_removing_last_shape)
{
  klimchuk::CompositeShape compositeShape(std::make_shared<klimchuk::Circle>(5.0, 1.0, 6.0));
  BOOST_CHECK_THROW(compositeShape.remove(0), std::length_error);
}

BOOST_AUTO_TEST_CASE(CompositeShape_removing_shape_changing_of_area)
{
  std::shared_ptr<klimchuk::Shape> circle = std::make_shared<klimchuk::Circle>(5.0, 1.0, 6.0);
  std::shared_ptr<klimchuk::Shape> rectangle = std::make_shared<klimchuk::Rectangle>(7.0, 1.0, 8.0, 13.0);
  std::shared_ptr<klimchuk::Shape> triangle = std::make_shared<klimchuk::Triangle>(klimchuk::point_t{ 1.0, 2.0 },
    klimchuk::point_t{ 3.0, -1.0 }, klimchuk::point_t{ 2.0, 5.0 });
  klimchuk::CompositeShape compositeShape(circle);
  double areaOfCircle = circle->getArea();
  compositeShape.add(rectangle);
  compositeShape.add(triangle);
  double areaBeforeRemovingCircle = compositeShape.getArea();
  compositeShape.remove(0);
  BOOST_CHECK_CLOSE(compositeShape.getArea(), areaBeforeRemovingCircle - areaOfCircle, EPSILON);
}

BOOST_AUTO_TEST_CASE(CompositeShape_removing_shape_changing_of_frame_rectangle)
{
  std::shared_ptr<klimchuk::Shape> circle = std::make_shared<klimchuk::Circle>(5.0, 1.0, 6.0);
  std::shared_ptr<klimchuk::Shape> rectangle = std::make_shared<klimchuk::Rectangle>(7.0, 1.0, 8.0, 13.0);
  klimchuk::CompositeShape compositeShape(circle);
  compositeShape.add(rectangle);
  compositeShape.remove(0);
  BOOST_CHECK_CLOSE(7.0, compositeShape.getFrameRect().width, EPSILON);
  BOOST_CHECK_CLOSE(1.0, compositeShape.getFrameRect().height, EPSILON);
  BOOST_CHECK_CLOSE(8.0, compositeShape.getFrameRect().pos.x, EPSILON);
  BOOST_CHECK_CLOSE(13.0, compositeShape.getFrameRect().pos.y, EPSILON);
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(CompositeShape_rotate)

BOOST_AUTO_TEST_CASE(CompositeShape_rotating_correctness)
{
  std::shared_ptr<klimchuk::Shape> circle = std::make_shared<klimchuk::Circle>(5.0, 1.0, 6.0);
  std::shared_ptr<klimchuk::Shape> rectangle = std::make_shared<klimchuk::Rectangle>(7.0, 1.0, 8.0, 13.0);
  std::shared_ptr<klimchuk::Shape> triangle = std::make_shared<klimchuk::Triangle>(klimchuk::point_t{ 1.0, 2.0 },
    klimchuk::point_t{ 3.0, -1.0 }, klimchuk::point_t{ 2.0, 5.0 });
  klimchuk::CompositeShape compositeShape(rectangle);
  const klimchuk::point_t centreOfCompositeShape = compositeShape.getCentre();
  const klimchuk::rectangle_t frameRectangle = compositeShape.getFrameRect();
  const double degrees = 180.0;
  compositeShape.rotate(degrees);
  BOOST_CHECK_CLOSE(compositeShape.getFrameRect().width, frameRectangle.width, EPSILON);
  BOOST_CHECK_CLOSE(compositeShape.getFrameRect().height, frameRectangle.height, EPSILON);
  BOOST_CHECK_CLOSE(compositeShape.getCentre().x, centreOfCompositeShape.x, EPSILON);
  BOOST_CHECK_CLOSE(compositeShape.getCentre().y, centreOfCompositeShape.y, EPSILON);
}

BOOST_AUTO_TEST_SUITE_END()
