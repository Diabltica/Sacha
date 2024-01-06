//--------------------------------------------------------------------------------------
// InputInterfacingUWP.cpp
//
// Advanced Technology Group (ATG)
// Copyright (C) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

#include "pch.h"
#include "InputInterfacingUWP.h"
#include <ppltasks.h>

#include "ATGColors.h"
#include <Windows.Gaming.Input.h>

extern void ExitSample() noexcept;

using namespace DirectX;
using namespace Windows::Gaming::Input;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Platform::Collections;

using Microsoft::WRL::ComPtr;
int currentGear;
boolean previousStateP = false;
boolean previousStateM = false;

namespace
{
	static const wchar_t* c_InputTestNames[] =
	{
		L"<Navigation Test>\n",
		L"<ArcadeStick Test>\n",
		L"<RacingWheel>\n",
		L"<FlightStick Test>\n",
	};

	static const wchar_t c_NavDescription[] =
		L"Using the UINavigationController allows you to read generic navigation \n"
		L"commands from a variety of input devices like wheels, gamepads, and \n"
		L"arcade sticks\n";
}

void Wheel::DrawWheel(XMFLOAT2 startPosition)
{
	wchar_t wheelString[128] = {};
	double percentages[7] = { 0.05, 0.1, 0.2, 0.4, 0.6, 0.8, 1.0 };
	swprintf_s(wheelString, L"Wheel %1.3f", m_wheelReading.Wheel * (2.0 / 0.34));
	m_font->DrawString(m_spriteBatch.get(), wheelString, startPosition, ATG::Colors::Green);
	startPosition.y += m_font->GetLineSpacing() * 1.1f;

	swprintf_s(wheelString, L"Throttle %1.3f", m_wheelReading.Throttle * (2 - percentages[currentGear - 1]));
	m_font->DrawString(m_spriteBatch.get(), wheelString, startPosition, ATG::Colors::Green);
	startPosition.y += m_font->GetLineSpacing() * 1.1f;

	swprintf_s(wheelString, L"Break %1.3f", m_wheelReading.Brake * (2 - percentages[currentGear - 1]));
	m_font->DrawString(m_spriteBatch.get(), wheelString, startPosition, ATG::Colors::Green);
	startPosition.y += m_font->GetLineSpacing() * 1.1f;

	if (m_currentWheel->HasClutch)
	{
		swprintf_s(wheelString, L"Clutch %1.3f", m_wheelReading.Clutch);
		m_font->DrawString(m_spriteBatch.get(), wheelString, startPosition, ATG::Colors::Green);
		startPosition.y += m_font->GetLineSpacing() * 1.1f;
	}

	if (m_currentWheel->HasHandbrake)
	{
		swprintf_s(wheelString, L"Handbrake %1.3f", m_wheelReading.Handbrake);
		m_font->DrawString(m_spriteBatch.get(), wheelString, startPosition, ATG::Colors::Green);
		startPosition.y += m_font->GetLineSpacing() * 1.1f;
	}

	if (m_currentWheel->HasPatternShifter)
	{
		if (m_buttonReading == RacingWheelButtons::NextGear && currentGear < m_currentWheel->MaxPatternShifterGear && !previousStateP) {
			currentGear++;
		}
		else if (m_buttonReading == RacingWheelButtons::PreviousGear && currentGear > 1 && !previousStateM) {
			currentGear--;
		}
		previousStateP = m_buttonReading == RacingWheelButtons::NextGear;
		previousStateM = m_buttonReading == RacingWheelButtons::PreviousGear;

		swprintf_s(wheelString, L"Shifter %d of %d", currentGear, m_currentWheel->MaxPatternShifterGear);
		m_font->DrawString(m_spriteBatch.get(), wheelString, startPosition, ATG::Colors::Green);
		startPosition.y += m_font->GetLineSpacing() * 1.1f;
	}
	int _modifier = 1;
	switch (m_buttonReading)
	{
	case Windows::Gaming::Input::RacingWheelButtons::None:
		break;
	case Windows::Gaming::Input::RacingWheelButtons::PreviousGear:
		break;
	case Windows::Gaming::Input::RacingWheelButtons::NextGear:
		break;
	case Windows::Gaming::Input::RacingWheelButtons::DPadUp:
		if (m_x + _modifier <= 255)
			m_x += _modifier;
		else
			m_x = 255;
		break;
	case Windows::Gaming::Input::RacingWheelButtons::DPadDown:
		if (m_x - _modifier >= 0)
			m_x -= _modifier;
		else
			m_x = 0;
		break;
	case Windows::Gaming::Input::RacingWheelButtons::DPadLeft:
		if (m_y - _modifier >= 0)
			m_y -= _modifier;
		else
			m_y = 0;
		break;
	case Windows::Gaming::Input::RacingWheelButtons::DPadRight:
		if (m_y + _modifier <= 255)
			m_y += _modifier;
		else
			m_y = 255;
		break;
	case Windows::Gaming::Input::RacingWheelButtons::Button1:
		break;
	case Windows::Gaming::Input::RacingWheelButtons::Button2:
		break;
	case Windows::Gaming::Input::RacingWheelButtons::Button3:
		break;
	case Windows::Gaming::Input::RacingWheelButtons::Button4:
		break;
	case Windows::Gaming::Input::RacingWheelButtons::Button5:
		break;
	case Windows::Gaming::Input::RacingWheelButtons::Button6:
		break;
	case Windows::Gaming::Input::RacingWheelButtons::Button7:
		break;
	case Windows::Gaming::Input::RacingWheelButtons::Button8:
		break;
	case Windows::Gaming::Input::RacingWheelButtons::Button9:
		break;
	case Windows::Gaming::Input::RacingWheelButtons::Button10:
		break;
	case Windows::Gaming::Input::RacingWheelButtons::Button11:
		break;
	case Windows::Gaming::Input::RacingWheelButtons::Button12:
		break;
	case Windows::Gaming::Input::RacingWheelButtons::Button13:
		break;
	case Windows::Gaming::Input::RacingWheelButtons::Button14:
		break;
	case Windows::Gaming::Input::RacingWheelButtons::Button15:
		break;
	case Windows::Gaming::Input::RacingWheelButtons::Button16:
		break;
	default:
		break;
	}
	swprintf_s(wheelString, L"Position X %d", m_x);
	m_font->DrawString(m_spriteBatch.get(), wheelString, startPosition, ATG::Colors::Green);
	startPosition.y += m_font->GetLineSpacing() * 1.1f;
	swprintf_s(wheelString, L"Position Y %d", m_y);
	m_font->DrawString(m_spriteBatch.get(), wheelString, startPosition, ATG::Colors::Green);
	startPosition.y += m_font->GetLineSpacing() * 1.1f;
}

