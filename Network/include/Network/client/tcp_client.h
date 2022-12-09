#pragma once
#include <boost/asio.hpp>
#include <queue>

namespace Test{
    namespace io = boost::asio;
    using MessageHandler = std::function<void(std::string)>;

    class TCPClient {
    public:
        TCPClient(const std::string &address, int port);

        void Run(); //server에서는 start지만 여기에서는 run
        void Stop();
        void Post(const std::string& message);
    
    private:
        void asyncRead();
        void onRead(boost::system::error_code ec, size_t bytesTransferred);
        void asyncWrite();
        void onWrite(boost::system::error_code ec, size_t bytesTransferred);
    
    public:
        MessageHandler OnMessage;

    private:
        io::io_context _ioContext{};
        io::ip::tcp::socket _socket;

        io::ip::tcp::resolver::results_type _endpoints;

        io::streambuf _streamBuf{65536};
        std::queue<std::string> _outgoingMessages{};
/*
    public:
        void makedirectory(const std::string& name);
        void deletedirectory();
        void installpkg(const std::string& pkgName);//인자로 passwd? 아니면 애초에 sudo 권한이 있나?
*/
    };
}