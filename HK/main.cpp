#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

struct MovieTicket
{
   string movieName;
   double adultTicketPrice, childTicketPrice;
   int noOfAdultTicketsSold, noOfChildTicketsSold;
   double percentDonation;
   double grossAmount;
   double amountDonated;
   double netSaleAmount;
};

void getInput( MovieTicket& mT )
{
   cout << "Enter the movie name: ";
   getline( cin, mT.movieName );
   cout << endl;

   cout << "Enter the price of an adult ticket: ";
   cin >> mT.adultTicketPrice;
   cout << endl;

   cout << "Enter the price of a child ticket: ";
   cin >> mT.childTicketPrice;
   cout << endl;

   cout << "Enter the amount of adult tickets sold: ";
   cin >> mT.noOfAdultTicketsSold;
   cout << endl;

   cout << "Enter the amount of child tickets sold: ";
   cin >> mT.noOfChildTicketsSold;
   cout << endl;

   cout << "Enter the percentage of donations: ";
   cin >> mT.percentDonation;
   cout << endl << endl;
}

void printOutput( const MovieTicket& mT )
{
   cout << "-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*" << endl;
   cout << setfill( '.' ) << left << setw( 35 ) << "Movie Name: "
        << right << " " << mT.movieName << endl;

   cout << left << setw( 35 ) << "Number of Tickets Sold: " << setfill( ' ' )
        << right << setw( 10 ) << mT.noOfAdultTicketsSold + mT.noOfChildTicketsSold << endl;

   cout << setfill( '.' ) << left << setw( 35 ) << "Gross Amount: "
        << setfill( ' ' ) << right << " $" << setw( 8 ) << mT.grossAmount << endl;

   cout << setfill( '.' ) << left << setw( 35 ) << "Percentage of Gross Amount Donated: "
        << setfill( ' ' ) << right << setw( 9 ) << mT.percentDonation << "%" << endl;

   cout << setfill( '.' ) << left << setw( 35 ) << "Amount Donated: "
        << setfill( ' ' ) << right << " $" << setw( 8 ) <<  mT.amountDonated << endl;

   cout << setfill( '.' ) << left << setw( 35 ) << "Net Sale: "
        << setfill( ' ' ) << right << " $" << setw( 8 ) << mT.netSaleAmount << endl;
}

void runProgram( void )
{
   MovieTicket mT;
   
   while( true )
   {
      getInput( mT );

      mT.grossAmount = ( mT.adultTicketPrice * mT.noOfAdultTicketsSold ) + 
                       ( mT.childTicketPrice *  mT.noOfChildTicketsSold );
      mT.amountDonated = ( mT.grossAmount * mT.percentDonation ) / 100;

      mT.netSaleAmount = mT.grossAmount - mT.amountDonated;

      printOutput( mT );

      char exit;
      cout << "Exit program (Y/N): ";
      cin >> exit;
      cout << endl;

      if( exit == 'y' || exit == 'Y' )
      {
         cout << "Program Terminated.\n";
         break;
      }

      cin.ignore();
      system( "CLS" );
   }
}

int main()
{
   cout << fixed << showpoint << setprecision( 2 );
   runProgram();

   return 0;
}