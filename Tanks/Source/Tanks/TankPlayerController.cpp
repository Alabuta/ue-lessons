// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"


void ATankPlayerController::BeginPlay()
{
    Super::BeginPlay();

    if (auto tank = GetControlledTank(); tank)
        UE_LOG(LogTemp, Warning, TEXT("Tank %s"), *(tank->GetName()))

    else UE_LOG(LogTemp, Warning, TEXT("Not posessing a tank"))
}

void ATankPlayerController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    AimTowardsCrosshair();
}

ATank *ATankPlayerController::GetControlledTank() const
{
    return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
    if (auto tank = GetControlledTank(); tank) {
        if (auto hitLocation = GetSightRayHitLocation(); hitLocation) {
            UE_LOG(LogTemp, Warning, TEXT("Hit at %s"), *hitLocation->ToString())
        }
    }
}

//TPair<FVector, FVector> UGrabber::GetReachLinePoints() const
//{
//    FVector location;
//    FRotator rotation;
//
//    if (auto controller = GetWorld()->GetFirstPlayerController(); controller)
//        controller->GetPlayerViewPoint(location, rotation);
//
//    return TPair<FVector, FVector>{location, location + rotation.Vector() * reachDistance};
//}

std::optional<FVector> ATankPlayerController::GetSightRayHitLocation() const
{
    int viewportWidth, viewportHeight;
    GetViewportSize(viewportWidth, viewportHeight);

    auto screenLocation = crossHairLocation * FVector2D{static_cast<float>(viewportWidth), static_cast<float>(viewportHeight)};

    FVector location, direction;
    DeprojectScreenPositionToWorld(screenLocation.X, screenLocation.Y, location, direction);

    return direction;

    //FHitResult hitResult;
    //FCollisionQueryParams collisionQueryParams{FName{TEXT("")}, false, GetOwner()};

    //auto world = GetWorld();

    //auto [lineStart, lineEnd] = std::pair(FVector{0}, FVector{0});

    //world->LineTraceSingleByObjectType(
    //    hitResult, lineStart, lineEnd, FCollisionObjectQueryParams{ECollisionChannel::ECC_PhysicsBody}, collisionQueryParams
    //);

    //if (auto actor = hitResult.GetActor(); actor) {
    //    return hitResult.Get
    //    /*auto grabComponent = hitResult.GetComponent();
    //    physicsHandleComponent->GrabComponentAtLocation(grabComponent, NAME_None, actor->GetActorLocation());*/
    //}

    return {};
}
