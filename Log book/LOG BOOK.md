## 3 June 2015

#### Done today
Downloaded _Qt creator_ to simplify the creation of GUI with Qt.
I have also searched for a simple node graph editor that I could use for my shader editor and I found _Qiwi_ which is a standalone and very light and easy to understand piece of code to create node graphs.

#### Goals for tomorrow
- Modify the code of _Qiwi_ so that I can integrate an _OpenGL_ textures viewer in each node
- Try to integrate a simple text editor in each node
- Try to make the nodes expand on click so that the user can easily see the whole node hierarchy on his screen

## 4 june 2015

#### Done today
Integration of a basic _OpenGL_ widget to the editor and 2 text editor for the fragment and vertex shader.
Too heavy to display _OpenGL_ textures directly on the nodes: the user will have to select a node to see its texture output.

#### Questions
- How to handle multiple _OpenGL_ widgets at the same time? (thread safe...)

#### Goals for tomorrow
- Display a simple cube
- Data structure for handling the creation an linkage of multiple render pass

## 5 june 2015

#### Done today
Simple display of a texture in the editor coded.
The data structure for the render passes has been created.
I found a way to handle all the _OpenGL_ calls in the same set of functions with _Qt_

#### Questions
- Should I keep using _Qiwi_? It seems a little buggy...

#### Goals for next time:
- Use the RenderPass object to draw a 3D cube
- Display an OpenGL frame buffer object on screen (the previously drawed cube)
- Link the interface with the RenderPass objects (possibility to create a render pass, click on it and see its output)

## 8 june 2015

#### Done today
Texture editor coded: it is now possible to add/remove a texture, choose its _OpenGL_ properties, its size and its name in the editor.
3D cube drawing is not possible right now, it might be better to start coding a data structure creator to pass some useful information to the shaders (camera matrix for example) before starting to draw 3D objects.
No problems with the _Qt_ threading for the moment: _OpenGL_ seems to work pretty well.

The project will be composed of 4 main panels:
- The render pass graph node, to link the different render pass together
- The render pass editor, to edit a render pass (the shaders code and the different properties of the pass)
- The texture editor to create and set the properties of the textures
- The data structure editor to create simple data structures to feed to the shader

#### Goals for tomorrow
- Code a simple data structure editor (to get the camera matrix in the shader)
- Allow to choose in the render pass between post-FX (draw a simpe quad on the screen) and 3D models (for the moment, just a 3D cube)

#### Thought
It could be nice to change the parameters of the textures in the render pass.

## 9 june 2015

#### Thought
I need to think about a way to handle the data structures in my program.
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

**TODO**: Check how to handle a tree view with complex elements in _Qt_

#### Thought
Should I keep the texture editor panel? Can it be merged in the data structure editor?
Two kind of textures:
- Render textures to draw in
- Loaded textures, to sample

But we can eventually draw in a loaded texture, so there is no real difference between those.

finally, the program will only have 3 main panels:
- The data structure editor
- The render pass node graph
- The render pass editor

They will be handled by the following managers:
- Render pass manager: keep the render pass graph node with all the render pass data
- The data manager: handle a collection of data structure, organized as a tree

#### Thought
Organization of the model view:
- Model Data: contains slots to update its attribute and the widget to display with access to the UI
- View Data: contains the UI created with the designer

#### Done today
I have started the implementation of the data structure editor and manager and I have merged the texture editor in it.

#### Goals for tomorrow
- Finish the data editor so that we can add and remove data structure
- The user must be able to reorganize the data tree
- Add a simple cube with vertex/color to load in the vertex buffer data

## 10 june 2015

#### Done today
I have implemented the vertex buffer editor (only for vec3 for the moment) and I had some difficulties creating an editable dynamic table with _Qt_ using the QAbstractItemModel and the QItemDelegate.
It is now also possible to load some presets (cube and plane), edit and add some data.
So I now have the implementation of the vertex buffer in the data structure editor, but not yet the matrix that are essential to have a useful shader.
I cannot reorganize the data in a tree yet, I need to implement it as soon as possible.

