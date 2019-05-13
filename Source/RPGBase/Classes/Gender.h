#pragma once

#include "CoreMinimal.h"

#include "Gender.generated.h"

UENUM(BlueprintType)
enum class EGender : uint8
{
	G_None = 0					UMETA(DisplayName = "None"),
	G_Male = 1					UMETA(DisplayName = "Male"),
	G_Female = 2				UMETA(DisplayName = "Female"),
	G_Any = G_Male | G_Female	UMETA(DisplayName = "Any")
};