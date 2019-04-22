#ifndef MRBUTIL_GRAPHICS_SHAPES_H_
#define MRBUTIL_GRAPHICS_SHAPES_H_



#define MAX_STR_LEN 64

extern "C++" {
std::class Shape {
protected:
  int16_t color;
  int16_t centerX;
  int16_t centerY;
public:

  Shape(int16_t color, int16_t centerX, int16_t centerY);
  virtual void changeColor(int16_t newColor);
  virtual void moveShape(int16_t newCenterX, int16_t newCenterY);
  virtual void draw(tContext* frame);
};
}

class Rectangle: public Shape {
private:
  tRectangle rect;
public:
  Rectangle(int16_t color, int16_t centerX, int16_t centerY);
  void changeColor(int16_t newColor);
  void moveShape(int16_t newCenterX, int16_t newCenterY);
  void draw(tContext* frame);
};

class Circle: public Shape {
private:
  int32_t radius;
public:
  Circle (int16_t color, int16_t centerX, int16_t centerY, int32_t radius);
  void changeRadius(int32_t newRadius);
  void changeColor(int16_t newColor);
  void moveShape(int16_t newCenterX, int16_t newCenterY);
  void draw(tContext* frame);
};

class Text: public Shape {
private:
  char thisStr[MAX_STR_LEN];
public: 
  Text(int16_t color, int16_t centerX, int16_t centerY);
  void changeColor(int16_t newColor);
  void moveShape(int16_t newCenterX, int16_t newCenterY);
  void draw(tContext* frame);
};

#endif /* MRBUTIL_GRAPHICS_SHAPES_H_ */