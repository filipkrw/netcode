#include <iostream>
#include <string>
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

    void MessageAll()
    {
        olc::net::message<CustomMsgTypes> msg;
        msg.header.id = CustomMsgTypes::MessageAll;
        Send(msg);
    }
};

void HandleInput(CustomClient &client)
{
    std::string input;
    while (true)
    {
        std::getline(std::cin, input);

        if (input == "ping")
            client.PingServer();
        if (input == "all")
            client.MessageAll();
    }
}

int main()
{
    CustomClient client;
    client.Connect("127.0.0.1", 60000);

    std::thread io_thread(HandleInput, std::ref(client));

    while (true)
    {
        if (client.IsConnected())
        {
            if (!client.Incoming().empty())
            {
                auto msg = client.Incoming().pop_front().msg;

                switch (msg.header.id)
                {
                case CustomMsgTypes::ServerAccept:
                {
                    std::cout << "[MESSAGE] Server Accepted Connection\n";
                }
                break;

                case CustomMsgTypes::ServerPing:
                {
                    std::chrono::system_clock::time_point timeNow = std::chrono::system_clock::now();
                    std::chrono::system_clock::time_point timeThen;
                    msg >> timeThen;
                    std::cout << "[MESSAGE] Ping: "
                              << std::chrono::duration<double>(timeNow - timeThen).count()
                              << "\n";
                }
                break;

                case CustomMsgTypes::ServerMessage:
                {
                    uint32_t clientID;
                    msg >> clientID;
                    std::cout << "[MESSAGE] Hello from [" << clientID << "]\n";
                }
                break;
                }
            }
        }
    }

    return 0;
}