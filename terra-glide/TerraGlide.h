#pragma once

#include "Event.h"
#include "Link.h"
#include "Request.h"
#include "Viewport.h"
#include <memory>

class TerraGlide
{
public:
    TerraGlide(std::shared_ptr<Link<Event>> events,
               std::shared_ptr<Link<StopRequest>> stopRequests) :
        m_events(events),
        m_stopRequests(stopRequests),
        dummy(0),
        m_running(true)
    {
    }

    TerraGlide(const TerraGlide&) = delete;
    TerraGlide(const TerraGlide&&) = delete;
    ~TerraGlide() = default;

    TerraGlide& operator=(const TerraGlide&) = delete;

    void run() noexcept;

private:
    void frame(const Viewport& viewport, double duration) noexcept;
    void stop() noexcept;

    std::shared_ptr<Link<Event>> m_events;
    std::shared_ptr<Link<StopRequest>> m_stopRequests;
    int dummy;
    bool m_running;
};
