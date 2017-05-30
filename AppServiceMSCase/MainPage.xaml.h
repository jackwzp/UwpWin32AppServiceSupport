//
// MainPage.xaml.h
// Declaration of the MainPage class.
//

#pragma once

#include "MainPage.g.h"

namespace AppServiceMSCase
{
	/// <summary>
	/// An empty page that can be used on its own or navigated to within a Frame.
	/// </summary>
	public ref class MainPage sealed
	{
	public:
		MainPage();

    private:
        void page_loaded(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
        void start_dummy_sender(); // Trigger a send event every 2ms
    };
}
