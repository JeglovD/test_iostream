#pragma once

namespace DJ
{
template< typename Elem, typename Traits >
class BasicStreambuf
{
public:
   typedef int Streamsize;
   typedef typename Traits::IntType IntType;

private:
   // Указатель на текущую позицию в буфере чтения
   Elem** mPGNext;
   // Длина буфера чтения
   int mGCount;

protected:
   Streamsize Gnavail() const
   {
      return *mPGNext != 0 ? mGCount: 0;
   }

   // Возвращает текущую позицию в буфере чтения
   Elem* PG() const
   {
      return *mPGNext;
   }

   // Выход за пределы потока при получении символа
   virtual IntType Underflow()
   {
      return Traits::Eof();
   }

public:
   typedef typename Traits::IntType IntType;

   // Возвращает символ в текущей позиции без изменения текущей позиции
   IntType Sgetc()
   {
      return Gnavail() > 0 ? Traits::ToIntType( *PG() ): Underflow();
   }
};
} // namespace DJ
