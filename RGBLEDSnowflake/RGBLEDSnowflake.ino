#include <Adafruit_NeoPixel.h>

#define TOTALMODES 8
#define NUMPIXELS 91
#define LEDPIN 6
#define BUTTONPIN 5
int mode = 7;

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, LEDPIN, NEO_RGB + NEO_KHZ400);
typedef uint32_t color;
color mainCols[] = {pixels.Color(150,0,0),pixels.Color(150,150,0),pixels.Color(0,150,0),pixels.Color(0,150,150),pixels.Color(0,0,150),pixels.Color(150,0,150)}; //List of basic colours to be used

//Define LED Groups
//There are 7 wings including the middle
const int wings[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,4,4,4,4,4,4,4,4,4,4,4,4,4,4,5,5,5,5,5,5,5,5,5,5,5,5,5,5,6,6,6,6,6,6,6};
//There are 8 rings
//OLD RINGS const int rings[] = {5, 4, 3, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 2, 5, 4, 3, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 2, 5, 4, 3, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 2, 5, 4, 3, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 2, 5, 4, 3, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 2, 5, 4, 3, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 2, 6, 6, 6, 6, 6, 6, 7};
const int rings[] = {2, 3, 4, 5, 5, 6, 7, 6, 7, 6, 7, 5, 5, 5, 2, 3, 4, 5, 5, 6, 7, 6, 7, 6, 7, 5, 5, 5, 2, 3, 4, 5, 5, 6, 7, 6, 7, 6, 7, 5, 5, 5, 2, 3, 4, 5, 5, 6, 7, 6, 7, 6, 7, 5, 5, 5, 2, 3, 4, 5, 5, 6, 7, 6, 7, 6, 7, 5, 5, 5, 2, 3, 4, 5, 5, 6, 7, 6, 7, 6, 7, 5, 5, 5, 1, 1, 1, 1, 1, 1, 0};
//There are 27 rows
const int rows[] = {18, 19, 21, 22, 21, 24, 25, 25, 26, 24, 25, 21, 22, 23, 15, 16, 17, 16, 15, 17, 16, 19, 20, 20, 21, 20, 19, 18, 11, 10, 9, 7, 6, 6, 4, 7, 6, 9, 10, 11, 10, 8, 8, 6, 5, 4, 5, 2, 1, 1, 0, 2, 1, 5, 4, 3, 11, 10, 9, 7, 6, 6, 4, 7, 6, 9, 10, 11, 10, 8, 15, 16, 17, 19, 20, 20, 21, 19, 20, 17, 16, 15, 16, 18, 14, 15, 14, 12, 11, 12, 13};
//There are 17 columns
const int cols[] = {8, 8, 8, 9, 10, 9, 10, 8, 8, 7, 6, 6, 7, 8, 11, 12, 13, 14, 14, 15, 16, 15, 16, 14, 14, 12, 13, 14, 11, 12, 13, 13, 12, 14, 14, 15, 16, 15, 16, 14, 14, 14, 8, 8, 8, 7, 6, 7, 6, 8, 8, 9, 10, 10, 9, 8, 5, 4, 3, 3, 4, 2, 2, 1, 0, 1, 0, 2, 2, 2, 5, 4, 3, 3, 4, 2, 2, 1, 0, 1, 0, 2, 2, 2, 7, 8, 9, 9, 8, 7, 8};
//List of led numbers in order of a spiral
const int spiral[] = {90,88,87,86,85,84,89,42,28,14,0,70,56,43,29,15,1,71,57,44,30,16,2,72,58,69,59,60,46,45,55,54,53,32,31,41,40,39,18,17,27,26,25,4,3,13,12,11,74,73,83,82,81,67,68,65,63,61,47,49,51,33,35,37,19,21,23,5,7,9,75,77,79,66,64,62,48,50,52,34,36,38,20,22,24,6,8,10,76,78,80};

