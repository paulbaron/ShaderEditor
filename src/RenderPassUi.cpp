#include "RenderPassUi.h"
#include "ui_renderpassui.h"

#include "OpenGLTextureWidget.hh"
#include "DataStructure/DataStructureManager.hh"
#include "RenderPassManager.hh"

#include "DataStructure/View/GLSLHighlighter.hh"

RenderPassUi::RenderPassUi(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RenderPassUi)
{
    ui->setupUi(this);

    _addSon = false;
    _removeSon = false;
    _isAddingSon = false;
    _isRemovingSon = false;

    OpenGLTextureWidget *mainRender = new OpenGLTextureWidget(true);

    mainRender->setMinimumHeight(300);
    mainRender->setMinimumWidth(533);
    QObject::connect(RenderPassManager::getManager(), SIGNAL(repaintRenderPass()),
                     mainRender, SLOT(repaint()));
    QObject::connect(RenderPassManager::getManager(), SIGNAL(textureToDisplayChanged(GLuint)),
                     mainRender, SLOT(textureToDisplayChanged(GLuint)));
    ui->renderPassDisplay->addWidget(mainRender);

    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);

    ui->inputName->setInputMask("nnnnnnnnnnnnnnnnnnnnnnnn");

    QObject::connect(DataStructureManager::getManager(), SIGNAL(currentSelectionChanged(SInstance*)),
                     this, SLOT(selectedDataChanged(SInstance*)));
    // Shaders
    QObject::connect(ui->vertexCodeEdit, SIGNAL(textChanged(void)),
                     this, SLOT(setCurrentVertexShader(void)));
    QObject::connect(ui->fragmentCodeEdit, SIGNAL(textChanged(void)),
                     this, SLOT(setCurrentFragmentShader(void)));
    // OpenGL State
    QObject::connect(ui->saveChanges, SIGNAL(released()),
                     this, SLOT(updateOpenGLState()));
    // Inputs
    QObject::connect(ui->instantiate, SIGNAL(released()),
                    this, SLOT(instantiate()));
    QObject::connect(ui->removeInstance, SIGNAL(released()),
                     this, SLOT(removeInstance()));
    QObject::connect(ui->treeWidget, SIGNAL(itemSelectionChanged()),
                     this, SLOT(selectedInputChanged()));
    QObject::connect(ui->createGroup, SIGNAL(released()),
                     this, SLOT(createGroup()));
    QObject::connect(ui->addSon, SIGNAL(released()),
                     this, SLOT(addSon()));
    QObject::connect(ui->removeSon, SIGNAL(released()),
                     this, SLOT(removeSon()));
    QObject::connect(ui->inputName, SIGNAL(textEdited(QString)),
                    this, SLOT(inputNameChanged()));
    // Output
    QObject::connect(ui->tableWidget, SIGNAL(currentCellChanged(int,int,int,int)),
                     this, SLOT(selectedOutputChanged()));
    QObject::connect(ui->setOutput, SIGNAL(released()),
                     this, SLOT(setOutput()));
    QObject::connect(ui->unsetOutput, SIGNAL(released()),
                     this, SLOT(unsetOutput()));
    QObject::connect(DataStructureManager::getManager(), SIGNAL(textureChangedType()),
                     this, SLOT(checkEnableOutput()));
    // Reload visual
    QObject::connect(ui->reloadView, SIGNAL(released()),
                     RenderPassManager::getManager(), SLOT(render()));
    // Add Snippet
    QObject::connect(ui->addSnippet, SIGNAL(released()),
                     this, SLOT(addSnippet()));

    QFont font("Monospace");
    font.setStyleHint(QFont::TypeWriter);

    ui->vertexCodeEdit->setFont(font);
    ui->vertexCodeEdit->setTabStopWidth(30);
    ui->fragmentCodeEdit->setFont(font);
    ui->fragmentCodeEdit->setTabStopWidth(30);
    _vertexHighlighter = new GLSLHighlighter(ui->vertexCodeEdit->document());
    _fragmentHighlighter = new GLSLHighlighter(ui->fragmentCodeEdit->document());
}

RenderPassUi::~RenderPassUi()
{
    delete ui;
}

void RenderPassUi::selectedDataChanged(SInstance *current)
{
    if (current == NULL)
    {
        ui->instantiate->setEnabled(false);
        ui->setOutput->setEnabled(false);
    }
    else
    {
        checkEnableOutput();
        ui->instantiate->setEnabled(true);
    }
}

void RenderPassUi::updateOpenGLState()
{
    RenderPassManager::getManager()->getCurrent()->updateOpenGLState(ui);
}

void RenderPassUi::instantiate()
{
    SInstance *instance = DataStructureManager::getManager()->getCurrent()->copy();

    RenderPassManager::getManager()->getCurrent()->setInput(instance);
    ui->treeWidget->addTopLevelItem(instance->getTreeItem());
}

