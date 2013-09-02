---
title: "AVR Programming with hackaday's tutorial"
layout: layout
---
Using [HackADay's AVR tutorial](http://hackaday.com/2010/11/05/avr-programming-03-reading-and-compiling-code/) to learn a bit of AVR programming, hopefully so I can construct a 4x4x4 LED cube and write some routines to make some nice visual effects, the big goal is to write a frequency visualiser for it, taking an audio input and lighting up columns of LEDs according to the amplitude of different frequencies in the source wave. I'll be content just writing routines to light up the LEDs prettily though for the time being.

Look at the [Miscellaneous Notes](../miscellaneous.md) for a few general things I stumbled over + other things.

# Hexadecimal and Binary
When dealing with binary numbers in C, it's quickest to type them out in hexadecimal, this is surprisingly easy due to a nice little trick allowing you to interpret a byte as 2 nibbles (four bit quantities):

`0x28 == 0010_1000`

`0xaf == 1010_1111`

Simply take the first part of the hexadecimal number, for `0xaf` it's `a`, which in binary is `1010` and then take the second part `f` which in binary is `1111`, then join them together -> `10101111`.

# Bitwise Operators
Refer to [Programming 101](http://www.avrfreaks.net/index.php?name=PNphpBB2&file=viewtopic&t=37871) for an in-depth tutorial.

<table border="1">
<tr><td>|    </td><td>OR         </td></tr>
<tr><td>&amp;</td><td>AND        </td></tr>
<tr><td>~    </td><td>NOT        </td></tr>
<tr><td>^    </td><td>XOR        </td></tr>
<tr><td>&lt;&lt;   </td><td>Shift Left </td></tr>
<tr><td>&gt;&gt;   </td><td>Shift Right</td></tr>
</table>

- `foo |= 0x01` takes a byte foo, and set's the `0x01` bit, think about the maths.
- `foo &= 0x01` will set foo as `0x01` if the first bit (as we're using `0x01`) is set, otherwise it will set foo as `0x00`
- Shift left and Shift right allow us to make binary numbers really easily, for example: 
  `0x01`

# Blink code
{% highlight c %}
  /*
  * Hackaday.com AVR Tutorial firmware
  * written by: Mike Szczys (@szczys)
  * 10/24/2010
  *
  * ATmega168
  * Blinks one LED conneced to PD0
  *
  * http://hackaday.com/2010/10/25/avr-programming-02-the-hardware/
  */

  #include <avr/io.h>
  #include <avr/interrupt.h>

  int main(void)
  {

    //Setup the clock
    cli();      //Disable global interrupts
    TCCR1B |= 1<<CS11 | 1<<CS10;  //Divide by 64
    OCR1A = 15624;    //Count 15624 cycles for 1 second interrupt
    TCCR1B |= 1<<WGM12;   //Put Timer/Counter1 in CTC mode
    TIMSK1 |= 1<<OCIE1A;    //enable timer compare interrupt
    sei();      //Enable global interrupts

    //Setup the I/O for the LED

    DDRD |= (1<<0);   //Set PortD Pin0 as an output
    PORTD |= (1<<0);    //Set PortD Pin0 high to turn on LED

    while(1) { }      //Loop forever, interrupts do the rest
  }

  ISR(TIMER1_COMPA_vect)    //Interrupt Service Routine
  {
    PORTD ^= (1<<0);    //Use xor to toggle the LED
  }  
{% endhighlight %}

Right, this to me looks like gobbledygook, regardless of having programmed in Processing...
`int main(void)` is the start of the program, `main` is responsible for starting execution, it's just an arbitrary function name that is now used in every programming language. 
Let's start off by looking at the program line by line, the top lines starting with `#include` tell the C-preprocessor to include the files in angle brackets, this makes some 
useful functions available. The largest chunk of code which resides in main sets up the clock, so that the LED is flashed every second.

`cli()` allows you to disable all global interupts, so you know, from there on, nothing will interupt the execution of your code (apart from pulling the power), to re-enable the global interrupts (they're useful) use `sei()`

`unsigned char <var_name>` is used to declare a byte (0-255). 
