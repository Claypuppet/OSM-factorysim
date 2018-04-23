#include "Manager.h"
#include "Server.h"
#include "Client.h"


#include <stdexcept>
#include <iostream>
#include <thread>
#include <mutex>
#include <memory>
#include <condition_variable>


#include <boost/asio/io_service.hpp>


namespace Network
{

	Manager::Manager()
	: mServicePtr(std::make_shared<io_service>())
	, mServicerWorkPtr(std::unique_ptr<io_service::work>(new io_service::work(*mServicePtr)))
	, mFStopping(false)
	, mFStopped(false)
	, mRemoteHost("127.0.0.1")
	, mRemotePort(12345)
	, mLocalPort(12345)
	{
	}

//	Manager::Manager(const Manager& m)
//	: mServicePtr(std::make_shared<io_service>())
//	, mServicerWorkPtr(std::unique_ptr<io_service::work>(new io_service::work(*mServicePtr)))
//	, mFStopping(false)
//	, mFStopped(false)
//	, mRemoteHost(m.mRemoteHost)
//	, mRemotePort(m.mRemotePort)
//	, mLocalPort(m.mLocalPort)
//	{
//	}

	Manager::~Manager()
	{
	}


	ClientPtr Manager::createClient(ConnectionHandlerPtr handler)
	{
		if(!handler)
			throw std::invalid_argument("handler can't be null");
		std::lock_guard<std::mutex> lockGuard(mMutex);
		if(mFStopped || mFStopping)
			return nullptr;
		if(auto c = mClient) {
			mClient.reset();
			c->stop();
			while(c->isRunning())
				std::this_thread::yield();
		}
		mClient = ClientPtr(new Client(*this, handler, mRemoteHost, mRemotePort));
		return mClient;
	}

	ServerPtr Manager::createServer(ConnectionHandlerPtr handler, uint16_t maxClients=Server::kDefaultMaxClients)
	{
		if(!handler)
			throw std::invalid_argument("handler can't be null");
		std::lock_guard<std::mutex> lockGuard(mMutex);
		if(mFStopped || mFStopping)
			return nullptr;
		if(auto s = mServer) {
			mServer.reset();
			s->stop();
			while(s->isRunning())
				std::this_thread::yield();
		}
		mServer = ServerPtr(new Server(*this, handler, mLocalPort, maxClients));
		return mServer;
	}

	void Manager::stop()
	{
		std::lock_guard<std::mutex> lockGuard(mMutex);
		if(mFStopping || mFStopped)
			return;

		mFStopping = true;
		auto s = mServer;
		auto c = mClient;

		if(s) {
			std::cout << "Stopping server..." << std::endl;
			s->stop();
			mServer.reset();
		}
		if(c) {
			std::cout << "Stopping client..." << std::endl;
			c->stop();
			mClient.reset();
		}

		// busy wait
		if(s) {
			while(s->isRunning())
				std::this_thread::yield();
			std::cout << "Server stopped" << std::endl;
			s.reset();
		}

		if(c) {
			while(c->isRunning())
				std::this_thread::yield();
			std::cout << "Client stopped" << std::endl;
			c.reset();
		}

		if(mServicerWorkPtr)
			mServicerWorkPtr.reset();
		if(mServicePtr) {
			mServicePtr->stop();
			mServicePtr.reset();
		}

		mFStopped = true;
	}

	void Manager::handleSingnal(error_code& error, int signal)
	{
		std::cerr << __PRETTY_FUNCTION__ << " signal: " << signal << " error: " << error.message() << std::endl;
	}

	void Manager::runService()
	{
		auto service = mServicePtr;
		if(!service) // wtf?
			return;

		try {
			std::cout << "Thread with id: " << std::hex << std::this_thread::get_id() << " running Network service" << std::dec << std::endl;
			service->run();
		}
		catch(std::exception& e) {
			std::cerr << __PRETTY_FUNCTION__ << " -> exception: " << e.what() << std::endl;
		}
		catch(...) {
			std::cerr << __PRETTY_FUNCTION__ << " ->  unknown exception" << std::endl;
		}
		std::cout << "Thread with id: " << std::hex << std::this_thread::get_id() << " stopped running Network service" << std::dec << std::endl;
	}

	ThreadPtr Manager::runServiceThread()
	{
		return std::make_shared<std::thread>([this](){ runService();});
	}

	const std::string& Manager::getRemoteHost() const
	{
		return mRemoteHost;
	}

	Manager& Manager::setRemoteHost(const std::string& host)
	{
		return mRemoteHost = host, *this;
	}

	uint16_t Manager::getRemotePort() const
	{
		return mRemotePort;
	}

	Manager& Manager::setRemotePort(uint16_t port)
	{
		return mRemotePort = port, *this;
	}

	uint16_t Manager::getLocalPort() const
	{
		return mLocalPort;
	}

	Manager& Manager::setLocalPort(uint16_t port)
	{
		return mLocalPort = port, *this;
	}

} // namespace Network


