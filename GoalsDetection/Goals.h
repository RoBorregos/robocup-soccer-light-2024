#ifndef Goals_h
  #define Goals_h

class Goals {
  private:
    String tag = ""; 
    int x = -1;
    int y = -1;
    int width = -1;
    int height = -1;
    int area = 0;

    public:

    Goals();
    void updateData(String str);
    int getX();
    int getY();
    String getTag();
    int getArea();
    int getWidth();
    int getHeight();
    
};

#endif