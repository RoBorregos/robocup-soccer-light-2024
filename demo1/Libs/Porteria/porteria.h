#ifndef Porteria_h
#define Porteria_h

#include <Arduino.h>

class Porteria {
private:
    int color;
    int x;
    int y;
    int w;
    int h;
    int area;

public:
    Porteria();
    void actualizar(const String& str);
    void setX(int xs);
    int getX() const;
    int getY() const;
    int getColor() const;
    int getArea() const;
    int getLargo() const;
    int getAlto() const;
};

#endif
