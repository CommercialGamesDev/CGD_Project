// Fill out your copyright notice in the Description page of Project Settings.


#include "UScreenShotter.h"
#include "ImageUtils.h"
#include "Engine/TextureRenderTarget2D.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"


bool UScreenShotter::SaveRTtoPNG(
    UTextureRenderTarget2D* RenderTarget,
    const FString& FilePath
)
{
    if (!RenderTarget)
    {
        return false;
    }

    FTextureRenderTargetResource* RTResource =
        RenderTarget->GameThread_GetRenderTargetResource();

    if (!RTResource)
    {
        return false;
    }

    // Read pixels
    TArray<FColor> Pixels;
    FReadSurfaceDataFlags ReadFlags(RCM_UNorm);
    ReadFlags.SetLinearToGamma(true);

    if (!RTResource->ReadPixels(Pixels, ReadFlags))
    {
        return false;
    }

    // Stop weird transparent stuff
    for (FColor& Pixel : Pixels)
    {
        Pixel.A = 255;
    }

    const int32 Width = RenderTarget->SizeX;
    const int32 Height = RenderTarget->SizeY;

    // Compress to PNG
    TArray<uint8> PNGData;
    FImageUtils::CompressImageArray(Width, Height, Pixels, PNGData);

    // Ensure directory exists
    FString FinalPath = FilePath;
    FString Directory = FPaths::GetPath(FinalPath);

    IFileManager::Get().MakeDirectory(*Directory, true);

    // Save file
    return FFileHelper::SaveArrayToFile(PNGData, *FinalPath);
}
