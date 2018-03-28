#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EGender : uint8
{
	G_Male = 0		UMETA(DisplayName = "Male"),
	G_Female = 1	UMETA(DisplayName = "Female")
};