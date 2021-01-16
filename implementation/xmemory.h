#pragma once

namespace DJ
{
// struct _Allocator_base
template< typename T >
struct AllocatorBase
{
   // value_type нужен std::basic_string< Elem, Traits, Alloc > BasicStringBuf::str()
   typedef T ValueType;
};

// class allocator
template< typename T >
class Allocator: public AllocatorBase< T >
{
public:
   typedef unsigned int SizeType;

   template< typename T >

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
