#include <iostream>
#include <olc_net.h>

enum class CustomMsgTypes : uint32_t
{
    ServerAccept,
    ServerDeny,
    ServerPing,
    MessageAll,
    ServerMessage
};

class CustomClient : public olc::net::client_interface<CustomMsgTypes>
{
public:
    void PingServer()
    {
        olc::net::message<CustomMsgTypes> msg;
        msg.header.id = CustomMsgTypes::ServerPing;

        std::chrono::system_clock::time_point timeNow = std::chrono::system_clock::now();

        msg << timeNow;
        Send(msg);
    }
};

int main()
{
    CustomClient c;
    c.Connect("127.0.0.1", 60000);

    while (true)
    {
        if (c.IsConnected())
        {
            c.PingServer();
            std::this_thread::sleep_for(std::chrono::seconds(60));
            break;
        }
    }

    return 0;
}