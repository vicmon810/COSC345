

#include "PagingUtil.h"

class PagingStyle1 : public PagingUtil
{
public:
    using PagingUtil::PagingUtil;

    void reCacheNumbers() override;

    virtual int minDisplaySize() const;
};