#include "item_id.h"

using namespace DB;

Item_ID::Item_ID()
{

}

Item_ID::Item_ID(Item_ID &other)
    :data{other.data}
{

}

Item_ID::Item_ID(const Item_ID &other)
    :data{other.data}
{

}

Item_ID::Item_ID(QByteArray &binaryInput)
    :data{binaryInput}
{

}

void Item_ID::setID(QByteArray input)
{
    this->data = input;
}

void Item_ID::hash(QByteArray input)
{
    QCryptographicHash h(QCryptographicHash::Algorithm::Md5);
    h.addData(input);
    data = h.result();
}

quint64 Item_ID::to64bitID()
{
    QByteArray result(8, '0');
    int j = 15;
    for(int i = 0; i < 8; i++)
    {
        result[i] = data[i]^data[j];
        j--;
    }
    return result.toHex().toULongLong(0, 16);
}

Item_ID Item_ID::fromHash(QByteArray array)
{
    Item_ID ret;
    ret.hash(array);
    return ret;
}
