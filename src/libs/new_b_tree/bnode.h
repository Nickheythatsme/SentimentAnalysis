#include "holder.h"

#ifndef SENTIMENTANALYSIS_BNODE_
#define SENTIMENTANALYSIS_BNODE_

template<T>
class bnode : public holder<T>
{
    public:
        bnode();
        bnode(const bnode &rhs);
        bnode(bnode &&rhs);
        ~bnode();
    protected:
    private:
};

#endif // SENTIMENTANALYSIS_BNODE_
