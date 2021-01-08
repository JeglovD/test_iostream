#pragma once

#define EOF -1

namespace DJ
{
template< typename Elem >
struct CharTraits
{
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
