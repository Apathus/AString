#if !defined( H_AString )
#define H_AString

#include <iostream>

#define SSIZE 64  //Size for a static string buffer

/***********************************************
* A Non-standard C++ String data type.         *
***********************************************/
class AStringBuffer
{
public:  //---------- Construction and Destruction ---------- 
   //Default Constructor - initializes to ""
   explicit AStringBuffer( void );
   //Copy Constructor
   AStringBuffer( const AStringBuffer& other );
   //Specific Constructor that is passed a const char*
   explicit AStringBuffer( const char* str );
   //Specific Constructor that is passed a char
   explicit AStringBuffer( char c );
   //Specific Constructor that is passed an int
   explicit AStringBuffer( int num );
   ////Specific Constructor that is passed a float
   //explicit AStringBuffer( float num );
   ////Specific Constructor that is passed a double
   //explicit AStringBuffer( double num );
   //Destructor
   ~AStringBuffer( void );
   
public:  //---------- Public Instance Methods ---------- 
   //Returns c-string constant equvalent of this string object
   const char* cStr( void ) const;
   //Returns the length of the string object
   int Length( void ) const;
   //Returns the char value at a specified index in the string
   char charAt( int index );
   //Appends a c-string value to the string
   void append( const char* str );
   //Returns true if string is equal to another string object
   bool equals( const AStringBuffer& other );
   //Returns true if string is equal to another c-string literal
   bool equals( const char* str );
   //Returns true if string is the same as the string representation of the passed char value
   bool equals( char c );
   //Returns true if string is the same as the string representation of the passed int value
   bool equals( int num );
   ////Returns true if string is the same as the string representation of the passed float value
   //bool equals( float num );
   ////Returns true if string is the same as the string representation of the passed double value
   //bool equals( double num );
   ////Returns a new string object that is the substring of this string object
   //AStringBuffer subStr( int startIndex, int endIndex );

public:  //---------- Public Non-friendly operator overloads ----------
   //Assignment operator that performs like copy construction
   AStringBuffer& operator = ( const AStringBuffer& rhs );
   //Assignment operator that constructs a string from a passed c-string
   AStringBuffer& operator = ( const char* rhs );
   //Assignment operator that constructs a string from a passed char
   AStringBuffer& operator = ( char c );
   //Assignment operator that constructs a string from a passed int
   AStringBuffer& operator = ( int num );
   ////Assignment operator that constructs a string from a passed float
   //AStringBuffer& operator = ( float num );
   ////Assignment operator that constructs a string from a passed double
   //AStringBuffer& operator = ( double num );

   //Concatenation operator that appends another string object
   AStringBuffer& operator += ( const AStringBuffer& rhs );
   //Concatenation operator that appends another c-string object
   AStringBuffer& operator += ( const char* rhs );
   //Concatenation operator that appends a char
   AStringBuffer& operator += ( char c );
   //Concatenation operator that appends an int
   AStringBuffer& operator += ( int num );
   ////Concatenation operator that appends a float
   //AStringBuffer& operator += ( float num );
   ////Concatenation operator that appends a double
   //AStringBuffer& operator += ( double num );

   //Tests for equality with another string object
   bool operator == ( const AStringBuffer& rhs );
   //Tests for equality with a c-string
   bool operator == ( const char* rhs );

   //Tests for inequality with another string object
   bool operator != ( const AStringBuffer& rhs );
   //Tests for inequality with a c-string
   bool operator != ( const char* rhs );

   //Less-than comparison between this string object and another string object
   bool operator < ( const AStringBuffer& rhs );
   //Less-than comparison between this string object and a c-string value
   bool operator < ( const char* rhs );
   //Less-than or equal-to comparison between this string object and another string object
   bool operator <= ( const AStringBuffer& rhs );
   //Less-than or equal-to comparison between this string object and a c-string
   bool operator <= ( const char* rhs );

   //Greater-than comparison between this string object and another string object
   bool operator > ( const AStringBuffer& rhs );
   //Greater-than comparison between this string object and a c-string
   bool operator > ( const char* rhs );
   //Greater-than or equal-to comparison between this string object and another string object
   bool operator >= ( const AStringBuffer& rhs );
   //Greater-than or equal-to comparison between this string object and c-string
   bool operator >= ( const char* rhs );

   //Returns a reference to the character at a specified index
   char& operator[] ( int index );

public:  //---------- Public friendly operator overloads ---------- 
   //Concatenation operator for two string objects.
   friend AStringBuffer operator + ( const AStringBuffer& lhs, const AStringBuffer& rhs );
   //Concatenation operator for a string and a c-string.
   friend AStringBuffer operator + ( const AStringBuffer& lhs, const char* str );
   //Concatenation operator for a string and a char.
   friend AStringBuffer operator + ( const AStringBuffer& lhs, char c );
   //Concatenation operator for a string and an integer.
   friend AStringBuffer operator + ( const AStringBuffer& lhs, int num );
   ////Concatenation operator for a string and a float.
   //friend AStringBuffer operator + ( const AStringBuffer& lhs, float num );
   ////Concatenation operator for a string and a double.
   //friend AStringBuffer operator + ( const AStringBuffer& lhs, double num );

   //Stream operator for outputting a string object
   friend std::ostream& operator << ( std::ostream& strm, const AStringBuffer& rhs );
   //Stream operator for inputting a string value
   friend std::istream& operator >> ( std::istream& strm, const AStringBuffer& rhs );

private: //---------- Instance data members ---------- 
   char* dynamic_buffer;      //Dynamic buffer used for longer strings
   char static_buffer[SSIZE]; //Static buffer used for strings up to 64 characters long
   char* m_buffer;            //The pointer to the current buffer
   int length;                //The number of characters in the string
   int buffer_size;           //The size of the buffer
};


//Returns a concatenated c-string literal from two c-strings
extern char* strconcat( char* dest, const char* src );
//Returns the length of a c-string
extern int strlength( const char* str );
//Compares two c-strings, returns -1, 0, and 1 in relation to str1
extern int strcompare( const char* str1, const char* str2, int comparisons = SSIZE );
//Copies src c-string into dest buffer, whose size is specified
extern char* strncopy( char* dest, const char* src, int size );
//Returns an uppercase copy of the passed c-string
extern char* touppercase( char* str );
//Returns a lowercase copy of the passed c-string
extern char* tolowercase( char* str );
//Returns a c-string copy of the passed int inside the passed c-string
extern char* IntToStr( int num, char* str );

#endif