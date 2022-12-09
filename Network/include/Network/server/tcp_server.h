#pragma once
#include <boost/asio.hpp>
#include <Network/server/tcp_connetcion.h>
#include <functional>
#include <optional>
#include <unordered_set>
#include <systemd/sd-bus.h>
#include "Network/server/dbus.h"

namespace Test{
    namespace io = boost::asio;

    enum class IPV {
        V4,
        V6
    };

    class TCPServer{
        using OnJoinHandler = std::function<void(TCPConnection::pointer)>;
        using OnLeaveHandler = std::function<void(TCPConnection::pointer)>;
        using OnClientMessageHandler = std::function<void(std::string)>;

    public:
        TCPServer(IPV ipv, int port);

        int Run();
        void Broadcast(const std::string& message);
        std::string ParseMessage(const std::string& message);
        void Task(const std::string& message);

    private:
        void startAccept();

    public:
        OnJoinHandler OnJoin;
        OnLeaveHandler OnLeave;
        OnClientMessageHandler OnClientMessage;
        
    private:
        IPV _ipVersion;
        int _port;

        io::io_context _ioContext;
        io::ip::tcp::acceptor _acceptor;

        std::optional<io::ip::tcp::socket> _socket;
        std::unordered_set<TCPConnection::pointer> _connections {};

/*
    public:
        void GetDevices();
        void makedirectory(const std::string& name);
        void deletedirectory();
        void installpkg(const std::string& pkgName);//인자로 passwd? 아니면 애초에 sudo 권한이 있나?
*/
    };


}