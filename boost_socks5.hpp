#include <cstdlib>
#include <iostream>
#include <string>
#include <memory>
#include <utility>
#include <fstream>

#include "trace.hpp"
#include "utils.hpp"
using namespace my_utils;

#include <boost/asio.hpp>
using boost::asio::ip::tcp;

namespace boost_socks
{
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
class Session : public std::enable_shared_from_this<Session>
{
public:
	Session(tcp::socket in_socket, unsigned session_id, size_t buffer_size, short verbose);
	void start();

private:

	void read_socks5_handshake();
	void write_socks5_handshake();
	void read_socks5_request();
	void do_resolve();
	void do_connect(tcp::resolver::iterator& it);
	void write_socks5_response();
	void do_read(int direction);
	void do_write(int direction, std::size_t Length);

	tcp::socket in_socket_;
	tcp::socket out_socket_;
	tcp::resolver resolver;

	std::string remote_host_;
	std::string remote_port_;
	std::vector<char> in_buf_;
	std::vector<char> out_buf_;
	int session_id_;
	short verbose_;
};

//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
class Server
{
public:
	Server(boost::asio::io_service& io_service, short port, unsigned buffer_size, short verbose);

private:
	void do_accept();

	tcp::acceptor acceptor_;
	tcp::socket in_socket_;
	size_t buffer_size_;
	short verbose_;
	unsigned session_id_;
};

//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
class SocksProxy {
public:
  static int run(int argc, char* argv[]);
};
}
