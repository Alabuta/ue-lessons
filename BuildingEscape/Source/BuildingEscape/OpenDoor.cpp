// MIT License Copyright(c) 2020 Almaz Kinziabulatov

#include "OpenDoor.h"
#include "Components/PrimitiveComponent.h"


UOpenDoor::UOpenDoor()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
}

void UOpenDoor::OpenOrCloseDoor(bool open)
{
	//GetOwner()->SetActorRotation(FRotator{0.f, openAngle * static_cast<float>(open), 0.f});
	if (open)
		onDoorOpenRequest.Broadcast();
}

float UOpenDoor::GetTotalMassOfActorsOnPlate() const
{
	if (pressurePlate == nullptr)
		return 0.f;

	TArray<AActor *> overlappingActors;
	pressurePlate->GetOverlappingActors(overlappingActors);

	float totalMass = 0.f;

	for (auto overlappingActor : overlappingActors) {
		auto primitiveComponent = overlappingActor->FindComponentByClass<UPrimitiveComponent>();

		if (primitiveComponent)
			totalMass += primitiveComponent->GetMass();
	}

	return totalMass;
}

void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	auto world = GetWorld();

	if (GetTotalMassOfActorsOnPlate() > doorOpenMassValue) {
		OpenOrCloseDoor(true);

		lastTimeDoorOpened = world->GetTimeSeconds();
	}

	if (world->GetTimeSeconds() - lastTimeDoorOpened > doorCloseDelay)
		OpenOrCloseDoor(false);
}