void Wheel::UpdateNavController()
{
	UINavigationController^ mostRecentNav = nullptr;

	if (m_navCollection->Size > 0)
	{
		mostRecentNav = m_navCollection->GetAt(0);
	}

	if (m_currentNav != mostRecentNav)
	{
		m_currentNav = mostRecentNav;
	}
}

void Wheel::UpdateWheel()
{
	RacingWheel^ mostRecentWheel = nullptr;

	if (m_wheelCollection->Size > 0)
	{
		mostRecentWheel = m_wheelCollection->GetAt(0);
	}

	if (m_currentWheel != mostRecentWheel)
	{
		m_currentWheel = mostRecentWheel;
		if (m_currentWheel->HasPatternShifter) {
			currentGear = 1;
		}
	}

	if (m_currentWheel != nullptr && m_currentWheel->WheelMotor != nullptr)
	{
		this->m_effect = ref new ForceFeedback::ConditionForceEffect(ForceFeedback::ConditionForceEffectKind::Spring);

		IAsyncOperation<ForceFeedback::ForceFeedbackLoadEffectResult>^ request = m_currentWheel->WheelMotor->LoadEffectAsync(this->m_effect);

		auto loadEffectTask = Concurrency::create_task(request);
		loadEffectTask.then([this](ForceFeedback::ForceFeedbackLoadEffectResult result) {
			if (result == ForceFeedback::ForceFeedbackLoadEffectResult::Succeeded)
			{
				m_effectLoaded = true;
			}
			else
			{
				m_effectLoaded = false;
			}
		}).wait();
		if (m_effectLoaded && this->m_effect->State != ForceFeedback::ForceFeedbackEffectState::Faulted){
			Windows::Foundation::Numerics::float3 vector;
			vector.x = 1.f;
			vector.y = 0.f;
			vector.z = 0.f;
			float coefficient = 1000000;
			float maxMagnitude = 1;
			float deadZone = 0;
			float bias = 0;
			this->m_effect->SetParameters(vector,
					coefficient, coefficient,
					maxMagnitude, maxMagnitude,
					deadZone, bias);
			this->m_effect->Start();
		}
	}
}