#### Goals for tomorrow
- completely finish the vertex buffer data structure for vec3
- Finish the matrix editor
- The user must be able to reorganize the data tree

## 11 june 2015

#### Done today
I have completely finished the vertex buffer data structure for the vec3 and improved the marix editor

#### Goals for tomorrow
- Finish the matrix editor
- The user must be able to reorganize the data tree

## 12 june 2015

#### Done today
I have completely finished the matrix editor. I have alost finished to implement the data tree. Still some bugs to correct, that might take some time.

#### Goals for tomorrow
- The user must be able to reorganize the data tree

## 13 june 2015

#### Thought
I must now think about how to instantiate the datas without copying them.
I have removed the container class and handle a container as a SInstance.
I have created a structure SInstance that has a pointer to the parent container and either a pointer to the data or a list of other instances (it is either a data or a list of datas).
This way, the data are never copied but the containers are always copied.
I will then have:

```C++
enum EInstanceType
{
	DATA_INSTANCE,
	CONTAINER_INSTANCE
};

struct SInstance
{
	EInstanceType type;
	SDataInstance *parent;
};

struct SContainerInstance : public SInstance
{
	QList<SInstance*> instances;
	QString containerName;
};

struct SDataInstance : public SInstance
{
	AbstractData *data;
};
```

This way, we can change the container and the shape of the tree in the render pass, but if we modify the data in the data editor, it will also be taken into account.

#### Done today
It is now possible to reorganize the data tree.
The data structures have been changed to allow easy instantiation and copy.

#### Goals for tomorrow
- Implement the instantiation of data in a render pass (the input tree)
- Choose the output texture of a render pass
- Have the first 3D rendering of a render pass

## 14 june 2015

#### Thought
I started to code the render function in the render pass object.
How is the tree going to be handled?

Lets imagine a tree like that:
- Draw Call 1
  - **Mesh 1** _draw call_
  - **Texture Mesh 1** _uniform variable_
- **Object Transform** _uniform variable_
- **Camera Transform and Projection** _uniform variable_
- **Mesh 2** _draw call_

This can actually be a problem as the draw call of **Mesh 2** does not have a uniform texture linked to it.
It means that at all the level of the tree with a draw call, all the uniforms needs to be present.
It would be also easier to handle if I had a rule saying that all the draw calls needs to be at the same depth in the input tree.

To resume the rules I need to code:
- All the draw calls at the same depth
- All the uniforms needs to be filled for all the draw calls, otherwise an error will appear
- A uniform can be set only once per level in the tree
- If a uniform is set in two different levels of the tree, the deeper one overwrite the other
- If two uniforms have the same name, they must be of the same type

#### Thought

Maybe think of a way to separate the data structures from the render groups.

#### Done today
I have a basic implementation of the inputs and outputs of a render pass and a basic render pass manager.

#### Goals for tomorrow
- Have the first 3D rendering as if the rules were implemented, this is very important!
- Implement the rules described above

## 15 june 2015

#### Thought

No need to separate the data structure from the render groups: the groups can be both: if a group contains a draw call, then it is a render group, otherwise it is a data structure.

#### Done today
Started a basic drawing. The rules for the input tree are not yet implemented.
I now can draw some basic 3D shapes.

