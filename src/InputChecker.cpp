#include "InputChecker.hh"

#include "DataStructure/ABufferData.hh"

#include "EditorException.hh"

#include <algorithm>
#include <iostream>

InputChecker::InputChecker()
{
    _currentTextureBinding = 0;
}

void InputChecker::checkInput(SContainerInstance const *root, QString &attributesCode, QString &uniformCode)
{
    getAllInputs(root, attributesCode, uniformCode);
    checkInputsTree(root);
}

void InputChecker::getAllInputs(SContainerInstance const *root, QString &uniformCode, QString &attributesCode)
{
    QList<SInstance*>::const_iterator it = root->begin();
    QList<SContainerInstance*> toExplore;
    QList<SDataInstance*> attributesDepth;

    while (it != root->end())
    {
        if ((*it)->getType() == CONTAINER_INSTANCE)
        {
            toExplore.push_back(static_cast<SContainerInstance*>(*it));
        }
        else
        {
            SDataInstance *inputData = static_cast<SDataInstance*>(*it);

            if (inputData->getData()->getType() == AbstractData::DATA_VERTEX_BUFFER)
            {
                attributesDepth.push_back(inputData);
            }
            else if (inputData->getData()->getType() != AbstractData::DATA_INDEX_BUFFER)
            {
                QString uniformName = inputData->getInputName();
                QMap<QString, AbstractData::EDataTypes>::const_iterator existing = _uniformNames.find(uniformName);

                if (existing == _uniformNames.end())
                {
                    // Fill the uniform code and add the uniform to the global list th
                    _uniformNames[uniformName] = inputData->getData()->getType();
                    uniformCode += "\n" + inputData->getData()->getInputType() + " " + uniformName + ";";
                    // Set the texture binding point for the uniform
                    if (inputData->getData()->getType() == AbstractData::DATA_RENDER_TEXTURE ||
                        inputData->getData()->getType() == AbstractData::DATA_LOADED_TEXTURE)
                    {
                        _texturesBinding[uniformName] = _currentTextureBinding++;
                    }
                }
                else if (existing.value() != inputData->getData()->getType())
                {
                    QString title = "Redefined input type";
                    QString details = "The input '" + existing.key() + "' redefines its type.";
                    throw EditorException(title, details);
                }
            }
        }
        ++it;
    }
    if (attributesCode.isEmpty())
    {
        for (QList<SDataInstance*>::const_iterator it = attributesDepth.begin(); it != attributesDepth.end(); ++it)
        {
            attributesCode += "\n" + (*it)->getData()->getInputType() + " " + (*it)->getInputName() + ";";
        }
    }
    for (QList<SContainerInstance*>::const_iterator it = toExplore.begin(); it != toExplore.end(); ++it)
    {
        getAllInputs(*it, uniformCode, attributesCode);
    }
}

// Check if an input is defined twice at the same level of the tree and if all the attributes and uniforms are filled for each draw call
void InputChecker::checkInputsTree(SContainerInstance const *root)
{
    bool foundDrawCall = false;
    QList<QString> uniformDepth;
    QList<QString> attributeDepth;
    QList<SContainerInstance*> toExplore;
    int attributeVertexNumber = -1;
    bool numberOfverticesChanges = false;
    bool isIndexed = false;

    for (QList<SInstance*>::const_iterator it = root->begin(); it != root->end(); ++it)
    {
        if ((*it)->getType() == CONTAINER_INSTANCE)
        {
            toExplore.push_back(static_cast<SContainerInstance*>(*it));
        }
        else
        {
            SDataInstance *inputData = static_cast<SDataInstance*>(*it);

            if (inputData->getData()->getType() == AbstractData::DATA_VERTEX_BUFFER)
            {
                foundDrawCall = true;
                // Check if the attribute is defined twice for this depth
                if (attributeDepth.contains(inputData->getInputName()))
                {
                    QString title = "Redefined attribute.";
                    QString details = "The attribute '" + inputData->getInputName() + "' is defined twice in the same container.";
                    throw EditorException(title, details);
                }
                attributeDepth.append(inputData->getInputName());
                if (attributeVertexNumber == -1)
                {
                    attributeVertexNumber = static_cast<ABufferData*>(inputData->getData())->getCount();
                }
                else if (attributeVertexNumber != static_cast<ABufferData*>(inputData->getData())->getCount())
                {
                    numberOfverticesChanges = true;
                }
            }
            else if (inputData->getData()->getType() == AbstractData::DATA_INDEX_BUFFER)
            {
                foundDrawCall = true;
                if (isIndexed == true)
                {
                    QString title = "Index buffer problem.";
                    QString details = "More than one index buffer in a draw call.";
                    throw EditorException(title, details);
                }
                isIndexed = true;
            }
            else
            {
                // If it is a texture, we set the binding to the instance
                if (inputData->getData()->getType() == AbstractData::DATA_RENDER_TEXTURE ||
                    inputData->getData()->getType() == AbstractData::DATA_LOADED_TEXTURE)
                {
                       inputData->setTextureBinding(_texturesBinding[inputData->getInputName()]);
                }
                // Check if the uniform is defined twice for this depth, otherwise just add it to the list and carry on
                if (uniformDepth.contains(inputData->getInputName()))
                {
                    QString title = "Redefined uniform.";
                    QString details = "The uniform '" + inputData->getInputName() + "' is defined twice in the same container.";
                    throw EditorException(title, details);
                }
                else if (_uniformFilled.contains(inputData->getInputName()) == false)
                {
                    uniformDepth.push_back(inputData->getInputName());
                }
            }
        }
    }
    // Add the uniforms found at this depth and add them to the total uniforms taversed
    _uniformFilled.append(uniformDepth);
    // If the draw call is in this depth, then all the uniforms must be filled
    // and all the attribute must have been found
    if (foundDrawCall)
    {
        if (_uniformNames.size() != _uniformFilled.size())
        {
            QString title = "Uniforms missing.";
            QString details = "All the uniforms are not filled for every draw call.";
            throw EditorException(title, details);
        }
        if (_attributeNames.size() != 0)
        {
            std::sort(attributeDepth.begin(), attributeDepth.end());
            if (attributeDepth != _attributeNames)
            {
                QString title = "Attributes missing.";
                QString details = "All the attributes are not filled for every draw call.";
                throw EditorException(title, details);
            }
        }
        else
        {
            _attributeNames = attributeDepth;
            std::sort(_attributeNames.begin(), _attributeNames.end());
        }
    }
    // Check if all the vertex buffers have the same number of vertices
    // (Doesn't matter if the draw call is indexed)
    if (numberOfverticesChanges == true && isIndexed == false)
    {
        QString title = "Vertex buffer size not matching.";
        QString details = "All the vertex buffers in the draw call do not have the same number of vertices.";
        throw EditorException(title, details);
    }
    // We check all the lower levels of the tree
    for (QList<SContainerInstance*>::const_iterator it = toExplore.begin(); it != toExplore.end(); ++it)
    {
        checkInputsTree(*it);
    }
    // And then we remove the uniforms from the filled list
    for (QList<QString>::const_iterator it = uniformDepth.begin(); it != uniformDepth.end(); ++it)
    {
        _uniformFilled.removeOne(*it);
    }
}

