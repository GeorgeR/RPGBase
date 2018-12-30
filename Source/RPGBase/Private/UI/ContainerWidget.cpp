#include "ContainerWidget.h"
#include "GridSlot.h"
#include "GridPanel.h"

void UContainerWidget::SetContext(UContainerInstanceComponent* InContext)
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

void UContainerWidget::OnItemAdded(const FItemInstance& Item, int32 InSlot) const
{
	auto ItemWidget = CreateWidget<UItemWidget>(this->GetOwningPlayer(), ItemWidgetClass);
	ItemWidget->SetContext(Item);

	if(!ItemsPanel->ReplaceChildAt(InSlot, ItemWidget))
	{
	    // TODO: Log error
	}
	else
	{
		const auto GridSlot = Cast<UGridSlot>(ItemsPanel->GetSlots()[InSlot]);
		ensure(GridSlot);

		const auto Grid = Cast<UGridPanel>(GridSlot->Parent);
		const auto ColumnCount = Grid->ColumnFill.Num();
		const auto Index2D = FItemInstance::GetIndex2D(ColumnCount, InSlot);
		GridSlot->Row = Index2D.X;
		GridSlot->Column = Index2D.Y;
	}
}

void UContainerWidget::OnItemRemoved(const FItemInstance& Item, int32 InSlot) const
{
	for(auto i = 0; i < ItemsPanel->GetChildrenCount(); i++)
	{
		auto ItemWidget = Cast<UItemWidget>(ItemsPanel->GetChildAt(i));
		if (ItemWidget->GetContext() == Item)
		{
			ItemsPanel->RemoveChildAt(i);
			break;
		}
	}
}