![shadereditor2](https://cloud.githubusercontent.com/assets/5550866/8174390/e10021b6-13d3-11e5-8c66-b03bea509465.png)

#### Goals for tomorrow
- Implement the rules for the input tree
- Test the multiple render targets drawing
- Need to check if the framebuffer attachments are all the same size

## 16 June 2015

Meeting with supervisor.

To do by June 29:
Litterature review (choice of technology...)
Structure of dissertation (outline)
Planning

Meeting July 1st 11am UK time on skype:
peter.j.rodgers

## 2 July 2015

#### Done today
Started to implement the rules for the inputs.
I decided that the software would be more flexible if some draw calls could be at different depth as it is actually not that hard to check the correctness of the inputs.

#### Thought
I also need to check the draw calls so that:
- There must be the same number of vertex buffer for each draw call
- They must have the same name

#### Goals for tomorrow
- Finish implementing the rules for the input tree

## 3 July 2015

#### Done today
The rules for the inputs are now working (for the uniforms and for the attributes) and also checking the attributes.
Still need to check empty branches, but its not a real problem.

#### Goals for tomorrow
- Add the possibility of adding sons in groups created in the inputs in the UI
- Make complex rendering possible with a simple render pass and multiple draw calls
- Maybe add a warning on the tree branches that does not contain a draw call (useless)
- Add a button to update the UI texture viewer (if we could choose what texture to display, it would be better)

## 4 July 2015

#### Done today
I Added the possibility for complex rendering in a single render pass (multiple draw calls) and I added a button to update the UI texture viewer.
The update of the rendering is now made by a click on a button.
It is also now possible to reorganize the input tree.

#### Goals for tomorrow
- Remove Qiwi and start with a simple list of render pass to update in order
- The input code generation is not working very well, adapt it to complex rendering in a single pass by integrating it in the input checker

## 5 July 2015

#### Done today
I have removed Qiwi from the project because it as crashing and a simple list of render pass must be enough to have a working software.
It is now possible to add multiple render pass.
I also added an abstract class for the vertex buffer to handle the same way all the different types of vertex buffer.
The class tat check if the inputs are correct now also does the input code generation for the shaders.

#### Thought
When implementing indexed rendering, check that there is not higher indexes than number of vertices for a draw call and that there is only one index buffer per draw call

Here are the final rules for the input tree:
**Display an error:**
  - All the uniforms needs to be filled for all the draw calls, otherwise an error will appear
  - A uniform can be set only once per level in the tree
  - If a uniform is set in two different levels of the tree, the deeper one overwrite the other and they must have the same type
  - All the attributes must be filled for each draw call in the tree (so if an attribute is present at one depth, all the other attributes needed must also be there)
  - All the vertex buffers must have the same number of vertices for the same draw call
  - In case of indexed rendering, the index buffer must not contain any index higher than the number of vertices in the other vertex buffers
  - There can only be one index buffer per draw call
**Display a warning:**
  - A branch of the tree does not contain any draw call

#### Goals for tomorrow
- Add to the input checker that the number of vertex on each vertex buffer must be the same for each draw call

## 8 July 2015

#### Done today
I totally finished the input checker and I have fixed some bugs on the input tree.
Complex rendering in a single pass is now working perfectly.

// Display screenshot

#### Goals for tomorrow
- Start implementing an index buffer for indexed rendering
- Add a text input to rename the data, it is very confusing without clear name

## 9 July 2015

#### Done today
Refactoring of the buffer data code so that all buffers are handled in the same way with templates.
Integration of index buffers as a data.
I added the rule that there can only be one index buffer per draw call to the input checker

#### Goals for tomorrow
- Finish the indexed rendering
- Add a text input to rename the data
- Remove the input name of the indexed buffer (it is useless as it is not used in the shader directly)

## 10 July 2015

#### Done today
Indexed rendering working.
I added some presets to test it: Cube Indexed Vertices and Plane Indexed Vertices that allow to have the minimum number of vertex for this shapes.
I also removed the input name for the indexed buffer and changed the default name of the data.

#### Goals for tomorrow
- Fix the bugs when removing an input or a data
- Replace the pointer in the SInstance by an index to prepare for serialization and avoid segfaults

## 11 July 2015

#### Done today
The pointer to abstract data has been removed from the instance, there is now an Id instead (useful for serialization and avoid the bugs when removing a data structure).
Fix of the bug when removing a container in the data structure editor and in the input editor.
Fix memory leak in data and instances.

#### Goals for tomorrow
- Be able to set a texture as an input
- Start a texture loading

## 12 July 2015

#### Done today
I added the handling of texture binding point to the InputChecker class.
It is now possible to set texture as input in the shaders.

#### Goals for tomorrow
- Loading a texture from a file

## 13 July 2015

#### Done today
I have abstracted the texture object so the user can now instantiate two kinds of textures:
- The render textures in which he can draw and use as a sampler in his shaders
- The loaded textures that he can load from a file in which he cannot draw
I also integrated the image library _DevIL_ to the project.

#### Goals for tomorrow
- Make the texture loading work

## 16 July 2015

#### Done today
The texture loading is now working.

// Display Screenshot

#### Goals for tomorrow
- Try to display a thumbnail of the loaded texture in the data structure editor

## 17 July 2015

#### Done today
There is now a generic widget to render _OpenGL_ textures on screen.
It is used to display the thumbnails of the loaded images and the current render pass.
A bug on the projection matrix has been corrected (degres instead of radians).

#### Goals for tomorrow
- Some textures causes a segfault on load, check why _DevIL_ returns wrong parameters.
- The loaded textures are flipped vertically.
- Start programming an interface for the _OpenGL_ states configuration (depth test, depth writing, face culling, stencil test...).

## 18 July 2015

#### Done today
The textures are now loaded correctly with _DevIL_.
I also added uv coordinates to the existing presets to be able to test the textures on simple meshes.

#### Goals for tomorrow
- Start programming an interface for the _OpenGL_ states configuration.

## 19 July 2015

#### Done today
The UI for the _OpenGL_ states is done. It is handling:
- Color Mask
- Depth Mask
- Depth Test
- Clear Buffer Configuration
- Stencil Test
- Face Culling
I also started to create an OpenGLState class to handle the _OpenGL_ state in each render pass

#### Goals for tomorrow
- Link the interface with the OpenGLState class
- Make the OpenGLStateClass call the _OpenGL_ functions to configure rendering

## 22 July 2015

#### Done today
The _OpenGL_ state is now working.

// screenshot

#### Things to finish in the software (in order of priority)
- Make multi pass rendering work
- Be able to choose which buffer to display for a render pass
- Resolve bug when removing an instanced data
- Error messages in UI (I will have to code my own Shader object)
- Syntax highlighting for the shader code
- Add snippets of code for the shaders
- Save and Load of projects
- Add uniform data types: float, double, int, vec2, vec3, vec4, mat2 and mat3
- Save of a RenderTexture as an image on disk
- Load 3D meshes

## 3 August 2015

#### Done today
Started to implement the multi pass rendering.
The UI is now updated according to the selected render pass.

#### Goals for tomorrow
- Make the multipass rendering work

## 4 August 2015

#### Done today
The multipass rendering is now working.
When rendering a pass, all the previous ones are also rendered and the output texture from a render pass can be used as an input for another one.

#### Goals for tomorrow
- Be able to choose which buffer to display

## 5 August 2015

#### Done today
It is now possible to display on screen any render target by selecting it in the Output panel.
I found a bug on the multiple render target rendering, I had to add a call to _glDrawBuffers_ corresponding to the current outputs.

#### Goals for tomorrow
- Resolve the bug when removing an instanced data

## 6 August 2015

#### Done today
It is now possible to remove data that has been set as inputs.
If the data is not a container, it will also be removed from the input tree.
If the data is a container, it will remove all its sons that are actual data from the input tree.

#### Goals for tomorrow
- Show the error messages as popup windows in the UI
- Code a shader object to show the compilation errors in the UI

## 7 August 2015

#### Done today
I have coded the syntax highlighting for the shader code.
There is a bug on the software, with more than one texture set as input, the first texture fill the screen and it is impossible to use the software again.
It must be due to an error in the reset of the _OpenGL_ state. The bug seems to be caused by the glActiveTexture.

#### Goals for tomorrow
- Find and resolve the _OpenGL_ state error
- Show the error messages as popup windows in the UI
- Code a shader object to show the compilation errors in the UI

## 10 August 2015

#### Done today
I fixed the bug, I just needed to reset the _glActiveTexture_ to _GL\_TEXTURE0_ after the rendering.
There is also a display bug when loading a texture (the render pass viewer displays another texture), but it is not a big problem.
I forgotted to implement a rule in the input tree which is that an attribute can only be defined once per level of the tree.

#### Goals for tomorrow
- Show the error messages as popup windows in the UI

## 11 August 2015

#### Done today
I have implemented a Singleton to handle the OpenGL context more easily.
The error messages from the input tree or the texture loading are now appearing as popup windows and handled by throwing exceptions.

#### Goals for tomorrow
- Start implementing a Shader object that throw exceptions that can be then displayed in popup windows.

## 12 August 2015

#### Done today
I now have my own Shader object that handle the compilation errors better than the one from Qt (that was writting on std::cerr).
I now have error messages for any kind of error that the user can do while using the software.

#### Goals for tomorrow
- Start the loading and saving of project

## 13 August 2015

#### Done today
After researching about the _Qt_ serialization, I decided to use another library to save and load the projects (to easily switch from text files to binary files for debugging purposes).
I have tried to use the _Cereal_ library but it needs a c++11 compatibility that doesn't work with the compiler I am currently using.
I then decided to use the _boost serialization_ library, but I have some problems to link it to the project.

#### Goals for tomorrow
- Manage to properly link the _boost serialization_ library to the project.

## 14 August 2015

#### Done today
I managed to link the _boost serialization_ library and to serialize a part of the RenderPassManager class in an xml file.
I still have a warning saying that the library is not built with the same compiler options as my project, but it seems to work anyway.

#### Goals for tomorrow
- Finish the serialization of the RenderPassManager and make it work with xml archives

## 17 August 2015

#### Done today
I have finished the serialization of the RenderPassManager, but I still have some bugs with the xml archives.

#### Goals for tomorrow
- Finsh the serialization of the project

## 18 August 2015

#### Done today
I can now save the projects in an xml file. I still have some work to do on the texture path so that the path of the loaded texture is relative to the folder in which I saved the project.

#### Goals for tomorrow
- Find a solution to the texture path problem so that I can reload a project with all its resources from anywhere
- Start the project loading

## 19 August 2015

#### Done today
It is now possible to load a project that has been saved, even if the project has been moved (only using relative path).
The software is now almost finished.

#### Goals for tomorrow
- Fix the matrix serialization

## 20 August 2015

#### Done today
The matrix serialization is now better. Instead of just saving the raw matrix values, it saves the state of the UI so that the user can see which matrix he is working with.
Still find a weird segfault when loading the matrix, I need to fix that quickly.

#### Goals for tomorrow
- Fix the matrix serialization bug
- Add some data types to instanciate
- Start to code some samples
- Add the code snippets to the shader code editor

## 21 August 2015

#### Done today
I have fixed the matrix loading bug.
I have also added the types for the uniforms float, vec2, vec3

#### Goals for tomorrow
- There are still some weird serialization bugs
- There are also some bugs on the render pass display

## 22 August 2015

#### Done today
I have fixed the serialization bugs that were due to a bad handling of the _uniqueId_ of the classes.
I also have fixed a part of the rendering bug that was due to a signal emitted to display a texture while another _FrameBuffer_ was binded.

#### Goals for tomorrow
- Start a deferred shading demonstration
- Include some snippets of code in the shader text editor

## 23 August 2015

#### Done today
I have started a simple deferred shading demo to display a cube on a plane with a simple point light.
I have added some functions as snippets of code:
- A basic random function
- A function to reconstruct the world position from the depth, the pixel position and the view-proj matrix
- A function to compute the lambert factor of a light

#### Goals for tomorrow
- Improve the basic deferred rendering with a stencil light culling

## 24 August 2015

#### Done today
I have made an advanced deferred shading project, handling multiple ccolored lights in an additive buffer with a phong illumination.
I have added as snippets of code:
- A funtion that returns the normal matrix from the model matrix
- A function that computes the phong illumination (pixel illumination and specular)
- A function that gets the camera position from the view matrix	

#### Goals for tomorrow
- Start a simple blur sample

## 25 August 2015

#### Done today
I have added a simple blur sample based on a piece of code found here:
http://callumhay.blogspot.fr/2010/09/gaussian-blur-shader-glsl.html
I have added in the snippets of code a function that applies a blur on a sampler.

#### Goals for tomorrow
- Work on a depth of field effect

## 26 August 2015

#### Done today
I have programmed a depth of field effect in addition to the deferred rendering:

// Screen shot here

#### Goals for tomorrow
- Produce a release version of the software

## 27 August 2015

#### Done today
I now have a release version of the software.