void RenderPassUi::removeInstance()
{
    RenderPassManager::getManager()->getCurrent()->removeCurrentInput();
    QModelIndex idx = ui->treeWidget->currentIndex();
    QTreeWidgetItem *toRm = ui->treeWidget->currentItem();

    if (toRm->parent() != NULL)
    {
        toRm = toRm->parent()->takeChild(toRm->parent()->indexOfChild(toRm));
    }
    else
    {
        toRm = ui->treeWidget->takeTopLevelItem(idx.row());
    }
    delete toRm;
}

void RenderPassUi::selectedInputChanged()
{
    RenderPass *currentRenderPass = RenderPassManager::getManager()->getCurrent();

    if (_isAddingSon || _isRemovingSon)
        return;
    if (ui->treeWidget->currentItem())
    {
        if (_addSon) // We add a son to the container
        {
            _isAddingSon = true;

            QTreeWidgetItem *toMove = ui->treeWidget->currentItem();
            // Change hierarchy in data structure
            int currentInputId = toMove->data(0, Qt::UserRole).toInt();
            SInstance *selected = currentRenderPass->getInput(currentInputId);
            SContainerInstance *container = static_cast<SContainerInstance*>(currentRenderPass->getCurrentInput());

            currentRenderPass->removeInput(selected);
            container->addSon(selected);

            // Change hierarchy in tree view
            QModelIndex idx = ui->treeWidget->currentIndex();

            if (toMove->parent())
                toMove = toMove->parent()->takeChild(toMove->parent()->indexOfChild(toMove));
            else
                toMove = ui->treeWidget->takeTopLevelItem(idx.row());

            _currentSelection->addChild(toMove);

            ui->treeWidget->selectionModel()->clearSelection();
            ui->treeWidget->setCurrentItem(_currentSelection);

            _addSon = false;
            _isAddingSon = false;
            ui->addSon->toggle();
        }
        else if (_removeSon) // We remove a son from the container
        {
            _isRemovingSon = true;

            QTreeWidgetItem *toMove = ui->treeWidget->currentItem();

            // Change in data structure
            SInstance *toMoveData = currentRenderPass->getInput(toMove->data(0, Qt::UserRole).toInt());
            SContainerInstance *father = toMoveData->getParent();
            // Remove it from manager and put it one level higher
            if (father->removeSon(toMoveData))
            {
                father->getParent()->addSon(toMoveData);

                // Change it in the view
                toMove = toMove->parent()->takeChild(_currentSelection->indexOfChild(toMove));
                if (_currentSelection->parent())
                {
                    _currentSelection->parent()->addChild(toMove);
                }
                else
                {
                    ui->treeWidget->addTopLevelItem(toMove);
                }
            }
            ui->treeWidget->selectionModel()->clearSelection();
            ui->treeWidget->setCurrentItem(_currentSelection);

            _removeSon = false;
            _isRemovingSon = false;
            ui->removeSon->toggle();
        }
        else
        {
            _currentSelection = ui->treeWidget->currentItem();
            int currentInputId = _currentSelection->data(0, Qt::UserRole).toInt();
            SInstance *currentInstance = currentRenderPass->getInput(currentInputId);
            currentRenderPass->setCurrentInput(currentInstance);

            ui->removeInstance->setEnabled(true);
            if (currentInstance->getType() != CONTAINER_INSTANCE)
            {
                SDataInstance *dataInstance = static_cast<SDataInstance*>(currentInstance);

                ui->addSon->setEnabled(false);
                ui->removeSon->setEnabled(false);
                if (static_cast<SDataInstance*>(currentInstance)->getData()->getType() == AbstractData::DATA_INDEX_BUFFER)
                {
                    ui->inputName->setEnabled(false);
                    ui->inputName->setText("");
                }
                else
                {
                    ui->inputName->setEnabled(true);
                    ui->inputName->setText(dataInstance->getInputName());
                }
            }
            else
            {
                ui->addSon->setEnabled(true);
                ui->removeSon->setEnabled(true);
                ui->inputName->setEnabled(false);
                ui->inputName->setText("");
            }
        }
    }
    else
    {
        _currentSelection = NULL;
        _addSon = false;
        _removeSon = false;
        ui->addSon->setEnabled(false);
        ui->removeSon->setEnabled(false);
        ui->removeInstance->setEnabled(false);
        ui->inputName->setEnabled(false);
        ui->inputName->setText("");
    }
}

void RenderPassUi::createGroup()
{
    SContainerInstance *toAdd = new SContainerInstance;

    ui->treeWidget->addTopLevelItem(toAdd->getTreeItem());
    RenderPassManager::getManager()->getCurrent()->setInput(toAdd);
}

