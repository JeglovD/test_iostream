#pragma once

template< typename Elem, typename Traits >
class BasicStreambuf
{
public:
   typedef typename Traits::IntType IntType;

   IntType Sgetc();
};
