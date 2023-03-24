#include <iostream>
#include <cstring>
#include <algorithm>
#include <stdexcept>

union UIntFloat
{
	float floatValue;
	uint32_t intValue;
	double doubleValue;
	uint64_t longValue;
};
struct StreamData
{
	char* buffer;
	int length;
	int position;
};
class DataStreamWriter
{
public:
	DataStreamWriter(int length)
	{
		m_writer = new StreamData();
		m_writer->buffer = new char[length];
		m_writer->length = length;
		m_writer->position = 0;
	}
	~DataStreamWriter()
	{
		delete[] m_writer->buffer;
		delete m_writer;
	}

	template<typename T>
	struct Deferred
	{
		Deferred(DataStreamWriter* writer, int size)
		{
			m_writer = writer->m_writer;
			m_position = m_writer->position;
			m_size = size;
			m_value = new T();
		}
		~Deferred()
		{
			delete m_value;
		}

		void Update(T value)
		{
			*m_value = value;
			std::memcpy(m_writer->buffer + m_position, m_value, m_size);
			m_writer->position += m_size;
		}
	private:
		StreamData* m_writer;
		int m_position;
		int m_size;
		T* m_value;
	};
	template<typename T>
	using DeferredNetworkByteOrder = Deferred<T>;
	
	void Write(char value)
	{
		m_writer->buffer[m_writer->position++] = value;
	}
	void Write(short value)
	{
		Deferred<short>(this, sizeof(short)).Update(value);
	}
	void Write(unsigned short value)
	{
		Deferred<unsigned short>(this, sizeof(unsigned short)).Update(value);
	}
	void Write(int value)
	{
		Deferred<int>(this, sizeof(int)).Update(value);
	}
	void Write(unsigned int value)
	{
		Deferred<unsigned int>(this, sizeof(unsigned int)).Update(value);
	}
	void Write(float value)
	{
		Deferred<float>(this, sizeof(float)).Update(value);
	}
	void WriteNetworkByteOrder(short value)
	{
		DeferredNetworkByteOrder<short>(this, sizeof(short)).Update(value);
	}

	void WriteNetworkByteOrder(unsigned short value)
	{
		DeferredNetworkByteOrder<unsigned short>(this, sizeof(unsigned short)).Update(value);
	}

	void WriteNetworkBtyeOrder(int value)
	{
		DeferredNetworkByteOrder<int>(this, sizeof(int)).Update(value);
	}
	void WriteNetworkByteOrder(unsigned int value)
	{
		DeferredNetworkByteOrder<unsigned int>(this, sizeof(unsigned int)).Update(value);
	}
	void WriteNetworkByteOrder(float value)
	{
		DeferredNetworkByteOrder<float>(this, sizeof(float)).Update(value);
	}
	int GetCapacity()
	{
		return m_writer->length;
	}
	void SetCapacity(int capacity)
	{
		char* newBuffer = new char[capacity];
		std::memcpy(newBuffer, m_writer->buffer, std::min(m_writer->length, capacity));
		delete[] m_writer->buffer;
		m_writer->length = capacity;
	}
	bool IsCreated()
	{
		return m_writer != nullptr;
	}
private:
	StreamData* m_writer;
};
class DataStreamReader
{
	struct Context
	{
		char* buffer;
		size_t offset;
		size_t length;
	} context;

	DataStreamReader(char* buffer, int offset, int length)
	{
		if(offset + length > std::strlen(buffer))
		{
			throw std::out_of_range("Invalid offset or length");
		}
		context.buffer = buffer;
		context.offset = offset;
		context.length = length;
	}
	void ReadBytes(char* dest, size_t count)
	{
		if(context.offset + count > context.length)
		{
			throw std::out_of_range("Read past end of buffer");
		}
		std::memcpy(dest, context.buffer + context.offset, count);
		context.offset += count;
	}
	char ReadByte()
	{
		char value;
		ReadBytes(&value, sizeof(value));
		return value;
	}
	short ReadShort()
	{
		short value;
		ReadBytes(reinterpret_cast<char*>(&value), sizeof(value));
		return value;
	}
	int ReadInt()
	{
		int value;
		ReadBytes(reinterpret_cast<char*>(&value), sizeof(value));
		return value;
	}

	float ReadFloat()
	{
		UIntFloat value;
		ReadBytes(reinterpret_cast<char*>(&value.intValue), sizeof(value.intValue));
		return value.floatValue;
	}
	char ReadNetworkByte()
	{
		return ReadByte();
	}
	short ReadNetworkShort()
	{
		short value = ReadShort();
		return (value << 8) | ((value >> 8) & 0xFF);
	}
	int ReadNetworkInt()
	{
		int value = ReadInt();
		return (value << 24) | ((value << 8) & 0xFF0000) | ((value >> 8) & 0xFF00) | ((value >> 24) & 0xFF);
	}
};
