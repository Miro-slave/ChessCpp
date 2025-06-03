#include <boost/asio.hpp>

#include <array>
#include <iostream>
#include <memory>
#include <string>


using boost::asio::ip::tcp;

int main(int argc, char* argv[]) {
  try {
    //if (argc != 2) {
    //  std::cerr << "Usage: client <host>" << std::endl;
    //  return 1;
    //}

    // std::string host = argv[1];

    std::string host = "127.0.0.1";

    boost::asio::io_context io_context;
    tcp::resolver resolver(io_context);

    tcp::resolver::results_type endpoints = resolver.resolve(host, "daytime");

    tcp::socket socket(io_context);
    boost::asio::connect(socket, endpoints);

    while(true) {
      std::array<char, 256> buff;

      size_t len = socket.read_some(boost::asio::buffer(buff));
      std::cout.write(buff.data(), len);

      len = socket.read_some(boost::asio::buffer(buff));
      std::cout.write(buff.data(), len);

      std::string move_res;

      const std::string success_res = "move proceed successfully\n";

      do {
        std::string move;
        std::getline(std::cin, move);

        boost::asio::write(socket, boost::asio::buffer(move));

        size_t len = socket.read_some(boost::asio::buffer(buff));

        move_res = std::string(buff.data(), len);
        std::cout << move_res << "\n\n";
      } while (move_res != success_res);
    }
  }
  catch (const std::exception& err) {
    std::cerr << err.what() << std::endl;
  }
}
