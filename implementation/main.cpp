#include "iosfwd.h"
#include "sstream.h"
#include "xmemory.h"
#include "xstring.h"

#include <iostream>

int main()
{
//   DJ::BasicStringBuf< char, DJ::CharTraits< char >, DJ::Allocator< char > > basic_string_buf;
//   basic_string_buf.str();
   DJ::BasicString< char, DJ::CharTraits< char >, DJ::Allocator< char > > bs;
   auto a = bs.Capacity();
}
