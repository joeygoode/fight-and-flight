Fight and Flight
----------------

Right, here's how to write your own shader code:
1.  Right now only the basicEffect file does anything.  Modify that.
2.  You can only use the data stored in the vertex 
(which I believe is just position and color data)
3.  You can also use 3 uniforms, world matrix, view matrix, 
and projection matrix.
4.  Run the executable.  It should work.  
If it doesn't, let me know and I'll see if I can fix it.
5.  Your changes to basicEffect should be reflected in the executable.  
Don't modify the other basicEffect as I'm using to make sure all the 
changes I'm making aren't breaking anything.  When I run it from inside 
the IDE, it uses the other basicEffect, so modify the one in the debug 
folder at will.

Just focus on learning the shader language for now.  I'll try and get an 
interface where I can expose whatever you need to you through XML.  I 
want to get billboards in next so I can draw some terrain.