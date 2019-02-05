#include "RPGItemWidget.h"

#include "RPGItem.h"

void URPGItemWidget::SetContext(const FRPGItemInstance& Context)
{
	this->Context = Context;

	const auto Item = this->Context.GetItem();
	Name = Item->GetDisplayName(Context);
	Description = Item->Description;
	Icon = Item->Icon.LoadSynchronous();
	StackSize = Context.StackSize;
	bIsStackable = Item->bIsStackable;
}

void URPGItemWidget::SplitStack(int32 Amount)
{
	URPGItem::SplitStack(Context, Amount);
}
