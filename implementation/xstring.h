#pragma once

#include "xutility.h"

namespace DJ
{
// class _CRTIMP2_PURE _String_base
class StringBase: public ContainerBase
{
};

// class _String_val
template< typename T, typename AllocatorIn >
class StringVal: public StringBase
{
protected:
   typedef typename AllocatorIn::template Rebind< T >::Other Allocator;
};

// class basic_string
template< typename Elem, typename Traits, typename AllocatorIn >
class BasicString: public StringVal< Elem, AllocatorIn >
{
public:
   typedef typename StringVal< Elem, AllocatorIn >::Allocator::SizeType SizeType;

   const unsigned int BUF_SIZE{ 16 / sizeof ( Elem ) < 1 ? 1 : 16 / sizeof( Elem ) };

private:
   // Текущая длина строки
   SizeType mSize;
   // Текущее хранилище, зарезервированное для строки
   SizeType mReserve;

   // initialize buffer, deallocating any storage
   // void __CLR_OR_THIS_CALL _Tidy(bool _Built = false,	size_type _Newsize = 0)
   void Tidy( bool build = false, SizeType new_size = 0 )
   {
      if( build )
         if( BUF_SIZE <= mReserve )
         {	// копируем все остатки в маленький буфер и освобождаем основной
            Elem* ptr = _Bx._Ptr;
            if (0 < _Newsize)
               _Traits_helper::copy_s<_Traits>(_Bx._Buf, _BUF_SIZE, _Ptr, _Newsize);
            _Mybase::_Alval.deallocate(_Ptr, _Myres + 1);
         }
      _Myres = _BUF_SIZE - 1;
      _Eos(_Newsize);
   }

public:
   // __CLR_OR_THIS_CALL basic_string()
   BasicString():
      StringVal< Elem, AllocatorIn >()
   {
      Tidy();
   }

   // size_type __CLR_OR_THIS_CALL size() const
   SizeType Size() const
   {
      return mSize;
   }
};
} // namespace DJ
