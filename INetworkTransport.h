#include <string>

struct TransportEvent
{
	enum class Type
	{
		Data,
		Connect,
		Disconnect
	};
	Type type;
	int connectionId;
	char* data;
	int dataSize;
};

class INetworkTransport
{
public:
	virtual int Connect(std::string ip, int port) = 0;
	virtual void Disconnect(int connectionId) = 0;
	virtual bool NextEvent(TransportEvent& e) = 0;
	virtual void SendData(int connectionId, char* data, int sendSize) = 0;
	virtual std::string GetConnectDescription(int connectionId) = 0;
	virtual void Update() = 0;
	virtual void Shutdown() = 0;
};
