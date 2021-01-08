#pragma once

#include "streambuf.h"

#include "iosfwd.h"

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
};
} // namespace DJ
