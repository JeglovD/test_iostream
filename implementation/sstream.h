#pragma once

#include "streambuf.h"

#include "iosfwd.h"
#include "xiosbase.h"

namespace DJ
{
//template<class _Elem,
//	class _Traits = char_traits<_Elem>,
//	class _Alloc = allocator<_Elem> >
//	class basic_stringbuf;


// class basic_stringbuf
template< typename Elem, typename Traits = DJ::CharTraits< Elem >/*, typename Alloc*/ >
class BasicStringbuf: public BasicStreambuf< Elem, Traits >
{
public:
   explicit BasicStringbuf( IOSBase::OpenMode /*ios_base::openmode*/ mode = IOSBase::omIN /*ios_base::in*/ | IOSBase::omOUT /*ios_base::out*/ )
   {
      Init( 0, 0, _Getstate( mode ) );
   }
};
} // namespace DJ
