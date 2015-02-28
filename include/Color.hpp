#ifndef COLOR_HPP
#define COLOR_HPP

class Color {
  public :
    Color(int r, int g, int b) : _red(r), _green(g), _blue(b) {}

    void getRGB(int& r, int& g, int& b) const 
      { r=_red; g=_green; b=_blue; }

    void setRGB(int r, int g, int b) 
      { _red=r; _green=g; _blue=b; }

  private :
    int _red;
    int _green;
    int _blue;
};
#endif
