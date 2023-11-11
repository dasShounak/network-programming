#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <string>
#include <cstring>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

using namespace std;

int main() {
  int status;
  struct addrinfo hints, *res;

  memset(&hints, 0, sizeof hints);
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;

  status = getaddrinfo("www.xvideos.com", NULL, &hints, &res);

  if(status !=0) {
    cout << "getaddrinfo error: " << gai_strerror(status) << endl;
    return 1;
  }

  struct addrinfo *p;
  for (p = res; p != NULL; p=p->ai_next) {
    void *addr;
    string version;

    if (p->ai_family = AF_INET) {
      struct sockaddr_in *ipv4 = (struct sockaddr_in *)p->ai_addr;
      addr = &(ipv4->sin_addr);
      version = "IPv4";
    } else {
      struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)p->ai_addr;
      addr = &(ipv6->sin6_addr);
      version = "IPv6";
    }

    char ipstr[INET6_ADDRSTRLEN];
    inet_ntop(p->ai_family, addr, ipstr, sizeof ipstr);

    cout << version << ": " << ipstr << endl;
  }

  freeaddrinfo(res);
}