const int xs[] = {399, 400, 400, 439, 480, 439, 478, 400, 400, 361, 322, 321, 363, 400, 511, 553, 592, 631, 629, 670, 712, 671, 712, 629, 630, 550, 593, 631, 511, 551, 589, 592, 553, 631, 629, 670, 711, 668, 711, 631, 630, 631, 400, 400, 400, 361, 321, 359, 323, 399, 399, 439, 478, 478, 439, 400, 289, 247, 209, 210, 249, 169, 169, 130, 88, 130, 90, 168, 168, 171, 288, 248, 208, 208, 249, 169, 169, 130, 88, 129, 90, 170, 171, 167, 349, 400, 450, 452, 400, 349, 400};
const int ys[] = {529, 575, 621, 642, 619, 690, 710, 710, 759, 689, 712, 621, 643, 665, 464, 488, 510, 489, 443, 511, 488, 557, 581, 579, 624, 577, 556, 532, 335, 314, 290, 244, 222, 223, 177, 243, 222, 290, 313, 359, 314, 267, 272, 225, 180, 158, 180, 111, 88, 88, 41, 111, 86, 180, 157, 135, 337, 313, 291, 245, 222, 222, 175, 244, 221, 289, 314, 360, 313, 267, 466, 489, 510, 556, 578, 576, 623, 558, 579, 511, 488, 442, 488, 533, 429, 461, 429, 371, 339, 370, 400};


void setup() {
  pinMode(BUTTONPIN,INPUT);
  pixels.setBrightness(50);
  pixels.begin();
}

void loop() {
  changeMode();
  typedef void (*function) (void);
  function modes[] = {mode0,mode1,mode2,mode3,mode4,mode5,mode6,mode7};    //An array of all the modes
  modes[mode]();
  pixels.show();
} 

boolean changeMode() {  //Checks if the button is pressed, an if it is it moves on to hte next mode
  if (digitalRead(BUTTONPIN)==HIGH) {
    mode+=1;
    if(mode>=TOTALMODES) mode=0;
    
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

void wipe(int r=0,int g=0,int b=0,int dist = 100,int dir=0,boolean hsv=false,boolean useRGB=true,color col=pixels.Color(0,0,0)) {
  int startLayer,endLayer,layerStep;
  int *groups;
  
  switch (dir) {
    case 0: startLayer = 0,  endLayer = 8,  layerStep = 1;  groups = rings;  break;   //Wipes from outside to inside
    case 1: startLayer = 7,  endLayer = 0,  layerStep = -1; groups = rings;  break;   //Wipes from inside to outside
    case 2: startLayer = 0,  endLayer = 27, layerStep = 1;  groups = rows;   break;   //Wipes from top to bottom
    case 3: startLayer = 26, endLayer = 0,  layerStep = -1; groups = rows;   break;   //Wipes from bottom to top
    case 4: startLayer = 0,  endLayer = 17, layerStep = 1;  groups = cols;   break;   //Wipes from left to right
    case 5: startLayer = 16, endLayer = 0,  layerStep = -1; groups = cols;   break;   //Wipes from right to left
    case 6: startLayer = 5,  endLayer = 0,  layerStep = -1; groups = wings;  break;   //Wipes through each wing clockwise
    case 7: startLayer = 6,  endLayer = 0,  layerStep = 1;  groups = wings;  break;   //Wipes through each wing counter-clockwise
  }
  if (useRGB && !hsv) col = pixels.Color(r,g,b);
  else if (useRGB && hsv) col = pixels.ColorHSV(r,g,b);
  
  for (int layer=startLayer; layer<max(startLayer+1,endLayer) && layer>=0; layer+=layerStep) {
    for (int i=0;i<=NUMPIXELS;i++) if (groups[i]==layer) pixels.setPixelColor(i,col);
    if (changeMode()) return;
    delay(dist); 
    pixels.show();
  }
}

void split(int r,int g,int b,int dist = 100, int dir=0, boolean hsv=false,boolean useRGB = true,color col=pixels.Color(0,0,0)) {
  int startLayer,endLayer,layerStep,totalLayers;
  int *groups;
  switch (dir) {
    case 0: startLayer = 0,  endLayer = 13, layerStep =  1, totalLayers=26; groups = rows; break; //Wipes inwards  vertically 
    case 1: startLayer = 13, endLayer = 0,  layerStep = -1, totalLayers=26; groups = rows; break; //Wipes outwards vertically
    case 2: startLayer = 0,  endLayer = 8,  layerStep =  1, totalLayers=16; groups = cols; break; //Wipes inwards  horizontally
    case 3: startLayer = 8,  endLayer = 0,  layerStep = -1, totalLayers=16; groups = cols; break; //Wipes outwards horizontally
  }
  
  if (useRGB && !hsv) col = pixels.Color(r,g,b);
  else if (useRGB && hsv) col = pixels.ColorHSV(r,g,b);
  
  for (int layer=startLayer; layer<max(startLayer+1,endLayer+1) && layer>=0; layer+=layerStep) {
    for (int i=0;i<91;i++) if (groups[i]==layer || groups[i]==totalLayers-layer) pixels.setPixelColor(i,col);
    if (changeMode()) return;
    delay(dist);
    pixels.show();
  }
}
