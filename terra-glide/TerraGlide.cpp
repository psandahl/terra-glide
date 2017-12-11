#include "Event.h"
#include "Link.h"
#include "TerraGlide.h"
#include "Viewport.h"
#include <iostream>

void TerraGlide::run() noexcept
{
    while (m_running)
    {
        Event&& event = m_events->receive();
        switch (event.eventType)
        {
        case EventType::Frame:
        {
            auto viewport = std::make_tuple(event.eventData.frameData.width, event.eventData.frameData.height);
            frame(viewport, event.eventData.frameData.frameDuration);
        }
            break;

        case EventType::Quit:
            std::cout << "TerraGlide::run(). Quit" << std::endl;
            m_running = false;
            break;

        default:
            std::cout << "TerraGlide::run(): unknown eventType" << std::endl;
            break;
        }
    }
}

void TerraGlide::frame(const Viewport& viewport, double duration) noexcept
{
    //std::cout << "TerraGlide::frame() - " << duration << std::endl;
    ++dummy;
    if (dummy == 300)
    {
        std::cout << "Frame 300. Stop\n";
        stop();
    }
}

void TerraGlide::stop() noexcept
{
    m_stopRequests->post(0);
    m_running = false;
}
