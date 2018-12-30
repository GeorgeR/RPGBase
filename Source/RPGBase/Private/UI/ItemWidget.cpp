#include "ItemWidget.h"
#include "Item.h"

void UItemWidget::SetContext(const FItemInstance& Context)
{
	this->Context = Context;

	const auto Item = this->Context.GetItem();
	Name = Item->GetDisplayName(Context);
	Description = Item->Description;
	Icon = Item->Icon.LoadSynchronous();
	StackSize = Context.StackSize;
	bIsStackable = Item->bIsStackable;
}

void UItemWidget::SplitStack(int32 Amount)
{
	UItem::SplitStack(Context, Amount);
}
