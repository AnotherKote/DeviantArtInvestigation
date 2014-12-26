#ifndef CMYCOOLITERATOR_HPP
#define CMYCOOLITERATOR_HPP

#include <stddef.h>
class CMyCoolIterator
{
   int number;
public:
   enum {MAX = 3};

   CMyCoolIterator():
      number(0){}
   int get();
   int& operator++();
   int operator++(int);
   operator int();
   int operator+(int num);
};
inline int CMyCoolIterator::get()
{
   return number;
}

inline int &CMyCoolIterator::operator++()
{
   number++;
   if(number == MAX)
   {
      number = 0;
   }
   return number;
}

inline int CMyCoolIterator::operator++(int)
{
   int copy = number;
   ++(*this);
   return copy;
}

inline int CMyCoolIterator::operator+(int num)
{
   if((number + (num % MAX)) == MAX)
   {
      return 0;
   }
   return (number + (num % MAX));
}

inline CMyCoolIterator::operator int()
{
   return number;
}

#endif // CMYCOOLITERATOR_HPP



