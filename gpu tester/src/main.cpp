/*
0 !   36 A  72  a
1 "   37 B  73  b
2 #   38 C  74  c
3 $   39 D  75  d
4 %   40 E  76  e
5 &   41 F  77  f
6 '   42 G  78  g
7     43 H  79  h
8 (   44 I  80  i
9 )   45 J  81  j
10 *  46 K  82  k
11 +  47 L  83  l
12 ,  48 M  84  m
13 -  49 N  85  n
14 .  50 O  86  o
15 /  51 P  87  p
16 0  52 Q  88  q
17 1  53 R  89  e
18 2  54 S  90  s
19 3  55 T  91  t
20 4  56 U  92  u
21 5  57 V  93  v
22 6  58 W  94  w
23 7  59 X  95  x
24 8  60 Y  96  y
25 9  61 Z  97  z
26 :  62 [  98  {
27 ;  63 \  99  |
28 <  64 ]  100 }
29 =  65 ^  101 ~
30 >  66 _  
31 ?  67 `  
32 @  68 Ć  
33 ą  69 ę  
34 Ą  70 Ę  
35 ć  71 Ł  
*/
#include <Arduino.h>


//pinout
// 8 data pins,
// 10(11) address pins,
// one pin for device select and write operation (both active low)
// why not using ports?
// the pinout is kind of messed, so it's easier to connect that way.

// address bus: 32-37 x-part, 38-42 y-part
#define DATA_LSB 9
#define DATA_MSB 2
#define ADD_MSB 32
#define ADD_LSB 42
#define SEL_IO  11
#define WR      10 
#define LED     13

void writeLetter(byte l, byte x, byte y)
{
  for(byte xx = ADD_MSB+6; xx <= ADD_LSB; xx++) //set y-part of address
    if(bitRead(y, (xx - ADD_MSB - 6)))
      digitalWrite(xx, 1);
    else
      digitalWrite(xx, 0);

  for(byte xx = ADD_MSB; xx <= ADD_LSB-5; xx++) //set x-part of address
    if(bitRead(x, (xx - ADD_MSB)))
      digitalWrite(xx, 1);
    else
      digitalWrite(xx, 0);

  for(byte xy = 0; xy < 8; xy++) //set data bus
    if(bitRead(l, xy))
      digitalWrite((DATA_MSB+xy), 1);
    else
      digitalWrite((DATA_MSB+xy), 0);

  digitalWrite(WR, LOW);
  digitalWrite(SEL_IO, LOW);
  delayMicroseconds(1);
  digitalWrite(WR, HIGH);
  digitalWrite(SEL_IO, HIGH); //write byte

  digitalWrite(WR, LOW);
  digitalWrite(SEL_IO, LOW);
  delayMicroseconds(1);
  digitalWrite(WR, HIGH);
  digitalWrite(SEL_IO, HIGH); //let's be sure we have wrote that byte
}

void blinkLED(int x) //yes.
{
  digitalWrite(LED, HIGH);
  delay(x);
  digitalWrite(LED, LOW);
}

void clearBuffer(bool invert) //fill buffer with empty char (7) or full char (252-255)
{
  for(int x = 0; x < 50; x++)
    for(int y = 0; y < 19; y++)
      if(invert) 
        writeLetter(255,x,y);
      else
        writeLetter(7,x,y);
}

void pasteCharset() //entire charset
{
  for(int y = 0; y < 7; y++)
    for(int x = 0; x < 36; x++)
     writeLetter(x + (y*36),x+4,y+4);
}

