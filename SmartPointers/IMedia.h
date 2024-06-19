#pragma once
#ifndef IMEDIA_H
#define IMEDIA_H

class IMedia {
public:
    virtual ~IMedia() = default;      // Virtual destructor
    virtual void playMedia() const = 0;  // Pure virtual function
};

#endif // IMEDIA_H