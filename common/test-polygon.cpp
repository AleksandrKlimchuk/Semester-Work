#include <stdexcept>
#include "boost/test/unit_test.hpp"
#include "polygon.hpp"
#include "shape.hpp"

const double EPSILON = 0.000001;

BOOST_AUTO_TEST_SUITE(Polygon_constructor)

BOOST_AUTO_TEST_CASE(Polygon_valid_constructor)
{
  klimchuk::Polygon polygon({ { -3.0, -3.0 }, { -3.0, 3.0 },
    { 3.0, 3.0 }, { 3.0, -3.0 } });
  BOOST_CHECK_EQUAL(polygon.getSize(), 4);
  BOOST_CHECK_CLOSE(polygon[0].x, -3.0, EPSILON);
  BOOST_CHECK_CLOSE(polygon[0].y, -3.0, EPSILON);
  BOOST_CHECK_CLOSE(polygon[1].x, -3.0, EPSILON);
  BOOST_CHECK_CLOSE(polygon[1].y,  3.0, EPSILON);
  BOOST_CHECK_CLOSE(polygon[2].x,  3.0, EPSILON);
  BOOST_CHECK_CLOSE(polygon[2].y,  3.0, EPSILON);
  BOOST_CHECK_CLOSE(polygon[3].x,  3.0, EPSILON);
  BOOST_CHECK_CLOSE(polygon[3].y, -3.0, EPSILON);
}

