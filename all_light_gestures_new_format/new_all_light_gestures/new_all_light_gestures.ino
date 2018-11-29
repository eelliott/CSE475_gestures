//total differnce in time
//uint32_t tdt;

boolean quadRand(uint32_t dt){
  uint16_t i;
  uint8_t R, G, B;

  
  
  if(dt >= 250){
    //tdt = 0;
    uint8_t rand = random(4);
    B = 0;
    for(i = 0; i < 16; i++) {
      switch (rand) {
        case 0:
          if (i >= 0 && i < 4) {
            R = 255;
            G = 165;
          } else {
            R = 0;
            G = 0;
          }
          break;
        case 1:
          if (i >= 4 && i < 8) {
            R = 255;
            G = 165;
          } else {
            R = 0;
            G = 0;
          }
          break;
        case 2:
          if (i >= 8 && i < 12) {
            R = 255;
            G = 165;
          } else {
            R = 0;
            G = 0;
          }
          break;
        case 3:
          if (i >= 12 && i < 16) {
            R = 255;
            G = 165;
          } else {
            R = 0;
            G = 0;
          }
          break;   
        default:
          break;
      }
      strip.setPixelColor(i, strip.Color(R, G, B));
    }
    strip.show();
    return true;
  }
  return false;
}


boolean fire(uint32_t dt){
  uint16_t i;
  byte R, G;

  //tdt += dt;
  
  if(dt >= 250){
    //tdt = 0;
    for(i = 0; i < 16; i++){
      if(random(4) == 0){
        R = 255;
        G = random(155);
      }else{
        R = 0;
        G = 0;
      }
      strip.setPixelColor(i, strip.Color(R, G, 0));
    }
    strip.show();
    return true;
  }
  return false;
}


//requires the rain function to run
byte rainDropState[16];
byte rainShineState[16];
byte rainDropVolume[16];
byte rainShineVolume[16];
boolean rainCycle(uint32_t dt) {
  uint16_t i;

  //tdt += dt;
  
  if(dt >= 250){
    //tdt = 0;
    for(i = 0; i < 16; i++){
      Rain((rainDropState + i), (rainShineState + i), (rainDropVolume + i), (rainShineVolume + i)); 
    }
    
    for(i = 0; i < 16; i++){
      strip.setPixelColor(i, strip.Color(0, 0, *(rainDropVolume + i), *(rainShineVolume + i)));
    }
    
    strip.show();
    return true;
  }
  return false;
}
void Rain(byte* rds, byte* rss, byte* rdv, byte* rsv) {
  uint16_t i;
  
  if(*rds == 0){
    if(random(16) == 1){
      *rds = 1;
    }
  }

  if(*rds == 1){
    i = random(120);
    if((i + *rdv) >= 250){
      *rdv = 250; 
      *rds = 2;
      *rss = 1;
    }else{
      *rdv = *rdv + i;
    }
  }else if(*rds == 2){
    i = random(20);
    if((*rdv - i) <= 0){
      *rdv = 0; 
      *rds = 0;
    }else{
      *rdv = *rdv - i;
    }

    if(*rss == 1){
      i = random(150);
      if((i + *rsv) >= 250){
        *rsv = 250; 
        *rss = 2;
      }else{
        *rsv = *rsv + i;
      }
    }else if(*rss == 2){
      i = random(80);
      if((*rsv - i) <= 0){
        *rsv = 0; 
        *rss = 0;
      }else{
        *rsv = *rsv - i;
      }
    }
  } 
}


boolean alternate(uint8_t wait){
  uint16_t i, j;
  static byte a = 0, b = 0;
  static byte C = 1, PratioR, PratioG, PratioB, cyleft;

  //tdt += dt;
  
  if(dt > 250){
    //tdt = 0;
    if(cyleft == 0){
      //for random colors instead of white set C to 1;
      if(C == 1){
        PratioR = random(1, 10);
        PratioG = random(1, 10);
        PratioB = random(1, 10);
      }else{
        PratioR = 1;
        PratioG = 1;
        PratioB = 1;
      }
      cyleft = 52;
    }
  
    if(cyleft > 26){
      b = 250 - a;
      for(j = 0; j < 8; j++){
        strip.setPixelColor((j * 2), strip.Color(a / PratioR, a / PratioG, a / PratioB));
        strip.setPixelColor((j * 2) + 1, strip.Color(b / PratioR, b / PratioG, b / PratioB));
      }
      a = a + 10;
    }else if(cyleft > 0){
      a = a - 10;
      b = 250 - a;
      for(j = 0; j < 8; j++){
        strip.setPixelColor((j * 2) + 1, strip.Color(a / PratioR, a / PratioG, a / PratioB));
        strip.setPixelColor((j * 2), strip.Color(b / PratioR, b / PratioG, b / PratioB));
      }
    }
    strip.show();
    return true;
  }
  return false;
}



