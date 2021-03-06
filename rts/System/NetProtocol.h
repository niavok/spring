/* This file is part of the Spring engine (GPL v2 or later), see LICENSE.html */

#ifndef NET_PROTOCOL_H
#define NET_PROTOCOL_H

#include <string>
#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>

#include "System/BaseNetProtocol.h" // not used in here, but in all files including this one

class CDemoRecorder;
namespace netcode
{
	class RawPacket;
	class CConnection;
}

/**
 * @brief Client interface for handling communication with the game server.
 *
 * Even when playing singleplayer, this is the way of communicating
 * with the server. It keeps the connection alive,
 * and is able to send and receive raw binary packets transparently
 * over the network.
*/
class CNetProtocol
{
public:
	CNetProtocol();
	~CNetProtocol();

	/**
	 * @brief Initialise in client mode (remote server)
	*/
	void InitClient(const char* server, unsigned portnum, const std::string& myName, const std::string& myPasswd, const std::string& myVersion);

	/**
	 * @brief Initialise in client mode (local server)
	 */
	void InitLocalClient();

	/// Are we still connected (or did the connection time-out)?
	bool CheckTimeout(int nsecs = 0, bool initial = false) const;

	void AttemptReconnect(const std::string& myName, const std::string& myPasswd, const std::string& myVersion);

	bool NeedsReconnect();

	/// This checks if any data has been received yet
	bool Connected() const;

	std::string ConnectionStr() const;

	/**
	 * @brief Take a look at the messages in the recieve buffer (read-only)
	 * @return A RawPacket holding the data, or 0 if no data
	 * @param ahead How many packets to look ahead. A typical usage would be:
	 * for (int ahead = 0; (packet = net->Peek(ahead)) != NULL; ++ahead) {}
	 */
	boost::shared_ptr<const netcode::RawPacket> Peek(unsigned ahead) const;

	/**
	 * @brief Deletes a packet from the buffer
	 * @param index queue index number
	 * useful for messages that skips queuing and needs to be processed immediately
	 */
	void DeleteBufferPacketAt(unsigned index);

	/**
	 * @brief Receive a single message (and remove it from the recieve buffer)
	 * @return The first data packet from the buffer, or 0 if there is no data
	 *
	 * Receives only one message at a time
	 * (even if there are more in the recieve buffer),
	 * so call this until you get a 0 in return.
	 * When a demo recorder is present it will be recorded.
	 */
	boost::shared_ptr<const netcode::RawPacket> GetData(int framenum);

	/**
	 * @brief Send a message to the server
	 */
	void Send(boost::shared_ptr<const netcode::RawPacket> pkt);
	/// @overload
	void Send(const netcode::RawPacket* pkt);

	CDemoRecorder* GetDemoRecorder() const { return record.get(); }

	/**
	 * Updates our network while the game loads to prevent timeouts.
	 * Runs until \a loading is false.
	 */
	void UpdateLoop();

	/// Must be called to send / recieve packets
	void Update();

	void DisableDemoRecording();


	volatile bool loading;

private:
	boost::scoped_ptr<netcode::CConnection> serverConn;
	boost::scoped_ptr<CDemoRecorder> record;
	bool disableDemo;
};

extern CNetProtocol* net;

#endif // NET_PROTOCOL_H

