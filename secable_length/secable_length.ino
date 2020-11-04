

String str ="Hello World! Here is some text. I need them to split into multiple lines without breaking the words. aaaaaaaaaaaaaaaaaaaaaaaaa";
const int wantedLength = 15;

String lines [9];
int c = 0;
int cl = 0;
int endOfLine = 0;

void setup(){
  Serial.begin(115200);
  split();
  printResult();
}
void loop(){}

void split(){
  c = 0;
  cl =0;
  endOfLine=0;
int temp = str.indexOf(' ',c); //indexOf(val,from)

  while(c<str.length()){
   
    if (str.charAt(c) == ' ' || c == str.length()-1)
    {
      if(c>endOfLine+wantedLength){
        c--; //if go too far from the end of actual line (cl)
        while(str.charAt(c) != ' '){
          c--; //go back until we find a space
        }
        lines[cl]=str.substring(endOfLine,c); //take the selection and past it in the lines array
        endOfLine = c+1; //+1 to ignore space at the begining of the line.
        if(c!= str.length()-1){
          cl++;
        }
      }
    }
    c++;
  } 
}

void printResult(){
  for (int i = 0; i < 9; i++)
  {
      Serial.println(lines[i]);
  }
}