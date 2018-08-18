byte valSpinDir = 1;

void valSpin(byte* vals){

  if (j == 0){
    if (random(2)){
      valSpinDir = 1;
    }
    else{
      valSpinDir = -1;
    }  

    switch ( (byte) random(2) ) {
    case 0:
      if (valSpinDir == 1){
        valSpinIncr = 1;
        valSpinSteps[0]  = 15;
        valSpinSteps[1]  = 14;
        valSpinSteps[2]  = 13;
        valSpinSteps[3]  = 12;
        valSpinSteps[4]  = 11;
        valSpinSteps[5]  = 10;
        valSpinSteps[6]  = 9;
        valSpinSteps[7]  = 8;
        valSpinSteps[8]  = 7;
        valSpinSteps[9]  = 6;
        valSpinSteps[10] = 5;
        valSpinSteps[11] = 4;
        valSpinSteps[12] = 3;
        valSpinSteps[13] = 2;
        valSpinSteps[14] = 1;
        valSpinSteps[15] = 0;
      }else{
        valSpinSteps[0]  = 0;
        valSpinSteps[1]  = 1;
        valSpinSteps[2]  = 2;
        valSpinSteps[3]  = 3;
        valSpinSteps[4]  = 4;
        valSpinSteps[5]  = 5;
        valSpinSteps[6]  = 6;
        valSpinSteps[7]  = 7;
        valSpinSteps[8]  = 8;
        valSpinSteps[9]  = 9;
        valSpinSteps[10] = 10;
        valSpinSteps[11] = 11;
        valSpinSteps[12] = 12;
        valSpinSteps[13] = 13;
        valSpinSteps[14] = 14;
        valSpinSteps[15] = 15;        
      }
      break;     
    case 1:
      if (valSpinDir == 1){
        valSpinSteps[0]  = 15;
        valSpinSteps[1]  = 12;
        valSpinSteps[2]  = 10;
        valSpinSteps[3]  = 8;
        valSpinSteps[4]  = 6;
        valSpinSteps[5]  = 4;
        valSpinSteps[6]  = 2;
        valSpinSteps[7]  = 0;
        valSpinSteps[8]  = 15;
        valSpinSteps[9]  = 12;
        valSpinSteps[10] = 10;
        valSpinSteps[11] = 8;
        valSpinSteps[12] = 6;
        valSpinSteps[13] = 4;
        valSpinSteps[14] = 2;
        valSpinSteps[15] = 0;
      }else{
        valSpinSteps[0]  = 0;
        valSpinSteps[1]  = 2;
        valSpinSteps[2]  = 4;
        valSpinSteps[3]  = 6;
        valSpinSteps[4]  = 8;
        valSpinSteps[5]  = 10;
        valSpinSteps[6]  = 12;
        valSpinSteps[7]  = 15;
        valSpinSteps[8]  = 0;
        valSpinSteps[9]  = 2;
        valSpinSteps[10] = 4;
        valSpinSteps[11] = 6;
        valSpinSteps[12] = 8;
        valSpinSteps[13] = 10;
        valSpinSteps[14] = 12;
        valSpinSteps[15] = 15;        
      }
      break;
//    case 2:
//      valSpinSteps[0]  = 15;
//      valSpinSteps[1]  = 7;
//      valSpinSteps[2]  = 3;
//      valSpinSteps[3]  = 0;
//      valSpinSteps[4]  = 15;
//      valSpinSteps[5]  = 7;
//      valSpinSteps[6]  = 3;
//      valSpinSteps[7]  = 0;
//      valSpinSteps[8]  = 15;
//      valSpinSteps[9]  = 7;
//      valSpinSteps[10] = 3;
//      valSpinSteps[11] = 0;
//      valSpinSteps[12] = 15;
//      valSpinSteps[13] = 7;
//      valSpinSteps[14] = 3;
//      valSpinSteps[15] = 0;
//      break;
    }    
  }

  if (j%4 == 0) {
    if (random(32) == 0){
      valSpinDir *= -1;
    }

    for (byte pix=0; pix<16; pix +=1){
      valSpinInds[pix] += valSpinDir;

      if (valSpinInds[pix] > 15){
        valSpinInds[pix] = 0;
      }
      else{
        if(valSpinInds[pix] <= 0){
          valSpinInds[pix] = 15;
        }
      }
    }
  }

  for (byte pix=0; pix<16; pix +=1){
    vals[pix] = valSpinVals[valSpinSteps[valSpinInds[pix]]];
  } 
}

