#include "PHOCInstance.h"
#include "PHOC/PHOC.h"

UPHOCInstance::UPHOCInstance() {
}

UPHOCInstance::~UPHOCInstance() {
}

void UPHOCInstance::InitializeSteamManager() {
    OnSteamOverlayActiveCallback.Register(this, &UPHOCInstance::OnSteamOverlayActive);
}



void UPHOCInstance::OnSteamOverlayActive(GameOverlayActivated_t* pCallbackData)
{
    const bool isCurrentOverlayActive = pCallbackData->m_bActive != 0;
    UPHOCInstance; //So that the call list reference on the Lambda works

    if (isCurrentOverlayActive)
    {
        AsyncTask(ENamedThreads::GameThread, [&]() {
            PublicOnSteamOverlayIsON();
        });
    }
    else {
        AsyncTask(ENamedThreads::GameThread, [&]() {
            PublicOnSteamOverlayIsOFF();
        });
    }
}

bool UPHOCInstance::InitializeCPPElements() 
{

     if (SteamUser() != nullptr) //Is the Steam API initialized?
     {
         InitializeSteamManager();
         return true;
     }
     else
     {
         return false;
     }

}

void UPHOCInstance::PublicOnSteamOverlayIsON()
{
    IsSteamOverlayActive = true;
    this->OnSteamOverlayIsActive(IsSteamOverlayActive);
}

void UPHOCInstance::PublicOnSteamOverlayIsOFF() 
{
    IsSteamOverlayActive = false;
    this->OnSteamOverlayIsActive(IsSteamOverlayActive);
}





