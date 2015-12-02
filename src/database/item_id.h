#ifndef ITEM_ID_H
#define ITEM_ID_H

#include <QCryptographicHash>
#include <QByteArray>
#include <QtGlobal>

namespace DB
{

class Item_ID
{
public:
    Item_ID();
    Item_ID(Item_ID &other);
    Item_ID(const Item_ID &other);
    Item_ID(QByteArray &binaryInput);

    static Item_ID fromHash(QByteArray array);

    void setID(QByteArray input);
    QByteArray getID() { return this->data; }
    void hash(QByteArray input);
    quint64 to64bitID();

    bool operator==(Item_ID &other) { return this->data == other.data; }
    bool operator!=(Item_ID &other) { return !(*this == other); }
    bool operator==(const Item_ID &other) { return this->data == other.data; }
    bool operator!=(const Item_ID &other) { return !(*this == other); }

private:
    QByteArray data;
};

}

#endif // ITEM_ID_H
