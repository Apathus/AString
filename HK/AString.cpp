#include "AString.h"

//=============================================================================
//Returns a concatenated c-string literal from two c-strings (!CAUTION! no size param)
char* strconcat( char* dest, const char* src )
{
   char* current = dest;            //Current pointer starts at base of dest

   while( *current != NULL )        //While there are chars in dest...
   {
      current++;                       //Increment current pointer
   }

   while( *src != NULL )            //Until you reach NULL character...
   {
      *current++ = *src++;             //Increment current and src
   }

   *current = 0;                    //Append NULL character

   return dest;
}


//=============================================================================
//Returns the length of a c-string
int strlength( const char* str )
{
   int count = 0;                

   while( *(str++) != NULL )     //Until you reach NULL character...
   {
      count++;                      //Increment counter
   }

   return count;
}


//=============================================================================
//Compares two c-strings, returns -1, 0, and 1 in relation to str1
int strcompare( const char* str1, const char* str2, int comparisons )
{
   int result = 0;

   char* str1_upper = new char[comparisons];
   str1_upper = strncopy( str1_upper, str1, comparisons );
   touppercase( str1_upper );
   char* str1_curr = str1_upper;

   char* str2_upper = new char[comparisons];
   str2_upper = strncopy( str2_upper, str2, comparisons );
   touppercase( str2_upper );
   char* str2_curr = str2_upper;

   while( *str1_curr == *str2_curr && *str1_curr != 0 )
   {
      str1_curr++;
      str2_curr++;
   }

   if( *str1_curr < *str2_curr )
   {
      result = -1;
   }
   else if( *str1_curr > *str2_curr )
   {
      result = 1;
   }

   delete [] str1_upper;
   delete [] str2_upper;
   return result;
}

//=============================================================================
//Copies src c-string into dest buffer, whose size is specified
char* strncopy( char* dest, const char* src, int size )
{
   int index = 0;
   char* current = dest;

   while( *src != NULL && index++ < size )
   {
      *current++ = *src++;
   }

   *current = 0;

   return dest;
}

//=============================================================================
//Returns the passed c-string in uppercase
char* touppercase( char* str )
{
   char* current;
   int len = strlength( str );

   for( int index = 0; index < len; index++ )
   {
      current = str + index;
      *current = ( *current >= 'a' && *current <= 'z' ) ? ( *current - 32 ) : ( *current );
   }
   
   return str;
}

//=============================================================================
//Returns the passed c-string in lowercase
char* tolowercase( char* str )
{
   char* current;
   int len = strlength( str );

   for( int index = 0; index < len; index++ )
   {
      current = str + index;
      *current = ( *current >= 'A' && *current <= 'Z' ) ? ( *current + 32 ) : ( *current );
   }
   
   return str;
}

//=============================================================================
//Returns a c-string copy of the passed int inside the passed c-string
char* IntToStr( int num, char* str )
{
   int count =  0;                              //counter is set to zero
   char int_buffer[16];                         //Allocate a buffer that can hold an integer str

   while( num > 0 )                             //While num is greater than 0
   {
      int rem = num % 10;                          //Save remainder
      int_buffer[count++] = rem + '0';             //Store char representation of number in buffer

      num = num / 10;                              //divide num by 10 and store back into num
   }

   *( str + count-- ) = NULL;                   //Save '\0' at end of str

   num = 0;                                     //Set num value to 0
   while( count >= 0 )                          //While there are indexes to use...
   {
      *( str + num++ ) = int_buffer[ count-- ];    //Place item from int buffer into str
   }

   return str;
}




//=============================================================================
//Default Constructor - initializes to ""
AStringBuffer::AStringBuffer( void )
{
   m_buffer = static_buffer;  //buffer points to the static buffer
   m_buffer[0] = NULL;        //Creates empty NULL terminated string

   dynamic_buffer = NULL;     //dynamic buffer is set to NULL
   length = 0;                //Length is zero for empty string
   buffer_size = SSIZE;       //Buffer size is saved at 64
}

