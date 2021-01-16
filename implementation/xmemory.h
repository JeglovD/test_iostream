#pragma once

namespace DJ
{
// struct _Allocator_base
template< typename T >
struct AllocatorBase
{
   // value_type нужен std::basic_string< Elem, Traits, Alloc > BasicStringBuf::str()
   typedef T value_type;
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
};
} // namespace DJ
