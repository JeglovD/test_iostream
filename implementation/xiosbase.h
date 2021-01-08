#pragma once

namespace DJ
{
// class _Iosb
// Определяет шаблонные битовые маски/перечисляемые типы
template< typename Dummy >
class IOSB
{
public:
   // Константы для параметров открытия файлов
   enum OpenMode
   {
      omMASK = 0xff
   };

   static const OpenMode omIN = static_cast< OpenMode >( 0x01 );
   static const OpenMode omOUT = static_cast< OpenMode >( 0x02 );
//   static const _Openmode ate = (_Openmode)0x04;
//   static const _Openmode app = (_Openmode)0x08;
//   static const _Openmode trunc = (_Openmode)0x10;
//   static const _Openmode _Nocreate = (_Openmode)_IOS_Nocreate;
//   static const _Openmode _Noreplace = (_Openmode)_IOS_Noreplace;
//   static const _Openmode binary = (_Openmode)_IOSbinary;
};

// class ios_base
class IOSBase: public IOSB< int >
{
public:
   typedef unsigned int IOState /*io_state*/, OpenMode /*open_mode*/, SeekDir /*seek_dir*/;
};
} // namespace DJ
