#pragma once

#include "iosfwd.h"
#include "xutility.h"

namespace DJ
{
// iterator for nonmutable string
template< typename Elem, typename Traits, typename Allocator >
// class _String_const_iterator
class StringConstIterator: public RanitBase<
      Elem,
      typename Allocator::DifferenceType,
      typename Allocator::ConstPointer,
      typename Allocator::ConstReference,
      IteratorBaseSecure >
{
public:
   // construct with null pointer
   // __CLR_OR_THIS_CALL _String_const_iterator()
   StringConstIterator()
   {
      _Myptr = 0;
   }

#define STRING_CONST_ITERATOR( ptr )	ConstIterator( ptr )

   // construct with pointer _Ptr
   // __CLR_OR_THIS_CALL _String_const_iterator(pointer _Ptr)
   StringConstIterator( Pointer ptr )
   {
      mPtr = ptr;
      this->mCont = IGNORE_MYCONT;
   }

   // offset of element in string
   Pointer mPtr;
};

// iterator for mutable string
template< typename Elem, typename Traits, typename Allocator >
// class _String_iterator
class StringIterator: public StringConstIterator< Elem, Traits, Allocator >
{
public:
   typedef StringIterator< Elem, Traits, Allocator > Myt;
   typedef StringConstIterator< Elem, Traits, Allocator > Mybase;
   typedef typename Allocator::DifferenceType DifferenceType;

#define STRING_ITERATOR( ptr ) Iterator( ptr )

   // construct with null string pointer
   // __CLR_OR_THIS_CALL _String_iterator()
   StringIterator()
   {}

   // construct with pointer _Ptr
   // __CLR_OR_THIS_CALL _String_iterator(pointer _Ptr)
   StringIterator( Pointer ptr ): StringConstIterator< Elem, Traits, Allocator >( ptr )
   {}

   // increment by integer
   // _Myt& __CLR_OR_THIS_CALL operator+=(difference_type _Off)
   Myt& operator+=( DifferenceType off )
   {
      (*(Mybase*)this) += off;
      return (*this);
   }

   // return this + integer
   // _Myt __CLR_OR_THIS_CALL operator+(difference_type _Off) const
   Myt operator+( DifferenceType off ) const
   {
      Myt tmp = *this;
      return tmp += off;
   }
};

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
   typedef BasicString< Elem,  Traits, AllocatorIn > Myt;
   typedef typename StringVal< Elem, AllocatorIn >::Allocator::SizeType SizeType;

   // length of internal buffer, [1, 16]
   // enum { _BUF_SIZE
   static const int BUFFER_SIZE{ ( ( 16 / sizeof ( Elem ) ) < 1 ? 1 : ( 16 / sizeof( Elem ) ) ) };

   typedef StringIterator< Elem, Traits, AllocatorIn > Iterator;
   typedef StringConstIterator< Elem, Traits, AllocatorIn > ConstIterator;

#define STR_ITER_BASE( it ) ( it ).mPtr

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
   Elem* Myptr()
   {
      return BUFFER_SIZE <= mReserve ? mSmallBufferOrPointer.p_buffer: mSmallBufferOrPointer.buffer;
   }

   // Установка новой длинны и null терминатора
   // void __CLR_OR_THIS_CALL _Eos(size_type _Newsize)
   void Eos( SizeType new_size )
   {
      Traits::Assign( Myptr()[ mSize = new_size ], Elem{} );
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

   // compute safe iterator difference
   // static size_type __CLRCALL_OR_CDECL _Pdif(const_iterator _P2, const_iterator _P1)
   static SizeType Pdif( ConstIterator p_2, ConstIterator p_1 )
   {
      return STR_ITER_BASE( p_2 ) == 0 ? 0 : p_2 - p_1;
   }

   // return iterator for beginning of mutable sequence
   // iterator __CLR_OR_THIS_CALL begin()
   Iterator Begin()
   {
      return STRING_ITERATOR( Myptr() );
   }

   // insert _Count * _Elem at _Where
   // void __CLR_OR_THIS_CALL insert(iterator _Where, size_type _Count, _Elem _Ch)
   void Insert( Iterator where, SizeType count, Elem ch )
   {
      size_type _Off = _Pdif(_Where, begin());
      insert(_Off, _Count, _Ch);
   }

   // insert _Count * _Ch at _Off
   // _Myt& __CLR_OR_THIS_CALL insert(size_type _Off,	size_type _Count, _Elem _Ch)
   Myt& Insert( SizeType off,	SizeType count, Elem ch )
   {
      if( mSize < off )
         _String_base::_Xran();	// _Off off end
      if (npos - _Mysize <= _Count)
         _String_base::_Xlen();	// result too long
      size_type _Num;
      if (0 < _Count && _Grow(_Num = _Mysize + _Count))
      {	// make room and insert new stuff
         _Traits_helper::move_s<_Traits>(_Myptr() + _Off + _Count, _Myres - _Off - _Count,
                                         _Myptr() + _Off, _Mysize - _Off);	// empty out hole
         _Chassign(_Off, _Count, _Ch);	// fill hole
         _Eos(_Num);
      }
      return (*this);
   }

   // insert _Ch at _Where
   // iterator __CLR_OR_THIS_CALL insert(iterator _Where, _Elem _Ch)
   Iterator Insert( Iterator where, Elem ch )
   {
      SizeType off = Pdif( where, Begin() );
      Insert( off, 1, ch );
      return Begin() + off;
   }

   // return iterator for end of mutable sequence
   // iterator __CLR_OR_THIS_CALL end()
   Iterator End()
   {
      return STRING_ITERATOR( Myptr() + mSize );
   }

   // insert element at end
   // void __CLR_OR_THIS_CALL push_back(_Elem _Ch)
   void PushBack( Elem ch )
   {
      Insert( End(), ch );
   }

};
} // namespace DJ
