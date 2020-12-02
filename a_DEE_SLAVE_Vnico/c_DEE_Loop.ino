//THE LOOP FUNCTION

void loop() {
  if(MSG_NEED_TO_BE_P){
   
    if(numLinesS){
     printMessage(lines, numLinesS);
    }
    MSG_NEED_TO_BE_P = false;   
  }
  delay(100);
  Watchdog.reset();
}
