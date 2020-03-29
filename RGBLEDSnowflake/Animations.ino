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
  int dirs[] = {2,5,3,4};
  for (int i=0;i<4;i++) {
    wipe(random(255),random(255),random(255),15,dirs[i]);
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
    wipe(0,0,0,100,0,false,false,mainCols[col]);
    wipe(0,0,0,100,1,false,false,mainCols[col+1]);
    if (changeMode()) break;
  }
}
void mode4() {
  for (int col=0;col<6;col+=2) {
    wipe(0,0,0,35,2,false,false,mainCols[col]);
    wipe(0,0,0,35,3,false,false,mainCols[col+1]);
    if (changeMode()) return;
  }
}
void mode5() {
  for (int col=0;col<6;col+=2) {
    wipe(0,0,0,35,4,false,false,mainCols[col]);
    wipe(0,0,0,35,5,false,false,mainCols[col+1]);
    if (changeMode()) return;
  }
}
void mode6() {
  for (int col=0;col<6;col+=2) {
    wipe(0,0,0,100,6,false,false,mainCols[col]);
    wipe(0,0,0,100,7,false,false,mainCols[col+1]);
    if (changeMode()) return;
  }
}
void mode7() {
  int centerLED = 0;
  int distances[NUMPIXELS];
  int maxDistance = 0;
  for (int i=0; i<NUMPIXELS;i++) {
    int distance = int(sqrt(sq(xs[i]-xs[centerLED])+sq(ys[i]-ys[centerLED]))); 
    distances[i] = distance;
    if (distance>maxDistance) maxDistance = distance;
  }
  for (int radius=0;radius<maxDistance;radius++) {
    for (int i=0; i<NUMPIXELS;i++) {
      if (distances[i]<=radius) pixels.setPixelColor(i,pixels.Color(255,0,0));  
    }  
    pixels.show();
    delay(20);
  }
}

