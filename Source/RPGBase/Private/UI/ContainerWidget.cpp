#include "ContainerWidget.h"
#include "GridSlot.h"
#include "GridPanel.h"
#include "UniformGridSlot.h"
#include "UniformGridPanel.h"

void UContainerWidget::SetContext(UContainerInstanceComponent* InContext)
{
	Context = InContext;

	TScriptDelegate<FWeakObjectPtr> AddedDelegate;
	AddedDelegate.BindUFunction(this, TEXT("OnItemAdded"));
	Context->OnItemAdded.Add(AddedDelegate);

	TScriptDelegate<FWeakObjectPtr> RemovedDelegate;
	RemovedDelegate.BindUFunction(this, TEXT("OnItemRemoved"));
	Context->OnItemRemoved.Add(RemovedDelegate);
}

void UContainerWidget::OnItemAdded(const FItemInstance& InItem, int32 InSlot) const
{
	auto ItemWidget = CreateWidget<UItemWidget>(this->GetOwningPlayer(), ItemWidgetClass);
	ItemWidget->SetContext(InItem);

	const auto Slot = ItemsPanel->InsertChildAt(InSlot, ItemWidget);

	const auto GridSlot = Cast<UGridSlot>(Slot);
	if(GridSlot != nullptr)
	{
		const auto Grid = Cast<UGridPanel>(Slot->Parent);
		const auto ColumnCount = Grid->ColumnFill.Num();
		const auto Index2D = FItemInstance::GetIndex2D(ColumnCount, InSlot);
		GridSlot->Row = Index2D.X;
		GridSlot->Column = Index2D.Y;
	}
}

void UContainerWidget::OnItemRemoved(const FItemInstance& InItem, int32 InSlot) const
{
	for(auto i = 0; i < ItemsPanel->GetChildrenCount(); i++)
	{
		auto ItemWidget = Cast<UItemWidget>(ItemsPanel->GetChildAt(i));
		if (ItemWidget->GetContext() == InItem)
		{
			ItemsPanel->RemoveChildAt(i);
			break;
		}
	}
}