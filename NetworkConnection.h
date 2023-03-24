#include "INetworkDriver.h"

class NetworkConnection
{
public:
	int m_NetworkId;
	int m_NetworkVersion;
	enum class State
	{
		Disconnected,
		Connecting,
		AwaitingResponse,
		Connected
	};

	template <typename T>
	int Disconnect(T& driver)
	{
		return driver.Disconnect(*this);
	}
	template <typename T>
	NetworkEvent::Type PopEevnt(T& driver, DataStreamReader& stream)
	{
		return driver.PopEventForConnection(*this, stream);
	}
	template <typename T>
	int send(T& driver, DataStreamWriter& bs)
	{
		return driver.Send(*this, bs);
	}

	template <typename T>
	int Close(T& driver)
	{
		if(m_NetworkId >= 0)
			return driver.Disconnect(*this);
		return -1;
	}
	bool IsCreated() const 
	{
		return m_NetworkVersion != 0;
	}
	template <typename T>
	State GetState(T& driver)
	{
		return driver.GetConnectionState(*this);
	}
	bool operator==(const NetworkConnection& rhs) const
	{
		return m_NetworkId == rhs.m_NetworkId && m_NetworkVersion == rhs.m_NetworkVersion;
	}
	bool operator !=(const NetworkConnection& rhs) const
	{
		return !(*this == rhs);
	}
	int GetHashCode() const
	{
		return (m_NetworkId << 8) ^ m_NetworkVersion;
	}
	int InternalId() const
	{
		return m_NetworkId;
	}
};