//=============================================================================
//Copy Constructor
AStringBuffer::AStringBuffer( const AStringBuffer& other )
{
   const char* otherStr = other.cStr();

   length = strlength( otherStr );
   buffer_size = length + 1;

   if( buffer_size > SSIZE )
   {
      dynamic_buffer = new char[buffer_size];
      m_buffer = dynamic_buffer;
   }
   else
   {
      dynamic_buffer = NULL;
      m_buffer = static_buffer;
      buffer_size = SSIZE;
   }

   strncopy( m_buffer, otherStr, length );
}

//=============================================================================
//Specific Constructor that is passed a const char*
AStringBuffer::AStringBuffer( const char* str )
{
   length = strlength( str );                   //Length of str is saved
   buffer_size = length + 1;                    //Buffer size is saved

   if( buffer_size > SSIZE )                    //If the buffer size is > 64...
   {
      dynamic_buffer = new char[buffer_size];      //Allocate dynamic buffer
      m_buffer = dynamic_buffer;                   //Set buffer ptr to dynamic buffer
   }
   else                                         //Else...
   {
      dynamic_buffer = NULL;
      m_buffer = static_buffer;
      buffer_size = SSIZE;                         //buffer size is reset to 64
   }

   strncopy( m_buffer, str, length );           //Copies characters from str into buffer
}

//=============================================================================
//Specific Constructor that is passed a char
AStringBuffer::AStringBuffer( char c )
{
   buffer_size = SSIZE;          //Buffer size is set to 64
   length = 1;                   //length is set to 1

   dynamic_buffer = NULL;        //Set dynamic buffer to NULL
   m_buffer = static_buffer;     //Point buffer to static buffer

   m_buffer[0] = c;              //Save c to the first index of the buffer
   m_buffer[1] = NULL;           //Add NULL terminated char to c-string
}

//=============================================================================
//Specific Constructor that is passed an int
AStringBuffer::AStringBuffer( int num )
{
   buffer_size = SSIZE;                   //Buffer size is set to 64

   dynamic_buffer = NULL;                 //Dynamic buffer points to nothing
   m_buffer = static_buffer;              //Point buffer to static buffer

   m_buffer = IntToStr( num, m_buffer );  //Convert int into c-string and store in buffer
   length = strlength( m_buffer );        //Save length
}



//=============================================================================
//Destructor: Destroys data in dynamic buffer, if there was memory allocated.
AStringBuffer::~AStringBuffer( void )
{
   if( dynamic_buffer != NULL )        //If dynamic buffer has allocated memory...
   {
      if( m_buffer == dynamic_buffer )    //If buffer points to dynamic buffer...
      {
         m_buffer = static_buffer;           //Point buffer to static buffer
      }

      delete [] dynamic_buffer;           //De-allocate dynamic buffer
      dynamic_buffer = NULL;              //Remove dangling ptr
   }
}


//=============================================================================
//Returns c-string constant equvalent of this string object
const char* AStringBuffer::cStr( void ) const
{
   return m_buffer;
}

//=============================================================================
//Returns the length of the string object
int AStringBuffer::Length( void ) const
{
   return length;
}

//=============================================================================
//Returns the char value at a specified index in the string
char AStringBuffer::charAt( int index )
{
   if( index < length )                //If index is > -1 && < length...
   {
      return *( m_buffer + index );        //Return char at that index
   }

   return 0;                           //Invalid result, return zero
}

//=============================================================================
//Appends a c-string value to the string
void AStringBuffer::append( const char* str )
{
   int new_size = length + strlength( str ) + 1;
   int old_size = length + 1;

   if( new_size > SSIZE && m_buffer == static_buffer )
   {
      dynamic_buffer =  new char[new_size];
      strncopy( dynamic_buffer, m_buffer, buffer_size );
      buffer_size = new_size;
      m_buffer = dynamic_buffer;
   }

   strncopy( ( m_buffer + old_size - 1 ), str, new_size - old_size );
   length = length + strlength( str );
   
   if( m_buffer[buffer_size - 1] != 0 )
   {
      m_buffer[buffer_size - 1] = 0;
   }
}

