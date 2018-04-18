/*
 * Network.h
 *
 *  Created on: 12 Oct 2017
 *      Author: Vuurvlieg
 */

#ifndef NETWORK_MANAGER_H_
#define NETWORK_MANAGER_H_


#include "Settings.h"
#include "../Singleton.h"

#include <stdint.h>
#include <string.h>
#include <string>
#include <memory>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <atomic>

#ifdef __GNUC__
#	pragma GCC diagnostic push
#	pragma GCC diagnostic ignored "-Wconversion"
#endif

#include <boost/asio.hpp>

#ifdef __GNUC__
#	pragma GCC diagnostic pop
#endif

typedef std::shared_ptr<std::thread> ThreadPtr;


namespace boost  {
	namespace system {
		class error_code;
	}
	namespace asio {
		class io_service;
	}
}

namespace network
{
	using boost::asio::io_service;
	using boost::system::error_code;


	class Server;
	class Client;

	typedef std::shared_ptr<Server> ServerPtr;
	typedef std::shared_ptr<Client> ClientPtr;

	struct IConnectionHandler;
	typedef std::shared_ptr<IConnectionHandler> ConnectionHandlerPtr;

	class Manager : public Singleton<Manager>
	{
	public:

		Manager();
		virtual ~Manager();

		io_service& getIOService() { return *mServicePtr.get(); }

		ClientPtr createClient(ConnectionHandlerPtr handler);
		ServerPtr createServer(ConnectionHandlerPtr handler, uint16_t maxClients);

		ClientPtr getClient() { return mClient; }
		ServerPtr getServer() { return mServer; }


		void runService();
		ThreadPtr runServiceThread();

		void stop();


		// settings
		void setSettings(std::string remoteIpAddress, std::string remotePort, std::string localPort);

		const std::string& 	getRemoteHost() const;
		Manager& 			setRemoteHost(const std::string& host);
		uint16_t 			getRemotePort() const;
		Manager& 			setRemotePort(uint16_t port);
		uint16_t 			getLocalPort() const;
		Manager&			setLocalPort(uint16_t port);

	protected:


		virtual void handleSingnal(error_code& error, int signal);




	protected:
		std::mutex					mMutex;
		std::shared_ptr<io_service> mServicePtr;
		std::unique_ptr<io_service::work> mServicerWorkPtr;
		ThreadPtr					mServiceThread;
		ServerPtr 					mServer;
		ClientPtr 					mClient;
		bool			 			mFStopping;
		bool						mFStopped;

		std::string 				mRemoteHost;
		uint16_t	 				mRemotePort;
		uint16_t	 				mLocalPort;
	};

} // namespace network



#endif /* NETWORK_MANAGER_H_ */
