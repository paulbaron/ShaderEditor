## 3 June 2015
Downloaded _Qt creator_ to simplify the creation of GUI with Qt.
I have also searched for a simple node graph editor that I could use for my shader editor and I found _Qiwi_ which is a standalone and very light and easy to understand piece of code to create node graphs.

Goals for tomorrow:
- Modify the code of _Qiwi_ so that I can integrate an _OpenGL_ textures viewer in each node
- Try to integrate a simple text editor in each node
- Try to make the nodes expand on click so that the user can easily see the whole node hierarchy on his screen

## 4 june 2015
Integration of a basic _OpenGL_ widget to the editor and 2 text editor for the fragment and vertex shader.
To heavy to display _OpenGL_ textures directly on the nodes: the user will have to select a node to see its texture output.

Questions:
- How to handle multiple _OpenGL_ widgets at the same time? (thread safe...)

Goals for tomorrow:
- Display a simple cube
- Data structure for handling the creation an linkage of multiple render pass

## 5 june 2015
Simple display of a texture in the editor coded.
The data structure for the render passes has been created.
I found a way to handle all the OpenGL calls in the same set of functions with Qt

Questions:
- Should I keep using Qiwi? It seems a little buggy...

Goals for tomorrow:
- Use the RenderPass object to draw a 3D cube
- Display an OpenGL frame buffer object on screen (the previously drawed cube)
- Link the interface with the RenderPass objects (possibility to create a render pass, click on it and see its output)