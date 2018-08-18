byte cycle_hue = 0;

void colorCycle(byte* hues, byte* sats) {
  
  if (j == 0){
    cycle_hue = random(255);
  }else{
    cycle_hue += 1;
  }
  
  for (byte i=0; i<16; i++) {
    hues[i] = cycle_hue;
    sats[i] = 255;
  }
 
}

