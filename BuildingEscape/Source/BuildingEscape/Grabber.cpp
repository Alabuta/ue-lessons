// MIT License Copyright(c) 2020 Almaz Kinziabulatov


#include "Grabber.h"

#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Components/InputComponent.h"


// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	auto owner = GetOwner();

	physicsHandleComponent = owner->FindComponentByClass<UPhysicsHandleComponent>();

	if (physicsHandleComponent == nullptr)
		UE_LOG(LogTemp, Error, TEXT("'%s' missing physics handle componet"), *owner->GetName())

	SetupInputComponent();
}

void UGrabber::SetupInputComponent()
{
	auto owner = GetOwner();

	inputComponent = owner->FindComponentByClass<UInputComponent>();

	if (inputComponent) {
		inputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		inputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}

	else UE_LOG(LogTemp, Error, TEXT("'%s' missing input componet"), *owner->GetName())
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UGrabber::Grab()
{
	if (auto world = GetWorld(); world) {
		if (auto controller = world->GetFirstPlayerController(); controller) {
			FVector location;
			FRotator rotation;

			controller->GetPlayerViewPoint(location, rotation);

			FVector lineTraceEnd = location + rotation.Vector() * reachDistance;
			DrawDebugLine(world, location, lineTraceEnd, FColor{255, 255, 0});

			FHitResult hitResult;
			FCollisionQueryParams collisionQueryParams{FName{TEXT("")}, false, GetOwner()};

			world->LineTraceSingleByObjectType(
				hitResult, location, lineTraceEnd, FCollisionObjectQueryParams{ECollisionChannel::ECC_PhysicsBody}, collisionQueryParams
			);

			if (auto actor = hitResult.GetActor(); actor)
				UE_LOG(LogTemp, Warning, TEXT("UGrabber: object '%s' "), *actor->GetName())
		}
	}
}

void UGrabber::Release()
{
	;
}

