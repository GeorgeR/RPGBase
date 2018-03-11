#include "ItemWidget.h"
#include "Item.h"

void UItemWidget::SetContext(const FItemInstance& InContext)
{
	Context = InContext;

	const auto Item = Context.LoadDefaultItem();
	Name = Item->DisplayName;
	Description = Item->Description;
	Icon = Item->Icon;
	StackSize = InContext.StackSize;
}

void UItemWidget::SplitStack(int32 InAmount)
{
	UItem::SplitStack(Context, InAmount);
}