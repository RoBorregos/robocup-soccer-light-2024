#include "Porteria.h"

Porteria::Porteria() : color(-1), x(-1), y(-1), w(-1), h(-1), area(-1) {}

void Porteria::actualizar(const String& str) {
    int arr[4];
    String data = "";
    int index = 0;

    for (int i = 2; i < str.length() && index < 4; i++) {
        if (!(str[i] == ',')) {
            data += str[i];
        } else if (str[i] == ',' || i == str.length() - 1) {
            arr[index++] = data.toInt();
            data = "";
        }
    }

    x = arr[0];
    y = arr[1];
    w = arr[2];
    h = data.toInt();
    area = w * h;
}

void Porteria::setX(int xs) {
    x = xs;
}

int Porteria::getX() const {
    return x;
}

int Porteria::getY() const {
    return y;
}

int Porteria::getColor() const {
    return color;
}

int Porteria::getArea() const {
    return area;
}

int Porteria::getLargo() const {
    return w;
}

int Porteria::getAlto() const {
    return h;
}
