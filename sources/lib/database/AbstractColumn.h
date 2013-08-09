#ifndef ABSTRACT_COLUMN_H_
#define ABSTRACT_COLUMN_H_

#include "win_defines.h"

template <typename _T_VALUE>
class AbstractColumn {
public:
    virtual void push_back(const _T_VALUE&) = 0;
    virtual _T_VALUE& get(const uint) = 0;
    virtual size_t size() = 0;
};

#endif