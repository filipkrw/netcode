#include <net_common/olc_net.h>
#include <iostream>

enum class CustomMsgTypes : uint32_t
{
    FireBullet,
    MovePlayer
};

int main()
{
    std::cout << "Hello";
    olc::net::message<CustomMsgTypes> msg;
    msg.header.id = CustomMsgTypes::FireBullet;

    int a = 5;
    bool b = true;
    float c = 2.123;

    struct
    {
        float x;
        float y;
    } d[5];

    msg << a << b << c << d;

    a = 99;
    b = false;
    c = 0.0;

    msg >> d >> c >> b;

    return 0;
}