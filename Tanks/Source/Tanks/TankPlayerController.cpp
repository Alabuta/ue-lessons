// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"


void ATankPlayerController::BeginPlay()
{
    Super::BeginPlay();


    if (auto tank = GetControlledTank(); tank)
        UE_LOG(LogTemp, Warning, TEXT("Tank %s"), *(tank->GetName()))

    else UE_LOG(LogTemp, Warning, TEXT("Not posessing a tank"))
}

ATank *ATankPlayerController::GetControlledTank() const
{
    return Cast<ATank>(GetPawn());
}
