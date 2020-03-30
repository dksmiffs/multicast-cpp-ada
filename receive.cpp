#include "ExampleSock.hpp"
#include <iostream>


int main()
{
  ExampleSock theSock;
  const char* msg = theSock.Read();
  std::cout << "Message from multicast sender: " << msg << std::endl;
  return 0;
}
