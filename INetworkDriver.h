#include <memory>
#include <function>
#include <iostream>
#include <cstring>

class INetworkDriver
{
public:
	virtual ~INetworkDriver() = default;
	virtual int Bind(NetworkEndPoint endpoint) = 0;
	virtual int Listen() = 0;
	virtual NetworkConnection Accept() = 0;
	virtual NetworkConnection Connect(NetworkEndPoint endpoint) = 0;
	virtual int Disconnect(NetworkConnection con) = 0;
	virtual NetworkConnection::State GetConnectState(NetworkConnection con) = 0;
	virtual NetworkEndPoint RemoteEndPoint(NetworkConnection con) = 0;
	virtual NetworkEndPoint LocalEndPoint() = 0;
	virtual int Send(NetworkConnection con, DataStreamWriter strm) = 0;
	virtual int Send(NetworkConnection con, const void* data, int len) = 0;
	virtual NetworkEvent::Type PopEvent(NetworkConnection& con, DataStreamReader& bs) = 0;
	virtual NetWorkEvent::Type PopEventForConnection(NetworkConnection con, DataStreamReader& bs) = 0;
	
};
