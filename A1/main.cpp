#include <iostream>

#include "rectangle.hpp"
#include "circle.hpp"
#include "triangle.hpp"

int main(int, char**)
{
  double width = 8.0 , height = 4.2, abscissa = -9.0, ordinate = 7.2, radius = 5.0;
  point_t centreOfCircle{4, 5.2};
  point_t firstTop{1, 1.5}, secondTop{6.2, 0.5}, thirdTop{4, 5.2};
  Rectangle rectangle(width, height, abscissa, ordinate);
  Circle circle(centreOfCircle.x, centreOfCircle.y, radius);
  Triangle triangle(firstTop, secondTop, thirdTop);

  std::cout << "The area of rectangle: " << rectangle.getArea() << '\n'
      << "The area of circle: " << circle.getArea() << '\n'
      << "The area of triangle: " << triangle.getArea() << "\n\n";

  std::cout << "Centres before moving:\n"
      << "The centre of rectangle: (" << rectangle.getCentre().x << ", " << rectangle.getCentre().y << ")\n"
      << "The centre of circle: (" << circle.getCentre().x << ", " << circle.getCentre().y << ")\n"
      << "The centre of triangle: (" << triangle.getCentre().x << ", " << triangle.getCentre().y << ")\n\n";

  double movingX = 9, movingY = 6;
  point_t newCentre{5, 19};
  rectangle.move(movingX, movingY);
  circle.move(newCentre);
  triangle.move(movingX, movingY);

  std::cout << "Centres after moving:\n"
      << "The centre of rectangle: (" << rectangle.getCentre().x << ", " << rectangle.getCentre().y << ")\n"
      << "The centre of circle: (" << circle.getCentre().x << ", " << circle.getCentre().y << ")\n"
      << "The centre of triangle: (" << triangle.getCentre().x << ", " << triangle.getCentre().y << ")\n\n";

  Shape* shape = &rectangle;
  std::cout << "Shape pointer:\n" << "The area of rectangle: " << shape->getArea() << '\n';
  shape = &circle;
  std::cout << "The area of circle: " << shape->getArea() << '\n';
  shape = &triangle;
  std::cout << "The area of triangle: " << shape->getArea() << '\n';

  return 0;
}
