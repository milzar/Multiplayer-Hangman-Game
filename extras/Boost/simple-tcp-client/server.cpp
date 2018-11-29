#include <iostream>
#include <string>
#include <boost/asio.hpp>

typedef boost::asio::ip::tcp BOOST;

std::string bitch()
{
  static int i=0;
  return "Bitch Lasagna ";
}

int main()
{
    // boost::asio::io_context io_context;
    boost::asio::io_service io_service;

    BOOST::acceptor acceptor(io_service, BOOST::endpoint(BOOST::v4(), 6666));
    std::cout<<"Server Running"<<std::endl;

    for (;;) {
      BOOST::socket socket(io_service);
      acceptor.accept(socket);
      std::cout<<"Connection Accepted"<<std::endl;
      std::string message = bitch();
      std::cout<<"Sending "+message<<std::endl;
      // boost::asio::write(socket, boost::asio::buffer(message));
      boost::asio::write(socket, boost::asio::buffer(message),
          boost::asio::transfer_all());
    }

  return 0;
}
