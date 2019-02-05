#include "AssetTypeActions_RPGItem.h"
#include "EditorFramework/ThumbnailInfo.h"

UThumbnailInfo* FAssetTypeActions_RPGItem::GetThumbnailInfo(UObject* Asset) const
{
	URPGItem* Item = Cast<URPGItem>(Asset);
	TSoftObjectPtr<UTexture2D> Icon = Item->Icon;
	if (!Icon.IsValid())
		return nullptr;

	UThumbnailInfo* ThumbnailInfo = NewObject<UThumbnailInfo>();

	//Item->ThumbnailInfo = ThumbnailInfo;

	return ThumbnailInfo;
}
