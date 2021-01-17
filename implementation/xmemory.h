#pragma once

#include <crtdefs.h>

namespace DJ
{
// specify standard memory model
#ifndef FARQ
#define FARQ
#define PDFT ptrdiff_t
#define SIZT size_t
#endif

// struct _Allocator_base
template< typename T >
struct AllocatorBase
{
   // value_type нужен std::basic_string< Elem, Traits, Alloc > BasicStringBuf::str()
   typedef T ValueType;
};

template< typename T >
// class allocator
class Allocator: public AllocatorBase< T >
{
public:
   typedef unsigned int SizeType;
   typedef PDFT DifferenceType;
   typedef const ValueType* ConstPointer;
   typedef const ValueType& ConstReference;

   template< typename T >
   // struct rebind
   struct Rebind
   {
      typedef Allocator< T > Other;
   };

   typedef typename AllocatorBase< T >::ValueType ValueType;
   // typedef value_type _FARQ *pointer;
   typedef ValueType* PValueType;

   // Освобождение пространства объекта, игнорируя размер
   // void deallocate(pointer _Ptr, size_type)
   void Deallocate( PValueType p, SizeType )
   {
      ::operator delete( p );
   }
};
} // namespace DJ
