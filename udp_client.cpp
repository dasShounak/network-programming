#include <iostream>
#include <string>
#include <cstring>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT 1234
#define BACKLOG 5

using namespace std;

int main()
{
  int sockfd;                     // Socket file descriptor
  char buff[1024];                // Message to be sent to the server
  char ipstr[INET6_ADDRSTRLEN];   // IP Address of Server in readable fomrat
  struct sockaddr_in server_addr; // Server Adderss
  socklen_t server_len;           // Length of server address
  server_len = sizeof server_addr;

  // Socket address structure
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = PORT;
  server_addr.sin_addr.s_addr = INADDR_ANY;

  // Initialize socket
  sockfd = socket(AF_INET, SOCK_DGRAM, 0);

  // Send message
  while (1)
  {
    cout << "\nEnter message: ";
    fgets(buff, sizeof buff, stdin);

    sendto(sockfd, buff, sizeof buff, 0, (struct sockaddr *)&server_addr, server_len);

    inet_ntop(AF_INET, &server_addr.sin_addr, ipstr, sizeof ipstr);
    cout << "Message sent to " << ipstr << " successfully." << endl;

    recvfrom(sockfd, buff, sizeof buff, 0, (struct sockaddr *)&server_addr, &server_len);
    cout << buff << endl;
  }
}