void pasteText() //some hardcoded text
{  
  writeLetter(80,1,0);
  writeLetter(49,2,0);
  writeLetter(72,3,0);
  writeLetter(87,4,0);
  writeLetter(7,5,0);
  writeLetter(42,6,0);
  writeLetter(51,7,0);
  writeLetter(56,8,0);
  writeLetter(73,1,1);
  writeLetter(96,2,1);
  writeLetter(7,3,1);
  writeLetter(47,4,1);
  writeLetter(76,5,1);
  writeLetter(86,6,1);
  writeLetter(85,7,1);
  writeLetter(76,8,1);
  writeLetter(88,9,1);
  writeLetter(7,10,1);   // iNap GPU
  writeLetter(251,11,1); // by Leoneq :3

  writeLetter(30,1,2);   // >

  writeLetter(90,20,6);
  writeLetter(72,21,6);
  writeLetter(84,22,6);
  writeLetter(87,23,6);
  writeLetter(83,24,6);
  writeLetter(76,25,6);
  writeLetter(7,26,6);
  writeLetter(91,27,6);
  writeLetter(76,28,6);
  writeLetter(95,29,6);
  writeLetter(91,30,6);  //sample text

  writeLetter(51,20,7);
  writeLetter(53,21,7);
  writeLetter(61,22,7);
  writeLetter(60,23,7);
  writeLetter(46,24,7);
  writeLetter(71,25,7);
  writeLetter(36,26,7);
  writeLetter(39,27,7);
  writeLetter(50,28,7);
  writeLetter(58,29,7);
  writeLetter(60,30,7);
  writeLetter(7,31,7);
  writeLetter(55,32,7);
  writeLetter(40,33,7);
  writeLetter(46,34,7);
  writeLetter(54,35,7);
  writeLetter(55,36,7);  // PRZYKŁADOWY TEKST

  writeLetter(103,30,15);
  writeLetter(104,31,15);
  writeLetter(105,32,15);
  writeLetter(106,33,15);
  writeLetter(107,34,15);
  writeLetter(139,30,16);
  writeLetter(140,31,16);
  writeLetter(141,32,16);
  writeLetter(142,33,16);
  writeLetter(143,34,16); //:o

  writeLetter(208, 1, 10);
  writeLetter(204, 2, 10);
  writeLetter(204, 3, 10);
  writeLetter(204, 4, 10);
  writeLetter(204, 5, 10);
  writeLetter(204, 6, 10);
  writeLetter(204, 7, 10);
  writeLetter(204, 8, 10);
  writeLetter(204, 9, 10);
  writeLetter(209, 10, 10); //start of the table

  writeLetter(205, 1, 11);
  writeLetter(91, 2, 11);
  writeLetter(72, 3, 11);
  writeLetter(73, 4, 11);
  writeLetter(76, 5, 11);
  writeLetter(83, 6, 11);
  writeLetter(82, 7, 11);
  writeLetter(72, 8, 11);
  writeLetter(0, 9, 11);
  writeLetter(205, 10, 11); // "tabelka!"
  
  writeLetter(223, 1, 12);
  writeLetter(194, 2, 12);
  writeLetter(194, 3, 12);
  writeLetter(194, 4, 12);
  writeLetter(194, 5, 12);
  writeLetter(194, 6, 12);
  writeLetter(194, 7, 12);
  writeLetter(194, 8, 12);
  writeLetter(194, 9, 12);
  writeLetter(226, 10, 12); // line

  writeLetter(205, 1, 13);
  writeLetter(205, 10, 13); // border

  writeLetter(205, 1, 14);
  writeLetter(205, 10, 14); // border

  writeLetter(218, 1, 15);
  writeLetter(204, 2, 15);
  writeLetter(204, 3, 15);
  writeLetter(204, 4, 15);
  writeLetter(204, 5, 15);
  writeLetter(204, 6, 15);
  writeLetter(204, 7, 15);
  writeLetter(204, 8, 15);
  writeLetter(204, 9, 15);
  writeLetter(219, 10, 15); //end of the table
}

void setup()
{
  //pinmodes
  for(int x = DATA_MSB; x <= DATA_LSB; x++)
    pinMode(x, OUTPUT);

  for(int x = ADD_MSB; x <= ADD_LSB; x++)
    pinMode(x, OUTPUT);

  pinMode(SEL_IO, OUTPUT);
  pinMode(WR, OUTPUT);
  pinMode(LED, OUTPUT);

  digitalWrite(WR, HIGH);
  digitalWrite(SEL_IO, HIGH);

  blinkLED(100);
  clearBuffer(0);
  pasteText();

  //serial
  Serial.begin(115200); //move to the end of setup()
  Serial.println("iNap GPU tester - ready");
}

void loop()
{
  writeLetter(7,2,2); //dynamic test buffer !
  delay(1000);

  writeLetter(66,2,2);
  delay(1000);
}