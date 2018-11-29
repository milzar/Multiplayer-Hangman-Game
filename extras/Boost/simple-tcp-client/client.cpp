
#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include<vector>
typedef boost::asio::ip::tcp BOOST;

int main(){


    // boost::asio::io_context io_context;
    boost::asio::io_service io_service;

    BOOST::resolver resolver(io_service);
    BOOST::resolver::results_type endpoints =  resolver.resolve("localhost", "6666");

    BOOST::socket socket(io_service);
    boost::asio::connect(socket, endpoints);

    for (;;){
      // std::vector<char> blah(128);
      boost::array<char, 128> buf;
      boost::system::error_code error;

      size_t len = socket.read_some(boost::asio::buffer(buf),error);
      if (error == boost::asio::error::eof){
        std::cout<<"error"<<std::endl;
        break; // Connection closed cleanly by peer.

      }
      else if (error){
        std::cout<<"error fak"<<std::endl;
        throw boost::system::system_error(error); // Some other error.

      }

        std::cout.write(buf.data(), len);
    }
  return 0;
}
