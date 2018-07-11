import processing.serial.*;
Serial Sonic;
////////////variables////////////
color from = color (244, 65, 65);
color to = color (76, 244, 65);

float val_L, val_C, val_R;

int maxValue = 150;
int minValue = 0;

float percentage_C, percentage_L, percentage_R;


int scaleWid = 50;
int scaleHeig = 200;

//unnecessary variables
int Left_C_X = 250;
int Left_C_Y = 300;
float avg;

////////////Setup////////////
void setup()
{
  size (1000,500);
  background(120);
  //noLoop();
  noStroke();
  textSize(32);
  Sonic = new Serial(this, Serial.list()[0], 9600);
}
////////////Main Program////////////
void draw()
{
  
  SerialEvent(Sonic);
  varCheck();
  //println(val_L,val_C,val_R);
  calculate();
  //println("|L|",percentage_L,"|C|",percentage_C,"|R|",percentage_R);
  
  rightSideDraw();
  avg = ((percentage_L+percentage_C+percentage_R)/3.0);
  fill(lerpColor(from,to,avg));
  ellipse(Left_C_X+(scaleWid/2),Left_C_Y + scaleWid, scaleWid, scaleWid);
  
  leftSideDraw();
}
/*L*/
void leftSideDraw()
{
  scaleDraw(Left_C_X, Left_C_Y, scaleWid, scaleHeig, percentage_C);
  
  translate(Left_C_X+scaleWid,Left_C_Y);
  
  rotate(PI/4);//rotating for 45g
  scaleDraw(10, 0, scaleWid, scaleHeig, percentage_R);
  
  
  rotate(PI/-4);//going back to regular angle.
  translate(-94,42); //calculated it experementally -> ONLY FOR -45g
  
  rotate(PI/-4);//rotating for -45g
  scaleDraw(0, 0, scaleWid, scaleHeig, percentage_L);
}
/*R*/
void rightSideDraw()
{
  //background
  fill(100);
  rect(570,0,430,500);
  //text
  fill(200);
  
  text("L: " + round(val_L) + " cm", 600, 100);
  text("C: " + round(val_C) + " cm", 600, 250);
  text("R: " + round(val_R) + " cm", 600, 400);
  //
  //text("Sound: "+"x"+" Db", 600, 400);
}
////////////Other Functions////////////
void scaleDraw(int x, int y, int scaleW, int scaleH, float percentage){
  fill(0);
  rect(x,y,scaleW,-scaleH);
  
  color internal = lerpColor(from,to,percentage);
  fill(internal);

  rect(x, y, scaleW, -round(percentage*scaleH));
}

/*void keyPressed() //will be unnecessary after using Serial values sent from Arduino.
{
    switch(key)
    {
      case 'z': val_L-=2; redraw(); break; //L
      case 'x': val_C-=2; redraw(); break; //C
      case 'c': val_R-=2; redraw(); break; //R
      //
      case 'a': val_L+=2; redraw(); break; //L
      case 's': val_C+=2; redraw(); break; //C
      case 'd': val_R+=2; redraw(); break; //R
      //
      default:break;
    }
}*/

void calculate()
{
  percentage_L = val_L/maxValue;
  percentage_C = val_C/maxValue;
  percentage_R = val_R/maxValue;
}

void varCheck()
{
  if (val_L<minValue) val_L = minValue;
  if (val_L>maxValue) val_L = maxValue;
  
  if (val_C<minValue) val_C = minValue;
  if (val_C>maxValue) val_C = maxValue;
  
  if (val_R<minValue) val_R = minValue;
  if (val_R>maxValue) val_R = maxValue;
}
///////////Serial///////////
void SerialEvent (Serial arduinoport) 
{
try{
  if (arduinoport.available() > 0 /*&& arduinoport.readStringUntil('\n').indexOf('_') != -1*/) 
  {
    String Line = arduinoport.readStringUntil('\n');
    if (Line != null)
    {
      Line = trim(Line);
      val_L = Integer.parseInt(Line.substring(Line.indexOf("L")+1,Line.indexOf("C")));
      val_C = Integer.parseInt(Line.substring(Line.indexOf("C")+1,Line.indexOf("R")));
      val_R = Integer.parseInt(Line.substring(Line.indexOf("R")+1,Line.indexOf("_")));
    }
  }
  catch(Exception e){}
}
