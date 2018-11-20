
//my demo code here
//
//
//
byte grassState1[16];
byte grassState2[16];
byte grassR[16];
byte grassG[16];
byte grassB[16];
byte grassW[16];
void growgrass(uint8_t wait) {
  uint16_t i;
  
  for(i = 0; i < 16; i++){
    grassCol((grassState1 + i), (grassState2 + i), (grassR + i), (grassG + i), (grassB + i), (grassW + i)); 
  }

  for(i = 0; i < 16; i++){
    strip.setPixelColor(i, strip.Color(*(grassR + i) * (*(grassG + i) / 250), *(grassG + i) * (*(grassG + i) / 250),
          *(grassB + i) * (*(grassG + i) / 250), *(grassW + i) * (*(grassG + i) / 250)));
  }
  
  strip.show();
  delay(wait);
}

void grassCol(byte* gS, byte* gS2, byte* gR, byte* gG, byte* gB, byte* gW) {
  uint16_t i;
  
  if((*gS == 0) || (*gS > 4)){
    *gS = random(1, 4);
  }
  if((*gS2 == 0) || (*gS2 > 4)){
    *gS2 = random(1, 8);
  }

  i = random(20);
  if(*gS == 1){
    if((*gR + i) > 100){
      *gR = 100;
      *gS = 3;
    }else{
      *gR = *gR + i;
    }
  }else if(*gS == 2){
    if((*gB + i) > 100){
      *gB = 100;
      *gS = 4;
    }else{
      *gB = *gB + i;
    }
  }else if(*gS == 3){
    if((*gR - i) < 0){
      *gR = 0;
      if(i < 2){
        *gS = 1;
      }else if(i > 18){
        *gS = 2;
      }
    }else{
      *gR = *gR - i;
    }
  }else if(*gS == 4){
    if((*gB - i) <= 0){
      *gB = 0;
      if(i < 2){
        *gS = 1;
      }else if(i > 18){
        *gS = 2;
      }
    }else{
      *gB = *gB - i;
    }
  }

  i = random(150);
  if(*gS2 == 1){
    if((*gW + i) < 150){
      *gW = 150;
      *gS2 = 2;
    }else{
      *gW = *gW + i;
    }
  }else if(*gS2 == 2){
    if((*gW - i) <= 0){
      *gW = 0;
      if(i < 15){
        *gS2 = 1;
      }
    }else{
      *gW = *gW - i;
    }
  }

  if(*gG == 0){
    *gG = random(150) + 100;
  }
  i = random(100);
  if((*gG + i) > 250){
    *gG = 250;
  }else{
    *gG = *gG + i;
  }
  i = random(100);
  if((*gG - i) < 0){
    *gG = 0;
  }else{
    *gG = *gG - i;
  }
  
}



//my demo code here
//
//
byte budstate[16];
byte budspd[16];
byte budR[16];
byte budG[16];
void sprout(uint8_t wait) {
  uint16_t i;
  
  for(i = 0; i < 16; i++){
    growbud((budstate + i), (budspd + i), (budR + i), (budG + i)); 
  }

  for(i = 0; i < 16; i++){
    strip.setPixelColor(i, strip.Color(*(budR + i), *(budG + i), 0, 0));
  }
  
  strip.show();
  delay(wait);
}

void growbud(byte* bSt, byte* bspd, byte* bR, byte* bG) {
  uint16_t i;
  
  if(*bSt == 0){
    if(random(16) == 16){
      *bSt = 1;
      *bspd = random(50, 125);
    }
  }else if(*bSt == 1){
    if((*bG + *bspd) > 250){
      *bG = 250;
      *bSt = 2;
    }else{
      *bG = *bG + *bspd;
    }
  }else if(*bSt == 2){
    if((*bG - (*bspd / 2)) < 0){
      *bG = 0;
      *bSt = 0;
    }else{
      *bG = *bG - (*bspd / 2);
    }
  }
  i = random(50);
  if((*bR + i) > 250){
    *bR = 250;
  }else{
    *bR = *bR + i;
  }
  i = random(50);
  if((*bR - i) < 0){
    *bR = 0;
  }else{
    *bR = *gG - i;
  }
}



//my demo code here
//
//
byte wormstate[2];
byte wormcol[16];
void worm(uint8_t wait) {
  uint16_t i;

  if(*(wormstate + 0) > 1){
    *(wormstate + 0) = random(30);
    if(*(wormstate + 0) <= 1){
      *(wormstate + 1) = random(15);
    }
  }else{
    if(*(wormstate + 0) == 1){
      *(wormstate + 1) = (*(wormstate + 1) + 1) % 16
    }else{
      *(wormstate + 1) = (*(wormstate + 1) + 15) % 16
    }
    if(random(10) == 0 ){
      *(wormstate + 0) = 10
    }
    *(wormcol + *(wormstate + 1)) = 240;
  }
  
  for(i = 0; i < 16; i++){
    if(*(wormcol + i) > 0){
      *(wormcol + i) =  *(wormcol + i) - 30;
    }
  }

  for(i = 0; i < 16; i++){
    strip.setPixelColor(i, strip.Color(*(wormcol + i), *(wormcol + i), 0, 0));
  }
  
  strip.show();
  delay(wait);
}
