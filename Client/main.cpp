#include <iostream>
#include <Network/client/tcp_client.h>
#include <thread>

using namespace Test;

int main(int argc, char* argv[]){
	TCPClient client {"localhost", 1337}; /*192.168.122.161*/ 

	client.OnMessage = [](const std::string& message){
		std::cout << message;
	};

	std::thread t{[&client] () {client.Run();}};

	while(true){
		std::string message;
		std::string name;
		getline(std::cin, message);

		if(message == "\\q") break;
		
		/*
		if(message == "mkdir") {
			std::cout<< "Directory name to create: ";
			getline(std::cin, name);
			client.makedirectory(name);
		}
		if(message=="rm -rf") client.deletedirectory();
		if(message=="install") {
			std::cout<<"Package name to install: ";
			getline(std::cin, name);
			client.installpkg(name);
		}
		*/
		message += "\n";

		client.Post(message);
	}
	client.Stop();
	t.join();
	return 0;
/*
	try {
		boost::asio::io_context ioContext; //create ioContext

		tcp::resolver resolver {ioContext}; //create resolver to resolve the hostname, connection string
		auto endpoints = resolver.resolve("127.0.0.1", "1337"); //server에서 1337 포트로 열어뒀음

		tcp::socket socket { ioContext }; //creaete socket
		boost::asio::connect(socket, endpoints); //connect socket

		//if connection success
		while(true) {
			//Listen for messages
			std::array<char, 128> buf {};
			boost::system::error_code error;
			
			size_t len = socket.read_some(boost::asio::buffer(buf), error);

			if(error == boost::asio::error::eof) {
				//Clean connection cut off
				break;
			} else if (error){
				throw boost::system::system_error(error);
			}

			std::cout.write(buf.data(), len);
		}

	} catch(std::exception& e){
		std::cerr << e.what() <<std::endl;
	}
	return 0;
*/
}