
char str[] ="Hello World! Here is some text. I need them to split into multiple lines without breaking the words.";
const int wantedLength = 20;

const char * split (const char * s, const int length)
  {
  // if it will fit return whole thing
  if (strlen (s) <= length)
    return s + strlen (s);

  // searching backwards, find the last space
  for (const char * space = &s [length]; space != s; space--)
    if (*space == ' ')
      return space;
   
  // not found? return a whole line
  return &s [length];       
  } // end of split
 
 
void setup ()
  {
  Serial.begin (115200);
  Serial.println ();

  const char * p = str;
 
  // keep going until we run out of text
  while (*p)
    {
    // find the position of the space
    const char * endOfLine = split (p, wantedLength); 
   
    // display up to that
    while (p != endOfLine)
      Serial.print (*p++);
     
    // finish that line
    Serial.println ();
   
    // if we hit a space, move on past it
    if (*p == ' ')
      p++;
    }
  }  // end of setup
 
void loop () { }
