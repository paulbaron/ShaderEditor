#include "EditorMainWindow.hpp"
#include "ui_EditorMainWindow.h"

#include "DataStructure/DataStructureManager.hh"
#include "RenderPassManager.hh"
#include "RenderPassUi.h"
#include "DataStructureEditor.hh"
#include "RenderPassListUi.hh"

#include <QFileDialog>
#include <QMessageBox>
#include <fstream>

#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>

EditorMainWindow::EditorMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::EditorMainWindow)
{
    ui->setupUi(this);

    _renderPassUi = new RenderPassUi();
    _renderPassListUi = new RenderPassListUi(_renderPassUi);
    _dataStructureEditor = new DataStructureEditor(_renderPassUi);

    ui->horizontalLayout->addWidget(_renderPassListUi);
    ui->horizontalLayout->addWidget(_renderPassUi);
    ui->horizontalLayout->addWidget(_dataStructureEditor);

    _renderPassUi->setEnabled(false);

    QObject::connect(ui->actionSave, SIGNAL(triggered(bool)),
                     this, SLOT(saveProject()));
    QObject::connect(ui->actionLoad, SIGNAL(triggered(bool)),
                     this, SLOT(loadProject()));
    QObject::connect(ui->actionSave_As, SIGNAL(triggered(bool)),
                     this, SLOT(saveProjectAs()));
    QObject::connect(ui->actionNew_Project, SIGNAL(triggered(bool)),
                     this, SLOT(newProject()));
}

EditorMainWindow::~EditorMainWindow()
{
    delete ui;
}

void EditorMainWindow::saveProject()
{
    if (_savePath.isEmpty())
    {
        _savePath = QFileDialog::getSaveFileName(this, "Save project", "", "Shader Editor Project (*.sep)");
    }
    std::ofstream file(_savePath.toStdString().c_str());

    if (file.is_open())
    {
        QFileInfo directory(_savePath);
        QString newCurrentPath = directory.path();
        QString oldCurrentPath = QDir::currentPath();
        QDir::setCurrent(newCurrentPath);

        boost::archive::xml_oarchive oa(file);

        oa << boost::serialization::make_nvp("DataStructureManager", *DataStructureManager::getManager())
            << boost::serialization::make_nvp("RenderPassManager", *RenderPassManager::getManager());

        QDir::setCurrent(oldCurrentPath);
    }
}

void EditorMainWindow::saveProjectAs()
{
    _savePath = QFileDialog::getSaveFileName(this, "Save project", "", "Shader Editor Project (*.sep)");
    saveProject();
}

void EditorMainWindow::loadProject()
{
    QString loadPath = QFileDialog::getOpenFileName(this, "Load project", "", "Shader Editor Project (*.sep)");
    std::ifstream file(loadPath.toStdString().c_str());

    if (file.is_open())
    {
        _savePath = loadPath;
        QFileInfo directory(loadPath);
        QString newCurrentPath = directory.path();
        QString oldCurrentPath = QDir::currentPath();
        QDir::setCurrent(newCurrentPath);

        boost::archive::xml_iarchive ia(file);

        try
        {
            ia >> boost::serialization::make_nvp("DataStructureManager", *DataStructureManager::getManager())
                >> boost::serialization::make_nvp("RenderPassManager", *RenderPassManager::getManager());
        }
        catch (boost::archive::archive_exception &e)
        {
            QMessageBox msgBox;

            msgBox.setWindowTitle("Loading Error");
            msgBox.setText("Could not load file '" + loadPath + "'");
            msgBox.setDetailedText(e.what());
            msgBox.setIcon(QMessageBox::Warning);
            msgBox.setStandardButtons(QMessageBox::Ok);
            msgBox.setDefaultButton(QMessageBox::Ok);

            QSpacerItem* horizontalSpacer = new QSpacerItem(500, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
            QGridLayout* layout = (QGridLayout*)msgBox.layout();
            layout->addItem(horizontalSpacer, layout->rowCount(), 0, 1, layout->columnCount());

            msgBox.exec();
        }

        QDir::setCurrent(oldCurrentPath);
        _renderPassUi->setEnabled(false);
        _renderPassListUi->reloadUi();
        _dataStructureEditor->reloadUi();
    }
}


void EditorMainWindow::newProject()
{
    DataStructureManager::getManager()->clearAll();
    RenderPassManager::getManager()->clearAll();
    _renderPassUi->setEnabled(false);
    _renderPassListUi->reloadUi();
    _dataStructureEditor->reloadUi();
}
