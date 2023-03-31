#include <iostream>
#include <boost/asio.hpp>
#include <thread>
#include <vector>
#include <mutex>

using boost::asio::ip::udp;

class Server
{
public:
	Server(boost::asio::io_context& io_context, unsigned short port):
		socket_(io_context, udp::endpoint(udp::v4(), port))
	{}
	void start()
	{
		receive();
	}
private:
	
};
