#ifndef BUFFERDATAVIEW_HH
#define BUFFERDATAVIEW_HH

#include <QWidget>

#include "../AbstractData.hh"
#include "ui_BufferDataView.h"
#include "GlmVecTableModel.hh"

class AbstractBufferDataView : public QWidget
{
    Q_OBJECT

public:
    explicit AbstractBufferDataView(AbstractData *data, QWidget *parent = 0) :
           QWidget(parent),
           ui(new Ui::BufferDataView)
    {
        ui->setupUi(this);
    }

    ~AbstractBufferDataView()
    {
        delete ui;
    }

public slots:
    void selectionChanged()
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

    void addRow()
    {
        int rowNbr = ui->tableView->model()->rowCount();
        ui->tableView->model()->insertRows(rowNbr, 1);
    }

    void deleteRow()
    {
        int curRow = ui->tableView->selectionModel()->currentIndex().row();
        ui->tableView->model()->removeRows(curRow, 1);
    }

    void loadPreset()
    {
        _loadPreset();
    }

protected:
    virtual void _loadPreset() = 0;

    Ui::BufferDataView *ui;
};

template<class GlmVec, class EditCellDelegate>
class BufferDataView : public AbstractBufferDataView
{
public:
    BufferDataView(AbstractData *data, QWidget *parent = 0) :
        AbstractBufferDataView(data, parent)
    {
        ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
        ui->tableView->horizontalHeader()->setStretchLastSection(true);
        ui->tableView->verticalHeader()->setStretchLastSection(false);

        ui->tableView->setEditTriggers(QAbstractItemView::DoubleClicked);
        ui->tableView->setModel(new GlmVecTableModel<GlmVec>(this));
        ui->tableView->setItemDelegate(new EditCellDelegate(this));

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

    GlmVec *getData() const
    {
        GlmVecTableModel<GlmVec> *model = static_cast<GlmVecTableModel<GlmVec>*>(ui->tableView->model());

        return (model->getData());
    }

    int getDataCount() const
    {
        return (ui->tableView->model()->rowCount());
    }

    void addPreset(QString name, QVector<GlmVec> const &preset)
    {
        _presets[name] = preset;
        ui->presetComboBox->addItem(name);
    }

    void appendRow(GlmVec const &value)
    {
        GlmVecTableModel<GlmVec> *model = static_cast<GlmVecTableModel<GlmVec>*>(ui->tableView->model());

        model->appendRow(value);
    }

protected:
    virtual void _loadPreset()
    {
        GlmVecTableModel<GlmVec> *model = static_cast<GlmVecTableModel<GlmVec>*>(ui->tableView->model());

        model->removeRows(0, model->rowCount());
        QVector<GlmVec> const &selectedPreset = _presets[ui->presetComboBox->currentText()];
        for (typename QVector<GlmVec>::const_iterator it = selectedPreset.begin(); it != selectedPreset.end(); ++it)
        {
            model->appendRow(*it);
        }
    }

private:
    QMap<QString, QVector<GlmVec> > _presets;
};

#endif // BUFFERDATAVIEW_HH
