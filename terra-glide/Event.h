#pragma once

#include "Viewport.h"

enum class EventType
{
    Frame = 0
};

struct FrameData
{
    double frameDuration;
    Viewport viewport;
};

union EventData
{
    FrameData frameData;
};

struct Event
{
    EventType eventType;
    union EventData eventData;
};
