PImage img;  // image


PrintWriter output;
int loc = 0;
int znakx = 0;
int znaky = 0;

void setup()
{
  
  size(320,240);
  img = loadImage("437.png");
  output = createWriter("array.txt"); 
  output.println("const static byte data[" + img.width/8*img.height/16+ "][16] PROGMEM = {"); //remember to delete last "," and add "};" to the very end.
  
  img.loadPixels();
  for (int y = 0; y < img.height / 16; y++) //for each row
  {
    for (int x = 0; x < img.width / 8; x++ ) //for each column
    {
      output.print("{");
      for(int yy = y-znakx+(y*16); yy < y-znakx+(y*16)+16; yy++)
      {
        output.print("B");
        for(int xx = x-znaky+(x*8); xx < x-znaky+(x*8)+8; xx++)
        {
          loc = xx + yy*img.width+(y*36);                             //some ugly math, don't mind - even I don't know how I achieved this
          if (brightness(img.pixels[loc]) > 127) output.print("1");
          else output.print("0");
        }
        output.print(", ");
       }
       output.println("},");
       znaky++;
     }
     znakx++;
   }

}

void draw() {
  background(0);
  image(img,0,0); //image :o
}


void keyPressed() {
  output.flush();  // writes data to the file
  output.close();  // and closes it
  exit();  // stop
}
