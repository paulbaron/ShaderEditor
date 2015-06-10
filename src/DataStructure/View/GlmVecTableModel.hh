#ifndef VEC3TABLEMODEL_H
#define VEC3TABLEMODEL_H

#include <QAbstractTableModel>
#include <QVector>
#include "../vendors/glm/glm.hpp"

template<class GlmVec>
class GlmVecTableModel : public QAbstractTableModel
{
public:
    GlmVecTableModel()
    {
        _buffer.push_back(GlmVec(0));
        _buffer.push_back(GlmVec(1));
        _buffer.push_back(GlmVec(2));
        _buffer.push_back(GlmVec(3));
    }

    int rowCount(const QModelIndex &parent) const
    {
        return (_buffer.size());
    }

    int columnCount(const QModelIndex &parent) const
    {
        return (GlmVec().length());
    }

    QVariant headerData(int section, Qt::Orientation orientation, int role) const
    {
        if (role != Qt::DisplayRole)
            return QVariant();
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
        return (QVariant());
    }

    QVariant data(const QModelIndex &index, int role) const
    {
        if (role == Qt::DisplayRole)
        {
            return (QString::number(_buffer[index.row()][index.column()]));
        }
        return QVariant::Invalid;
    }

    GlmVec *getData()
    {
        return (_buffer.data());
    }

    bool insertRows(int row, int count, const QModelIndex &parent)
    {
        beginInsertRows(parent, row, row + count - 1);
        for (int i = 0; i < count; ++i)
        {
            _buffer.insert(row, (GlmVec(0)));
        }
        endInsertRows();
    }

    bool removeRows(int row, int count, const QModelIndex &parent)
    {
        beginRemoveRows(parent, row, row + count - 1);
        for (int i = 0; i < count; ++i)
        {
            _buffer.removeAt(row);
        }
        endRemoveRows();
        emit layoutChanged();
    }

private:
    QVector<GlmVec> _buffer;
};

#endif // VEC3TABLEMODEL_H
