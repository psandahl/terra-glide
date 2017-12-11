#pragma once

#include <condition_variable>
#include <mutex>
#include <queue>
#include <optional>

template <class Request>
class Link
{
public:
    Link() = default;
    Link(const Link&) = delete;
    Link(const Link&&) = delete;
    ~Link() = default;

    Link& operator=(const Link&) = delete;

    void post(const Request& item) noexcept
    {
        {
            std::lock_guard<std::mutex> lock(m_mutex);
            m_queue.push(item);
        }
        m_cv.notify_one();
    }

    Request receive() noexcept
    {
        std::unique_lock<std::mutex> lock(m_mutex);
        m_cv.wait(lock, [&]() { return !m_queue.empty(); });

        auto val = m_queue.front();
        m_queue.pop();

        lock.unlock();
        m_cv.notify_one();

        return val;
    }

    std::optional<Request> poll() noexcept
    {
        std::unique_lock<std::mutex> lock(m_mutex);

        std::optional<Request> empty;
        std::optional<Request> result = !m_queue.empty() ? m_queue.front() : empty;

        if (!m_queue.empty())
        {
            m_queue.pop();
        }

        lock.unlock();

        return result;
    }

private:
    std::mutex m_mutex;
    std::condition_variable m_cv;
    std::queue<Request> m_queue;
};
