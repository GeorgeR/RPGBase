#include "IconTextureThumbnailRenderer.h"

#include "Engine/Texture2D.h"
#include "CanvasItem.h"
#include "CanvasTypes.h"

#include "RPGItem.h"

bool UIconTextureThumbnailRenderer::CanVisualizeAsset(UObject* Object)
{
	return true;

	URPGItem* Item = Cast<URPGItem>(Object);
	if (Item == nullptr)
		return false;

	TSoftObjectPtr<UTexture2D> Icon = Item->Icon;
	if (!Icon.IsValid())
		return false;

	return true;
}

void UIconTextureThumbnailRenderer::GetThumbnailSize(UObject* Object, float Zoom, uint32& OutWidth, uint32& OutHeight) const
{
	OutWidth = 0;
	OutHeight = 0;

	URPGItem* Item = Cast<URPGItem>(Object);
	if (Item == nullptr)
		return;

	TSoftObjectPtr<UTexture2D> Icon = Item->Icon;
	if (!Icon.IsValid())
		return;

	auto IconTexture = Icon.LoadSynchronous();
	if(IconTexture != nullptr)
	{
		OutWidth = FMath::TruncToInt(Zoom * (float)IconTexture->GetSurfaceWidth());
		OutHeight = FMath::TruncToInt(Zoom * (float)IconTexture->GetSurfaceHeight());
	}
}

void UIconTextureThumbnailRenderer::Draw(UObject* Object, int32 X, int32 Y, uint32 Width, uint32 Height, FRenderTarget*, FCanvas* Canvas)
{
	Canvas->Clear(FLinearColor::Transparent);

	URPGItem* Item = Cast<URPGItem>(Object);
	if (Item == nullptr)
		return;

	TSoftObjectPtr<UTexture2D> Icon = Item->Icon;
	if (!Icon.IsValid())
	{
		
		return;
	}

	auto IconTexture = Icon.LoadSynchronous();
	if (IconTexture == nullptr || IconTexture->Resource == nullptr)
		return;

	const bool bUseTranslucentBlend = IconTexture && IconTexture->HasAlphaChannel();

	FCanvasTileItem CanvasTile(FVector2D(X, Y), IconTexture->Resource, FVector2D(Width, Height), FLinearColor::White);
	CanvasTile.BlendMode = bUseTranslucentBlend ? ESimpleElementBlendMode::SE_BLEND_Translucent : ESimpleElementBlendMode::SE_BLEND_Opaque;
	CanvasTile.Draw(Canvas);
}
