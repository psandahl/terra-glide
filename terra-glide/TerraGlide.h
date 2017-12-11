#pragma once

#include "Event.h"
#include "Link.h"
#include "Viewport.h"
#include <memory>

class TerraGlide
{
public:
    TerraGlide(std::shared_ptr<Link<Event>> events) :
        m_events(events),
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

    std::shared_ptr<Link<Event>> m_events;
    bool m_running;
};
