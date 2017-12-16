#pragma once

#include <cstddef>

class Attributes
{
public:
    virtual ~Attributes() = 0;
    virtual void setAttributesInBoundBuffer() noexcept = 0;
    virtual std::size_t storageSize() const noexcept = 0;
    virtual const void* raw() const noexcept = 0;
};
