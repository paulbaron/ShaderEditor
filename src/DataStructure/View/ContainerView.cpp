#include "ContainerView.hh"
#include "ui_ContainerView.h"

#include "DataStructureEditor.hh"

ContainerView::ContainerView(DataStructureEditor *editor, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ContainerView)
{
    ui->setupUi(this);

    QObject::connect(ui->addSon, SIGNAL(released()),
                     editor, SLOT(setAddSon()));
    QObject::connect(editor, SIGNAL(sonAdded(bool)),
                     ui->addSon, SLOT(setChecked(bool)));
    QObject::connect(ui->removeSon, SIGNAL(released()),
                     editor, SLOT(setRemoveSon()));
    QObject::connect(editor, SIGNAL(sonRemoved(bool)),
                     ui->removeSon, SLOT(setChecked(bool)));
}

ContainerView::~ContainerView()
{
    delete ui;
}
