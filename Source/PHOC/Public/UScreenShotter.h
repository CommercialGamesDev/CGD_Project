#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "Engine/TextureRenderTarget2D.h"
#include "UScreenShotter.generated.h"


UCLASS()
class PHOC_API UScreenShotter : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:

    UFUNCTION(BlueprintCallable, Category = "Rendering")
    static bool SaveRTtoPNG(
        UTextureRenderTarget2D* RenderTarget,
        const FString& FilePath
    );
};
