#include "AString.h"
#include <cstdio>

void print( const AStringBuffer& string )
{
   printf( "%s\n", string.cStr() );
}

void printCmp( const AStringBuffer& str1, const AStringBuffer& str2 )
{   
   int result = strcompare( str1.cStr(), str2.cStr() );

   switch( result )
   {
   case -1:
      printf( "%s is before %s.\n", str1.cStr(), str2.cStr() );
      return;
   case 0:
      printf( "%s is equal to %s.\n", str1.cStr(), str2.cStr() );
      return;
   case 1:
      printf( "%s is after %s.\n", str1.cStr(), str2.cStr() );
      return;
   }
}

void printCmp( const char* str1, const char* str2 )
{
   int result = strcompare( str1, str2 );

   switch( result )
   {
   case -1:
      printf( "%s is before %s.\n", str1, str2 );
      return;
   case 0:
      printf( "%s is equal to %s.\n", str1, str2 );
      return;
   case 1:
      printf( "%s is after %s.\n", str1, str2 );
      return;
   }
}


int main()
{
   AStringBuffer alex = AStringBuffer( "Alexander Koerber" );
  
   alex.append( " is awesome!" );
   AStringBuffer bob = alex;

   print( alex );

   if( alex.equals( bob ) )
   {
      printf( "Thats right, Alex IS awesome!\n" );
   }


   return 0;
}