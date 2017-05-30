//
// App.xaml.h
// Declaration of the App class.
//

#pragma once

#include "App.g.h"

namespace AppServiceMSCase
{
    /// <summary>
    /// Provides application-specific behavior to supplement the default Application class.
    /// </summary>
    ref class App sealed
    {
    public:
        // Public static method to get the AppService connection object
        static Windows::ApplicationModel::AppService::AppServiceConnection^ GetConnectionService() { return app_service_; }
    protected:
        virtual void OnLaunched(Windows::ApplicationModel::Activation::LaunchActivatedEventArgs^ e) override;

        // All AppService connection request will trigger this method to execute
        virtual void OnBackgroundActivated(Windows::ApplicationModel::Activation::BackgroundActivatedEventArgs^ args) override;

    internal:
        App();

    private:
        void OnSuspending(Platform::Object^ sender, Windows::ApplicationModel::SuspendingEventArgs^ e);
        void OnNavigationFailed(Platform::Object ^sender, Windows::UI::Xaml::Navigation::NavigationFailedEventArgs ^e);

        // Cache the AppService connection obj
        static Windows::ApplicationModel::AppService::AppServiceConnection^ app_service_; 
    };
}
