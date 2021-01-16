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
inline typename CharTraitsCategory< Traits >::SecureCharTraits CharTraitsCat()
{
   typename CharTraitsCategory< Traits >::SecureCharTraits Secure;
   return Secure;
}

// namespace _Traits_helper
namespace traits_helper
{
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
   return Traits::copy( p_first_1, p_first_2, count );
}

template< typename Traits >
// typename _Traits::char_type *copy_s(
inline typename Traits::char_type* CopyS(
      typename Traits::char_type* p_first_1,
      size_t size,
      const typename Traits::char_type* p_first_2,
      size_t count )
{
   return CopyS< Traits >( p_first_1, size, p_first_2, count, CharTraitsCategory< Traits >() );
}
} // traits_helper
} // namespace DJ