//=============================================================================
//Returns true if string is equal to another string object
bool AStringBuffer::equals( const AStringBuffer& other )
{
   const char* otherStr = other.cStr();

   int otherLen = other.Length();    //Calculate length of other str buffer

   if( otherLen != length )            //If otherLen doesn't match length...
   {
      return false;                       //Exit early
   }

   int maxLen = ( length > SSIZE ) ? ( length ) : ( SSIZE );

   int result = strcompare( m_buffer, otherStr, maxLen );

   return result == 0;
}

//=============================================================================
//Returns true if string is equal to another c-string literal
bool AStringBuffer::equals( const char* str )
{
   int otherLen = strlength( str );    //Calculate length of other str buffer

   if( otherLen != length )            //If otherLen doesn't match length...
   {
      return false;                       //Exit early
   }

   int maxLen = ( length > SSIZE ) ? ( length ) : ( SSIZE );

   int result = strcompare( m_buffer, str, maxLen );

   return result == 0;
}

//=============================================================================
//Returns true if string is the same as the string representation of the passed char value
bool AStringBuffer::equals( char c )
{
   if( length != 1 )
   {
      return false;
   }

   return m_buffer[0] == c;
}

//=============================================================================
//Returns true if string is the same as the string representation of the passed int value
bool AStringBuffer::equals( int num )
{
   char int_buffer[16];

   IntToStr( num, int_buffer );

   int result = strcompare( m_buffer, int_buffer );

   return result == 0;
}

////Returns true if string is the same as the string representation of the passed float value
//bool AStringBuffer::equals( float num )
//{
//}
//
////Returns true if string is the same as the string representation of the passed double value
//bool AStringBuffer::equals( double num )
//{
//}
//
////Returns a new string object that is the substring of this string object
//AStringBuffer AStringBuffer::subStr( int startIndex, int endIndex )
//{
//}

//=============================================================================
//Assignment operator that performs like copy construction
AStringBuffer& AStringBuffer::operator = ( const AStringBuffer& rhs )
{
   const char* rhsStr = rhs.cStr();          //c-string for rhs is stored

   length = strlength( rhsStr );             //length is saved
   buffer_size = length + 1;                 //buffer size is updated temporarily

   if( dynamic_buffer != NULL )              //If dynamic buffer is not null...
   {
      delete [] dynamic_buffer;                 //Delete memory allocated
      dynamic_buffer = NULL;                    //dynamic buffer is set to null
   }

   if( buffer_size > SSIZE )                 //If buffer size is > 64...
   {
      dynamic_buffer = new char[buffer_size];   //Allocate a dynamic buffer
      m_buffer = dynamic_buffer;                //Point buffer to dynamic buffer
   }
   else                                      //Else...
   {
      m_buffer = static_buffer;                 //Point buffer to static buffer
      buffer_size = SSIZE;                      //Update buffer size
   }

   strncopy( m_buffer, rhsStr, length );     //Copy the c-string from rhs to buffer

   return *this;
}

//=============================================================================
//Assignment operator that constructs a string from a passed c-string
AStringBuffer& AStringBuffer::operator = ( const char* str )
{
   length = strlength( str );                   //Length of str is saved
   buffer_size = length + 1;                    //Buffer size is saved

   if( dynamic_buffer != NULL )              //If dynamic buffer is not null...
   {
      delete [] dynamic_buffer;                 //Delete memory allocated
      dynamic_buffer = NULL;                    //dynamic buffer is set to null
   }

   if( buffer_size > SSIZE )                    //If the buffer size is > 64...
   {
      dynamic_buffer = new char[buffer_size];      //Allocate dynamic buffer
      m_buffer = dynamic_buffer;                   //Set buffer ptr to dynamic buffer
   }
   else                                         //Else...
   {
      m_buffer = static_buffer;
      buffer_size = SSIZE;                         //buffer size is reset to 64
   }

   strncopy( m_buffer, str, length );           //Copies characters from str into buffer
   
   return *this;
}

