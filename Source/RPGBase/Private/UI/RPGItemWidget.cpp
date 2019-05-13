#include "UI/RPGItemWidget.h"

#include "Items/RPGItem.h"

void URPGItemWidget::SetContext(const FRPGItemInstance& InContext)
{
	this->Context = InContext;

	const auto Item = this->Context.GetItem();
	Name = Item->GetDisplayName(InContext);
	Description = Item->Description;
	Icon = Item->Icon.LoadSynchronous();
	StackSize = InContext.StackSize;
	bIsStackable = Item->bIsStackable;
}

void URPGItemWidget::SplitStack(int32 Amount)
{
	URPGItem::SplitStack(Context, Amount);
}
