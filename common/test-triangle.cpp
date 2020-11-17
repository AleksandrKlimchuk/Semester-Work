#include <stdexcept>
#include <algorithm>
#include "boost/test/unit_test.hpp"
#include "triangle.hpp"

const double EPSILON = 0.000001;

BOOST_AUTO_TEST_SUITE(triangle_constructor)
BOOST_AUTO_TEST_CASE(triangle_valid_construct)
{
  klimchuk::Triangle triangle({1.0, 2.0}, {3.0, -1.0}, {2.0, 5.0});
  BOOST_CHECK_CLOSE(triangle.getCentre().x, (1.0 + 3.0 + 2.0) / 3, EPSILON);
  BOOST_CHECK_CLOSE(triangle.getCentre().y, (2.0 - 1.0 + 5.0) / 3, EPSILON);
  BOOST_CHECK_CLOSE(triangle.getFrameRect().pos.x, (1.0 + 3.0 + 2.0) / 3, EPSILON);
  BOOST_CHECK_CLOSE(triangle.getFrameRect().pos.y, (2.0 - 1.0 + 5.0) / 3, EPSILON);
  BOOST_CHECK_CLOSE(triangle.getFrameRect().width, std::max({1.0, 3.0, 2.0}) - std::min({ 1.0, 3.0, 2.0 }), EPSILON);
  BOOST_CHECK_CLOSE(triangle.getFrameRect().height, std::max({2.0, -1.0, 5.0}) - std::min({2.0, -1.0, 5.0}), EPSILON);
}

