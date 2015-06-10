#include "Vec3BufferDataView.hh"
#include "ui_Vec3BufferDataView.h"
#include "GlmVecTableModel.hh"

Vec3BufferDataView::Vec3BufferDataView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Vec3BufferDataView)
{
    ui->setupUi(this);
    ui->tableView->setModel(new GlmVecTableModel<glm::vec3>);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);
    ui->tableView->verticalHeader()->setStretchLastSection(false);
    ui->tableView->setEditTriggers(QAbstractItemView::SelectedClicked);
    QObject::connect(ui->addButton, SIGNAL(released()),
                     this, SLOT(addRow()));
    QObject::connect(ui->deleteButton, SIGNAL(released()),
                     this, SLOT(deleteRow()));
    QObject::connect(ui->tableView->selectionModel(), SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
                     this, SLOT(selectionChanged()));
}

Vec3BufferDataView::~Vec3BufferDataView()
{
    delete ui;
}

void Vec3BufferDataView::selectionChanged()
{
    if (ui->tableView->currentIndex().isValid())
    {
        ui->deleteButton->setEnabled(true);
    }
    else
    {
        ui->deleteButton->setEnabled(false);
    }
}

void Vec3BufferDataView::addRow()
{
    int rowNbr = ui->tableView->model()->rowCount();
    ui->tableView->model()->insertRows(rowNbr, 1);
}

void Vec3BufferDataView::deleteRow()
{
    int curRow = ui->tableView->selectionModel()->currentIndex().row();
    ui->tableView->model()->removeRows(curRow, 1);
}

void Vec3BufferDataView::loadPreset()
{

}

void Vec3BufferDataView::valueChanged()
{
}
