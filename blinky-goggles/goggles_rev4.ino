

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
 while (digitalRead(REMOTE_BUTTON_1)==LOW) {
    for (byte i=0; i<16; i++){
      neopixel1.setPixelColor(i,255,0,255);
      neopixel2.setPixelColor(i,255,0,255);
      
    }
    neopixel1.show();
    neopixel2.show();
 }
 while (digitalRead(REMOTE_BUTTON_2)==LOW) {
    for (byte i=0; i<16; i++){
      neopixel1.setPixelColor(i,0,0,255);
      neopixel2.setPixelColor(i,0,0,255);
      
    }
    neopixel1.show();
    neopixel2.show();
 } 
}

