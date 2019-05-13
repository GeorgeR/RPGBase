#include "Factories/UniqueIdFactory.h"

FString UUniqueIdFactory::GetNewId(const FString& Context)
{
	return FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens);
}
