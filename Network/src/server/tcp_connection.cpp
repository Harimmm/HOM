#include "Network/server/tcp_connetcion.h"
#include <iostream>



namespace Test{
    TCPConnection::TCPConnection(io::ip::tcp::socket&& socket) : _socket(std::move(socket)){ //move를 사용해 && 타입으로 변환해준것
        boost::system::error_code ec;

        std::stringstream name;
        name << _socket.remote_endpoint();
        _username = name.str();
    }

    void TCPConnection::Start(MessageHandler&& messageHandler, ErrorHandler&& errorHandler){
        _messageHandler = std::move(messageHandler);
        _errorHandler = std::move(errorHandler);
        asyncRead();
    }

    void TCPConnection::Post(const std:: string &message){ 
        bool queueIdle = _outgoingMessage.empty();
        _outgoingMessage.push(message); //queue에 메세지를 넣어줌

        if(queueIdle){ 
            asyncWrite(); //queue가 idle이면 write를 시작한다
        }
    }

    void TCPConnection::asyncRead(){
        io::async_read_until(_socket, _streamBuf, "\n", [self = shared_from_this()]
            (boost::system::error_code ec, size_t bytesTransferred){
                self->onRead(ec, bytesTransferred);
        });
    }

    void TCPConnection::onRead(boost::system::error_code ec, size_t bytesTransferred){
        if(ec){
            _socket.close(ec);   
            _errorHandler();
            return;
        }

        std::stringstream message;
        message <<_username <<": "<< std::istream(&_streamBuf).rdbuf();
        _streamBuf.consume(bytesTransferred);

        std::cout << message.str();

        _messageHandler(message.str());
        asyncRead();
    }

    void TCPConnection::asyncWrite(){
                io::async_write(_socket, io::buffer(_outgoingMessage.front()), [self = shared_from_this()]
                    (boost::system::error_code ec, size_t bytesTransffered){
                        self->onWrite(ec, bytesTransffered);
        });
    }

    void TCPConnection::onWrite(boost::system::error_code ec, size_t bytesTransferred){
        if(ec){
            _socket.close(ec);
            
            _errorHandler();
            return;
        }
        
        _outgoingMessage.pop();

        if(!_outgoingMessage.empty()){
            asyncWrite();
        }
    }
}