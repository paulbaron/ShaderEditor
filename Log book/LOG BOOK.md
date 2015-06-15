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
To heavy to display _OpenGL_ textures directly on the nodes: the user will have to select a node to see its texture output.

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
No problem with the _Qt_ threading for the moment: _OpenGL_ seems to work pretty well.

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
