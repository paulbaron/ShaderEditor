#include "Vec3BufferDataView.hh"
#include "ui_Vec3BufferDataView.h"
#include "GlmVecTableModel.hh"
#include "DoubleSpinBoxDelegate.hh"

Vec3BufferDataView::Vec3BufferDataView(AbstractData *data, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Vec3BufferDataView)
{
    ui->setupUi(this);

    ui->presetComboBox->addItem("Cube vertices");
    ui->presetComboBox->addItem("Plane vertices");

    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);
    ui->tableView->verticalHeader()->setStretchLastSection(false);

    ui->tableView->setEditTriggers(QAbstractItemView::DoubleClicked);
    ui->tableView->setModel(new GlmVecTableModel<glm::vec3>(this));
    ui->tableView->setItemDelegate(new DoubleSpinBoxDelegate(this));

    QObject::connect(ui->addButton, SIGNAL(released()),
                     this, SLOT(addRow()));
    QObject::connect(ui->deleteButton, SIGNAL(released()),
                     this, SLOT(deleteRow()));
    QObject::connect(ui->tableView->selectionModel(), SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
                     this, SLOT(selectionChanged()));
    QObject::connect(ui->loadPresetButton, SIGNAL(released()),
                     this, SLOT(loadPreset()));
    QObject::connect(ui->saveChanges, SIGNAL(released()),
                     data, SLOT(saveChanges()));
}

Vec3BufferDataView::~Vec3BufferDataView()
{
    delete ui;
}

glm::vec3 *Vec3BufferDataView::getData() const
{
    GlmVecTableModel<glm::vec3> *model = static_cast<GlmVecTableModel<glm::vec3>*>(ui->tableView->model());

    return (model->getData());
}

int Vec3BufferDataView::getDataCount() const
{
    return (ui->tableView->model()->rowCount());
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
    GlmVecTableModel<glm::vec3> *model = static_cast<GlmVecTableModel<glm::vec3>*>(ui->tableView->model());
    glm::vec3 cube[8] =
    {
        glm::vec3(-0.5, 0.5, 0.5),
        glm::vec3(-0.5, 0.5, -0.5),
        glm::vec3(0.5, 0.5, -0.5),
        glm::vec3(0.5, 0.5, 0.5),
        glm::vec3(-0.5, -0.5, 0.5),
        glm::vec3(-0.5, -0.5, -0.5),
        glm::vec3(0.5, -0.5, -0.5),
        glm::vec3(0.5, -0.5, 0.5),
    };

    model->removeRows(0, model->rowCount());
    switch (ui->presetComboBox->currentIndex())
    {
    case 0:
        // Face 1
        model->appendRow(cube[0]);
        model->appendRow(cube[1]);
        model->appendRow(cube[2]);

        model->appendRow(cube[2]);
        model->appendRow(cube[3]);
        model->appendRow(cube[0]);

        // Face 2
        model->appendRow(cube[4]);
        model->appendRow(cube[5]);
        model->appendRow(cube[6]);

        model->appendRow(cube[6]);
        model->appendRow(cube[7]);
        model->appendRow(cube[4]);

        // Face 3
        model->appendRow(cube[0]);
        model->appendRow(cube[3]);
        model->appendRow(cube[7]);

        model->appendRow(cube[7]);
        model->appendRow(cube[4]);
        model->appendRow(cube[0]);

        // Face 4
        model->appendRow(cube[1]);
        model->appendRow(cube[2]);
        model->appendRow(cube[6]);

        model->appendRow(cube[6]);
        model->appendRow(cube[5]);
        model->appendRow(cube[1]);

        // Face 5
        model->appendRow(cube[1]);
        model->appendRow(cube[0]);
        model->appendRow(cube[4]);

        model->appendRow(cube[4]);
        model->appendRow(cube[5]);
        model->appendRow(cube[1]);

        // Face 6
        model->appendRow(cube[2]);
        model->appendRow(cube[3]);
        model->appendRow(cube[7]);

        model->appendRow(cube[7]);
        model->appendRow(cube[6]);
        model->appendRow(cube[2]);
        break;
    case 1:
        model->appendRow(glm::vec3(-1, -1, 0));
        model->appendRow(glm::vec3(-1, 1, 0));
        model->appendRow(glm::vec3(1, 1, 0));
        model->appendRow(glm::vec3(1, 1, 0));
        model->appendRow(glm::vec3(1, -1, 0));
        model->appendRow(glm::vec3(-1, -1, 0));
        break;
    default:
        assert(!"Preset not implemented");
        break;
    }
}
