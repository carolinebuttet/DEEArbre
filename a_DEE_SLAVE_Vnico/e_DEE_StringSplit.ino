void processMessageForPrint(String message){
  String messageToProcess = message;
  messageToProcess.replace("\n"," ");
  messageToProcess.replace("\r"," ");
  
  Serial.println(message);
  if(DEBUG_ENABLED){
    messageToProcess = "Joyeux Noël à tous et une bonne et heureuse année ABCDEFGHIJKLMNOPQRSTUVWXYZ Et zoup ti dop!";
   }
  const char * charMessage = messageToProcess.c_str();          //Convert from string to char *
  splitTextmessage(charMessage);
 }


 // Adapted from  https://forum.arduino.cc/index.php?topic=267449.0
void splitTextmessage (const char* str){
  const char * p = str;                                               // An arrayy of String to store our final message
  numLinesS = 0;                                           // The value to count the number of lines
 //int numLines = 0;
  while (*p)                                                  // keep going until we run out of text
    {
                                                              // find the position of the space
    String line ="";
    const char * endOfLine = split (p, maxCharsForPrinter); 
    
    while (p != endOfLine){                                   // display up to that
      line+= *p;
      *p++;
      }
     
                                                              // finish that line
    lines[numLinesS] = line;
    numLinesS++;
   
                                                              // if we hit a space, move on past it
    if (*p == ' ')
      p++;
    }
     MSG_NEED_TO_BE_P = true;
     //printMessage(lines, numLines);                          // Send this message for print (in f_DEE_Print)
  } 



 // Adapted from  https://forum.arduino.cc/index.php?topic=267449.0
const char * split (const char * s, const int length){
                                                              // if it will fit return whole thing
  if (strlen (s) <= length)
    return s + strlen (s);

                                                              // searching backwards, find the last space
  for (const char * space = &s [length]; space != s; space--)
    if (*space == ' ')
      return space;
   
                                                              // not found? return a whole line
  return &s [length];       
 }
  
 
