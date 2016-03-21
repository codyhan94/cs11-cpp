#ifndef _PRINT_VECTOR_H_
#define _PRINT_VECTOR_H_
#include <iostream>

/* Operator overload for printing a vector. */
template<class T>
inline std::ostream &operator << (std::ostream &os, const std::vector<T> &v)
{
    os << "[ ";
    for (typename std::vector<T>::const_iterator ii = v.begin(); ii != v.end(); ++ii)
    {
        os << *ii << " ";
    }
    os << "]";
    return os;
}

#endif /* End of include guard for print_vector.h */
