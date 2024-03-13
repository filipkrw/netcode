#include <iostream>
#include <chrono>

#define ASIO_STANDALONE
#include <asio.hpp>
#include <asio/ts/buffer.hpp>
#include <asio/ts/internet.hpp>

#include <net_common/olc_net.h>

std::vector<char> vBuffer(20 * 1024);

enum class CustomMsgTypes : uint32_t
{
    FireBullet,
    MovePlayer
};

int main()
{
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

    msg >> d >> c >> b >> a;

    return 0;
}

// void GrabSomeData(asio::ip::tcp::socket &socket)
// {
//     socket.async_read_some(
//         asio::buffer(vBuffer.data(), vBuffer.size()),
//         [&](std::error_code ec, std::size_t length)
//         {
//             if (!ec)
//             {
//                 std::cout << "\n\nRead " << length << " bytes\n\n";

//                 for (int i = 0; i < length; i++)
//                 {
//                     std::cout << vBuffer[i];
//                 }

//                 GrabSomeData(socket);
//             }
//         });
// }

// int main()
// {
//     asio::error_code ec;
//     asio::io_context context;
//     asio::io_context::work idleWork(context);

//     std::thread thrContext = std::thread([&]()
//                                          { context.run(); });

//     asio::ip::tcp::endpoint endpoint(asio::ip::make_address("93.184.216.34", ec), 80);
//     asio::ip::tcp::socket socket(context);

//     socket.connect(endpoint, ec);

//     if (!ec)
//     {
//         std::cout << "Connected!" << std::endl;
//     }
//     else
//     {
//         std::cout << "Failed to connect to address:\n"
//                   << ec.message() << std::endl;
//     }

//     if (socket.is_open())
//     {
//         GrabSomeData(socket);

//         std::string request = "GET /index.html HTTP/1.1\r\n"
//                               "Host: example.com\r\n"
//                               "Connection: close\r\n\r\n";

//         socket.write_some(asio::buffer(request.data(), request.size()), ec);

//         using namespace std::chrono_literals;
//         std::this_thread::sleep_for(5000ms);

//         context.stop();

//         if (thrContext.joinable())
//         {
//             thrContext.join();
//         }
//     }

//     return 0;
// }