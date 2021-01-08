#include "iosfwd.h"
#include "streambuf.h"

#include <iostream>

int main()
{
   DJ::BasicStreambuf< char, DJ::CharTraits< char > > sb;
   auto a = sb.Sgetc();
   std::cout << "a = " << a << std::endl;
}
