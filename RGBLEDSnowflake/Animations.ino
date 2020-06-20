//Simple animations

void wipe(colour col=pixels.Color(0,0,0),int wipeSpeed=4,int dir=0) {
  for (int i=-400;i<400;i+=wipeSpeed) {
    for (int pixel=0;pixel<NUMPIXELS;pixel++) {
      switch (dir) {
        case 0: if (ys[pixel]<=i)     pixels.setPixelColor(pixel,col); break;  //Wipes from top to botom
        case 1: if (ys[pixel]>=-1*i)  pixels.setPixelColor(pixel,col); break;  //Wipes from bottom to top
        case 2: if (xs[pixel]<=i)     pixels.setPixelColor(pixel,col); break;  //Wipes from left to right
        case 3: if (xs[pixel]>=-1*i)  pixels.setPixelColor(pixel,col); break;  //Wipes from right to left
      }
    }
    pixels.show();
    if (changeMode()) return;
  }
}
void circleFrom(colour col=pixels.Color(0,0,0),int radStep=5,int centerLED = 90,int dir=0) { //Circles in or out from a particular LED on the snowflake
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
void rotate(colour col=pixels.Color(0,0,0),float rotateSpeed=0.15,int firstSpeed = 30,int radius = 400) {
  //Stage0 - Run up the first bar of the rotate
  for (int pixel:spokes[0]) {
    if (ys[pixel]<-radius) break;
    pixels.setPixelColor(pixel,col);
    pixels.show();
    delay(firstSpeed);
    if (changeMode()) return;
  }
  for (float a=-PI/2+rotateSpeed;a<=3*PI/2;a+=rotateSpeed) {
    for (int pixel=0;pixel<NUMPIXELS;pixel++) {
      if (xs[pixel]>=0 && ys[pixel]<=xs[pixel]*tan(a)  && pow(xs[pixel],2)+pow(ys[pixel],2)<=pow(radius,2)) pixels.setPixelColor(pixel,col);
      if (ys[pixel]>=xs[pixel]*tan(a) && a>=PI/2 && pow(xs[pixel],2)+pow(ys[pixel],2)<=pow(radius,2)) pixels.setPixelColor(pixel,col);
    }
    if (changeMode()) return;
    pixels.show();
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

void mode1() {
  for (colour col:mainCols) {
    for (int i=0;i<91;i++) {
      pixels.setPixelColor(spiral[i],col);
      pixels.show();
      delay(10);
      if (changeMode()) return;
    }
  }
}
void mode2() {
  int dir=0;
  for (colour col:mainCols) {
    if (changeMode()) return;
    circleFrom(col,5,90,dir=1-dir);
  }
}
void mode3() {
  int dir=0;
  for (colour col:mainCols) {
    if (changeMode()) return;
    wipe(col,4,dir++);
    if (dir>=4) dir=0;
  }
}
void mode4() {
  for (colour col:mainCols) {
    circleFrom(col,5,int(random(90)));
    if (changeMode()) return;
  }
}
void mode5() {
  for (int pixel=0;pixel<NUMPIXELS;pixel++) {
    int r = int(float(xs[pixel]+400)*255/800);
    int g = int(float(ys[pixel]+400)*255/800);

    pixels.setPixelColor(pixel,pixels.Color(r,g,0));
  }
  pixels.show();
}
void mode6() {
  for (colour col:mainCols) {
    rotate(col);
    if (changeMode()) return;
  }
}
void mode7() {
  int delayVal = 75;
  for (colour col:mainCols) {
    for (int i=0;i<8;i++) {
      for (int j=0;j<6;j++) pixels.setPixelColor(spokes[j][i],col);
      pixels.show();
      delay(delayVal);
      if (changeMode()) return;
    }
    for (int i=0;i<10;i++) {
      for (int j=0;j<6;j++) pixels.setPixelColor(otherLines[j][i],col);
      pixels.show();
      delay(delayVal);
      if (changeMode()) return;
    }
  }
}
