
const byte colorSpinIncr = 4;

byte colorSpinDir = 1;

void colorSpin(byte* hues, byte* sats){

  if (j == 0){

    if (random(2)){
      colorSpinDir = 1;
    }else{
      colorSpinDir = -1;
    }  

    if (random(2) == 0) {
      hues[15]  = 0;
      hues[14]  = 15;
      hues[13]  = 31;
      hues[12]  = 47;
      hues[11]  = 63;
      hues[10]  = 79;
      hues[9]  = 95;
      hues[8]  = 111;
      hues[7]  = 127;
      hues[6]  = 143;
      hues[5] = 159;
      hues[4] = 175;
      hues[3] = 191;
      hues[2] = 207;
      hues[1] = 233;
      hues[0] = 249;
    } else {
      hues[0]  = 0;
      hues[1]  = 15;
      hues[2]  = 31;
      hues[3]  = 47;
      hues[4]  = 63;
      hues[5]  = 79;
      hues[6]  = 95;
      hues[7]  = 111;
      hues[8]  = 127;
      hues[9]  = 143;
      hues[10] = 159;
      hues[11] = 175;
      hues[12] = 191;
      hues[13] = 207;
      hues[14] = 233;
      hues[15] = 249;
    }
    
    for (byte pix=0; pix<16; pix +=1){
      sats[pix] = 255;
    }
  }

  if (random(32) == 0){
    colorSpinDir *= -1;
  }
  
  for (byte i=0; i<16; i++){
    hues[i] += colorSpinDir*colorSpinIncr;
  }
}
