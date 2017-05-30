#pragma once

#pragma once

#include "pch.h"

using namespace Windows::ApplicationModel::AppService;
using namespace Windows::Foundation::Collections;

namespace AppServiceMSCase
{
    /// This class will handle all events related to AppService conneciton.
    /// It is mainly used for the UWP app to send OSC data to another win32
    /// process that will send the data on localhost to any OSC listeners.
    public ref class MyCustomAppService sealed
    {
    public:
        static MyCustomAppService^ instance();

        void SetupConnection(); // Setup the handler to handle app service connections
        void SendMessage(); // Dummy method to send a message to win32 process

    private:
        MyCustomAppService();

        // This method will actually handle what to do when we receive an AppService Connection
        void OnRequestReceived(AppServiceConnection ^sender, AppServiceRequestReceivedEventArgs ^args);

        static MyCustomAppService^ instance_;
        ValueSet^ data_;
        int count_;

    };
}