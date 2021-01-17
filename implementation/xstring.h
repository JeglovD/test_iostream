#pragma once

#include "iosfwd.h"
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

   Allocator mAllocator;
};

// class basic_string
template< typename Elem, typename Traits, typename AllocatorIn >
class BasicString: public StringVal< Elem, AllocatorIn >
{
public:
   typedef typename StringVal< Elem, AllocatorIn >::Allocator::SizeType SizeType;

   // length of internal buffer, [1, 16]
   // enum { _BUF_SIZE
   static const int BUFFER_SIZE{ ( 16 / sizeof ( Elem ) ) < 1 ? 1 : ( 16 / sizeof( Elem ) ) };

private:
   // Текущая длина строки
   SizeType mSize;
   // Текущее хранилище, зарезервированное для строки
   SizeType mReserve;

   // Хранилище для маленького буфера или указателя на основной
   union SmallBufferOrPointer
   {
      Elem buffer[ BUFFER_SIZE ];
      Elem* p_buffer;
   } mSmallBufferOrPointer;

   // initialize buffer, deallocating any storage
   // void __CLR_OR_THIS_CALL _Tidy(bool _Built = false,	size_type _Newsize = 0)
   void Tidy( bool build = false, SizeType new_size = 0 )
   {
      if( build )
         if( BUFFER_SIZE <= mReserve )
         {	// копируем все остатки в маленький буфер и освобождаем основной
            Elem* p_buffer = mSmallBufferOrPointer.p_buffer;
            if( new_size > 0 )
               traits_helper::CopyS< Traits >( mSmallBufferOrPointer.buffer, BUFFER_SIZE, p_buffer, new_size );
            StringVal< Elem, AllocatorIn >::mAllocator.Deallocate( p_buffer, mReserve + 1 );
         }
      mReserve = BUFFER_SIZE - 1;
      Eos( new_size );
   }

protected:
   // Определить текущий указатель в буфере для изменяемой строки
   // _Elem *__CLR_OR_THIS_CALL _Myptr()
   Elem* Pointer()
   {
      return BUFFER_SIZE <= mReserve ? mSmallBufferOrPointer.p_buffer: mSmallBufferOrPointer.buffer;
   }

   // Установка новой длинны и null терминатора
   // void __CLR_OR_THIS_CALL _Eos(size_type _Newsize)
   void Eos( SizeType new_size )
   {
      Traits::Assign( Pointer()[ mSize = new_size ], Elem{} );
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

   // return current length of allocated storage
   // size_type __CLR_OR_THIS_CALL capacity() const
   SizeType Capacity() const
   {
      return mReserve;
   }
};
} // namespace DJ
