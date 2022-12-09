#include "Network/server/tcp_server.h"
#include <iostream>
#include <systemd/sd-bus.h>

namespace Test { 
    //생성자
    using boost::asio::ip::tcp;
    TCPServer::TCPServer(IPV ipv, int port) : _ipVersion(ipv), _port(port), 
        _acceptor (_ioContext, tcp::endpoint(_ipVersion == IPV::V4 ? tcp::v4() : tcp::v6(), _port)){
    }

    //server run
    int TCPServer::Run(){
        try{
            startAccept();
            _ioContext.run();
        } catch (std::exception& e){
		    std::cerr << e.what() <<std::endl;
            return -1;
        }
        return 0;
    }
    
    //client들에게 전체 메세지 전달
    void TCPServer::Broadcast(const std::string& message){
            for(auto& connection : _connections){
                connection -> Post(message);
            }
    }
    std::string TCPServer::ParseMessage(const std::string& message){
        std::size_t pos = message.rfind(' ');
        std::string text = message.substr(pos+1);
        return text;
    }

    void TCPServer::Task(const std::string& message){
        /*using dbus*/
        service(message);      

        /*resource file read*/



        /*dnf cli*/
    }

    void TCPServer::startAccept(){ 
        _socket.emplace(_ioContext);

        _acceptor.async_accept(*_socket, [this](const boost::system::error_code& error){
            auto connection = TCPConnection::Create(std::move(*_socket));

            if(OnJoin){
                OnJoin(connection);
            }

            _connections.insert(connection);
            if (!error){
                connection->Start(
                    [this](const std::string& message) { if(OnClientMessage) OnClientMessage(message); },
                    [&, weak = std::weak_ptr(connection)]{
                        if(auto shared = weak.lock(); shared && _connections.erase(shared)){
                            if(OnLeave) OnLeave(shared);
                        }
                    }

                );
            }
            startAccept();
        });
    }
}