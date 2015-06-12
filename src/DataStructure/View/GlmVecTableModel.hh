#ifndef VEC3TABLEMODEL_H
#define VEC3TABLEMODEL_H

#include <QAbstractTableModel>
#include <QVector>
#include "../vendors/glm/glm.hpp"

template<class GlmVec>
class GlmVecTableModel : public QAbstractTableModel
{
public:
    GlmVecTableModel(QObject *parent = 0) :
        QAbstractTableModel(parent)
    {
    }

    int rowCount(const QModelIndex &parent = QModelIndex()) const
    {
        return (_buffer.size());
    }

    int columnCount(const QModelIndex &parent = QModelIndex()) const
    {
        return (GlmVec().length());
    }

    QVariant headerData(int section, Qt::Orientation orientation, int role) const
    {
        if (role != Qt::DisplayRole)
            return QVariant::Invalid;
        if (orientation == Qt::Vertical)
        {
            return (QString::number(section));
        }
        else
        {
            if (section == 0)
                return (QString("X"));
            else if (section == 1)
                return (QString("Y"));
            else if (section == 2)
                return (QString("Z"));
            else if (section == 3)
                return (QString("W"));
        }
        return (QVariant::Invalid);
    }

    QVariant data(const QModelIndex &index, int role) const
    {
        if (role == Qt::DisplayRole)
        {
            return (QString::number(_buffer[index.row()][index.column()]));
        }
        else if (role == Qt::EditRole)
        {
            return (_buffer[index.row()][index.column()]);
        }
        return QVariant::Invalid;
    }

    bool setData(const QModelIndex &index, const QVariant &value, int role)
    {
        _buffer[index.row()][index.column()] = value.toFloat();
        return (true);
    }

    void appendRow(GlmVec const &vec)
    {
        beginInsertRows(QModelIndex(), _buffer.size(), _buffer.size());
        _buffer.push_back(vec);
        endInsertRows();
    }

    Qt::ItemFlags flags(const QModelIndex &index) const
    {
        if (!index.isValid())
            return (Qt::ItemIsEnabled);

        return (QAbstractItemModel::flags(index) | Qt::ItemIsEditable);
    }

    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex())
    {
        beginInsertRows(parent, row, row + count - 1);
        for (int i = 0; i < count; ++i)
        {
            _buffer.insert(row, (GlmVec(0)));
        }
        endInsertRows();
        return (true);
    }

    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex())
    {
        if (_buffer.size() == 0)
            return (false);
        beginRemoveRows(parent, row, row + count - 1);
        for (int i = 0; i < count; ++i)
        {
            _buffer.removeAt(row);
        }
        endRemoveRows();
        return (true);
    }

    GlmVec *getData()
    {
        return (_buffer.data());
    }

private:
    QVector<GlmVec> _buffer;
};

#endif // VEC3TABLEMODEL_H
