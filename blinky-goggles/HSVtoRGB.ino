uint32_t HSVtoRGB(uint8_t hue, uint8_t sat, uint8_t val){

  // initialize RGB values
  uint32_t r,g,b;

  int base;
  
  if (sat==0) {
    r = val;
    g = val;
    b = val;
 
  } else {
    base = ((255 - sat) * val) >> 8;
    int H = hue * 359. / 255.;
    switch (H/60) {

      case 0:
        r = val;
        g = (((val - base) * H) / 60) + base;
        b = base;
        break;

      case 1:
        r = (((val-base)*(60-(H%60)))/60)+base;
        g = val;
        b = base;
        break;
  
      case 2:
        r = base;
        g = val;
        b = (((val-base)*(H%60))/60)+base;
        break;
  
      case 3:
        r = base;
        g = (((val-base)*(60-(H%60)))/60)+base;
        b = val;
        break;
  
      case 4:
        r = (((val-base)*(H%60))/60)+base;
        g = base;
        b = val;
        break;
  
      case 5:
        r = val;
        g = base;
        b = (((val-base)*(60-(H%60)))/60)+base;
        break;
    }
  }
  return r << 16 | g << 8 | b;
}

