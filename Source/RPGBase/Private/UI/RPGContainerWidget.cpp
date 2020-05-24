#include "UI/RPGContainerWidget.h"

#include "Components/GridSlot.h"
#include "Components/GridPanel.h"

void URPGContainerWidget::SetContext(URPGContainerInstanceComponent* InContext)
{
    if(Context != nullptr)
    {
		Context->OnItemAdded.RemoveAll(this);
		Context->OnItemRemoved.RemoveAll(this);
    }

	Context = InContext;
    
	TScriptDelegate<FWeakObjectPtr> AddedDelegate;
	AddedDelegate.BindUFunction(this, TEXT("OnItemAdded"));
	Context->OnItemAdded.Add(AddedDelegate);

	TScriptDelegate<FWeakObjectPtr> RemovedDelegate;
	RemovedDelegate.BindUFunction(this, TEXT("OnItemRemoved"));
	Context->OnItemRemoved.Add(RemovedDelegate);
}

void URPGContainerWidget::OnItemAdded(const FRPGItemInstance& Item, int32 InSlot) const
{
	auto ItemWidget = CreateWidget<URPGItemWidget>(this->GetOwningPlayer(), ItemWidgetClass);
	ItemWidget->SetContext(Item);

	if(!ItemsPanel->ReplaceChildAt(InSlot, ItemWidget))
	{
	    // #todo Log error
	}
	else
	{
		const auto GridSlot = Cast<UGridSlot>(ItemsPanel->GetSlots()[InSlot]);
		ensure(GridSlot);

		const auto Grid = Cast<UGridPanel>(GridSlot->Parent);
		const auto ColumnCount = Grid->ColumnFill.Num();
		const auto Index2D = FRPGItemInstance::GetIndex2D(ColumnCount, InSlot);
		GridSlot->Row = Index2D.X;
		GridSlot->Column = Index2D.Y;
	}
}

void URPGContainerWidget::OnItemRemoved(const FRPGItemInstance& Item, int32 InSlot) const
{
	for(auto i = 0; i < ItemsPanel->GetChildrenCount(); i++)
	{
		auto ItemWidget = Cast<URPGItemWidget>(ItemsPanel->GetChildAt(i));
		if (ItemWidget->GetContext() == Item)
		{
			ItemsPanel->RemoveChildAt(i);
			break;
		}
	}
}
