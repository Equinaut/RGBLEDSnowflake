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

//Define LED Groups
//There are 7 wings including the middle
const int wings[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,4,4,4,4,4,4,4,4,4,4,4,4,4,4,5,5,5,5,5,5,5,5,5,5,5,5,5,5,6,6,6,6,6,6,6};
//There are 8 rings
//OLD RINGS const int rings[] = {5, 4, 3, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 2, 5, 4, 3, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 2, 5, 4, 3, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 2, 5, 4, 3, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 2, 5, 4, 3, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 2, 5, 4, 3, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 2, 6, 6, 6, 6, 6, 6, 7};
//const int rings[] = {2, 3, 4, 5, 5, 6, 7, 6, 7, 6, 7, 5, 5, 5, 2, 3, 4, 5, 5, 6, 7, 6, 7, 6, 7, 5, 5, 5, 2, 3, 4, 5, 5, 6, 7, 6, 7, 6, 7, 5, 5, 5, 2, 3, 4, 5, 5, 6, 7, 6, 7, 6, 7, 5, 5, 5, 2, 3, 4, 5, 5, 6, 7, 6, 7, 6, 7, 5, 5, 5, 2, 3, 4, 5, 5, 6, 7, 6, 7, 6, 7, 5, 5, 5, 1, 1, 1, 1, 1, 1, 0};
//There are 27 rows
const int rows[] = {18, 19, 21, 22, 21, 24, 25, 25, 26, 24, 25, 21, 22, 23, 15, 16, 17, 16, 15, 17, 16, 19, 20, 20, 21, 20, 19, 18, 11, 10, 9, 7, 6, 6, 4, 7, 6, 9, 10, 11, 10, 8, 8, 6, 5, 4, 5, 2, 1, 1, 0, 2, 1, 5, 4, 3, 11, 10, 9, 7, 6, 6, 4, 7, 6, 9, 10, 11, 10, 8, 15, 16, 17, 19, 20, 20, 21, 19, 20, 17, 16, 15, 16, 18, 14, 15, 14, 12, 11, 12, 13};
//There are 17 columns
const int cols[] = {8, 8, 8, 9, 10, 9, 10, 8, 8, 7, 6, 6, 7, 8, 11, 12, 13, 14, 14, 15, 16, 15, 16, 14, 14, 12, 13, 14, 11, 12, 13, 13, 12, 14, 14, 15, 16, 15, 16, 14, 14, 14, 8, 8, 8, 7, 6, 7, 6, 8, 8, 9, 10, 10, 9, 8, 5, 4, 3, 3, 4, 2, 2, 1, 0, 1, 0, 2, 2, 2, 5, 4, 3, 3, 4, 2, 2, 1, 0, 1, 0, 2, 2, 2, 7, 8, 9, 9, 8, 7, 8};
//List of led numbers in order of a spiral from the center out
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

//Simple animations

void wipe(color col=pixels.Color(0,0,0),int dist = 100,int dir=0) {
  int startLayer,endLayer,layerStep;
  int *groups;
  
  switch (dir) {
    case 0: startLayer = 0,  endLayer = 27, layerStep = 1;  groups = rows;   break;   //Wipes from top to bottom
    case 1: startLayer = 26, endLayer = 0,  layerStep = -1; groups = rows;   break;   //Wipes from bottom to top
    case 2: startLayer = 0,  endLayer = 17, layerStep = 1;  groups = cols;   break;   //Wipes from left to right
    case 3: startLayer = 16, endLayer = 0,  layerStep = -1; groups = cols;   break;   //Wipes from right to left
    case 4: startLayer = 5,  endLayer = 0,  layerStep = -1; groups = wings;  break;   //Wipes through each wing clockwise
    case 5: startLayer = 6,  endLayer = 0,  layerStep = 1;  groups = wings;  break;   //Wipes through each wing counter-clockwise
  }
  
  for (int layer=startLayer; layer<max(startLayer+1,endLayer) && layer>=0; layer+=layerStep) {
    for (int i=0;i<=NUMPIXELS;i++) if (groups[i]==layer) pixels.setPixelColor(i,col);
    if (changeMode()) return;
    delay(dist); 
    pixels.show();
  }
}

void split(color col=pixels.Color(0,0,0),int dist = 100, int dir=0) {
  int startLayer,endLayer,layerStep,totalLayers;
  int *groups;
  switch (dir) {
    case 0: startLayer = 0,  endLayer = 13, layerStep =  1, totalLayers=26; groups = rows; break; //Wipes inwards  vertically 
    case 1: startLayer = 13, endLayer = 0,  layerStep = -1, totalLayers=26; groups = rows; break; //Wipes outwards vertically
    case 2: startLayer = 0,  endLayer = 8,  layerStep =  1, totalLayers=16; groups = cols; break; //Wipes inwards  horizontally
    case 3: startLayer = 8,  endLayer = 0,  layerStep = -1, totalLayers=16; groups = cols; break; //Wipes outwards horizontally
  }
  for (int layer=startLayer; layer<max(startLayer+1,endLayer+1) && layer>=0; layer+=layerStep) {
    for (int i=0;i<91;i++) if (groups[i]==layer || groups[i]==totalLayers-layer) pixels.setPixelColor(i,col);
    if (changeMode()) return;
    delay(dist);
    pixels.show();
  }
}
void circleFrom(color col=pixels.Color(0,0,0),int radStep=5,int centerLED = 90,int dir=0) { //Circles in or out from a particular LED on the snowflake
  int maxDistance = 0;
  int distances[NUMPIXELS];
  
  for (int i=0; i<NUMPIXELS;i++) {
    distances[i] = pow(pow(xs[i]-xs[centerLED],2)+pow(ys[i]-ys[centerLED],2),0.5 );
    if (distances[i]>maxDistance) maxDistance = distances[i];
  }
  for (int radius = 0;radius<=maxDistance+radStep;radius+=radStep) {
    if (dir==0) for (int i=0; i<NUMPIXELS;i++) if (distances[i]<=radius) pixels.setPixelColor(i,col);             //Circle in
    if (dir==1) for (int i=0; i<NUMPIXELS;i++) if (distances[i]>=maxDistance-radius) pixels.setPixelColor(i,col); //Circle out 
    pixels.show();
    if (changeMode()) return;  
  }
}
