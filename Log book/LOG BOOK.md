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
I found a way to handle all the _OpenGL_ calls in the same set of functions with _Qt_

Questions:
- Should I keep using _Qiwi_? It seems a little buggy...

Goals for next time:
- Use the RenderPass object to draw a 3D cube
- Display an OpenGL frame buffer object on screen (the previously drawed cube)
- Link the interface with the RenderPass objects (possibility to create a render pass, click on it and see its output)

## 8 june 2015
Texture editor coded: it is now possible to add/remove a texture, choose its _OpenGL_ properties, its size and its name in the editor.
3D cube drawing is not possible right now, it might be better to start coding a data structure creator to pass some useful information to the shaders (camera matrix for example) before starting to draw 3D objects.
No problem with the _Qt_ threading for the moment: _OpenGL_ seems to work pretty well.

The project will be composed of 4 main panels:
- The render pass graph node, to link the different render pass together
- The render pass editor, to edit a render pass (the shaders code and the different properties of the pass)
- The texture editor to create and set the properties of the textures
- The data structure editor to create simple data structures to feed to the shader

Goals for tomorrow:
- Code a simple data structure editor (to get the camera matrix in the shader)
- Allow to choose in the render pass between post-FX (draw a simpe quad on the screen) and 3D models (for the moment, just a 3D cube)

**Thought:** It could be nice to change the parameters of the textures in the render pass.

## 9 june 2015
**Thought:** I need to think about a way to handle the data structures in my program.
What is a data structure?
- Set of uniform (constant) variables given to a shader
- Vertex buffer (geometry) that needs to be drawn

Some uniform change by draw call (for each geometry drawed, for example the texture or material of the current geometry) and other are constant over all the draw calls.
It would be nice to choose how the uniform are given.
Could we organize that as a tree?

Sample:
- Draw All Elements
  - Draw Object
    - Draw Call 1
      - **Mesh 1** _actual draw call here_
      - **Texture Mesh 1** _uniform variable_
    - Draw Call 2
      - **Mesh 2** _actual draw call here_
      - **Texture Mesh 2** _uniform variable_
    - **Object Transform** _uniform variable_
  - **Camera Transform and Projection** _uniform variable_

There should not be more than one draw call per branch of the tree.
This tree should actually be specific to the render pass.
It might be nice to have the data separated from this tree so that we can give them in different ways depending on the render pass. But for the 3D objects, we need to keep the hierarchy to see the link between the textures/material data and the vertices.
So the data structure editor must allow to create/load branches that can then be used as building blocks for the update of the data in the render pass.

Actual data corresponding to the sample above:
- Draw Call 1
  - **Mesh 1** _actual draw call here_
  - **Texture Mesh 1** _uniform variable_
- Draw Call 2
  - **Mesh 2** _actual draw call here_
  - **Texture Mesh 2** _uniform variable_
- **Object Transform** _uniform variable_
- **Camera Transform and Projection** _uniform variable_

TODO: Check how to handle a tree view with complex elements in _Qt_
