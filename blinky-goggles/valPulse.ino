// declare counter for tracking brightnesses
byte val;

void valPulse(byte* vals) {
  
  val = VALAVG + (float)VALAMP*cos(theta);
  for (byte i=0; i<16; i++) {
    vals[i] = val;
  }
}

