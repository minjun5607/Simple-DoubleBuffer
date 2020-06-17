# Why Double Buffering?
-------------
the reason is exactly what you are seeing.

If you do not use double buffer there will always be a period of time at which the screen data is not there.
It does not matter how fast you clear the screen, you will always notice flicker.
With double buffering you essentially have 2 screens.

# How to use double buffer
-------------
I used a method called 'page flipping'.

**1. Console::CreatBuffer()**
It creates two Console screen buffer. One is the front buffer and the other is the back buffer.

**2. Console::WriteBuffer(const char* fmt, ...)**
It writes one line for one call. \n is not necessary.
If you've called CreateBuffer(), it doesn't matter how many times you've called.
  
**3. Console::FlipBuffer()**
It flips the buffer just like the function name. 
In other words, it hide front-buffer and display back-buffer.
