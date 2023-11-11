#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdlib.h>
#include <cstring>
#include <netinet/in.h>
#include <string>

using namespace std;

int main()
{
  int status;
  struct addrinfo hints, *servinfo;

  memset(&hints, 0, sizeof(hints));
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_family = AF_UNSPEC;

  status = getaddrinfo("www.srmist.edu.in", NULL, &hints, &servinfo);

  if (status != 0) {
    cerr << "getaddressinfo error: " << gai_strerror(status) << endl;
    return 1;
  }

  struct addrinfo *p;
  for (p = servinfo; p != NULL; p=p->ai_next) {
    void *addr;
    string ipver;

    if (p->ai_family==AF_INET) {
      struct sockaddr_in *ipv4 = (struct sockaddr_in *)p->ai_addr;
      addr = &(ipv4->sin_addr);
      ipver = "IPv4";
    } else {
      struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)p->ai_addr;
      addr = &(ipv6->sin6_addr);
      ipver = "IPv6";
    }

    char ipstr[INET6_ADDRSTRLEN];
    inet_ntop(p->ai_family, addr, ipstr, sizeof ipstr);
    cout << ipver << ": " << ipstr << endl;
  }

  freeaddrinfo(servinfo);

  return 0;
}