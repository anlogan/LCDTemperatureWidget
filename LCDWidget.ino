#include <TFT.h> // Arduino LCD library
#include <SPI.h>

// pin definition 
#define cs 10
#define dc 9
#define rst 7

// create an instance of the library
TFT TFTscreen = TFT(cs, dc, rst);

// char array to print percentage to screen
char valArray[4];

class RGB
{
  public:
  int r = 0;
  int g = 0;
  int b = 0;
  RGB();
  RGB(int r, int g, int b) {
    this->r = r;
    this->g = g;
    this->b = b;
  }
};

class Rectangle
{
  public:
    int x,y,l,w;
    RGB rgb;
    Rectangle();
    Rectangle(int x, int y, int l, int w, RGB rgb) {
      this->x = x;
      this->y = y;
      this->l = l;
      this->w = w;
      this->rgb = rgb;
    }

    void set_rgb(int r, int g, int b) {
      this->rgb.r = r;
      this->rgb.g = g;
      this->rgb.b = b;
    }
};
void setup()
{

  // Put this line at the beginning of every sketch that uses the GLCD:
  TFTscreen.begin();

  // clear the screen with a black background
  TFTscreen.background(0, 0, 0);

  // write the static text to the screen
  // set the font color to white
  TFTscreen.stroke(255, 255, 255);
  // ste the font size very large for the loop
  TFTscreen.setTextSize(5);
}

int a = 0;
int b = 0;
int counter = 0;
bool flag = true;
int percentage = 0;



int drawRectangle(Rectangle rect, RGB rgb)
{
  TFTscreen.noStroke();
  TFTscreen.fill(rgb.b, rgb.g, rgb.r); // set fill color
  TFTscreen.rect(rect.x, rect.y, rect.l, rect.w);  
  return 1;
}

/*
void drawBar(double percent, Rectangle::Rectangle outter, Rectangle::Rectangle inner)
{

  // draw outter rectangle
  // check percent for color?
  
  // Inner rectangle
  if (percent > 0 && percent <= 33) {
    TFTscreen.fill(30,230,30); // set fill color
  }
  else if (percent >33 && percent <=66) {
    TFTscreen.fill(0,255,255); // set fill color
  }
  else if (percent >66 && percent <=100) {
    TFTscreen.fill(0,0,255); // set fill color
  }
  else {
    //TODO error over 100%
  }
  TFTscreen.rect(63,8,a,w-6);
  
  // draw inner w/ percent change
}
*/

void drawPercent(double percentVal, RGB rgb)
{
  String percentString = String((int)percentVal) + "%";
  percentString.toCharArray(valArray, 4);

  TFTscreen.setTextSize(3);

  // set the font color
  TFTscreen.stroke(rgb.b, rgb.g, rgb.r);
  // print the sensor value
  TFTscreen.text(valArray, 5, 10);
}

void loop()
{
  // Rectangle innerCPU;
  // Rectangle outterGPU;
  // Rectangle innerGPU;
  RGB outterCPURGB(190,190,190);
  
  Rectangle outterCPU(60,5,95,25, outterCPURGB);


  drawRectangle(outterCPU,outterCPURGB);

  // wait for a moment
  delay(500);
  TFTscreen.fill(0, 0, 0); // set fill color
  TFTscreen.noStroke();
  TFTscreen.rect(0, 0, 59, 40);
  // TFTscreen.background(0,0,0);
}
