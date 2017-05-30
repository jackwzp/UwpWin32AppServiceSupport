//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"
#include "MyCustomAppService.h"

using namespace AppServiceMSCase;

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
using namespace concurrency;
using namespace Windows::ApplicationModel;
using namespace Windows::ApplicationModel::AppService;

// The Blank Page item template is documented at http://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x409

MainPage::MainPage()
{
	InitializeComponent();
}


void AppServiceMSCase::MainPage::page_loaded(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
    // Launch WinForm app
    create_task([=]() {
        Windows::ApplicationModel::FullTrustProcessLauncher::LaunchFullTrustProcessForCurrentAppAsync();
    }).then([=] {
        start_dummy_sender();
    });
}

// This method simulates data transmission from a real world bluetooth device
void MainPage::start_dummy_sender()
{
    while (true) {
        MyCustomAppService::instance()->SendMessage();
        MyCustomAppService::instance()->SendMessage();
        Sleep(1);
    }

}