//=============================================================================
//Assignment operator that constructs a string from a passed char
AStringBuffer& AStringBuffer::operator = ( char c )
{
   buffer_size = SSIZE;          //Buffer size is set to 64
   length = 1;                   //length is set to 1

   if( dynamic_buffer != NULL )  //If dynamic data was allocated earlier...
   {
      delete [] dynamic_buffer;     //Delete that data
      dynamic_buffer = NULL;        //Set dynamic buffer to NULL
   }

   m_buffer = static_buffer;     //Point buffer to static buffer

   m_buffer[0] = c;              //Save c to the first index of the buffer
   m_buffer[1] = NULL;           //Add NULL terminated char to c-string

   return *this;
}

//=============================================================================
//Assignment operator that constructs a string from a passed int
AStringBuffer& AStringBuffer::operator = ( int num )
{
   buffer_size = SSIZE;                   //Buffer size is set to 64

   if( dynamic_buffer != NULL )           //If dynamic data was allocated...
   {
      delete [] dynamic_buffer;              //Delete dynamic data
      dynamic_buffer = NULL;                 //Dynamic buffer points to nothing
   }

   m_buffer = static_buffer;              //Point buffer to static buffer

   m_buffer = IntToStr( num, m_buffer );  //Convert int into c-string and store in buffer
   length = strlength( m_buffer );        //Save lengt

   return *this;
}


//=============================================================================
//Concatenation operator that appends another string object
AStringBuffer& AStringBuffer::operator += ( const AStringBuffer& rhs )
{
   return *this;
}

//=============================================================================
//Concatenation operator that appends another c-string object
AStringBuffer& AStringBuffer::operator += ( const char* rhs )
{
   return *this;
}

//=============================================================================
//Concatenation operator that appends a char
AStringBuffer& AStringBuffer::operator += ( char c )
{
   return *this;
}

//=============================================================================
//Concatenation operator that appends an int
AStringBuffer& AStringBuffer::operator += ( int num )
{
   return *this;
}


//=============================================================================
//Tests for equality with another string object
bool AStringBuffer::operator == ( const AStringBuffer& rhs )
{
   const char* rhsStr = rhs.cStr();

   int rhsLen = rhs.Length();

   if( rhsLen != length )
   {
      return false;
   }

   int maxLen = ( length > SSIZE ) ? ( length ) : ( SSIZE );

   int result = strcompare( m_buffer, rhs.cStr(), maxLen );

   return result == 0;
}

//=============================================================================
//Tests for equality with a c-string
bool AStringBuffer::operator == ( const char* rhs )
{
   int otherLen = strlength( rhs );

   if( otherLen != length )
   {
      return false;
   }

   int maxLen = ( length > SSIZE ) ? ( length ) : ( SSIZE  );

   int result = strcompare( m_buffer, rhs, maxLen );

   return result == 0;
}

//=============================================================================
//Tests for inequality with another string object
bool AStringBuffer::operator != ( const AStringBuffer& rhs )
{
   const char* rhsStr = rhs.cStr();

   int rhsLen = rhs.Length();

   if( rhsLen != length )
   {
      return false;
   }

   int maxLen = ( length > SSIZE ) ? ( length ) : ( SSIZE );

   int result = strcompare( m_buffer, rhs.cStr(), maxLen );

   return result != 0;
}

//=============================================================================
//Tests for inequality with a c-string
bool AStringBuffer::operator != ( const char* rhs )
{
   int otherLen = strlength( rhs );

   if( otherLen != length )
   {
      return false;
   }

   int maxLen = ( length > SSIZE ) ? ( length ) : ( SSIZE );

   int result = strcompare( m_buffer, rhs, maxLen );

   return result != 0;
}