void RenderPassUi::addSon()
{
    _addSon = true;
}

void RenderPassUi::removeSon()
{
    _removeSon = true;
}

void RenderPassUi::inputNameChanged()
{
    SDataInstance *currentInput = static_cast<SDataInstance*>(RenderPassManager::getManager()->getCurrent()->getCurrentInput());
    QString newName = ui->inputName->text();

    newName.replace(" ", "");
    if (newName == "")
    {
        newName = "uniformData";
    }
    currentInput->setInputName(newName);
    ui->treeWidget->currentItem()->setText(1, newName);
}

void RenderPassUi::selectedOutputChanged()
{
    checkEnableOutput();
    if (ui->tableWidget->currentItem() &&
        ui->tableWidget->currentItem()->text() != "")
    {
        ui->unsetOutput->setEnabled(true);
    }
    else
    {
        ui->unsetOutput->setEnabled(false);
    }
    int row = ui->tableWidget->currentRow();
    if (row != -1)
    {
        RenderPassManager::getManager()->setTextureToDisplay((RenderPass::EOutputs)row);
    }
}

void RenderPassUi::setOutput()
{
    RenderPass::EOutputs attachment = static_cast<RenderPass::EOutputs>(ui->tableWidget->currentRow());
    SDataInstance *dataInst = static_cast<SDataInstance*>(DataStructureManager::getManager()->getCurrent());
    RenderTextureData *texture = static_cast<RenderTextureData*>(dataInst->getData());
    QTableWidgetItem *item;

    RenderPassManager::getManager()->getCurrent()->setOutput(attachment, texture);
    item = ui->tableWidget->item(ui->tableWidget->currentRow(), 0);
    if (item == NULL)
    {
        item = new QTableWidgetItem(texture->getName());
        ui->tableWidget->setItem(ui->tableWidget->currentRow(), 0, item);
    }
    item->setText(dataInst->getName());
}

void RenderPassUi::unsetOutput()
{
    RenderPass::EOutputs attachment = static_cast<RenderPass::EOutputs>(ui->tableWidget->currentRow());

    RenderPassManager::getManager()->getCurrent()->unsetOutput(attachment);
    ui->tableWidget->item(ui->tableWidget->currentRow(), 0)->setText("");
}

void RenderPassUi::setCurrentVertexShader()
{
    QString shaderCode = ui->vertexCodeEdit->toPlainText();
    if (RenderPassManager::getManager()->getCurrent() != NULL)
    {
        RenderPassManager::getManager()->getCurrent()->setVertexCode(shaderCode);
    }
}

void RenderPassUi::setCurrentFragmentShader()
{
    QString shaderCode = ui->fragmentCodeEdit->toPlainText();
    if (RenderPassManager::getManager()->getCurrent() != NULL)
    {
        RenderPassManager::getManager()->getCurrent()->setFragmentCode(shaderCode);
    }
}

void RenderPassUi::checkEnableOutput()
{
    SInstance *current = DataStructureManager::getManager()->getCurrent();

    if (current != NULL &&
        ui->tableWidget->currentRow() != -1 &&
        current->getType() == DATA_INSTANCE)
    {
        SDataInstance *dataInst = static_cast<SDataInstance*>(current);

        if (dataInst->getData()->getType() == AbstractData::DATA_RENDER_TEXTURE)
        {
            RenderTextureData *texture = static_cast<RenderTextureData*>(dataInst->getData());

            switch (ui->tableWidget->currentRow())
            {
            case 0:
                if (texture->getInternalFormat() == GL_DEPTH_COMPONENT16 ||
                    texture->getInternalFormat() == GL_DEPTH_COMPONENT24 ||
                    texture->getInternalFormat() == GL_DEPTH_COMPONENT32)
                {
                    ui->setOutput->setEnabled(true);
                }
                else
                {
                    ui->setOutput->setEnabled(false);
                }
                break;
            case 1:
                if (texture->getInternalFormat() == GL_DEPTH24_STENCIL8)
                {
                    ui->setOutput->setEnabled(true);
                }
                else
                {
                    ui->setOutput->setEnabled(false);
                }
                break;
            default:
                if (texture->getInternalFormat() != GL_DEPTH_COMPONENT16 &&
                    texture->getInternalFormat() != GL_DEPTH_COMPONENT24 &&
                    texture->getInternalFormat() != GL_DEPTH_COMPONENT32 &&
                    texture->getInternalFormat() != GL_DEPTH24_STENCIL8)
                {
                    ui->setOutput->setEnabled(true);
                }
                else
                {
                    ui->setOutput->setEnabled(false);
                }
                break;
            }
        }
        else
        {
            ui->setOutput->setEnabled(false);
        }
    }
    else
    {
        ui->setOutput->setEnabled(false);
    }
}

