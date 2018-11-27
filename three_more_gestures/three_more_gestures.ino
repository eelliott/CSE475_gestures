
byte lpower[8];
void windmill(uint8_t wait) {
  uint16_t i;
  static byte loca = 0;
  static byte pred = 100;
  static unsigned long timex = millis();

  if((millis() - timex) > 500){
    if((millis() - timex) > 5000){
      pred = 100;
    }
    timex = millis();
    
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
  }     
}


void lightn(uint8_t wait) {
  uint16_t i;
  static byte lstate = 0;
  static byte lpower = 0;
  static unsigned long timex = millis();

  if((millis() - timex) > 500){
    timex = millis();
    
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
  }     
}


byte sranp[16];
byte srans[16];
void slowrand(uint8_t wait) {
  uint16_t i;
  static unsigned long timex = millis();

  if((millis() - timex) > 500){

    if((millis() - timex) > 3000){
      for(i = 0; i < 16; i++){
        if(*(srans + i) == 0){
          *(srans + i) = random(1,2);
        }
      }
    }
    timex = millis();

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
  }     
}


void randmill(uint8_t wait) {
  uint16_t i;
  static byte loca = 16;
  static byte tomov = 0;
  static byte stat = 0;
  static unsigned long timex = millis();

  if((millis() - timex) > 500){
    timex = millis();
    
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
  }     
}
