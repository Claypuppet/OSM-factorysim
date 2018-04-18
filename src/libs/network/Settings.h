///*
// * Settings.h
// *
// *  Created on: 16 Oct 2017
// *      Author: Vuurvlieg
// */
//
//#ifndef NETWORK_SETTINGS_H_
//#define NETWORK_SETTINGS_H_
//
//#include <stdint.h>
//#include <string>
//
//namespace network
//{
//
//	struct Settings
//	{
//
//		static const std::string kDefaultHostname;
//		static const uint32_t kDefaultPort = 12345;
//
//		Settings();
//		~Settings() = default;
//
//
//		void 					setServer(const std::string& hostname, uint16_t port=kDefaultPort);
//		void 					setClient(const std::string& hostname, uint16_t port=kDefaultPort);
//
//		void 					validate() const;
//
//		void 					fromCommandlineArguments(int argc, char* argv[]);
//
//		const std::string& 		getHostname() const;
//		void					setHostname(const std::string& hostname);
//
//		bool 					getIsClient() const;
//		bool 					getIsServer() const;
//
//		uint16_t 				getPort() const;
//		void					setPort(uint16_t port);
//
//	private:
//
//		bool mFClient : 1;
//		bool mFServer : 1;
//		uint16_t mPort;
//		std::string mHostname;
//	};
//
//} /* namespace network */
//
//#endif /* NETWORK_SETTINGS_H_ */
