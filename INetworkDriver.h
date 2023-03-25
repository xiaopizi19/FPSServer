#ifndef INetworkDriver_H_
#define INetworkDriver_H_

#include <memory>
#include <vector>
#include <cstring>
#include <cstdint>

class DataStreamReader;
class DataStreamWriter;

enum class ConnectionState
{
	Disconnected,
	Connecting,
	Connected,
	Disconnecting,
};

struct NetworkEndPoint
{
	uint32_t address;
	uint16_t port;
};

class NetworkEvent
{
public:
	enum class Type
	{
		Empty,
		Connect,
		Disconnect,
		Data,
	};
	NetworkEvent(Type type, NetworkConnection connection, DataStreamReader& stream)
	:m_Type(type), m_Connection(connection),m_Stream(stream){}
	Type GetType()const {return m_Type;}
	NetworkConnection GetConnection() const {return m_Connection;}
	const DataStreamReader& GetStream() const {return m_Stream;}
private:
	Type m_Type;
	NetworkConnection m_Connection;
	DataStreamReader& m_Stream;

};

class NetworkConnection
{
public:
	NetworkConnection(uint32_t id) : m_Id(id), m_State(ConnectionState::Disconnected){}
	uint32_t GetId() const {return m_Id;}
	ConnectionState GetState() const {return m_State;}
	void SetState(ConnectionState state){m_State = state;}
	NetworkEndPoint GetRemoteEndpoint() const {return m_RemoteEndPoint;}
	void SetRemoteEndPoint(NetworkEndPoint endPoint) {m_RemoteEndPoint = endPoint;}
private:
	uint32_t m_Id;
	ConnectionState m_State;
	NetworkEndPoint m_RemoteEndPoint;
};

class INetworkDriver
{
public:
	virtual ~INetworkDriver(){}
	virtual int Bind(NetworkEndPoint endpoint) = 0;
	virtual int Listen() = 0;
	virtual std::shared_ptr<NetworkConnection> Accept()= 0;
	virtual std::shared_ptr<NetworkConnection> Connect(NetworkEndPoint endpoint) = 0;
	virtual int Disconnect(std::shared_ptr<NetworkConnection> connection) = 0;
	virtual ConnectionState GetConnectionState(std::shared_ptr<NetworkConnection> connection) = 0;
	virtual NetworkEndPoint GetLocalEndPoint() const = 0;
	virtual int Send(std::shared_ptr<NetworkConnection> connection, const DataStreamWriter& stream) = 0;
	virtual NetworkEvent PopEvent() = 0;
	virtual NetworkEvent PopEventForConnection(std::shared_ptr<NetworkConnection> connection) = 0;
};

#endif 

