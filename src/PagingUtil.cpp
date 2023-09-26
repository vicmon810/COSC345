#include "PagingUtil.h"

PagingUtil::PagingUtil(QObject *parent)
    : QObject(parent), totalSize(10), sizeofPerPage(2), curSelectNumber(1)
{
}

PagingUtil::~PagingUtil()
{
}

PagingUtil &PagingUtil::operator=(const PagingUtil &other)
{
    this->totalSize = other.totalSize;
    this->sizeofPerPage = other.sizeofPerPage;
    this->curSelectNumber = other.curSelectNumber;
    return *this;
}

int PagingUtil::getTotalSize() const
{
    return totalSize;
}

void PagingUtil::setTotalSize(int size)
{
    totalSize = size;
    pre2ReCacheNumbers();
}

int PagingUtil::getSizeofPerPage() const
{
    return sizeofPerPage;
}

void PagingUtil::setSizeofPerPage(int size)
{
    Q_ASSERT(size > 0);
    sizeofPerPage = size;
    pre2ReCacheNumbers();
}

void PagingUtil::numberSelected(int number)
{
    if (number < 1)
    {
        return;
    }
    if (number > getPageSize())
    {
        return;
    }

    curSelectNumber = number;
    pre2ReCacheNumbers();
    emit numberSelectChanged();
}

bool PagingUtil::isSelectedNumber(int number) const
{
    return curSelectNumber == number;
}

int PagingUtil::getPageSize() const
{
    int pageSize = 1;
    if (totalSize != 0)
    {
        pageSize = (totalSize - 1) / sizeofPerPage + 1;
    }
    return pageSize;
}

void PagingUtil::pre2ReCacheNumbers()
{
    int oldNumberSize = curCacheNumbers.size();

    reCacheNumbers();

    if (curCacheNumbers.size() != oldNumberSize)
    {
        emit numberArraySizeChanged();
    }

    emit numbersChanged();

    // check select number when total size changed
    auto pageSize = getPageSize();
    if (curSelectNumber > pageSize)
    {
        curSelectNumber = pageSize;
        emit numberSelectChanged();
    }
}