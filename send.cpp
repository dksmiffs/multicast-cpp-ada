// Guidance:  www.tenouk.com/Module41c.html
#include <arpa/inet.h>
#include "diagnose.hpp"
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include "udpSock.hpp"

int main()
{
  UdpSock sock;
  diagnose(sock.isGood(), "Opening datagram socket for send");

  sockaddr_in groupSock = {};   // init to all zeroes
  groupSock.sin_family = AF_INET;
  groupSock.sin_addr.s_addr = inet_addr("226.1.1.1");
  groupSock.sin_port = htons(4321);

  in_addr localIface = {};   // init to all zeroes
  localIface.s_addr = inet_addr("127.0.0.1");
  diagnose(setsockopt(sock(), IPPROTO_IP, IP_MULTICAST_IF, (char*)&localIface,
                      sizeof(localIface)) >= 0, "Setting local interface");

  const std::string databuf = "Multicast from C++";
  diagnose(sendto(sock(), databuf.c_str(), databuf.length(), 0,
                  (sockaddr*)&groupSock, sizeof(groupSock)) >= 0,
           "Sending datagram message");

  return 0;
}
