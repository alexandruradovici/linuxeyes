// Definition of the ClientSocket class

#ifndef ClientSocket_class
#define ClientSocket_class

#include "Socket.h"


class ClientSocket : private Socket
{
 public:

  ClientSocket (){};
  int link (std::string host, int port);
  virtual ~ClientSocket(){};

  const ClientSocket& operator << ( char *s ) const;
  char * read();

};


#endif

