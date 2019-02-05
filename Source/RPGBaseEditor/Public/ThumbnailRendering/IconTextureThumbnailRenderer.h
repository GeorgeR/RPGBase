#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "ThumbnailRendering/ThumbnailRenderer.h"
#include "ThumbnailRendering/TextureThumbnailRenderer.h"

#include "IconTextureThumbnailRenderer.generated.h"

class FCanvas;
class FRenderTarget;

UCLASS(MinimalAPI)
class UIconTextureThumbnailRenderer
	: public UTextureThumbnailRenderer
{
	GENERATED_BODY()

public:
	// Begin UThumbnailRenderer Object
	RPGBASEEDITOR_API virtual bool CanVisualizeAsset(UObject* Object);
	RPGBASEEDITOR_API virtual void GetThumbnailSize(UObject* Object, float Zoom, uint32& OutWidth, uint32& OutHeight) const override;
	RPGBASEEDITOR_API virtual void Draw(UObject* Object, int32 X, int32 Y, uint32 Width, uint32 Height, FRenderTarget*, FCanvas* Canvas) override;
	// End UThumbnailRenderer Object
};