BOOST_AUTO_TEST_CASE(triangle_invalid_construct)
{
  klimchuk::point_t a{1.0, 2.0}, b{3.0, -1.0}, c{ 2.0, 5.0};
  BOOST_CHECK_THROW(klimchuk::Triangle triangle(a, a, a), std::invalid_argument);
  BOOST_CHECK_THROW(klimchuk::Triangle triangle(a, a, b), std::invalid_argument);
  BOOST_CHECK_THROW(klimchuk::Triangle triangle(a, a, c), std::invalid_argument);
  BOOST_CHECK_THROW(klimchuk::Triangle triangle(a, b, a), std::invalid_argument);
  BOOST_CHECK_THROW(klimchuk::Triangle triangle(a, c, a), std::invalid_argument);
  BOOST_CHECK_THROW(klimchuk::Triangle triangle(b, a, a), std::invalid_argument);
  BOOST_CHECK_THROW(klimchuk::Triangle triangle(c, a, a), std::invalid_argument);
  BOOST_CHECK_THROW(klimchuk::Triangle triangle(b, b, b), std::invalid_argument);
  BOOST_CHECK_THROW(klimchuk::Triangle triangle(b, b, a), std::invalid_argument);
  BOOST_CHECK_THROW(klimchuk::Triangle triangle(b, b, c), std::invalid_argument);
  BOOST_CHECK_THROW(klimchuk::Triangle triangle(b, a, b), std::invalid_argument);
  BOOST_CHECK_THROW(klimchuk::Triangle triangle(b, c, b), std::invalid_argument);
  BOOST_CHECK_THROW(klimchuk::Triangle triangle(a, b, b), std::invalid_argument);
  BOOST_CHECK_THROW(klimchuk::Triangle triangle(c, b, b), std::invalid_argument);
  BOOST_CHECK_THROW(klimchuk::Triangle triangle(c, c, c), std::invalid_argument);
  BOOST_CHECK_THROW(klimchuk::Triangle triangle(c, c, a), std::invalid_argument);
  BOOST_CHECK_THROW(klimchuk::Triangle triangle(c, c, b), std::invalid_argument);
  BOOST_CHECK_THROW(klimchuk::Triangle triangle(c, a, c), std::invalid_argument);
  BOOST_CHECK_THROW(klimchuk::Triangle triangle(c, b, c), std::invalid_argument);
  BOOST_CHECK_THROW(klimchuk::Triangle triangle(a, c, c), std::invalid_argument);
  BOOST_CHECK_THROW(klimchuk::Triangle triangle(b, c, c), std::invalid_argument);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(triangle_area)
BOOST_AUTO_TEST_CASE(triangle_area_before_moving_and_scaling)
{
  klimchuk::Triangle triangle({ 1.0, 2.0 }, { 3.0, -1.0 }, { 2.0, 5.0 });
  BOOST_CHECK_CLOSE(triangle.getArea(), std::abs(((1.0 - 2.0) * (-1.0 - 5.0)) - ((3.0 - 2.0) * (2.0 - 5.0))) / 2, EPSILON);
}
BOOST_AUTO_TEST_CASE(triangle_area_after_moving)
{
  klimchuk::Triangle triangle({ 1.0, 2.0 }, { 3.0, -1.0 }, { 2.0, 5.0 });
  const double movingX = 5.0;
  const double movingY = 6.0;
  triangle.move(movingX, movingY);
  BOOST_CHECK_CLOSE(triangle.getArea(), std::abs(((1.0 - 2.0) * (-1.0 - 5.0)) - ((3.0 - 2.0) * (2.0 - 5.0))) / 2, EPSILON);

  klimchuk::point_t newCentre{ 1.0, 9.0 };
  triangle.move(newCentre);
  BOOST_CHECK_CLOSE(triangle.getArea(), std::abs(((1.0 - 2.0) * (-1.0 - 5.0)) - ((3.0 - 2.0) * (2.0 - 5.0))) / 2, EPSILON);
}
BOOST_AUTO_TEST_CASE(triangle_area_after_scaling)
{
  klimchuk::Triangle triangle({ 1.0, 2.0 }, { 3.0, -1.0 }, { 2.0, 5.0 });
  const double coefficient = 2.5;
  triangle.scale(coefficient);
  BOOST_CHECK_CLOSE(triangle.getArea(), (std::abs(((1.0 - 2.0) * (-1.0 - 5.0)) - ((3.0 - 2.0) * (2.0 - 5.0))) / 2) * coefficient * coefficient, EPSILON);
}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(triangle_frame_rect)
BOOST_AUTO_TEST_CASE(triangle_frame_rect_before_scaling)
{
  klimchuk::Triangle triangle({ 1.0, 2.0 }, { 3.0, -1.0 }, { 2.0, 5.0 });
  BOOST_CHECK_CLOSE(triangle.getFrameRect().pos.x, (1.0 + 3.0 + 2.0) / 3, EPSILON);
  BOOST_CHECK_CLOSE(triangle.getFrameRect().pos.y, (2.0 - 1.0 + 5.0) / 3, EPSILON);
  BOOST_CHECK_CLOSE(triangle.getFrameRect().width, std::max({ 1.0, 3.0, 2.0 }) - std::min({ 1.0, 3.0, 2.0 }), EPSILON);
  BOOST_CHECK_CLOSE(triangle.getFrameRect().height, std::max({ 2.0, -1.0, 5.0 }) - std::min({ 2.0, -1.0, 5.0 }), EPSILON);
}
BOOST_AUTO_TEST_CASE(triangle_frame_rect_after_scale)
{
  klimchuk::Triangle triangle({ 1.0, 2.0 }, { 3.0, -1.0 }, { 2.0, 5.0 });
  double coefficient = 1.5;
  triangle.scale(coefficient);
  BOOST_CHECK_CLOSE(triangle.getFrameRect().pos.x, (1.0 + 3.0 + 2.0) / 3, EPSILON);
  BOOST_CHECK_CLOSE(triangle.getFrameRect().pos.y, (2.0 - 1.0 + 5.0) / 3, EPSILON);
  BOOST_CHECK_CLOSE(triangle.getFrameRect().width, (std::max({ 1.0, 3.0, 2.0 }) - std::min({ 1.0, 3.0, 2.0 })) * coefficient, EPSILON);
  BOOST_CHECK_CLOSE(triangle.getFrameRect().height, (std::max({ 2.0, -1.0, 5.0 }) - std::min({ 2.0, -1.0, 5.0 })) * coefficient, EPSILON);
}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(triangle_moving)
BOOST_AUTO_TEST_CASE(triangle_moving_add_abscissa_ordinate)
{
  klimchuk::Triangle triangle({ 1.0, 2.0 }, { 3.0, -1.0 }, { 2.0, 5.0 });
  const double movingX = 5.0;
  const double movingY = 6.0;
  triangle.move(movingX, movingY);
  BOOST_CHECK_CLOSE(triangle.getCentre().x, ((1.0 + 3.0 + 2.0) / 3) + movingX, EPSILON);
  BOOST_CHECK_CLOSE(triangle.getCentre().y, ((2.0 - 1.0 + 5.0) / 3) + movingY, EPSILON);
}
BOOST_AUTO_TEST_CASE(triangle_move_to_point)
{
  klimchuk::Triangle triangle({ 1.0, 2.0 }, { 3.0, -1.0 }, { 2.0, 5.0 });
  klimchuk::point_t newCentre{ 6.0, 7.0 };
  triangle.move(newCentre);
  BOOST_CHECK_CLOSE(triangle.getCentre().x, newCentre.x, EPSILON);
  BOOST_CHECK_CLOSE(triangle.getCentre().y, newCentre.y, EPSILON);

}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(triangle_scaling)
BOOST_AUTO_TEST_CASE(triangle_scaling_valid)
{
  klimchuk::Triangle triangle({ 1.0, 2.0 }, { 3.0, -1.0 }, { 2.0, 5.0 });
  double coefficient = 1.5;
  triangle.scale(coefficient);
  BOOST_CHECK_CLOSE(triangle.getArea(), (std::abs(((1.0 - 2.0) * (-1.0 - 5.0)) - ((3.0 - 2.0) * (2.0 - 5.0))) / 2) * coefficient * coefficient, EPSILON);
  BOOST_CHECK_CLOSE(triangle.getCentre().x, (1.0 + 3.0 + 2.0) / 3, EPSILON);
  BOOST_CHECK_CLOSE(triangle.getCentre().y, (2.0 - 1.0 + 5.0) / 3, EPSILON);
  BOOST_CHECK_CLOSE(triangle.getFrameRect().pos.x, (1.0 + 3.0 + 2.0) / 3, EPSILON);
  BOOST_CHECK_CLOSE(triangle.getFrameRect().pos.y, (2.0 - 1.0 + 5.0) / 3, EPSILON);
  BOOST_CHECK_CLOSE(triangle.getFrameRect().width, (std::max({ 1.0, 3.0, 2.0 }) - std::min({ 1.0, 3.0, 2.0 })) * coefficient, EPSILON);
  BOOST_CHECK_CLOSE(triangle.getFrameRect().height, (std::max({ 2.0, -1.0, 5.0 }) - std::min({ 2.0, -1.0, 5.0 })) * coefficient, EPSILON);

}
BOOST_AUTO_TEST_CASE(triangle_scaling_invalid)
{
  klimchuk::Triangle triangle({ 1.0, 2.0 }, { 3.0, -1.0 }, { 2.0, 5.0 });
  BOOST_CHECK_THROW(triangle.scale(0.0), std::invalid_argument);
  BOOST_CHECK_THROW(triangle.scale(-12.0), std::invalid_argument);
}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(triangle_rotate)

BOOST_AUTO_TEST_CASE(triangle_rotating_correctness)
{
  klimchuk::Triangle triangle({ 1.0, 2.0 }, { 3.0, -1.0 }, { 2.0, 5.0 });
  const double degrees = 720.0;
  klimchuk::rectangle_t rectnalge = triangle.getFrameRect();
  triangle.rotate(degrees);
  BOOST_CHECK_CLOSE(triangle.getCentre().x, (1.0 + 3.0 + 2.0) / 3.0, EPSILON);
  BOOST_CHECK_CLOSE(triangle.getCentre().y, (2.0 - 1.0 + 5.0) / 3.0, EPSILON);
  BOOST_CHECK_CLOSE(triangle.getFrameRect().width, rectnalge.width, EPSILON);
  BOOST_CHECK_CLOSE(triangle.getFrameRect().height, rectnalge.height, EPSILON);
}

BOOST_AUTO_TEST_SUITE_END()
