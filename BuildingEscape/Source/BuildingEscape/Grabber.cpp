// MIT License Copyright(c) 2020 Almaz Kinziabulatov


#include "Grabber.h"

#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Components/InputComponent.h"


UGrabber::UGrabber()
{
	PrimaryComponentTick.bCanEverTick = true;
}

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

void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (physicsHandleComponent && physicsHandleComponent->GrabbedComponent) {
		auto [lineStart, lineEnd] = GetReachLinePoints();
		physicsHandleComponent->SetTargetLocation(lineEnd);
	}
}

TPair<FVector, FVector> UGrabber::GetReachLinePoints() const
{
	FVector location;
	FRotator rotation;

	if (auto controller = GetWorld()->GetFirstPlayerController(); controller)
		controller->GetPlayerViewPoint(location, rotation);

	return TPair<FVector, FVector>{location, location + rotation.Vector() * reachDistance};
}

void UGrabber::Grab()
{
	auto world = GetWorld();

	if (auto controller = world->GetFirstPlayerController(); controller) {
		auto [lineStart, lineEnd] = GetReachLinePoints();

		FHitResult hitResult;
		FCollisionQueryParams collisionQueryParams{FName{TEXT("")}, false, GetOwner()};

		world->LineTraceSingleByObjectType(
			hitResult, lineStart, lineEnd, FCollisionObjectQueryParams{ECollisionChannel::ECC_PhysicsBody}, collisionQueryParams
		);

		if (auto actor = hitResult.GetActor(); actor) {
			auto grabComponent = hitResult.GetComponent();
			physicsHandleComponent->GrabComponentAtLocation(grabComponent, NAME_None, actor->GetActorLocation());
		}
	}
}

void UGrabber::Release()
{
	if (physicsHandleComponent)
		physicsHandleComponent->ReleaseComponent();
}

