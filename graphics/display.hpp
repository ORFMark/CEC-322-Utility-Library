#ifndef MRBUTIL_GRAPHICS_DISPLAY_H_
#define MRBUTIL_GRAPHICS_DISPLAY_H_


#include "mrbUtil/graphics/shapes.hpp"

#define MAX_SHAPE 16

extern "C++" {
class Display {
private:
  tContext frameBuffer[2];
  Shape* sprites[16];
  uint16_t numberOfShapes;
public:
  Display();
  uint8_t addShape(Shape* shapeToAdd);
  void removeShape(uint8_t shapeKey);
  void update();
};
}
#endif /*MRBUTIL_GRAPHICS_DISPLAY_H_*/