#pragma once

#include "net_common.h"
#include "net_tsqueue.h"
#include "net_message.h"

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
                // try
                // {
                // m_connection = std::make_unique<connection<T>>(); // TODO
                //     asio::ip::tcp::resolver resolver(m_context);
                //     m_endpoints = resolver.resolve(host, std::to_string(port));

                //     m_connection->ClientToServer(m_endpoints);

                //     thrContext = std::thread([this]()
                //                              { m_conext.run(); });
                // }
                // catch (std::exception &e)
                // {
                //     std::cerr << "Client Exception: " << e.what() << "\n";
                //     return false;
                // }

                return true;
            }

            void Disconnect()
            {
                if (IsConnected())
                {
                    // m_connection->Disconnect();
                }

                m_context.stop();
                if (thrContext.joinable())
                    thrContext.join(); // close thread?

                // m_connection.release();
            }

            bool IsConnected()
            {
                // if (m_connection)
                //     // return m_connection->IsConnected();
                //     std::cout << "Hello";
                // else
                //     return false;
                return false;
            }

            tsqueue<owned_message<T>> &Incoming()
            {
                // return m_qMessagesIn;
                return nullptr;
            }

        protected:
            asio::io_context m_context;
            std::thread thrContext;
            asio::ip::tcp::socket m_socket;
            // std::unique_ptr<connection<T>> m_connection;

        private:
            tsqueue<owned_message<T>> m_qMessagesIn;
        };
    };
}