/*
void mode0() {
  for (int i=0; i<91; i++) {
      pixels.setPixelColor(i,pixels.Color((100*i/91),(100-100*i/91),0));
      pixels.show();  
      delay(10);
  }
  for (int i=90; i>=0; i--) {
      pixels.setPixelColor(i,pixels.Color(0,0,0));
      pixels.show();  
      delay(10);
  }
}

void mode1() {
  for (int i=0; i<91; i++) {
      pixels.setPixelColor(i,pixels.Color((100*i/91),0,(100-100*i/91)));
      pixels.show();  
      delay(15);
  }
  delay(1000);
  for (int i=90; i>=0; i--) {
      pixels.setPixelColor(i,pixels.Color((100*i/91),(100-100*i/91),0));
      pixels.show();  
      delay(15);
  }
  delay(1000);
}

void mode2() {
  int dist = 100;
  wipe(255,0,0,dist,0);
  wipe(0,255,0,dist,1);
  wipe(0,0,255,dist,0);
  wipe(255,0,0,dist,1);
  wipe(0,255,0,dist,0);
  wipe(0,0,255,dist,1);  
}
void mode3() {
  int dist = 20;
  wipe(255,0,0,dist,2);
  wipe(0,255,0,dist,3);
  wipe(0,0,255,dist,2);
  wipe(255,0,0,dist,3);
  wipe(0,255,0,dist,2);
  wipe(0,0,255,dist,3);  
}
void mode4() {
  int dist = 30;
  wipe(255,0,0,dist,4);
  wipe(0,255,0,dist,5);
  wipe(0,0,255,dist,4);
  wipe(255,0,0,dist,5);
  wipe(0,255,0,dist,4);
  wipe(0,0,255,dist,5);  
}
void mode5() {
  int dist = 30;
  wipe(255,0,0,dist,2);
  wipe(0,255,0,dist,4);
  wipe(0,0,255,dist,3);
  wipe(255,0,0,dist,5);
  wipe(0,255,0,dist,0);
  wipe(0,0,255,dist,1);
}
void mode6() {
  int dist = 150;
  wipe(255,0,0,dist,6);
  wipe(0,255,0,dist,6);
  wipe(0,0,255,dist,6);
  wipe(255,0,0,dist,6);
  wipe(0,255,0,dist,6);
  wipe(0,0,255,dist,6);
}
void mode7() {
  int r = 255;int g=0;int b=0;int dist = 50;
  int r2 = 0;int g2 = 255; int b2 = 0;
  for (int row=0; row<27; row++) {
    int invrow = 26-row;
    for (int i=0;i<91;i++) {
      if (rows[i]==row && (wings[i]==0 || wings[i]==3 || wings[i]==6)) {pixels.setPixelColor(i,pixels.Color(r,g,b));}
      if (rows[i]==invrow && !(wings[i]==0 || wings[i]==3 || wings[i]==6)) {pixels.setPixelColor(i,pixels.Color(r2,g2,b2));}
    } 
    delay(dist); pixels.show();
  }
  pixels.clear();
  //else if (dir==3) {for (int row=26; row>=0; row--) {for (int i=0;i<91;i++) {if (rows[i]==row) {pixels.setPixelColor(i,pixels.Color(r,g,b));}} delay(dist); pixels.show();}}
}
void mode8() {
  int dist = 100;
  split(255,0,0,dist,2);
  split(0,255,0,dist,3);  
}

void mode9() {
    int r = 255;
    int g = 0;
    int b = 0;
    int stage = 0;
    int diff=5;
    while (stage<=5) {
        if (stage==0) {g+=diff; if (g>=255) {g=255; stage+=1;}}
        else if (stage==1) {r-=diff; if (r<=0) {r=0; stage+=1;}}
        else if (stage==2) {b+=diff; if (b>=255) {b=255; stage+=1;}}
        else if (stage==3) {g-=diff; if (g<=0) {g=0; stage+=1;}}
        else if (stage==4) {r+=diff; if (r>=255) {r=255; stage+=1;}}
        else if (stage==5) {b-=diff; if (b<=0) {b=0; stage+=1;}}
        for (int i=0; i<91; i++) {pixels.setPixelColor(i,pixels.Color(r,g,b));}
        pixels.show();
      }
}
void mode10() {
    int r[] = {255,223,191,159,127,95,63,31};
    int g[] = {0,0,0,0,0,0,0,0};
    int b[] = {0,0,0,0,0,0,0,0};
    int stage[] = {0,0,0,0,0,0,0,0};
    int diff=20;
    while (stage[7]<=5) {
        for (int j=0; j<8; j++) {
          if (stage[j]==0) {g[j]+=diff; if (g[j]>=255) {g[j]=255; stage[j]+=1;}}
          else if (stage[j]==1) {r[j]-=diff; if (r[j]<=0) {r[j]=0; stage[j]+=1;}}
          else if (stage[j]==2) {b[j]+=diff; if (b[j]>=255) {b[j]=255; stage[j]+=1;}}
          else if (stage[j]==3) {g[j]-=diff; if (g[j]<=0) {g[j]=0; stage[j]+=1;}}
          else if (stage[j]==4) {r[j]+=diff; if (r[j]>=255) {r[j]=255; stage[j]+=1;}}
          else if (stage[j]==5) {b[j]-=diff; if (b[j]<=0) {r[j]=255;g[j]=0;b[j]=0; stage[j]+=1;}}
          for (int i=0; i<91; i++) {if (rings[i]==j) {pixels.setPixelColor(i,pixels.Color(r[j],g[j],b[j]));}}
          pixels.show();
        }
      }
}
void mode11() {
    int r[] = {255,246,237,228,219,210,201,192,183,174,165,156,147,138,129,120,111,102,93,84,75,66,57,48,39,30,21};
    int g[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    int b[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    int stage[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    int diff=40;
    while (stage[26]<=5) {
        for (int j=0; j<27; j++) {
          if (stage[j]==0) {g[j]+=diff; if (g[j]>=255) {g[j]=255; stage[j]+=1;}}
          else if (stage[j]==1) {r[j]-=diff; if (r[j]<=0) {r[j]=0; stage[j]+=1;}}
          else if (stage[j]==2) {b[j]+=diff; if (b[j]>=255) {b[j]=255; stage[j]+=1;}}
          else if (stage[j]==3) {g[j]-=diff; if (g[j]<=0) {g[j]=0; stage[j]+=1;}}
          else if (stage[j]==4) {r[j]+=diff; if (r[j]>=255) {r[j]=255; stage[j]+=1;}}
          else if (stage[j]==5) {b[j]-=diff; if (b[j]<=0) {r[j]=255;g[j]=0;b[j]=0; stage[j]+=1;}}
          for (int i=0; i<91; i++) {if (rows[i]==j) {pixels.setPixelColor(i,pixels.Color(r[j],g[j],b[j]));}}
          pixels.show();
        }
      }
}*/
