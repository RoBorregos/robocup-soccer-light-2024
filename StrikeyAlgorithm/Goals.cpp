#include "Arduino.h"
#include "Goals.h"

Goals::Goals() {
}

void Goals::updateData(String str) {
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
    width = arr[2];
    height = arr[3];
    area = width * height;

}

String Goals::getTag() {
  return tag;
}

int Goals::getY() {
  return y;
}

int Goals::getX() {
  return x;
}


int Goals::getWidth() {
  return width;
}

int Goals::getHeight() {
  return height;
} 

int Goals::getArea(){
    return area;
}