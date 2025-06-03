#include "game.h"

#include <boost/asio.hpp>

#include <ctime>
#include <iostream>
#include <string>


using namespace chess;
using boost::asio::ip::tcp;


int main() {
  try {
    boost::asio::io_context io_context;
    tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), 13));

    while (true) {
      Game game;

      std::cout << "## Waiting for player ##\n\n";

      tcp::socket socket(io_context);
      acceptor.accept(socket);

      while (true) {
        std::string message = game.print() + "\nopponent's turn:\n\n";
        boost::asio::write(socket, boost::asio::buffer(message));
        std::cout << (game.print() + "\nyour turn:\n\n");

        std::string host_move;
        std::string host_move_res;

        do {
          std::getline(std::cin, host_move);

          host_move_res = game.processMove(host_move);
          std::cout << host_move_res << '\n';
        } while (host_move_res != "move proceed successfully");

        message = host_move + "\n\n" + game.print() + "\nyour turn:\n\n";
        boost::asio::write(socket, boost::asio::buffer(message));
        std::cout << (game.print() + "\nopponent's turn:\n\n");

        std::string opponent_move;
        std::string opponent_move_res;

        do {
          std::array<char, 256> buff;
          size_t len = socket.read_some(boost::asio::buffer(buff));

          opponent_move = std::string(buff.data(), len);
          opponent_move_res = game.processMove(opponent_move);

          boost::asio::write(socket, boost::asio::buffer(opponent_move_res));
        } while (opponent_move_res != "move proceed successfully");

        std::cout << opponent_move << "\n\n";
      }
    }
  } catch (const std::exception& err) {
    std::cerr << err.what() << std::endl;
  }

  return 0;
}
