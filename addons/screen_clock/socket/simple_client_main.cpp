#include "ClientSocket.h"
#include "SocketException.h"
#include <stream.h>
#include <string>

int main ( int argc, int argv[] )
{
  ClientSocket client;
  client.link ("127.0.0.1",6006);
  try
    {


    while (1)
    {
      char reply[500];

      strcpy (reply,"");
      try
	{
//	  client_socket << "Test message.";
	  strcpy (reply,client.read());
	}
      catch ( SocketException& ) {}

      cout << "We received this response from the server:\n\"" << reply << "\"\n";;
     }

    }
  catch ( SocketException& e )
    {
      cout << "Exception was caught:" << e.description() << "\n";
    }

  return 0;
}

