//--------------------------------------------------------------------------------------
// InputInterfacingUWP.h
//
// Advanced Technology Group (ATG)
// Copyright (C) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

#pragma once

#include "DeviceResources.h"
#include "StepTimer.h"
#include <collection.h>
#include <sstream>
#include <chrono>
#include <ctime>    

enum Modes
{
    NavigationDevice = 0,
    ArcadeStickDevice,
    RacingWheelDevice,
	FlightStickDevice
};

// A basic sample implementation that creates a D3D11 device and
// provides a render loop.
class Wheel final : public DX::IDeviceNotify
{
public:

    Wheel() noexcept(false);
    ~Wheel() = default;

    Wheel(Wheel&&) = default;
    Wheel& operator= (Wheel&&) = default;

    Wheel(Wheel const&) = delete;
    Wheel& operator= (Wheel const&) = delete;

    struct wheelData {
        double angle;
        double throttle;
        double brake;
        int gear;
        int x;
        int y;
    };

    // Initialization and management
    void Initialize(IUnknown* window, int width, int height, DXGI_MODE_ROTATION rotation);

    // Basic render loop
    void Tick();

    // IDeviceNotify
    virtual void OnDeviceLost() override;
    virtual void OnDeviceRestored() override;

    // Messages
    void OnActivated();
    void OnDeactivated();
    void OnSuspending();
    void OnResuming();
    void OnWindowSizeChanged(int width, int height, DXGI_MODE_ROTATION rotation);
    void ValidateDevice();
    void setCarData(std::string msg);
    // Properties
    void GetDefaultSize( int& width, int& height ) const;
    wheelData getData();

private:
	void DrawWheel(DirectX::XMFLOAT2 startPosition);

    void UpdateNavController();
    void UpdateWheel();

    void Update(DX::StepTimer const& timer);
    void Render();

    void Clear();

    void CreateDeviceDependentResources();
    void CreateWindowSizeDependentResources();

    double FixStringValue(double value);

    void updateSpeed();
    void updateBatteryLevel();
    
    // Device resources.
    std::unique_ptr<DX::DeviceResources>    m_deviceResources;

    // Render objects.
    std::unique_ptr<DirectX::SpriteBatch>   m_spriteBatch;
    std::unique_ptr<DirectX::SpriteFont>    m_font;

    //Input
    Windows::Gaming::Input::UINavigationController^     m_currentNav;
    Windows::Gaming::Input::UINavigationReading         m_navReading;
    Windows::Gaming::Input::RacingWheel^                m_currentWheel;
    Windows::Gaming::Input::RacingWheelReading          m_wheelReading;
    Windows::Gaming::Input::RacingWheelButtons          m_buttonReading;
    Windows::Gaming::Input::ForceFeedback::ConditionForceEffect^ m_effect;

    Platform::Collections::Vector<Windows::Gaming::Input::UINavigationController^>^ m_navCollection;
    Platform::Collections::Vector<Windows::Gaming::Input::RacingWheel^>^ m_wheelCollection;

    bool                                                m_effectLoaded;
    Modes                   m_currentMode;
    bool                    m_selectPressed;
    bool                    m_connected;
    std::wstring            m_buttonString;
    int                     m_x;
    int                     m_y;
    std::string             m_msg;
    // Rendering loop timer.
    DX::StepTimer                           m_timer;
    std::chrono::steady_clock::time_point m_lastTimestamp;
    bool                    m_isFirstMessage;
    double                  currentSpeed;
    double                  currentBatteryLevel;
};
