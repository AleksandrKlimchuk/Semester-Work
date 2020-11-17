#include <cmath>
#include <stdexcept>
#include "boost/test/unit_test.hpp"
#include "circle.hpp" 

const double EPSILON = 0.000001;

BOOST_AUTO_TEST_SUITE(circle_construction)

BOOST_AUTO_TEST_CASE(circle_construction_valid)
{
  klimchuk::Circle circle(2.8, 4.16, 2.089);
  BOOST_CHECK_CLOSE(circle.getRadius(), 2.089, EPSILON);
  BOOST_CHECK_CLOSE(circle.getCentre().x, 2.8, EPSILON);
  BOOST_CHECK_CLOSE(circle.getCentre().y, 4.16, EPSILON);
}

BOOST_AUTO_TEST_CASE(circle_construction_invalid)
{
  BOOST_CHECK_THROW(klimchuk::Circle circle(12.0, 13.0, -1.0), std::invalid_argument);
  BOOST_CHECK_THROW(klimchuk::Circle circle(12.0, 13.0, 0.0), std::invalid_argument);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(circle_area)

BOOST_AUTO_TEST_CASE(circle_area_before_moving_and_scaling)
{
  klimchuk::Circle circle(1.0, 2.0, 10.0);
  BOOST_CHECK_CLOSE(circle.getArea(), M_PI * 10 * 10, EPSILON); 
}

BOOST_AUTO_TEST_CASE(circle_area_after_moving)
{
  klimchuk::Circle circle(1.0, 2.0, 10.0);
  const double movingX = 5.0;
  const double movingY = 6.0;
  circle.move(movingX, movingY);
  BOOST_CHECK_CLOSE(circle.getArea(), M_PI * 10 * 10, EPSILON);

  const klimchuk::point_t newCenter{10.0, 12.0};
  circle.move(newCenter);
  BOOST_CHECK_CLOSE(circle.getArea(), M_PI * 10 * 10, EPSILON);
}

BOOST_AUTO_TEST_CASE(circle_area_after_scaling)
{
  klimchuk::Circle circle(1.0, 2.0, 10.0);
  const double coefficient = 1.5;
  circle.scale(coefficient);
  BOOST_CHECK_CLOSE(circle.getArea(), M_PI * 10 * 10 * coefficient * coefficient, EPSILON);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(circle_get_frame_rect)

BOOST_AUTO_TEST_CASE(circle_frame_rect_before_scaling)
{
  klimchuk::Circle circle(12.0, 1.0, 10.0);
  klimchuk::rectangle_t rectangle = circle.getFrameRect();
  BOOST_CHECK_CLOSE(rectangle.height, circle.getRadius() * 2, EPSILON);
  BOOST_CHECK_CLOSE(rectangle.width, circle.getRadius() * 2, EPSILON);
  BOOST_CHECK_CLOSE(rectangle.pos.x, circle.getCentre().x, EPSILON);
  BOOST_CHECK_CLOSE(rectangle.pos.y, circle.getCentre().y, EPSILON);
}

BOOST_AUTO_TEST_CASE(circle_frame_rect_after_scaling)
{
  klimchuk::Circle circle(12.0, 1.0, 10.0);
  const double coefficient = 1.5;
  circle.scale(coefficient);
  klimchuk::rectangle_t rectangle = circle.getFrameRect();
  BOOST_CHECK_CLOSE(rectangle.height, 10.0 * 2 * coefficient, EPSILON);
  BOOST_CHECK_CLOSE(rectangle.width, 10.0 * 2 * coefficient, EPSILON);
  BOOST_CHECK_CLOSE(rectangle.pos.x, circle.getCentre().x, EPSILON);
  BOOST_CHECK_CLOSE(rectangle.pos.y, circle.getCentre().y, EPSILON);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(circle_moving)

BOOST_AUTO_TEST_CASE(circle_moving_add_abscissa_ordinate)
{
  klimchuk::Circle circle(14.0, 7.0, 12.0);
  const double moveAbscissa = 71.0;
  const double moveOrdinate = 13.0;
  circle.move(moveAbscissa, moveOrdinate);
  BOOST_CHECK_CLOSE(circle.getCentre().x, 14.0 + moveAbscissa, EPSILON);
  BOOST_CHECK_CLOSE(circle.getCentre().y, 7.0 + moveOrdinate, EPSILON);
}

BOOST_AUTO_TEST_CASE(circle_move_to_point)
{
  klimchuk::Circle circle(14.0, 7.0, 12.0);
  const klimchuk::point_t newCenter{ 8.0, 11.0 };
  circle.move(newCenter);
  BOOST_CHECK_CLOSE(circle.getCentre().x, newCenter.x, EPSILON);
  BOOST_CHECK_CLOSE(circle.getCentre().y, newCenter.y, EPSILON);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(circle_scaling)

BOOST_AUTO_TEST_CASE(circle_scaling_valid)
{
  klimchuk::Circle circle(13.0, 11.0, 8.0);
  const double coefficient = 3.0;
  circle.scale(coefficient);
  BOOST_CHECK_CLOSE(circle.getRadius(), 8.0 * coefficient, EPSILON);
  BOOST_CHECK_CLOSE(circle.getCentre().x, 13.0, EPSILON);
  BOOST_CHECK_CLOSE(circle.getCentre().y, 11.0, EPSILON);
  BOOST_CHECK_CLOSE(circle.getFrameRect().pos.x, 13.0, EPSILON);
  BOOST_CHECK_CLOSE(circle.getFrameRect().pos.y, 11.0, EPSILON);
  BOOST_CHECK_CLOSE(circle.getFrameRect().width, 8.0 * 2 * coefficient, EPSILON);
  BOOST_CHECK_CLOSE(circle.getFrameRect().height, 8.0 * 2 * coefficient, EPSILON);
}
BOOST_AUTO_TEST_CASE(cirlce_scaling_invalid)
{
  klimchuk::Circle circle(13.0, 11.0, 8.0);
  BOOST_CHECK_THROW(circle.scale(-11.0), std::invalid_argument);
  BOOST_CHECK_THROW(circle.scale(0), std::invalid_argument);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(circle_rotate)

BOOST_AUTO_TEST_CASE(circle_rotating_correctness)
{
  klimchuk::Circle circle(13.0, 11.0, 8.0);
  const double degrees = 100.0;
  const double width = circle.getFrameRect().width;
  const double height = circle.getFrameRect().height;
  circle.rotate(degrees);
  BOOST_CHECK_CLOSE(circle.getCentre().x, 13.0, EPSILON);
  BOOST_CHECK_CLOSE(circle.getCentre().y, 11.0, EPSILON);
  BOOST_CHECK_CLOSE(circle.getFrameRect().width, width, EPSILON);
  BOOST_CHECK_CLOSE(circle.getFrameRect().height, height, EPSILON);
}

BOOST_AUTO_TEST_SUITE_END()
