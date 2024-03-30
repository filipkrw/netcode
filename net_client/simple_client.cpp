#include <olc_net.h>
#include <net_client.h>
#include <iostream>

enum class CustomMsgTypes : uint32_t
{
    FireBullet,
    MovePlayer
};

class CustomClient : public olc::net::client_interface<CustomMsgTypes>
{
public:
    CustomClient() {}

    bool FireBullet(float x, float y)
    {
        olc::net::message<CustomMsgTypes> msg;
        msg.header.id = CustomMsgTypes::FireBullet;
        msg << x << y;
        Send(msg);
        return true;
    };

    bool Send(const olc::net::message<CustomMsgTypes> &msg)
    {
        std::cout << msg;
        return true;
    }
};

int main()
{
    CustomClient c;
    // c.Connect("community.onelonecoder.com", 60000);
    c.FireBullet(2.0f, 5.0f);
    return 0;
}