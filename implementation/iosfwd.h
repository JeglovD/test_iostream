#pragma once

#define EOF -1

namespace DJ
{
// struct _Char_traits_base
struct CharTraitsBase
{
};

// struct char_traits
template< typename Elem >
struct CharTraits: public CharTraitsBase
{
   // char_type нужен basic_string, который используется в BasicStringBuf
   typedef Elem char_type;
   typedef long IntType;

   static IntType ToIntType( const Elem& ch )
   {
      return static_cast< IntType >( ch );
   }

   static IntType Eof()
   {
      return static_cast< IntType >( EOF );
   }
};
} // namespace DJ
