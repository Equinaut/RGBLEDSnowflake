#include <Adafruit_NeoPixel.h>

#define TOTALMODES 8

#define NUMPIXELS 91
#define LEDPIN 6
#define BUTTONPIN 5
int mode = 7;

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, LEDPIN, NEO_RGB + NEO_KHZ400);
typedef void (*function) (void);
typedef uint32_t color;
color mainCols[] = {pixels.Color(150,0,0),pixels.Color(150,150,0),pixels.Color(0,150,0),pixels.Color(0,150,150),pixels.Color(0,0,150),pixels.Color(150,0,150)}; //List of basic colours to be used

const int spiral[] = {90,88,87,86,85,84,89,42,28,14,0,70,56,43,29,15,1,71,57,44,30,16,2,72,58,69,59,60,46,45,55,54,53,32,31,41,40,39,18,17,27,26,25,4,3,13,12,11,74,73,83,82,81,67,68,65,63,61,47,49,51,33,35,37,19,21,23,5,7,9,75,77,79,66,64,62,48,50,52,34,36,38,20,22,24,6,8,10,76,78,80};

const int xs[] = {0, 0, 0, 39, 80, 39, 78, 0, 0, -39, -78, -79, -37, 0, 111, 153, 192, 231, 229, 270, 312, 271, 312, 229, 230, 150, 193, 231, 111, 151, 189, 192, 153, 231, 229, 270, 311, 268, 311, 231, 230, 231, 0, 0, 0, -39, -79, -41, -77, -1, -1, 39, 78, 78, 39, 0, -111, -153, -191, -190, -151, -231, -231, -270, -312, -270, -310, -232, -232, -229, -112, -152, -192, -192, -151, -231, -231, -270, -312, -271, -310, -230, -229, -233, -51, 0, 50, 52, 0, -51, 0};
const int ys[] = {129, 175, 221, 242, 219, 290, 310, 310, 359, 289, 312, 221, 243, 265, 64, 88, 110, 89, 43, 111, 88, 157, 181, 179, 224, 177, 156, 132, -65, -86, -110, -156, -178, -177, -223, -157, -178, -110, -87, -41, -86, -133, -128, -175, -220, -242, -220, -289, -312, -312, -359, -289, -314, -220, -243, -265, -63, -87, -109, -155, -178, -178, -225, -156, -179, -111, -86, -40, -87, -133, 66, 89, 110, 156, 178, 176, 223, 158, 179, 111, 88, 42, 88, 133, 29, 61, 29, -29, -61, -30, 0};


void setup() {
  pinMode(BUTTONPIN,INPUT);
  pixels.setBrightness(50);
  pixels.begin();
}

void loop() {
  changeMode();
  function modes[] = {mode0,mode1,mode2,mode3,mode4,mode5,mode6,mode7};    //An array of all the modes
  
  modes[mode]();
  pixels.show();
} 

boolean changeMode() {  //Checks if the button is pressed, an if it is it moves on to hte next mode
  if (digitalRead(BUTTONPIN)==HIGH) {
    if(++mode>=TOTALMODES) mode=0; //Increments the mode by 1 and if it is then higher than the amount of modes, it is set to 0
    pixels.clear();
    for (int i=0; i<=mode;i++) pixels.setPixelColor(i,pixels.Color(255,255,255));
    pixels.show();
    delay(500);
    pixels.clear();
    pixels.show();
    return true;
  }
  return false;
}
