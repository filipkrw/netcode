#pragma once
#include "net_common.h"

namespace olc
{
    namespace net
    {
        template <typename T>
        class tsqueue
        {
        public:
            tsqueue() = default;
            tsqueue(const tsqueue<T> &) = delete;
            virtual ~tsqueue() { clear(); }

            const T &front()
            {
                std::scoped_lock lock(muxQueue);
                return deqQueue.front();
            }

            const T &back()
            {
                std::scoped_lock lock(muxQueue);
                return deqQueue.back();
            }

            void push_back(const T &item)
            {
                std::scoped_lock lock(muxQueue);
                deqQueue.emplace_back(std::move(item));
            }

            void push_front(const T &item)
            {
                std::scoped_lock lock(muxQueue);
                deqQueue.emplace_front(std::move(item));
            }

            void empty()
            {
                std::scoped_lock lock(muxQueue);
                deqQueue.empty();
            }

            size_t count()
            {
                std::scoped_lock lock(muxQueue);
                deqQueue.size();
            }

            void clear()
            {
                std::scoped_lock lock(muxQueue);
                deqQueue.clear();
            }

            T pop_front()
            {
                std::scoped_lock lock(muxQueue);
                auto t = std::move(deqQueue.front());
                deqQueue.pop_front();
                return t;
            }

        protected:
            std::mutex muxQueue;
            std::deque<T> deqQueue;
        };
    };
}