Wheel::Wheel() noexcept(false)
{
	m_deviceResources = std::make_unique<DX::DeviceResources>();
	m_deviceResources->RegisterDeviceNotify(this);
}

// Initialize the Direct3D resources required to run.
void Wheel::Initialize(IUnknown* window, int width, int height, DXGI_MODE_ROTATION rotation)
{
	m_deviceResources->SetWindow(window, width, height, rotation);

	m_deviceResources->CreateDeviceResources();
	CreateDeviceDependentResources();

	m_deviceResources->CreateWindowSizeDependentResources();
	CreateWindowSizeDependentResources();

	m_currentMode = NavigationDevice;
	m_selectPressed = false;
	m_connected = false;
	m_effectLoaded = false;
	m_x = 127;
	m_y = 127;
	//Create an effect
	/*m_effect = ref new ForceFeedback::ConditionForceEffect(ForceFeedback::ConditionForceEffectKind::Spring);
	Windows::Foundation::Numerics::float3 vector;
	vector.x = 1.f;
	vector.y = 0.f;
	vector.z = 0.f;
	m_effect->SetParameters(vector,
							2.0f, -2.0f,
							1.0f, -1.0f,
							0.0f, 0.0f);*/

	m_navCollection = ref new Vector<UINavigationController^>();
	m_wheelCollection = ref new Vector<RacingWheel^>();

	auto navControllers = UINavigationController::UINavigationControllers;
	for (auto controller : navControllers)
	{
		m_navCollection->Append(controller);
	}

	auto wheelControllers = RacingWheel::RacingWheels;
	for (auto controller : wheelControllers)
	{
		m_wheelCollection->Append(controller);
	}

	UINavigationController::UINavigationControllerAdded += ref new EventHandler<UINavigationController^ >([=](Platform::Object^, UINavigationController^ args)
		{
			m_navCollection->Append(args);
			UpdateNavController();
		});

	UINavigationController::UINavigationControllerRemoved += ref new EventHandler<UINavigationController^ >([=](Platform::Object^, UINavigationController^ args)
		{
			unsigned int index;
			if (m_navCollection->IndexOf(args, &index))
			{
				m_navCollection->RemoveAt(index);
				UpdateNavController();
			}
		});
	RacingWheel::RacingWheelAdded += ref new EventHandler<RacingWheel^ >([=](Platform::Object^, RacingWheel^ args)
		{
			m_wheelCollection->Append(args);
			UpdateWheel();
		});

	RacingWheel::RacingWheelRemoved += ref new EventHandler<RacingWheel^ >([=](Platform::Object^, RacingWheel^ args)
		{
			unsigned int index;
			if (m_wheelCollection->IndexOf(args, &index))
			{
				m_wheelCollection->RemoveAt(index);
				UpdateWheel();
			}
		});

	// UWP on Xbox One triggers a back request whenever the B button is pressed
	// which can result in the app being suspended if unhandled
	using namespace Windows::UI::Core;

	auto navigation = SystemNavigationManager::GetForCurrentView();

	navigation->BackRequested += ref new EventHandler<BackRequestedEventArgs^>([](Platform::Object^, BackRequestedEventArgs^ args)
		{
			args->Handled = true;
		});
}

#pragma region Frame Update
// Executes basic render loop.
void Wheel::Tick()
{
	m_timer.Tick([&]()
		{
			Update(m_timer);
		});

	Render();
}

// Updates the world.
void Wheel::Update(DX::StepTimer const&)
{
	PIXBeginEvent(PIX_COLOR_DEFAULT, L"Update");

	bool toggleFFB = false;
	if (m_currentNav == nullptr)
	{
		m_connected = false;
		m_currentMode = NavigationDevice;
		PIXEndEvent();
		return;
	}
	m_currentMode = RacingWheelDevice;
	m_connected = true;
	m_navReading = m_currentNav->GetCurrentReading();

	if ((m_navReading.RequiredButtons & RequiredUINavigationButtons::View) == RequiredUINavigationButtons::View)
	{
		ExitSample();
	}
	if (m_currentWheel != nullptr)
	{
		m_wheelReading = m_currentWheel->GetCurrentReading();
		m_buttonReading = m_wheelReading.Buttons;
	}
	PIXEndEvent();
}
#pragma endregion

