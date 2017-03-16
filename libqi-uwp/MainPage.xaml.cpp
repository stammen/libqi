//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"

#include <qi/log.hpp>
#include <qi/applicationsession.hpp>
#include <qi/anyobject.hpp>
#include <string>
#include <vector>

using namespace libqi_uwp;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;

// The Blank Page item template is documented at http://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x409

#pragma comment(lib, "qi.lib")

MainPage::MainPage()
{
	InitializeComponent();

    int argc = 1;
    char* a = "RobotHello";
    char** argv = &a;

    qi::ApplicationSession app(argc, argv);
    app.startSession();
    qi::SessionPtr session = app.session();
    qi::AnyObject motion = session->service("ALMotion");
    motion.call<void>("wakeUp");
    motion.call<void>("rest");


}
