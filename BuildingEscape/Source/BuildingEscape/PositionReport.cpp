// MIT License
// Copyright(c) 2020 Almaz Kinziabulatov


#include "PositionReport.h"

// Sets default values for this component's properties
UPositionReport::UPositionReport()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UPositionReport::BeginPlay()
{
	Super::BeginPlay();

	auto objectName = GetOwner()->GetName();

	auto &&objectTransform = GetOwner()->GetTransform();
	auto objectPosition = objectTransform.GetLocation();

	UE_LOG(LogTemp, Warning, TEXT("Position Report: object '%s' is at %s "), *objectName, *objectPosition.ToString())
}


// Called every frame
void UPositionReport::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