#pragma region Frame Render
// Draws the scene.
void Wheel::Render()
{
	// Don't try to render anything before the first Update.
	if (m_timer.GetFrameCount() == 0)
	{
		return;
	}

	Clear();

	auto context = m_deviceResources->GetD3DDeviceContext();
	PIXBeginEvent(context, PIX_COLOR_DEFAULT, L"Render");

	auto rect = m_deviceResources->GetOutputSize();
	auto safeRect = SimpleMath::Viewport::ComputeTitleSafeArea(rect.right, rect.bottom);

	XMFLOAT2 pos(float(safeRect.left), float(safeRect.top));

	m_spriteBatch->Begin();

	if (m_connected)
	{
		// Draw description
		m_font->DrawString(m_spriteBatch.get(), c_InputTestNames[m_currentMode], pos, ATG::Colors::White);
		pos.y += m_font->GetLineSpacing() * 1.5f;
		if (m_currentWheel != nullptr)
		{
			DrawWheel(pos);
		}
		else
		{
			m_font->DrawString(m_spriteBatch.get(), L"No wheel connected", pos, ATG::Colors::Orange);
		}

	}
	else
	{
		m_font->DrawString(m_spriteBatch.get(), L"No navigation input connected", pos, ATG::Colors::Orange);
	}

	m_spriteBatch->End();

	//PIXEndEvent(context);

	// Show the new frame.
	PIXBeginEvent(PIX_COLOR_DEFAULT, L"Present");
	m_deviceResources->Present();
	PIXEndEvent();
}

// Helper method to clear the back buffers.
void Wheel::Clear()
{
	auto context = m_deviceResources->GetD3DDeviceContext();
	PIXBeginEvent(context, PIX_COLOR_DEFAULT, L"Clear");

	// Clear the views.
	auto renderTarget = m_deviceResources->GetRenderTargetView();
	auto depthStencil = m_deviceResources->GetDepthStencilView();

	context->ClearRenderTargetView(renderTarget, ATG::Colors::Background);
	context->ClearDepthStencilView(depthStencil, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	context->OMSetRenderTargets(1, &renderTarget, depthStencil);

	// Set the viewport.
	auto viewport = m_deviceResources->GetScreenViewport();
	context->RSSetViewports(1, &viewport);

	PIXEndEvent(context);
}
#pragma endregion

#pragma region Message Handlers
// Message handlers
void Wheel::OnActivated()
{
}

void Wheel::OnDeactivated()
{
}

void Wheel::OnSuspending()
{
	auto context = m_deviceResources->GetD3DDeviceContext();
	context->ClearState();

	m_deviceResources->Trim();
}

void Wheel::OnResuming()
{
	m_timer.ResetElapsedTime();
}

void Wheel::OnWindowSizeChanged(int width, int height, DXGI_MODE_ROTATION rotation)
{
	if (!m_deviceResources->WindowSizeChanged(width, height, rotation))
		return;

	CreateWindowSizeDependentResources();
}

void Wheel::ValidateDevice()
{
	m_deviceResources->ValidateDevice();
}

// Properties
void Wheel::GetDefaultSize(int& width, int& height) const
{
	width = 1280;
	height = 720;
}
#pragma endregion

#pragma region Direct3D Resources
// These are the resources that depend on the device.
void Wheel::CreateDeviceDependentResources()
{
	auto context = m_deviceResources->GetD3DDeviceContext();
	auto device = m_deviceResources->GetD3DDevice();

	m_spriteBatch = std::make_unique<SpriteBatch>(context);

	m_font = std::make_unique<SpriteFont>(device, L"SegoeUI_24.spritefont");
}

// Allocate all memory resources that change on a window SizeChanged event.
void Wheel::CreateWindowSizeDependentResources()
{
}

void Wheel::OnDeviceLost()
{
	m_spriteBatch.reset();
	m_font.reset();
}

void Wheel::OnDeviceRestored()
{
	CreateDeviceDependentResources();

	CreateWindowSizeDependentResources();
}

Wheel::wheelData Wheel::getData() {
	return {
		m_wheelReading.Wheel,
		m_wheelReading.Throttle,
		m_wheelReading.Brake,
		currentGear,
		m_x,
		m_y
	};
}
#pragma endregion
