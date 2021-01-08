#pragma once

namespace DJ
{
// class basic_streambuf
template< typename Elem, typename Traits >
class BasicStreambuf
{
public:
   typedef int Streamsize;
   typedef typename Traits::IntType IntType;

   // Возвращает символ в текущей позиции без изменения текущей позиции
   IntType Sgetc()
   {
      return GetNAvail() > 0 ? Traits::ToIntType( *PGet() ): Underflow();
   }

protected:
   BasicStreambuf()
   {
      Init();
   }

   // Установка указателей для буфера чтения
   void SetGet( Elem* p_first, Elem* p_next, Elem* p_last )
   {
      *mPPGetFirst = p_first;
      *mPPGetNext = p_next;
      *mPGetCount = static_cast< int >( p_last - p_next );
   }

   // Установка указателей для буфера записи
   void SetPut( Elem* p_first, Elem* p_last )
   {
      *mPPPutFirst = p_first;
      *mPPPutNext = p_first;
      *mPPutCount = static_cast< int >( p_last - p_first );
   }

   // Инициализация буфера, при вызове констуктора без параметров
   void Init()
   {
      mPPGetFirst = &mPGetFirst;
      mPPPutFirst = &mPPutFirst;
      mPPGetNext = &mPGetNext;
      mPPPutNext = &mPPutNext;
      mPGetCount = &mGetCount;
      mPPutCount = &mPutCount;
      SetGet( 0, 0, 0 );
      SetPut( 0, 0 );
   }

   // _Gnavail()
   // Посчитать количество доступных элементов в буфере чтения
   Streamsize GetNAvail() const
   {
      return *mPPGetNext != 0 ? mGetCount: 0;
   }

   // gptr()
   // Возвращает текущую позицию в буфере чтения
   Elem* PGet() const
   {
      return *mPPGetNext;
   }

   // Выход за пределы потока при получении символа
   virtual IntType Underflow()
   {
      return Traits::Eof();
   }

private:
   BasicStreambuf( const BasicStreambuf< Elem, Traits >& ) = delete;
   BasicStreambuf< Elem, Traits>& operator=( const BasicStreambuf< Elem, Traits>& ) = delete;

   // Указатель начала буфера чтения
   Elem* mPGetFirst;
   // Указатель начала буфера записи
   Elem* mPPutFirst;
   // Указатель на указатель начала буфера чтения
   Elem** mPPGetFirst;
   // Указатель на указатель начала буфера записи
   Elem** mPPPutFirst;
   // Указатель текущей позиции в буфере чтения
   Elem* mPGetNext;
   // Указатель текущей позиции в буфере записи
   Elem* mPPutNext;
   // Указатель на указатель текущей позиции в буфере чтения
   Elem** mPPGetNext;
   // Указатель на указатель текущей позиции в буфере записи
   Elem** mPPPutNext;
   // Длина буфера чтения
   int mGetCount;
   // Длина буфера записи
   int mPutCount;
   // Указатель на длину буфера чтения
   int* mPGetCount;
   // Указатель на длину буфера записи
   int* mPPutCount;
};
} // namespace DJ
