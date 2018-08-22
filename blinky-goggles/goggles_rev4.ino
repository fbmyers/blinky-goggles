

void setupSpinner(){

  for (byte k=0; k<16; k++) {
    valSpinVals[k] = (float)VALMAX * (float)k/15.;
  }
  
  for (byte s=0; s<16; s++){
    valSpinInds[s] = s;
  }


}

void updateSpinner(){

  nCycles = random(3) + 1;
  theta = pi/2.;

  for (j=0; j<64*nCycles; j++){
    theta += dtheta;
    if (theta > tau){
      theta -= tau;
    }
    valPulse(vals);
    colorConstant(hues, sats);
    update(vals, sats, hues);
    delay(pause);

    checkRemote();
  }

  nCycles = random(3) + 1;
  theta = pi/2.;

  for (j=0; j<64*nCycles; j++){

    theta += dtheta;
    if (theta > tau){
      theta -= tau;
    }

    valPulse(vals);
    colorSpin(hues, sats);
    update(vals, sats, hues);
    delay(pause);
    
    checkRemote();
  }  

  nCycles = random(3) + 1;
  theta = pi/2.;

  for (j=0; j<64*nCycles; j++){
    theta += dtheta;
    if (theta > tau){
      theta -= tau;
    }
    valPulse(vals);
    colorCycle(hues, sats);
    update(vals, sats, hues);
    delay(pause);
    
    checkRemote();
  }

  nCycles = random(3);
  theta = pi/2.;

  for (j=0; j<64*nCycles; j++){
    theta += dtheta;
    if (theta > tau){
      theta -= tau;
    }
    valSpin(vals);
    colorCycle(hues, sats);
    update(vals, sats, hues);
    delay(pause);
    
    checkRemote();
  }  
  
  

}

void update(byte vals[], byte sats[], byte hues[]){

  for (byte i=0; i<16; i++){
    neopixel1.setPixelColor(i,HSVtoRGB(hues[i], sats[i], vals[i]));
    neopixel2.setPixelColor(i,HSVtoRGB(hues[i], sats[i], vals[i]));
    
  }
  neopixel1.show();
  neopixel2.show();
  
}

void checkRemote(){
 char crazy_val = 150;
 char love_hue = 240;
 char love_sat = 255;
 char love_val_start = 1;
 char love_val_stop = 100;
 char crazy_blink = 0;
 uint32_t crazy_odd,crazy_even; 
 char love_val = love_val_start;
 int refractory = 0;
 
 while (refractory>0 || digitalRead(REMOTE_BUTTON_1)==LOW) {
  if (digitalRead(REMOTE_BUTTON_1)==LOW) {
   if (digitalRead(REMOTE_BUTTON_2)==LOW) { // MUAHAHAHA
    if (crazy_blink==0) {
      crazy_odd = HSVtoRGB(255,0,crazy_val);
      crazy_even = HSVtoRGB(0,0,0);
    }
    else {
      crazy_odd = HSVtoRGB(0,0,0);
      crazy_even = HSVtoRGB(255,0,crazy_val);
    }
    for (byte i=0; i<16; i+=2){
      neopixel1.setPixelColor(i,crazy_even);
      neopixel2.setPixelColor(i,crazy_even);
      
    }
    for (byte i=1; i<16; i+=2){
      neopixel1.setPixelColor(i,crazy_odd);
      neopixel2.setPixelColor(i,crazy_odd);
      
    }    
    delay(50);
    crazy_blink = crazy_blink==0?1:0;
   }
   
   else { // I LOVE YOU
    Serial.println("luv");
    for (byte i=0; i<16; i++){
      //byte r = random(30);
      byte v = min(max(love_val,0),255);
      Serial.println(v);
      neopixel1.setPixelColor(i,HSVtoRGB(love_hue,love_sat,v));
      neopixel2.setPixelColor(i,HSVtoRGB(love_hue,love_sat,v));
    }
    delay(5);  
    if (love_val<love_val_stop)
      love_val++;  
   }
   refractory = 1000;
  }
 else { //in refractory period
  love_val = love_val_start;
  refractory--;
  for (byte i=0; i<16; i++){
    neopixel1.setPixelColor(i,0,0,0);
    neopixel2.setPixelColor(i,0,0,0); 
  } 
  delay(1);
 }   
 neopixel1.show();
 neopixel2.show();
 
 } 
}

