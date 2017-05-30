
#include "pch.h"
#include "MyCustomAppService.h"

using namespace AppServiceMSCase;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;


// Initialize static member
MyCustomAppService^ MyCustomAppService::instance_ = nullptr;

MyCustomAppService ^ MyCustomAppService::instance()
{
    if (instance_ == nullptr) {
        instance_ = ref new MyCustomAppService();
    }
    return instance_;
}


void AppServiceMSCase::MyCustomAppService::SetupConnection()
{
    OutputDebugString(L"AppService UWP: SetupConnection\n");
    // Establish a connection
    auto app_connection = App::GetConnectionService();

    if (app_connection != nullptr) {
        OutputDebugString(L"AppService UWP: app_connection_ is valid\n");
        app_connection->RequestReceived +=
            ref new TypedEventHandler<AppServiceConnection^, AppServiceRequestReceivedEventArgs^>(this, &MyCustomAppService::OnRequestReceived);

    }
}

void AppServiceMSCase::MyCustomAppService::SendMessage()
{
    auto connection = App::GetConnectionService();

    if (connection != nullptr) {
        // Sending dummy data
        auto msg = ref new ValueSet();
        msg->Insert("count", ++count_);
        auto db = "Sending: " + count_.ToString() + "\n";
        OutputDebugString(db->Data());
        connection->SendMessageAsync(msg);
    }
}


//==============================
//      Private
//==============================

MyCustomAppService::MyCustomAppService()
{
    data_ = ref new ValueSet();
    data_->Insert("name", "test");
    count_ = 0;
}

void AppServiceMSCase::MyCustomAppService::OnRequestReceived(AppServiceConnection ^ sender, AppServiceRequestReceivedEventArgs ^ args)
{
    // This should only be called once since we're sending data from UWP -> WinForm, not the other way around
    OutputDebugString(L"AppService UWP: OnRequestReceived!!!\n");
    auto deferral = args->GetDeferral();
    auto res = ref new ValueSet();
    args->Request->SendResponseAsync(res);
    deferral->Complete();
}