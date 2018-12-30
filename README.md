# RPGBase
RPG base classes for Unreal Engine 4. Note that i'm building this as I need the functionality, and not everything is tested.

# Networking
This plugin has been setup to work in both single and multiplayer. By default, networking is enabled. To disable it, in RPGBase.Build.cs change Definitions.Add("WITH_NETWORKING=1"); to Definitions.Add("WITH_NETWORKING=0");

In Unreal, RPC's to the Server from a Client have to be on a client-owned object, usually attached to the PlayerController. To get around filling up your player controller with unrelated RPC's, i've come up with a pattern called Accessors. Objects in the world have an accessor class that should be created in your playercontroller, and is fed to the appropriate function in the object itself. This makes things slightly more complicated but far easier to use and override.

As an example, if you have a chest with a ContainerInstance in it in your level, you have a ContainerAccessor in your PlayerController, and call AddItem like so:

Chest->Container->AddItem(ContainerAccessor, Item, 5);

Container will handle the RPC for you, and you should watch Chest->Container->OnItemAdded to know when the item is actually added.

# Objects & Instances
To optimize memory usage, many of the objects are split up. For example, Items. The base Item class should be extended as a child class or blueprint to create the definition about the item, this contains all of the information that doesn't change per instance. An ItemInstance, however, is an instance of that item with values that do change, for example the current stack size (if it can stack).

The same applies to the Container, where a Container might be Inventory, or SmallChest, and ContainerInstance is an actual instance of an inventory or SmallChest. The base container contains information like how many slots it contains, which doesn't change per instance, and the instance contains information about the actual items it contains.

In this way your game isnt filled up with duplicate data about what an item is called, only what it needs to know.

# Association
An Association could be a Guild, Clan, etc. It contains Members with a Rank, and information on when they joined. It also has a DefaultRank for new members. An Assocation can be Created if the Creator isn't already in one, a player can be invited to it if they aren't already in one, they can be added with a rank (or the default rank if not specified), removed by a member of greater rank or themselves, have their rank changed by a member of greater rank, or disbanded by a member of sufficient rank.

All of the functionality is checked on the server, and you should use the function with the accessor parameter if you're using multiplayer.

# Items

## Item
An item has a Name, Description, Icon and MaxStackSize (if stackable at all). Item also contains functions for ItemInstance, as structs can't contain functions.

An ItemInstance contains information about its Item class, container and stack size. You can Add and Remove from the stack, Split it and Clone it.

An ItemInstanceActor is a base class for items that can be spawned in the world, such as a weapon.

Item's don't yet contain network logic but they will.

## Item.Usable
An interface to describe any item that is usable. Probably applies to most items.
```cpp
bool CanUse(AActor* TargetUser, FItemInstance& Instance);
void Use(AActor* TargetUser, FItemInstance& Instance);
```

## Item.Usable.Consumable
An interface for a usable item to describe a consumable item (ie. food).
```cpp
bool CanConsume(AActor* TargetConsumer, FItemInstance& Instance);
void Consume(AActor* TargetConsumer, FItemInstance& Instance);
```

## Item.Usable.Equippable
An interface for a usable item you wish to be equippable/wearable. It has a CanEquip, Equip and UnEquip function. The equip target is a player and either named or indexed slot.
```cpp
bool CanEquip(AActor* TargetWearer, FItemInstance& Instance, FName? TargetSocket, int32? TargetSlot);
void Equip(AActor* TargetWearer, FItemInstance& Instance, FName? TargetSocket, int32? TargetSlot);
void UnEquip(AActor* Wearer, FItemInstance& Instance, FName? Socket, int32? Slot)
```
# Container
A Container could be an inventory, chest or lootbox, etc. It should have a name, and how many columns and rows it has. If it simply has a capacity and you don't care about a grid size, make the column count 1, and row count as many items as you wish.

A ContainerInstance is an actor component that you attached to an actor. It has a Container which holds information about its name and capacity as described above, and holds a list of items. You can Add and Remove an item, Swap (between two different slots) and transfer an item to a different container.

All of this functionality is checked on the server, and you should use the function with the accessor parameter if you're using multiplayer.