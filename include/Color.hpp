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


// Defining some colors
const Color _RED(255, 0, 0);
const Color _GREEN(0, 255, 0);
const Color _BLUE(0, 0, 255);
const Color _WHITE(255, 255, 255);
const Color _BLACK(0, 0, 0);
const Color _CRIMSON(220, 20, 60);
const Color _MAROON(255, 52, 179);

#endif
