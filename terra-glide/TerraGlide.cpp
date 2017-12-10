#include "Event.h"
#include "Link.h"
#include "TerraGlide.h"
#include <iostream>

void TerraGlide::run()
{
    while (m_running)
    {
        Event&& event = m_events->receive();
        switch (event.eventType)
        {
        case EventType::Frame:
            std::cout << "TerraGlide::run(): Frame duration: " << event.eventData.frameData.frameDuration
                << ", width: " << event.eventData.frameData.width
                << ", height: " << event.eventData.frameData.height << std::endl;
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