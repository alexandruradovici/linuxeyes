// Definition of the ServerSocket class

#ifndef ServerSocket_class
#define ServerSocket_class

#include "Socket.h"


class ServerSocket : private Socket
{
 public:

  ServerSocket ( int port );
  ServerSocket (){};
  virtual ~ServerSocket();

  const ServerSocket& operator << ( char *s ) const;
  const ServerSocket& operator >> ( char *s ) const;

  void accept ( ServerSocket& );

};


#endif

