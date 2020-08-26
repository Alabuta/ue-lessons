// MIT License Copyright(c) 2020 Almaz Kinziabulatov


#include "OpenDoor.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	if (auto world = GetWorld(); world)
		if (auto controller = world->GetFirstPlayerController(); controller)
			actorThatOpens = controller->GetPawn();
}

void UOpenDoor::OpenOrCloseDoor(bool open)
{
	if (auto owner = GetOwner(); owner)
		owner->SetActorRotation(FRotator{0.f, openAngle * static_cast<float>(open), 0.f});
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (pressurePlate && pressurePlate->IsOverlappingActor(actorThatOpens)) {
		OpenOrCloseDoor(true);

		if (auto world = GetWorld(); world)
			lastTimeDoorOpened = world->GetTimeSeconds();
	}

	if (auto world = GetWorld(); world)
		if (world->GetTimeSeconds() - lastTimeDoorOpened > doorCloseDelay)
			OpenOrCloseDoor(false);
}

