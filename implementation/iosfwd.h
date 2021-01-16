#pragma once

#include <stdio.h>

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
   typedef Elem CharType;
   typedef long IntType;

   // Назначить элемент
   // static void __CLRCALL_OR_CDECL assign(_Elem& _Left, const _Elem& _Right)
   static void Assign( Elem& left, const Elem& right)
   {
      left = right;
   }

   static IntType ToIntType( const Elem& ch )
   {
      return static_cast< IntType >( ch );
   }

   static IntType Eof()
   {
      return static_cast< IntType >( EOF );
   }

   // Копирует [_First1, _First1 + _Count) to [_First2, ...)
   // предположим, что в принимающем буфере достаточно места
   // static _Elem *__CLRCALL_OR_CDECL copy(_Elem *_First1,	const _Elem *_First2, size_t _Count)
   static Elem* Copy( Elem* p_first_1,	const Elem* p_first_2, size_t count )
   {
      return CopyS( p_first_1, count, p_first_2, count );
   }

   // Копирует [_First1, _First1 + _Count) to [_First2, ...)
   // static _Elem *__CLRCALL_OR_CDECL _Copy_s(_Elem *_First1, size_t _Dest_size, const _Elem *_First2, size_t _Count)
   static Elem* CopyS( Elem* p_first_1, size_t dest_size, const Elem* p_first_2, size_t count )
   {
      // Jeglov
//      _SCL_SECURE_CRT_VALIDATE(_Dest_size >= _Count, NULL);
      Elem* p_next = p_first_1;
      for(; count > 0; --count, ++p_next, ++p_first_2 )
         Assign( *p_next, *p_first_2 );
      return p_first_1;
   }
};

template< typename Traits >
// class _Inherits_from_char_traits_base
class InheritsFromCharTraitsBase
{
   typedef char True;
   class False { char dummy[ 2 ]; };
   static True Inherits( CharTraitsBase );
   static False Inherits( ... );
   static Traits MakeTraits();

public:
   enum
   {
      EXISTS = sizeof( Inherits( MakeTraits() ) ) == sizeof( True )
   };
};

// struct _Unsecure_char_traits_tag
struct UnsecureCharTraitsTag
{
};

// struct _Secure_char_traits_tag
struct SecureCharTraitsTag
{
};

template< typename Traits, bool inherits_from_char_traits_base >
// class _Char_traits_category_helper
class CharTraitsCategoryHelper
{
public:
   typedef UnsecureCharTraitsTag SecureCharTraits;
};

template< typename Traits >
// class _Char_traits_category
class CharTraitsCategory
{
public:
   typedef typename CharTraitsCategoryHelper< Traits, InheritsFromCharTraitsBase< Traits >::EXISTS >::SecureCharTraits SecureCharTraits;
};

// Retrieve the _Secure_char_traits tag from a user defined char_traits
// methods.
template< typename Traits >
// typename _Char_traits_category<_Traits>::_Secure_char_traits _Char_traits_cat()
inline typename CharTraitsCategory< Traits >::SecureCharTraits GetCharTraitsCategory()
{
   typename CharTraitsCategory< Traits >::SecureCharTraits Secure;
   return Secure;
}

// namespace _Traits_helper
namespace traits_helper
{
template< typename Traits >
// typename _Traits::char_type *copy_s(typename _Traits::char_type *_First1, size_t _Size, const typename _Traits::char_type *_First2, size_t _Count, _Secure_char_traits_tag)
inline typename Traits::CharType* CopyS(
      typename Traits::CharType* p_first_1,
      size_t size,
      const typename Traits::CharType* p_first_2,
      size_t count,
      SecureCharTraitsTag )
{
   return Traits::CopyS( p_first_1, size, p_first_2, count );
}

// If _SECURE_SCL is turned on, the user will get a deprecation warning when calling an unsecure _Traits::copy
template< typename Traits >
//typename _Traits::char_type *copy_s(typename _Traits::char_type *_First1, size_t _Size, const typename _Traits::char_type *_First2, size_t _Count, _Unsecure_char_traits_tag)
inline typename Traits::CharType* CopyS(
      typename Traits::CharType* p_first_1,
      size_t size,
      const typename Traits::CharType* p_first_2,
      size_t count,
      UnsecureCharTraitsTag )
{
   return Traits::Copy( p_first_1, p_first_2, count );
}

template< typename Traits >
// typename _Traits::char_type *copy_s(
inline typename Traits::CharType* CopyS(
      typename Traits::CharType* p_first_1,
      size_t size,
      const typename Traits::CharType* p_first_2,
      size_t count )
{
   return CopyS< Traits >( p_first_1, size, p_first_2, count, GetCharTraitsCategory< Traits >() );
}
} // traits_helper
} // namespace DJ
