#pragma once

#include "streambuf.h"

#include "iosfwd.h"
#include "xiosbase.h"
#include "xmemory.h"
#include "xstring.h"

#include <string>

namespace DJ
{
//template<class _Elem,
//	class _Traits = char_traits<_Elem>,
//	class _Alloc = allocator<_Elem> >
//	class basic_stringbuf;


// class basic_stringbuf
template< typename Elem, typename Traits = DJ::CharTraits< Elem >, typename Alloc = DJ::Allocator< Elem > >
class BasicStringBuf: public BasicStreamBuf< Elem, Traits >
{
public:
   typedef std::basic_string< Elem, Traits, Alloc > MyStr;

   MyStr str() const
   {
   }
};
} // namespace DJ