void RenderPassUi::addSnippet()
{
    QString toAdd;

    switch (ui->snippetComboBox->currentIndex())
    {
    case 0:
        toAdd = "\n\
float rand(vec2 co)\n\
{\n\
    return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);\n\
}\n\
";
        break;
    case 1:
        toAdd = "mat3 getNormalMatrix(mat4 transform)\n\
{\n\
    return(mat3(transpose(inverse(transform))));\n\
}\n\
";
        break;
    case 2:
        toAdd = "vec3 getWorldPosition(float depth, vec2 screenUv, mat4 viewProj)\n\
{\n\
    vec4 worldPos = vec4(screenUv * 2.0f - 1.0f, depth * 2.0f - 1.0f, 1.0f);\n\
    worldPos = inverse(viewProj) * worldPos;\n\
    worldPos /= worldPos.w;\n\
    return (vec3(worldPos));\n\
}\n\
";
        break;
    case 3:
        toAdd = "float calcLambert(vec3 lightPos, vec3 pointPos, vec3 pointNormal)\n\
{\n\
    vec3 pointToLight = normalize(lightPos - pointPos);\n\
    return (max(dot(pointToLight, pointNormal), 0));\n\
}\n\
";
        break;
    case 4:
        toAdd = "vec2 calcPhong(vec3 lightPos, vec3 pointPos, vec3 pointNormal, vec3 eyePos, float specularRatio)\n\
{\n\
    vec3 pointToLight = normalize(lightPos - pointPos);\n\
    float lambert = max(dot(pointToLight, pointNormal), 0);\n\
    vec3 reflected = normalize(reflect(pointPos - eyePos, pointNormal));\n\
    float specular = max(dot(pointToLight, reflected), 0);\n\
    specular = pow(specular, specularRatio);\n\
    return (vec2(lambert, specular));\n\
}\n\
";
        break;
    case 5:
        toAdd = "vec3 eyePositionFromView(mat4 view)\n\
{\n\
    mat4 invView = inverse(view);\n\
    return (invView[3].xyz / invView[3].w);\n\
}\n\
";
        break;
    case 6:
        toAdd = "vec4 getBlurredColor(uvec2 sourceSize, vec2 texCoord,\n\
        int blurSize, bool horizontalPass,\n\
        float sigma, sampler2D sourceTexture)\n\
{\n\
    vec2 texOffset = vec2(1.0) / vec2(sourceSize);\n\
    const float pi = 3.14159265;\n\
    float numBlurPixelsPerSide = float(blurSize / 2);\n\
    vec2 blurMultiplyVec = horizontalPass ? vec2(1.0, 0.0) : vec2(0.0, 1.0);\n\
    vec3 incrementalGaussian;\n\
    incrementalGaussian.x = 1.0 / (sqrt(2.0 * pi) * sigma);\n\
    incrementalGaussian.y = exp(-0.5 / (sigma * sigma));\n\
    incrementalGaussian.z = incrementalGaussian.y * incrementalGaussian.y;\n\
    vec4 avgValue = vec4(0.0, 0.0, 0.0, 0.0);\n\
    float coefficientSum = 0.0;\n\
\n\
    avgValue += texture2D(sourceTexture, texCoord) * incrementalGaussian.x;\n\
    coefficientSum += incrementalGaussian.x;\n\
    incrementalGaussian.xy *= incrementalGaussian.yz;\n\
    for (float i = 1.0; i <= numBlurPixelsPerSide; i++)\n\
    {\n\
        avgValue += texture2D(sourceTexture, texCoord - i * texOffset * blurMultiplyVec) * incrementalGaussian.x;\n\
        avgValue += texture2D(sourceTexture, texCoord + i * texOffset * blurMultiplyVec) * incrementalGaussian.x;\n\
        coefficientSum += 2.0 * incrementalGaussian.x;\n\
        incrementalGaussian.xy *= incrementalGaussian.yz;\n\
    }\n\
    return (avgValue / coefficientSum);\n\
}\n\
";
        break;
    case 7:
        toAdd = "float linearizeDepth(float depth, float near, float far)\n\
{\n\
    float clipDepth = depth * 2.0 - 1.0;\n\
    return (2.0 * near * far / (far + near - clipDepth * (far - near)));\n\
}\n\
";
        break;
    default:
        break;
    }
    if (ui->ShaderTextTabs->currentIndex() == 0)
    {
        ui->vertexCodeEdit->setPlainText(toAdd + ui->vertexCodeEdit->toPlainText());
    }
    else if (ui->ShaderTextTabs->currentIndex() == 1)
    {
        ui->fragmentCodeEdit->setPlainText(toAdd + ui->fragmentCodeEdit->toPlainText());
    }
}
