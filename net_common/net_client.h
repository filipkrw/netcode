#pragma once

#include "net_common.h"
#include "net_tsqueue.h"
#include "net_message.h"
#include "net_connection.h"

namespace olc
{
    namespace net
    {
        template <typename T>
        class client_interface
        {
        protected:
            client_interface() : m_socket(m_context) {}

            virtual ~client_interface()
            {
                Disconnect();
            }

        public:
            bool Connect(const std::string &host, const uint16_t port)
            {
                try
                {
                    // Resolve hostname/ip-address into tangiable physical address
                    asio::ip::tcp::resolver resolver(m_context);
                    asio::ip::tcp::resolver::results_type endpoints = resolver.resolve(host, std::to_string(port));

                    // Create connection
                    m_connection = std::make_unique<connection<T>>(connection<T>::owner::client, m_context, asio::ip::tcp::socket(m_context), m_qMessagesIn);

                    // Tell the connection object to connect to server
                    m_connection->ConnectToServer(endpoints);

                    // Start Context Thread
                    thrContext = std::thread([this]()
                                             { m_context.run(); });
                }
                catch (std::exception &e)
                {
                    std::cerr << "Client Exception: " << e.what() << "\n";
                    return false;
                }

                return true;
            }

            void Disconnect()
            {
                if (IsConnected())
                {
                    m_connection->Disconnect();
                }

                m_context.stop();
                if (thrContext.joinable())
                    thrContext.join(); // close thread?

                m_connection.release();
            }

            bool IsConnected()
            {
                if (m_connection)
                    return m_connection->IsConnected();
                else
                    return false;
                return false;
            }

            void Send(const message<T> &msg)
            {
                if (IsConnected())
                    m_connection->Send(msg);
            }

            tsqueue<owned_message<T>> &Incoming()
            {
                return m_qMessagesIn;
            }

        protected:
            asio::io_context m_context;
            std::thread thrContext;
            asio::ip::tcp::socket m_socket;
            std::unique_ptr<connection<T>> m_connection;

        private:
            tsqueue<owned_message<T>> m_qMessagesIn;
        };
    };
}