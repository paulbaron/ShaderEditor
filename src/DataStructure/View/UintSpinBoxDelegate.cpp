#include "UintSpinBoxDelegate.hh"

#include <QDoubleSpinBox>
#include <limits>

UintSpinBoxDelegate::UintSpinBoxDelegate(QObject *parent):
    QItemDelegate(parent)
{

}

QWidget *UintSpinBoxDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                      const QModelIndex &index) const
{
    QSpinBox *editor = new QSpinBox(parent);
    editor->setFrame(false);
    editor->setMinimum(0);
    editor->setMaximum(std::numeric_limits<int>::max());
    editor->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));

    return (editor);
}

void UintSpinBoxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    unsigned int value = index.model()->data(index, Qt::EditRole).toUInt();

    QSpinBox *spinBox = static_cast<QSpinBox*>(editor);
    spinBox->setValue(value);
}

void UintSpinBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                  const QModelIndex &index) const
{
    QSpinBox *spinBox = static_cast<QSpinBox*>(editor);
    spinBox->interpretText();
    unsigned int value = static_cast<unsigned int>(spinBox->value());

    model->setData(index, value, Qt::EditRole);
}

void UintSpinBoxDelegate::updateEditorGeometry(QWidget *editor,
                          const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}
