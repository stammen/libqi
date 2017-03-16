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

    std::vector<std::string> arguments = { "libqi-uwp" };

    std::vector<char*> args;
    for (const auto& arg : arguments)
        args.push_back((char*)arg.data());
    args.push_back(nullptr);
    int argc = args.size() - 1;
    auto argv = args.data();
    qi::ApplicationSession app(argc, argv);

}
