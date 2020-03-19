#include <LedControl.h>
#include <Timer.h>
/* LED board set up */
int DIN = 11, CLK = 9, CS = 10, devices = 1;
LedControl lc = LedControl(DIN, CLK, CS, devices);
/* Definitions */
#define controlPin A2
#define debug 1
/* Creates an instance or event of time */
Timer timer;
/* Variable delcarations */
byte ball_direction;
int xball;
int yball;
int yball_prev;
int ball_timer;
byte bar;
/* Initial set up */
void setup()
{
  Serial.begin(9600);
  startUp();
  animationSequence();
}
/* Repeats all functions */
void loop()
{
  moveBar();
  DEBUG("pong");
}
/* Intro animation for start of every game */
void animationSequence()
{
  lc.clearDisplay(0);
  for(int r = 0; r < 8; r++)
  {
    for (int c = 0; c < 8; c++)
    {
      lc.setLed(0, r, c, HIGH);
      delay(50);
    }
  }
  delay(1500);
  centerOut();
  lc.clearDisplay(0);
}
/* Clears the animation sequence starting from the center going outwards */
void centerOut()
{
  for(int r = 3; r <= 4; r++)
  {
    for(int c = 3; c <= 4; c++)
    {
      lc.setLed(0, r, c, 0);
    }
  }
  delay(150);
  for(int r = 2; r <= 5; r++)
  {
    for(int c = 2; c <= 5; c++)
    {
      lc.setLed(0, r, c, 0);
    }
  }
  delay(150);
  for(int r = 0; r <= 7; r++)
  {
    for(int c = 0; c <= 7; c++)
    {
      lc.setLed(0, r, c, 0);
    }
  }
  delay(150);
}
/* Sets up the LED board */
void startUp()
{
  lc.shutdown(0, false);
  lc.setIntensity(0,3);
}
/* Allows the pong bar to move */
void moveBar()
{
/* 0xFF is 11111111 and B111 is 00000111 */
  byte pos[2] = {0xFF, B111};
/* Scales the min and max values of the potentiometer down to 5-0. If the potentiometer reads
 * zero, then bar will equal 5. If it reads 1000, then var will equal 0. */
  bar = map(analogRead(controlPin), 0, 1000, 5, 0);
/* pad is set equal to pos[0]. pos [0] starts out as 11111111. Then it is shifted to the right by 5.
 * Giving 00000111. Afterwards, 00000111 is shifted to the left by bar units. Bar is controled by the 
 * control pin, or potentiometer. */
  byte pad = pos[0] >> 5 << bar;
  lc.setRow(0, 7, pad);
}
/* Displays values if debug is defined. (const char *desc) means whatever is typed 
 * within DEBUG() is read only, cannot be changed, and whatever is typed is a character. */
void DEBUG(const char* desc)
{
  #ifdef debug
  Serial.print(desc);
  Serial.print("  XY: (");
  Serial.print(xball);
  Serial.print(", ");
  Serial.print(yball);
  Serial.print(")  bar: ");
  Serial.print(bar);
  Serial.print("  ball direction: ");
  Serial.println(ball_direction);
  #endif
}
