void colorWipe(uint32_t color, int strip) {
  if(strip == 0){
    for(int i=0; i<led_count; i++) { 
    front_strip.setPixelColor(i, color);
    front_strip.show();                       
  }}
  else if(strip == 1){
    for(int i=0; i<led_count; i++) { 
    back_strip.setPixelColor(i, color);
    back_strip.show();     
  }}
  else if(strip == 2){
    for(int i=0; i<led_count; i++) { 
    front_strip.setPixelColor(i, color);
    back_strip.setPixelColor(i, color);
    front_strip.show();     
    back_strip.show();
  }}
  else{
    front_strip.clear();
    back_strip.clear();
    front_strip.show();
    back_strip.show();
  }
}