//=============================================================================
//Less-than comparison between this string object and another string object
bool AStringBuffer::operator < ( const AStringBuffer& rhs )
{
   const char* rhsStr = rhs.cStr();

   int rhsLen = rhs.Length();

   if( rhsLen != length )
   {
      return false;
   }

   int maxLen = ( length > SSIZE ) ? ( length ) : ( SSIZE );

   int result = strcompare( m_buffer, rhs.cStr(), maxLen );

   return result < 0;
}

//=============================================================================
//Less-than comparison between this string object and a c-string value
bool AStringBuffer::operator < ( const char* rhs )
{
   int otherLen = strlength( rhs );

   if( otherLen != length )
   {
      return false;
   }

   int maxLen = ( length > SSIZE ) ? ( length ) : ( SSIZE );

   int result = strcompare( m_buffer, rhs, maxLen );

   return result < 0;
}

//=============================================================================
//Less-than or equal-to comparison between this string object and another string object
bool AStringBuffer::operator <= ( const AStringBuffer& rhs )
{
   const char* rhsStr = rhs.cStr();

   int rhsLen = rhs.Length();

   if( rhsLen != length )
   {
      return false;
   }

   int maxLen = ( length > SSIZE ) ? ( length ) : ( SSIZE );

   int result = strcompare( m_buffer, rhs.cStr(), maxLen );

   return result <= 0;
}

//=============================================================================
//Less-than or equal-to comparison between this string object and a c-string
bool AStringBuffer::operator <= ( const char* rhs )
{
   int otherLen = strlength( rhs );

   if( otherLen != length )
   {
      return false;
   }

   int maxLen = ( length > SSIZE ) ? ( length ) : ( SSIZE );

   int result = strcompare( m_buffer, rhs, maxLen );

   return result <= 0;
}

//=============================================================================
//Greater-than comparison between this string object and another string object
bool AStringBuffer::operator > ( const AStringBuffer& rhs )
{
   const char* rhsStr = rhs.cStr();

   int rhsLen = rhs.Length();

   if( rhsLen != length )
   {
      return false;
   }

   int maxLen = ( length > SSIZE ) ? ( length ) : ( SSIZE );

   int result = strcompare( m_buffer, rhs.cStr(), maxLen );

   return result > 0;
}

//=============================================================================
//Greater-than comparison between this string object and a c-string
bool AStringBuffer::operator > ( const char* rhs )
{
   int otherLen = strlength( rhs );

   if( otherLen != length )
   {
      return false;
   }

   int maxLen = ( length > SSIZE ) ? ( length ) : ( SSIZE );

   int result = strcompare( m_buffer, rhs, maxLen );

   return result > 0;
}

//=============================================================================
//Greater-than or equal-to comparison between this string object and another string object
bool AStringBuffer::operator >= ( const AStringBuffer& rhs )
{
   const char* rhsStr = rhs.cStr();

   int rhsLen = rhs.Length();

   if( rhsLen != length )
   {
      return false;
   }

   int maxLen = ( length > SSIZE ) ? ( length ) : ( SSIZE );

   int result = strcompare( m_buffer, rhs.cStr(), maxLen );

   return result >= 0;
}

//=============================================================================
//Greater-than or equal-to comparison between this string object and c-string
bool AStringBuffer::operator >= ( const char* rhs )
{
   int otherLen = strlength( rhs );

   if( otherLen != length )
   {
      return false;
   }

   int maxLen = ( length > SSIZE ) ? ( length ) : ( SSIZE );

   int result = strcompare( m_buffer, rhs, maxLen );

   return result >= 0;
}

//=============================================================================
//Returns a reference to the character at a specified index
char& AStringBuffer::operator[] ( int index )
{
   return m_buffer[index];
}