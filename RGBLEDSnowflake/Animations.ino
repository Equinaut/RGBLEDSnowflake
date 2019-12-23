//Define all modes
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
    wipe(pixels.Color(random(255),random(255),random(255)),15,dirs[i]);
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
    circleFrom(mainCols[col+1],5,90,1);
    if (changeMode()) break;
  }
}
void mode4() {
  for (int col=0;col<6;col+=2) {
    wipe(mainCols[col],35,0);
    wipe(mainCols[col],35,1);
    if (changeMode()) return;
  }
}
void mode5() {
  for (int col=0;col<6;col+=2) {
    wipe(mainCols[col],35,2);
    wipe(mainCols[col+1],35,3);
    if (changeMode()) return;
  }
}
void mode6() {
  for (int col=0;col<6;col+=2) {
    wipe(mainCols[col],100,4);
    wipe(mainCols[col+1],100,5);
    if (changeMode()) return;
  }
}
void mode7() {
  for (int col=0;col<6;col++) {
    circleFrom(mainCols[col],5,int(random(90)));
    if (changeMode()) return;
  }
}
