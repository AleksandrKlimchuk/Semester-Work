#include <stdexcept>
#include "boost/test/unit_test.hpp"
#include "rectangle.hpp"

const double EPSILON = 0.000001;

BOOST_AUTO_TEST_SUITE(rectangle_constructor)

BOOST_AUTO_TEST_CASE(rectangle_valid_construct)
{
  klimchuk::Rectangle rectangle(10.0, 12.0, 1.0, 2.0);
  BOOST_CHECK_CLOSE(rectangle.getWidth(), 10.0, EPSILON);
  BOOST_CHECK_CLOSE(rectangle.getHeight(), 12.0, EPSILON);
  BOOST_CHECK_CLOSE(rectangle.getCentre().x, 1.0, EPSILON);
  BOOST_CHECK_CLOSE(rectangle.getCentre().y, 2.0, EPSILON);
}

BOOST_AUTO_TEST_CASE(rectangle_invalid_construct)
{
  BOOST_CHECK_THROW(klimchuk::Rectangle rectangle(-10.0, 12.0, 1.0, 2.0), std::invalid_argument);
  BOOST_CHECK_THROW(klimchuk::Rectangle rectangle(10.0, -12.0, 1.0, 2.0), std::invalid_argument);
  BOOST_CHECK_THROW(klimchuk::Rectangle rectangle(0.0, 12.0, 1.0, 2.0), std::invalid_argument);
  BOOST_CHECK_THROW(klimchuk::Rectangle rectangle(10.0, 0.0, 1.0, 2.0), std::invalid_argument);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(rectangle_area)
BOOST_AUTO_TEST_CASE(rectangle_area_before_moving_and_scaling)
{
  klimchuk::Rectangle rectangle(18.0, 11.0, 3.0, 12.0);
  BOOST_CHECK_CLOSE(rectangle.getArea(), 18.0 * 11.0, EPSILON);
}
BOOST_AUTO_TEST_CASE(rectangle_area_after_moving)
{
  klimchuk::Rectangle rectangle(18.0, 11.0, 3.0, 12.0);
  const double movingX = 5.0;
  const double movingY = 6.0;
  rectangle.move(movingX, movingY);
  BOOST_CHECK_CLOSE(rectangle.getArea(), 18.0 * 11.0, EPSILON);
  klimchuk::point_t newCentre{1.0, 9.0};
  rectangle.move(newCentre);
  BOOST_CHECK_CLOSE(rectangle.getArea(), 18.0 * 11.0, EPSILON);
}
BOOST_AUTO_TEST_CASE(rectangle_area_after_scaling)
{
  klimchuk::Rectangle rectangle(18.0, 11.0, 3.0, 12.0);
  const double coefficient = 1.5;
  rectangle.scale(coefficient);
  BOOST_CHECK_CLOSE(rectangle.getArea(), 18.0 * 11.0 * coefficient * coefficient, EPSILON);
}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(rectangle_frame_rect)
BOOST_AUTO_TEST_CASE(rectangle_frame_rect_valid)
{
  klimchuk::Rectangle rectangle(1.0, 13.0, 12.0, 4.0);
  BOOST_CHECK_CLOSE(rectangle.getFrameRect().width, 1.0, EPSILON);
  BOOST_CHECK_CLOSE(rectangle.getFrameRect().height, 13.0, EPSILON);
  BOOST_CHECK_CLOSE(rectangle.getFrameRect().pos.x, 12.0, EPSILON);
  BOOST_CHECK_CLOSE(rectangle.getFrameRect().pos.y, 4.0, EPSILON);
}
BOOST_AUTO_TEST_CASE(rectangle_frame_rect_after_scaling)
{
  klimchuk::Rectangle rectangle(1.0, 13.0, 12.0, 4.0);
  const double coefficient = 2.0;
  rectangle.scale(coefficient);
  BOOST_CHECK_CLOSE(rectangle.getFrameRect().width, 1.0 * coefficient, EPSILON);
  BOOST_CHECK_CLOSE(rectangle.getFrameRect().height, 13.0 * coefficient, EPSILON);
  BOOST_CHECK_CLOSE(rectangle.getFrameRect().pos.x, 12.0, EPSILON);
  BOOST_CHECK_CLOSE(rectangle.getFrameRect().pos.y, 4.0, EPSILON);
}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(rectangle_moving)
BOOST_AUTO_TEST_CASE(rectangle_moving_add_abscissa_ordinate)
{
  klimchuk::Rectangle rectangle(8.0, 7.0, 1.0, 0.0);
  const double movingX = 5.0;
  const double movingY = 6.0;
  rectangle.move(movingX, movingY);
  BOOST_CHECK_CLOSE(rectangle.getCentre().x, 1.0 + movingX, EPSILON);
  BOOST_CHECK_CLOSE(rectangle.getCentre().y, 0.0 + movingY, EPSILON);
}
BOOST_AUTO_TEST_CASE(rectangle_move_to_point)
{
  klimchuk::Rectangle rectangle(8.0, 7.0, 1.0, 0.0);
  klimchuk::point_t newCentre{ 6.0, 7.0 };
  rectangle.move(newCentre);
  BOOST_CHECK_CLOSE(rectangle.getCentre().x, newCentre.x, EPSILON);
  BOOST_CHECK_CLOSE(rectangle.getCentre().y, newCentre.y, EPSILON);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(rectangle_scaling)
BOOST_AUTO_TEST_CASE(rectangle_scaling_valid)
{
  klimchuk::Rectangle rectangle(3.0, 13.0, 8.0, 12.0);
  const double coefficient = 4.0;
  rectangle.scale(coefficient);
  BOOST_CHECK_CLOSE(rectangle.getCentre().x, 8.0, EPSILON);
  BOOST_CHECK_CLOSE(rectangle.getCentre().y, 12.0, EPSILON);
  BOOST_CHECK_CLOSE(rectangle.getFrameRect().pos.x, 8.0, EPSILON);
  BOOST_CHECK_CLOSE(rectangle.getFrameRect().pos.y, 12.0, EPSILON);
  BOOST_CHECK_CLOSE(rectangle.getFrameRect().width, 3.0 * coefficient, EPSILON);
  BOOST_CHECK_CLOSE(rectangle.getFrameRect().height, 13.0 * coefficient, EPSILON);
}
BOOST_AUTO_TEST_CASE(rectangle_scaling_invalid)
{
  klimchuk::Rectangle rectangle(3.0, 13.0, 8.0, 12.0);
  BOOST_CHECK_THROW(rectangle.scale(-6.0), std::invalid_argument);
  BOOST_CHECK_THROW(rectangle.scale(0.0), std::invalid_argument);
}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(rectangle_rotate)

BOOST_AUTO_TEST_CASE(rectangle_rotating_correctness)
{
  klimchuk::Rectangle rectangle(3.0, 13.0, 8.0, 12.0);
  const double degrees = 180.0;
  rectangle.rotate(degrees);
  BOOST_CHECK_CLOSE(rectangle.getFrameRect().pos.x, 8.0, EPSILON);
  BOOST_CHECK_CLOSE(rectangle.getFrameRect().pos.y, 12.0, EPSILON);
  BOOST_CHECK_CLOSE(rectangle.getFrameRect().width, 3.0, EPSILON);
  BOOST_CHECK_CLOSE(rectangle.getFrameRect().height, 13.0, EPSILON);
}

BOOST_AUTO_TEST_SUITE_END()
