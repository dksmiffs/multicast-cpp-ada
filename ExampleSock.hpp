// Guidance:  https://www.tenouk.com/Module41c.html
#pragma once
#include <arpa/inet.h>
#include <array>
#include "diagnose.hpp"
#include <netinet/in.h>
#include <string>
#include <string.h>
#include "udpSock.hpp"


class ExampleSock {
  public:
    ExampleSock()
    {
      diagnose(m_sock.isGood(),
               "Opening datagram socket for receive");

      {
        // enable SO_REUSEADDR to allow multiple instances of this app to
        //    receive copies of the multicast datagrams.
        int reuse = 1;
        diagnose(setsockopt(m_sock(), SOL_SOCKET, SO_REUSEADDR, (char*)&reuse,
                            sizeof(reuse)) >= 0,
                 "Setting SO_REUSEADDR");
      }

      // Bind to the proper port number w/ IP address specified as INADDR_ANY
      sockaddr_in localSock = {};    // initialize to all zeroes
      localSock.sin_family      = AF_INET;
      localSock.sin_port        = htons(4321);
      localSock.sin_addr.s_addr = INADDR_ANY;
      // Note from manpage that bind returns 0 on success
      diagnose(!bind(m_sock(), (sockaddr*)&localSock, sizeof(localSock)),
               "Binding datagram socket");

      // Join the multicast group on the local interface.  Note that this
      //    IP_ADD_MEMBERSHIP option must be called for each local interface
      //    over which the multicast datagrams are to be received.
      ip_mreq group = {};    // initialize to all zeroes
      group.imr_multiaddr.s_addr = inet_addr("226.1.1.1");
      group.imr_interface.s_addr = inet_addr("127.0.0.1");
      diagnose(setsockopt(m_sock(), IPPROTO_IP, IP_ADD_MEMBERSHIP,
                          (char*)&group, sizeof(group)) >= 0,
               "Adding multicast group");
    }

    // For C++ clients
    const char* Read()
    {
      std::array<char, 1024> arr;
      arr.fill('\0');
      _Read(arr.data(), arr.size());
      return arr.data();
    }

    // For external clients that need to manage their own buffer
    void Read(char* read_buf, int length)
    {
      memset(read_buf, 0, length);
      _Read(read_buf, length);
    }

  private:
    void _Read(char* read_buf, int length)
    {
      diagnose(read(m_sock(), read_buf, length) >= 0,
               "Reading datagram message");
    }

    UdpSock m_sock;
};