byte lpower[8];
boolean windmill(uint32_t dt) {
  uint16_t i;
  static byte loca = 0;
  static byte pred = 100;
  
  //tdt += dt;

  if(dt > 500){
    if(dt > 5000){
      pred = 100;
    }
    //tdt = 0;
    
    *(lpower + loca) = 270;
    if(loca != 7){
      loca++;
    }else{
      loca = 0;
    }
    
    for(i = 0; i < 8; i++){
      if(*(lpower + i) >= 30){
        *(lpower + i) -= 30;
      }
    }

    for(i = 0; i < 8; i++){
      strip.setPixelColor(i, strip.Color(*(lpower+ i) * pred / 100, *(lpower+ i), 0));
      strip.setPixelColor(i+8, strip.Color(*(lpower+ i) * pred / 100, *(lpower+ i), 0));
    }
    pred -= 5;
    strip.show();
    return true;
  }     
  return false;
}


boolean lightn(uint32_t dt) {
  uint16_t i;
  static byte lstate = 0;
  static byte lpower = 0;

  //tdt += dt;

  if(dt > 500){
    //tdt = 0;
    
    if(lstate == 0){
      if(random(10) == 0){
        lpower = 250;
        lstate = 1;
      }else{
        if(lpower > 0){ 
          lpower -= 50;
        }else{
          lpower = 0;
        }
      }
    }else if(lstate = 1){
      lpower = 0;
      lstate = 2;
    }else if(lstate = 2){
      lpower = 250;
      lstate = 0;
    }else{
      lstate = 0;
    }
    
    for(i = 0; i < 16; i++){
      strip.setPixelColor(i, strip.Color( 0, 0, 0, lpower));
    }
    strip.show();
    return true;
  }     
  return false;
}


byte sranp[16];
byte srans[16];
boolean slowrand(uint32_t dt) {
  uint16_t i;
  
  //tdt += dt;

  if(dt > 500){
    //tdt = 0;
    if(random(6) == 0){
      for(i = 0; i < 16; i++){
        if(*(srans + i) == 0){
          *(srans + i) = random(1,2);
        }
      }
    }

    for(i = 0; i < 16; i++){
      if(*(srans + i) == 1){
        if(*(sranp + i) <= 9){
          *(srans + i) = 0;
        }else{
          *(srans + i) -= 10;
        }
      }else if(*(srans + i) == 2){
        if(*(sranp + i) >= 241){
          *(srans + i) = 0;
        }else{
          *(srans + i) += 10;
        }
      }
    }
    
    

    for(i = 0; i < 16; i++){
      strip.setPixelColor(i, strip.Color(0, *(sranp + i), 0, *(sranp + i)));
    }
    strip.show();
    return true;
  }     
  return false;
}


boolean randmill(uint32_t dt) {
  uint16_t i;
  static byte loca = 16;
  static byte tomov = 0;
  static byte stat = 0;
  
  //tdt += dt;

  if(dt > 250){
    //tdt = 0;
    
    if(tomov == 0){
      stat != stat;
      tomov = random(4,16);
    }else{
      if(stat == 1){
        loca++;
        if(loca == 24){
          loca = 16;
        }
      }else{
        loca--;
        if(loca == 8){
          loca = 16;
        }
      }
      tomov--;
    }
    *(lpower + (loca % 16)) = 300;
    
    for(i = 0; i < 8; i++){
      if(*(lpower + i) >= 50){
        *(lpower + i) -= 50;
      }
    }

    for(i = 0; i < 8; i++){
      strip.setPixelColor(i, strip.Color(0, *(lpower + i), 0, *(lpower + i)));
      strip.setPixelColor(i+8, strip.Color(0, *(lpower + i), 0, *(lpower + i)));
    }
    strip.show();
    return true;
  }     
  return false;
}



//requires grassCol to work
byte grassState1[16];
byte grassState2[16];
byte grassR[16];
byte grassG[16];
byte grassB[16];
byte grassW[16];
boolean growgrass(uint32_t dt) {
  uint16_t i;

  //tdt += dt;
  if(dt > 500){
    //tdt = 0;
    for(i = 0; i < 16; i++){
      grassCol((grassState1 + i), (grassState2 + i), (grassR + i), (grassG + i), (grassB + i), (grassW + i)); 
    }
  
    for(i = 0; i < 16; i++){
      strip.setPixelColor(i, strip.Color(*(grassR + i) * (*(grassG + i) / 250), *(grassG + i) * (*(grassG + i) / 250),
            *(grassB + i) * (*(grassG + i) / 250), *(grassW + i) * (*(grassG + i) / 250)));
    }
    
    strip.show();
    return true;
  }
  return false;
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



//requires growbud to work
byte budstate[16];
byte budspd[16];
byte budR[16];
byte budG[16];
boolean sprout(uint32_t dt) {
  uint16_t i;

  //tdt += dt;
  
  if(dt > 500){
    //tdt = 0;
    for(i = 0; i < 16; i++){
      growbud((budstate + i), (budspd + i), (budR + i), (budG + i)); 
    }
  
    for(i = 0; i < 16; i++){
      strip.setPixelColor(i, strip.Color(*(budR + i), *(budG + i), 0, 0));
    }
    
    strip.show();
    return true;
  }
  return false;
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




byte wormstate[2];
byte wormcol[16];
boolean worm(uint32_t dt) {
  uint16_t i;

  //tdt += dt;

  if(dt > 250){
    if(*(wormstate + 0) > 1){
      *(wormstate + 0) = random(16);
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
    return true;
  }
  return false;
}
