void processMessageForPrint(String message){
  //Serial.println(message);
  String messageTest = "Joyeux Noël à tous et une bonne et heureuse année ABCDEFGHIJKLMNOPQRSTUVWXYZ Et zoup ti dop!";
  const char * charMessage = messageTest.c_str();
  splitTextmessage(charMessage);
 }



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
  
 
 
void splitTextmessage (const char* str){
 
  const char * p = str;
  String lines[10];
  int numLines = 0;

  // keep going until we run out of text
  while (*p)
    {
    // find the position of the space
    String line ="";
    const char * endOfLine = split (p, maxCharsForPrinter); 
    // display up to that
    while (p != endOfLine){
      line+= *p;
      *p++;
      }
     
    // finish that line
    //Serial.println(line);
    lines[numLines] = line;
    numLines++;
   
    // if we hit a space, move on past it
    if (*p == ' ')
      p++;
    }
     printMessage(lines, numLines);
  }  
 
