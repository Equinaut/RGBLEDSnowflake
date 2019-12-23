//Simple animations

void wipe(color col=pixels.Color(0,0,0),int wipeSpeed=4,int dir=0) {
  for (int i=-400;i<400;i+=wipeSpeed) {
    for (int pixel=0;pixel<NUMPIXELS;pixel++) {
      switch (dir) {
        case 0: if (ys[pixel]<=i)    pixels.setPixelColor(pixel,col); break;   //Wipes from top to botom
        case 1: if (ys[pixel]>=-1*i) pixels.setPixelColor(pixel,col); break;   //Wipes from bottom to top
        case 2: if (xs[pixel]<=i)    pixels.setPixelColor(pixel,col); break;   //Wipes from left to right
        case 3: if (xs[pixel]>=-1*i) pixels.setPixelColor(pixel,col); break;   //Wipes from right to left
      }
    }
    pixels.show();
    if (changeMode()) return;
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


//All modes

void mode0() { //Blue-green random pixels
  //Run at start
  for (int i=0; i<NUMPIXELS;i++) {
    pixels.setPixelColor(i,pixels.Color(0,random(255),random(255)));
  }
  pixels.show();
  boolean modeChange = false;
  //Keep running until escaped
  while (!modeChange) {
    pixels.setPixelColor(int(random(0,NUMPIXELS)),pixels.Color(0,random(255),random(255)));
    pixels.show();
    delay(8);
    modeChange = changeMode();
  }
}
void mode1() { //Random wipe
  int dirs[] = {0,3,1,2};
  for (int i=0;i<4;i++) {
    wipe(pixels.Color(random(255),random(255),random(255)),4,dirs[i]);
    if (changeMode()) return;
  }
}
void mode2() {
  for (int col=0;col<6;col++) {
    for (int i=0;i<91;i++) {
      pixels.setPixelColor(spiral[i],mainCols[col]);
      pixels.show();
      delay(10);
      if (changeMode()) return;
    }
  }
}
void mode3() {
  for (int col=0;col<6;col+=2) {
    circleFrom(mainCols[col],5,90,0);
    if (changeMode()) return;
    circleFrom(mainCols[col+1],5,90,1);
    if (changeMode()) return;
  }
}
void mode4() {
  for (int col=0;col<6;col+=2) {
    wipe(mainCols[col],4,0);
    if (changeMode()) return;
    wipe(mainCols[col+1],4,1);
    if (changeMode()) return;
  }
}
void mode5() {
  for (int col=0;col<6;col+=2) {
    wipe(mainCols[col],4,2);
    if (changeMode()) return;
    wipe(mainCols[col+1],4,3);
    if (changeMode()) return;
  }
}
void mode6() {
  for (int col=0;col<6;col++) {
    circleFrom(mainCols[col],5,int(random(90)));
    if (changeMode()) return;
  }
}
void mode7() {
  for (int pixel=0;pixel<NUMPIXELS;pixel++) {
    int r = int(float(xs[pixel]+400)*255/800);
    int g = int(float(ys[pixel]+400)*255/800);
    
    pixels.setPixelColor(pixel,pixels.Color(r,g,0));
  }
  pixels.show();
}