BOOST_AUTO_TEST_CASE(Polygon_invalid_constructor)
{
  BOOST_CHECK_THROW(klimchuk::Polygon({ { 1.0, 2.0 }, { 2.0, 3.0 } }), std::length_error);
  BOOST_CHECK_THROW(klimchuk::Polygon({ { 1.0, 0.0 }, { 5.0, 0.0 },
    { 10.0, 0.0 } }), std::invalid_argument);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(Polygon_area)

BOOST_AUTO_TEST_CASE(Polygon_area_before_moving_and_scaling)
{
  klimchuk::Polygon polygon({ { -3.0, -3.0 }, { -3.0, 3.0 },
    { 3.0, 3.0 }, { 3.0, -3.0 } });
  BOOST_CHECK_CLOSE(polygon.getArea(), 6 * 6, EPSILON);
}

BOOST_AUTO_TEST_CASE(Polygon_area_after_moving)
{
  klimchuk::Polygon polygon({ { -3.0, -3.0 }, { -3.0, 3.0 },
    { 3.0, 3.0 }, { 3.0, -3.0 } });
  const double movingX = 5.0;
  const double movingY = 6.0;
  polygon.move(movingX, movingY);
  BOOST_CHECK_CLOSE(polygon.getArea(), 6 * 6, EPSILON);

  const klimchuk::point_t newCenter{ 10.0, 12.0 };
  polygon.move(newCenter);
  BOOST_CHECK_CLOSE(polygon.getArea(), 6 * 6, EPSILON);
}

BOOST_AUTO_TEST_CASE(Polygon_area_after_scaling)
{
  klimchuk::Polygon polygon({ { -3.0, -3.0 }, { -3.0, 3.0 },
    { 3.0, 3.0 }, { 3.0, -3.0 } });
  const double coefficient = 1.5;
  polygon.scale(coefficient);
  BOOST_CHECK_CLOSE(polygon.getArea(), 6 * 6 * coefficient * coefficient, EPSILON);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(polygon_get_frame_rect)

BOOST_AUTO_TEST_CASE(polygon_frame_rect_before_scaling)
{
  klimchuk::Polygon polygon({ { -3.0, -3.0 }, { -3.0, 3.0 },
    { 3.0, 3.0 }, { 3.0, -3.0 } });
  klimchuk::rectangle_t rectangle = polygon.getFrameRect();
  BOOST_CHECK_CLOSE(rectangle.height, 6, EPSILON);
  BOOST_CHECK_CLOSE(rectangle.width, 6, EPSILON);
  BOOST_CHECK_CLOSE(rectangle.pos.x, polygon.getCentre().x, EPSILON);
  BOOST_CHECK_CLOSE(rectangle.pos.y, polygon.getCentre().y, EPSILON);
}

BOOST_AUTO_TEST_CASE(Polygon_frame_rect_after_scaling)
{
  klimchuk::Polygon polygon({ { -3.0, -3.0 }, { -3.0, 3.0 },
    { 3.0, 3.0 }, { 3.0, -3.0 } });
  const double coefficient = 1.5;
  polygon.scale(coefficient);
  klimchuk::rectangle_t rectangle = polygon.getFrameRect();
  BOOST_CHECK_CLOSE(rectangle.height, 6 * coefficient, EPSILON);
  BOOST_CHECK_CLOSE(rectangle.width, 6 * coefficient, EPSILON);
  BOOST_CHECK_CLOSE(rectangle.pos.x, polygon.getCentre().x, EPSILON);
  BOOST_CHECK_CLOSE(rectangle.pos.y, polygon.getCentre().y, EPSILON);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(polygon_moving)

BOOST_AUTO_TEST_CASE(polygon_moving_add_abscissa_ordinate)
{
  klimchuk::Polygon polygon({ { -3.0, -3.0 }, { -3.0, 3.0 },
    { 3.0, 3.0 }, { 3.0, -3.0 } });
  const double moveAbscissa = 71.0;
  const double moveOrdinate = 13.0;
  polygon.move(moveAbscissa, moveOrdinate);
  BOOST_CHECK_CLOSE(polygon.getCentre().x, 0.0 + moveAbscissa, EPSILON);
  BOOST_CHECK_CLOSE(polygon.getCentre().y, 0.0 + moveOrdinate, EPSILON);
}

BOOST_AUTO_TEST_CASE(Polygon_move_to_point)
{
  klimchuk::Polygon polygon({ { -3.0, -3.0 }, { -3.0, 3.0 },
    { 3.0, 3.0 }, { 3.0, -3.0 } });
  const klimchuk::point_t newCenter{ 8.0, 11.0 };
  polygon.move(newCenter);
  BOOST_CHECK_CLOSE(polygon.getCentre().x, newCenter.x, EPSILON);
  BOOST_CHECK_CLOSE(polygon.getCentre().y, newCenter.y, EPSILON);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(polygon_scaling)

BOOST_AUTO_TEST_CASE(polygon_scaling_valid)
{
  klimchuk::Polygon polygon({ { -3.0, -3.0 }, { -3.0, 3.0 },
    { 3.0, 3.0 }, { 3.0, -3.0 } });
  const double coefficient = 3.0;
  polygon.scale(coefficient);
  BOOST_CHECK_CLOSE(polygon.getCentre().x, 0.0, EPSILON);
  BOOST_CHECK_CLOSE(polygon.getCentre().y, 0.0, EPSILON);
  BOOST_CHECK_CLOSE(polygon.getFrameRect().pos.x, 0.0, EPSILON);
  BOOST_CHECK_CLOSE(polygon.getFrameRect().pos.y, 0.0, EPSILON);
  BOOST_CHECK_CLOSE(polygon.getFrameRect().width, 6.0 * coefficient, EPSILON);
  BOOST_CHECK_CLOSE(polygon.getFrameRect().height, 6.0 * coefficient, EPSILON);
}
BOOST_AUTO_TEST_CASE(cirlce_scaling_invalid)
{
  klimchuk::Polygon polygon({ { -3.0, -3.0 }, { -3.0, 3.0 },
    { 3.0, 3.0 }, { 3.0, -3.0 } });
  BOOST_CHECK_THROW(polygon.scale(-11.0), std::invalid_argument);
  BOOST_CHECK_THROW(polygon.scale(0), std::invalid_argument);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(polygon_rotate)

BOOST_AUTO_TEST_CASE(polygon_rotating_correctness)
{
  klimchuk::Polygon polygon({ { -3.0, -3.0 }, { -3.0, 3.0 },
    { 3.0, 3.0 }, { 3.0, -3.0 } });
  const klimchuk::point_t centreOfPolygon = polygon.getCentre();
  const klimchuk::rectangle_t rectangle = polygon.getFrameRect();
  const double degrees = 180.0;
  polygon.rotate(degrees);
  BOOST_CHECK_CLOSE(polygon.getCentre().x, centreOfPolygon.x, EPSILON);
  BOOST_CHECK_CLOSE(polygon.getCentre().y, centreOfPolygon.y, EPSILON);
  BOOST_CHECK_CLOSE(polygon.getFrameRect().width, rectangle.width, EPSILON);
  BOOST_CHECK_CLOSE(polygon.getFrameRect().height, rectangle.height, EPSILON);
}

BOOST_AUTO_TEST_SUITE_END()
