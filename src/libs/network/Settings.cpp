///*
// * Settings.cpp
// *
// *  Created on: 16 Oct 2017
// *      Author: Vuurvlieg
// */
//
//#include "Settings.h"
//
//#include <string.h>
//#include <stdexcept>
//
//namespace network
//{
//
//	const std::string Settings::kDefaultHostname = {"127.0.0.1"};
//
//	Settings::Settings()
//	: mFClient(false)
//	, mFServer(false)
//	, mPort(0)
//	, mHostname()
//	{
//	}
//
//	void Settings::setServer(const std::string& hostname, uint16_t port)
//	{
//		mFServer = true;
//		mPort = port;
//
//	}
//	void Settings::setClient(const std::string& hostname, uint16_t port)
//	{
//		mFClient = true;
//		mPort = port;
//	}
//
//	void Settings::validate() const
//	{
//		if(!mFServer && !mFClient)
//			throw std::runtime_error("No client or server specified");
//		if(mFServer && mFClient)
//			throw std::runtime_error("Both server and client were specified");
//		if(mPort <= 0)
//			throw std::runtime_error("Invalid port specified");
//		if(mHostname.empty())
//			throw std::runtime_error("Invalid hostname specified");
//	}
//
//	void Settings::fromCommandlineArguments(int argc, char* argv[])
//	{
//		for(int i = 0; i < argc; ++i) {
//			const char* arg = argv[i];
//			const bool hasNext = i + 1 < argc;
//			if(!stricmp(arg, "-s") || !stricmp(arg, "--server"))
//				mFServer = true;
//			else if(!stricmp(arg, "-c") || !stricmp(arg, "--client"))
//				mFClient = true;
//			else if(!stricmp(arg, "-p") && hasNext)
//				mPort = (uint16_t)strtoul(argv[i+1], NULL, 10);
//			else if(!strnicmp(arg, "--port=", 7))
//				mPort = (uint16_t)strtoul(arg + 7, NULL, 10);
//			else if(!stricmp(arg, "-h") && hasNext)
//				mHostname = argv[i+1];
//			else if(!strnicmp(arg, "--host=", 7))
//				mHostname = argv[i+1] + 7;
//
//		}
//
//		if(mFClient || mFServer) {
//			if(!mPort)
//				mPort = kDefaultPort;
//			if(mHostname.empty())
//				mHostname = kDefaultHostname;
//		}
//
//		validate();
//	}
//
//
//	const std::string& Settings::getHostname() const
//	{
//		return mHostname;
//	}
//
//	void Settings::setHostname(const std::string& hostname)
//	{
//		mHostname = hostname;
//	}
//
//	bool Settings::getIsClient() const
//	{
//		return mFClient;
//	}
//
//	bool Settings::getIsServer() const
//	{
//		return mFServer;
//	}
//
//	uint16_t Settings::getPort() const
//	{
//		return mPort;
//	}
//
//	void Settings::setPort(uint16_t port)
//	{
//		mPort = port;
//	}
//
//} /* namespace network */
