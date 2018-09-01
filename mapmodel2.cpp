#include "mapmodel2.h"


MapModel2::MapModel2(QObject *parent) :
    QAbstractTableModel(parent)
{
    _map = NULL;
}

int MapModel2::rowCount(const QModelIndex& parent) const
{
    if (_map)
        return _map->count();
    return 0;
}

int MapModel2::columnCount(const QModelIndex & parent) const
{
    return 2;
}

QVariant MapModel2::data(const QModelIndex& index, int role) const
{
    if (!_map)
        return QVariant();
    if (index.row() < 0 ||
        index.row() >= _map->count() ||
        role != Qt::DisplayRole) {
        return QVariant();
    }
    if (index.column() == 0)
        return (_map->values().at(index.row())._name);
    if (index.column() == 1)
        return (_map->values().at(index.row())._quantity);
    return QVariant();
}

QVariant MapModel2::headerData(int section, Qt::Orientation orientation,
                                int role = Qt::DisplayRole) const
{
    if(role != Qt::DisplayRole)
        return QVariant();
    if(orientation == Qt::Horizontal){
        switch(section){
        case 0:
            return QObject::tr("Наименование");
        case 1:
            return QObject::tr("Количество");
        default:
            return QVariant();
        }
    }
    return QVariant();
}
