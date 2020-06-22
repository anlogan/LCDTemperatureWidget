#include <TFT.h> // Arduino LCD library
#include <SPI.h>

// pin definition 
#define cs 10
#define dc 9
#define rst 7

// create an instance of the library
TFT TFTscreen = TFT(cs, dc, rst);

// char array to print percentage to screen
char tempArray[5];
char percentArray[5];
bool flag = true;
int cpuPercent =43;
int gpuPercent =100;
int cpuTemp =0;
int gpuTemp =0;

class RGBval
{
  public:
    int r = 0;
    int g = 0;
    int b = 0;
    RGBval(){};
    RGBval(int r, int g, int b) {
      this->r = r;
      this->g = g;
      this->b = b;
    }
    void set_rgb(int r, int g, int b) {
      this->r = r;
      this->g = g;
      this->b = b;
    }
};

class Rectangle
{
  public:
    int x,y,l,h;
    RGBval rgb;
    Rectangle();
    Rectangle(int x, int y, int l, int h, RGBval rgb) {
      this->x = x;
      this->y = y;
      this->l = l;
      this->h = h;
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

  // set the font color to white
  TFTscreen.stroke(255, 255, 255);
  // ste the font size very large for the loop
  TFTscreen.setTextSize(5);
}

void drawPercent(double percent, RGBval rgb, int x, int y)
{
  String percentString = String((int)percent) + "%";
  percentString.toCharArray(percentArray, 5);

  TFTscreen.setTextSize(2);

  // set the font color
  TFTscreen.stroke(rgb.b, rgb.g, rgb.r);
  // print the sensor value
  TFTscreen.text(percentArray, x, y);
}

int drawRectangle(Rectangle rect, RGBval rgb)
{
  TFTscreen.noStroke();
  TFTscreen.fill(rgb.b, rgb.g, rgb.r); // set fill color
  TFTscreen.rect(rect.x, rect.y, rect.l, rect.h);  
  return 1;
}

void drawBar(double percent, Rectangle outer, Rectangle inner)
{

  // draw outer rectangle
  drawRectangle(outer, outer.rgb);

  // Inner rectangle
  if (percent > 0 && percent <= 50) {
    inner.set_rgb(30,230,30); // green 
  }
  else if (percent >50 && percent <=70) {
    inner.set_rgb(255,255,0); // yellow
  }
  else if (percent >70 && percent <=100) {
    inner.set_rgb(255,0,0); // red
  }
  else {
    //TODO error over 100%
  }

  // draw inner w/ percent change
  double lengthAdj = 84 * percent / (double)100;
  inner.l = (int)lengthAdj; // Vary this value by % of 84? 
  drawRectangle(inner,inner.rgb);
  RGBval percentRGB(30,30,30);
  // -17 and -10 for x and y are to center the text itself, otherwise it centers the upper left corner
  drawPercent(percent, percentRGB, outer.l / (2) +outer.x - 17, outer.h /2 + outer.y - 7 );
}

void drawTemp(double tempVal, int x, int y)
{
  String tempString = String((int)tempVal) + "c";
  tempString.toCharArray(tempArray, 5);
  RGBval rgb;
  TFTscreen.setTextSize(3);

  if (tempVal > 0 && tempVal <= 50) {
    rgb.set_rgb(30,230,30); // green 
  }
  else if (tempVal >50 && tempVal <=75) {
    rgb.set_rgb(255,255,0); // yellow
  }
  else if (tempVal >75 && tempVal <=100) {
    rgb.set_rgb(255,0,0); // red
  }
  // set the font color
  TFTscreen.stroke(rgb.b, rgb.g, rgb.r);
  // print the sensor value
  TFTscreen.text(tempArray, x, y);
}

RGBval outerCPURGB(190,190,190);
RGBval innerCPURGB(0,240,0);
RGBval outerGPURGB(190,190,190);
RGBval innerGPURGB(0,240,0);

Rectangle outerCPU(63,10, TFTscreen.width() - 70,35, outerCPURGB);
Rectangle innerCPU(66,13, TFTscreen.width() - 76,29, innerCPURGB);
Rectangle outerGPU(63,65, TFTscreen.width() - 70,35, outerGPURGB);
Rectangle innerGPU(66,68, TFTscreen.width() - 76,29, innerGPURGB);

void loop()
{
  // draw top bar
  drawBar(cpuPercent, outerCPU, innerCPU);
  // draw bot bar
  drawBar(gpuPercent, outerGPU, innerGPU);
  // CPU Temp
  drawTemp(40, 5, 16);
  // GPU Temp
  drawTemp(32, 5, 71);


  // wait for a moment
  delay(2000);
  TFTscreen.fill(0, 0, 0); // set fill color
  TFTscreen.noStroke();
  TFTscreen.rect(0, 0, 59, 40);
  // TFTscreen.background(0,0,0);
}
