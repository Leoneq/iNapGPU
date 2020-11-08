# iNapGPU 🖥
Text-mode graphics card, using only TTL gates.
![](https://github.com/Leoneq/iNapGPU/blob/main/images/charset.jpg?raw=true)
#### Specs
- VGA resolution 800x600@60Hz (accessible 400x300), mono
- 50x18 characters
- up to 255 chars in charset, up to 4 charsets using 1Mbit EPROM
- created using 2 counters, some TTL gates and EPROM with SRAM
- parallel interface; works with arduino or Z80
- terrible idea anyway, use fpga instead
- total IC count: 21
- supports latin alphabet with polish letters, and Standard Galactic Alphabet

Inspired by Ben Eater's "[World's worst video card](http:/https://eater.net/vga/ "World's worst video card")", I built myself something more.. worse? His video card was rather a digital frame, than a working video card. I fixed this - and I optimized the timer circuitry.

(anyway, i have to tell you that my english is not best, but i try)

I haven't built a computer yet, so the card is tested with Arduino Mega, as it have many pins and it's quite cheap. So, as long as you have 21 free pins on your microcontroller (or you have hooked some shift registers), you can connect the GPU card to almost anything - Arduino, ESP, STM etc. The test code for Mega is attached in this repository.

Here is how the card looks:
![](https://github.com/Leoneq/iNapGPU/blob/main/images/gora.jpg?raw=true)
![](https://github.com/Leoneq/iNapGPU/blob/main/images/dol.jpg?raw=true)
I know it's terrible, and soldering many, MANY connections with .12mm wire is terrible too, but it's how I done it. When I was creating the schematic, I didn't know that it will work - this is why I soldered it on protoboard. I suggest you to ~~do it on fpga 'cause everyone's life will be easier then~~ create a normal PCB, DIY or bought.

So - I'll skip the most obvious parts, and focus on the HSYNC timer.
![](https://github.com/Leoneq/iNapGPU/blob/main/images/schematics/hc.png?raw=true)
The pixel clock is 20MHz - two times more than Ben's card. Instead of using 3 4bit counters, I used one, 12bit counter. The thing is, it's rated for 12MHz max. at 15V! This is why I DON'T GUARANTEE this will work for you; you should use those 4bit counters. (tip: for me only SMD versions of CD4040 worked) Next, the numbers from counter are going to NAND gates. There are two things with it - I'm comparing only "ones"of numbers, but Ben is comparing the entire number. The thing is, when I'm not comparing "zeros", the number will be "shown" multiple times, what luckily won't affect us. Since the RS flip-flop is activated once, activating it more times won't do anything. Same for resetting it. The signal from last pixel (528) is connected via NOT gate, as reset and clock are high active signals.
![](https://github.com/Leoneq/iNapGPU/blob/main/images/schematics/vc.png?raw=true)
With the vertical timer the thing is same: normal CD4040 counter, with NAND gates and two RS flip-flops. And at this stage, I did a small mistake, just as Ben did: the timers are counting from 0. Thus, when the total amount of pixels in a row WILL be 528px, the first pixel is 0, and the last is 527. At least let's say it's not that important, as everything is working just fine. Another thing is, that the timer IS running at 37.(87)kHz, and physically we could achieve resolution 400x600 - but this is really bad idea. This is why the first bit of the counter is not used.
![](https://github.com/Leoneq/iNapGPU/blob/main/images/schematics/mem.png?raw=true)
The heart of my GPU is in the last sheet. I've successfully connected RAM and ROM to timers, that generate actual image. I used M27C1001 with read time up to 100ns, and as far as I checked - version 45ns doesn't really change anything. The IC is UV EPROM with capacity of 1Mbit. Sadly, this decreases to "only" 128kbit, as I'm using the memory as 1bit memory. At least, it was enough for 4 charsets with 255 chars each.
The first 8 bits of address is a character from SRAM. The next four bits are rows, next three bits are columns, and last two bits are for chosing the codepage. 
Also, you can select the actual color of the font.
As being said, the first 8 bits are connected to the SRAM. I used 2kB HM6116 IC, as I don't need more (there's only 900 chars to store). The tricky thing is connecting the entire card with the environment. I used tri-state logic buffers, 74LS245 and 74LS244 as most optimal choice. They're separating timers from the SRAM while writing, and separating data and address bus while timers are reading from SRAM. Also, I did there a small mistake, and connected '245 between SRAM and EPROM. The best solution here should be a latch, as it will store actual character for a moment, not clear the entire bus. This should work better than '245, but I don't have '373 at this moment.

And this is it! An actual video card from TTL gates, as I said. I'm giving to you tools to convert an image into a charset, and code I used for testing with Arduino.  On [this repository](http://https://github.com/Leoneq/eprom_programmer "this repository") is also code for my DIY eprom programmer. I hope you won't do this, really, this is huge waste of time (but I can say "I built a graphics card without any microcontroller!" at least ;d )

Known anomalies:
- the image is slightly glitching while writing. This happpens beacuse I can't write and read at same time, so I have to live with it.
- the card is very sensitive to environment noise. The image can distort when there's an USB cable nearby, or oscilloscope cable.
- the characters are not clear. This happens because of the ROM, in many ways, such as power supply, read access time etc.
- there are strange lines in the background, at least in mine card. I have no idea what are these, and as soon as I get new oscilloscope, I'll try to erase them (literally)
- the image is ugly. Really, what were you expecting from second world's worst video card?

![](https://github.com/Leoneq/iNapGPU/blob/main/images/gpuqa.png?raw=true)
![](https://github.com/Leoneq/iNapGPU/blob/main/images/przyklad.jpg?raw=true)
![](https://github.com/Leoneq/iNapGPU/blob/main/images/tabelka.jpg?raw=true)
created with ❤ by Leoneq ;3
