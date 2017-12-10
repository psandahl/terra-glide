#pragma once

enum class EventType
{
    Frame = 0,
    Quit
};

struct FrameData
{
    double frameDuration;
    int width;
    int height;
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
