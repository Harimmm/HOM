#include <iostream>
#include <Network/server/tcp_server.h>

int main(int argc, char* argv[]){
    Test::TCPServer server{Test::IPV::V4, 1337};

	server.OnJoin = [](Test::TCPConnection::pointer server){
		std::cout<<"User has joined the server: " <<server->GetUsername() << std::endl;
	};
	server.OnLeave = [](Test::TCPConnection::pointer server){
		std::cout<<"User has left the server: " <<server->GetUsername() << std::endl;
	};
	server.OnClientMessage = [&server](const std::string& message){
		//Parse the message
		//Do server things
		//Send message to client 등등 그런거 여기에서 함
		server.Broadcast(message);

		//parse
		std::string text=server.ParseMessage(message);
		std::cout<<"This is the message: "<<text<<std::endl;
		server.Task(text);

	};
	//server.GetDevices();
    server.Run();

    return 0;
}
