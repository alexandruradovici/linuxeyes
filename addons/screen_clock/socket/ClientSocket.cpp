// Implementation of the ClientSocket class

#include "ClientSocket.h"
#include "SocketException.h"


ClientSocket::ClientSocket ()
{
  if ( ! Socket::create() )
    {
      throw SocketException ( "Could not create client socket." );
    }

  if ( ! Socket::connect ( host, port ) )
    {
      throw SocketException ( "Could not bind to port." );
    }

}



int ClientSocket::link (std::string host, int port)
{
  if ( ! Socket::create() )
    {
      return 0;
    }

  if ( ! Socket::connect ( host, port ) )
    {
      return 0;
    }
    return 1;
}

const ClientSocket& ClientSocket::operator << ( char *s ) const
{
  if ( ! Socket::send ( s ) )
    {
      throw SocketException ( "Could not write to socket." );
    }

  return *this;

}


char * ClientSocket::read ()
{
/*  if ( ! Socket::recv ( s ) )
    {
      throw SocketException ( "Could not read from socket." );
    }*/
    return Socket::recv ();

}

