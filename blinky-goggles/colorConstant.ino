byte constant_hue = 0;

void colorConstant(byte* hues, byte* sats) {
  
  if (j == 0){
    constant_hue = random(255);
  }
  
  for (byte i=0; i<16; i++) {
    hues[i] = constant_hue;
    sats[i] = 255;
  }  
}

