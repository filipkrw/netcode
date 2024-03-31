#include <atomic>
#include <thread>
#include <iostream>
#include <mutex>
#include <condition_variable>
#include <string>

std::mutex mutex;
std::condition_variable cv;
std::string shared_input;
bool is_processing = false;

void ReadInput(std::atomic<bool> &is_running)
{
    while (is_running.load())
    {
        std::string input;
        std::cin >> input;

        {
            std::lock_guard<std::mutex> lock(mutex);
            shared_input = input;
            is_processing = true;
        }

        cv.notify_one();

        if (input == "q")
            is_running.store(false);
    }
}

int main()
{
    std::atomic<bool> is_running(true);
    std::thread io_thread(ReadInput, std::ref(is_running));

    while (is_running.load())
    {
        std::unique_lock<std::mutex> lock(mutex);
        cv.wait(lock, []
                { return is_processing; });

        if (!is_running.load())
            break;

        std::cout << "Main Thread processing shared data: " << shared_input << std::endl;
        is_processing = false;
    }

    if (io_thread.joinable())
        io_thread.join();

    return 0;
}
