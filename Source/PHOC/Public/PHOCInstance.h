#pragma comment(lib, "ThirdParty/Steamworks/Steamv164/sdk/redistributable_bin/win64/steam_api64")

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "ThirdParty/Steamworks/Steamv164/sdk/public/steam/steam_api.h"
#include "PHOCInstance.generated.h"

/**
 * 
 */
UCLASS()
class PHOC_API UPHOCInstance : public UGameInstance
{
    GENERATED_BODY()

    public:

    UPHOCInstance();

    ~UPHOCInstance();

    STEAM_CALLBACK_MANUAL(UPHOCInstance, OnSteamOverlayActive, GameOverlayActivated_t, OnSteamOverlayActiveCallback);

    void InitializeSteamManager();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Steamworks")
    bool IsSteamOverlayActive;

    /*
    * Fire this from Blueprints to tell the actor when to initialize CPP elements
    */

    UFUNCTION(BlueprintCallable, Category = "Steamworks")
    bool InitializeCPPElements();

    /*A function pair that can be called externally executes OnSteamOverlayIsActive()*/
    void PublicOnSteamOverlayIsON();
    void PublicOnSteamOverlayIsOFF();

    UFUNCTION(BlueprintImplementableEvent, Category = "Steamworks")
    void OnSteamOverlayIsActive(bool isOverlayActive);

};
