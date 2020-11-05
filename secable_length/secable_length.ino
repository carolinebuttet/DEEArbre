

String str ="Hello World! Here is some text. I need them to split into multiple lines without breaking the words.";
const int wantedLength = 15;

String lines [10];
int c = 0; // global cursor
int cl = 0; // line cursor 
int endOfLine = 0; // end line cursor
int checklength = 0;
int letterWithoutSpace = 0;


void setup(){
  Serial.begin(115200);
  split();
  printResult();
}
void loop(){}

void split(){
  c = 0;
  cl = 0;
  endOfLine = 0;

  while(c<str.length()){
    
    if (str.charAt(c) == ' ')
    {
       letterWithoutSpace = 0;
      if(c>endOfLine+wantedLength){
        c--; //if go too far from the end of actual line (cl)  
        //checklength++;    
        while(str.charAt(c) != ' '){          
          c--; //go back until we find a space
        }
        lines[cl]=str.substring(endOfLine,c); //take the selection and past it in the lines array
        endOfLine = c+1; //+1 to ignore space at the begining of the line. 
        cl++;
        
      }  
    }else
    {
      letterWithoutSpace++;
      if (letterWithoutSpace > wantedLength)
      {
        lines[cl]=str.substring(endOfLine,c); //take the selection and past it in the lines array
        endOfLine = c; //+1 to ignore space at the begining of the line. 
        cl++;
        letterWithoutSpace = 0;
      }
    }
    c++;

  } 
  while(str.charAt(c)!= ' '){
          c--;
  }
  //handle the last word, 
  //add it to the current line if the word is short enough. 
  lines[cl]=str.substring(c+1,str.length());

}

void printResult(){
  for (int i = 0; i < 10; i++)
  {
      Serial.println(lines[i]);
  }
}
