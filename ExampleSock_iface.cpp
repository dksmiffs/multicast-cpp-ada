#include "ExampleSock.hpp"


char read_buf[1024] = {};

// So that an Ada program can reuse the code here
extern "C" char* read_from_the_sock()
{
  ExampleSock theSock;
  theSock.Read(read_buf, 1024);
  return read_buf;
}

