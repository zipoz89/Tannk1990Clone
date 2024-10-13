#pragma once

class IState
{
public:
    // Virtual destructor to ensure proper cleanup of derived classes
    virtual ~IState() = default;

    // Method to initialize the state, called when entering this state
    virtual void Initialize() = 0;

    // Method to update the state, called every frame
    virtual void Update(float DeltaTime) = 0;

    // Method to uninitialize the state, called when exiting this state
    virtual void Uninitialize() = 0;
};