//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"

#include <boost/make_shared.hpp>
#include <qi/log.hpp>
#include <qi/applicationsession.hpp>
#include <qi/anyobject.hpp>
#include <exception>
#include <string>
#include <vector>
#include <ppltasks.h>

using namespace libqi_uwp;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Core;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;
using namespace concurrency;

// The Blank Page item template is documented at http://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x409

#pragma comment(lib, "qi.lib")

qiLogCategory("myapplication");


qi::ApplicationSession* gApp = nullptr;
qi::AnyObject gMotion;
qi::SessionPtr gSession = nullptr;

MainPage::MainPage()
{
    InitializeComponent();

    m_dispatcher = Window::Current->CoreWindow->Dispatcher;

    auto task = create_task(create_async([this]
    {
        try
        {
            int argc = 1;
            char* a = "RobotHello";
            char** argv = &a;
            gApp = new qi::ApplicationSession(argc, argv);
            gApp->startSession();
            gSession = gApp->session();
            gMotion = gSession->service("ALMotion");
            gMotion.call<void>("rest");
            SetText(L"App running...");
            gApp->run();

        }
        catch (std::exception& ex)
        {
            SetText(ex.what());
        }
    }));
}


void libqi_uwp::MainPage::wakeButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
    auto task = create_task(create_async([this]
    {
        Platform::String^ text = L"wakeUp";
        try
        {
            gMotion.call<void>("wakeUp");
            SetText(L"wakeUp");
        }
        catch (std::exception& ex)
        {
            SetText(ex.what());
        }
    }));
}


void libqi_uwp::MainPage::restButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
    auto task = create_task(create_async([this]
    {
        try
        {
            gMotion.call<void>("rest");
            SetText(L"rest");
        }
        catch (std::exception& ex)
        {
            SetText(ex.what());
        }
    }));
}

void libqi_uwp::MainPage::SetText(const std::string &text)
{
    std::wstring wText(text.begin(), text.end());
    SetText(ref new Platform::String(wText.c_str()));
}


void libqi_uwp::MainPage::SetText(Platform::String^ text)
{
    m_dispatcher->RunAsync(Windows::UI::Core::CoreDispatcherPriority::Normal, ref new DispatchedHandler([this, text]()
    {
        errortext->Text = text;
    }));
}


