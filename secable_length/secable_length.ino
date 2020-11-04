

String str ="Hello World! Here is some text. I need them to split into multiple lines without breaking the words.";
const int wantedLength = 15;

String lines [10];
int c = 0;
int cl = 0;
int endOfLine = 0;

void setup(){
  Serial.begin(115200);
  //Serial.println(str.substring(0,15));
  //Serial.println(str.substring(15,30));
  split();
}
void loop(){

}

void split(){
int temp = str.indexOf(' ',c); //indexOf(val,from)

  while(c<str.length()){
   
    if (str.charAt(c) == ' ')
    {
      if(c>(cl+1)*15){
        c--;
        while(str.charAt(c) != ' '){
          c--;
        }
        lines[cl]=str.substring(endOfLine,c);
        endOfLine = c+1;
        cl++;
      }
    }
    c++;
  }
  
for (int i = 0; i < 10; ++i)
{
  Serial.println(lines[i]);
}
  
}