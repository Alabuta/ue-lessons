// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"


void ATankAIController::BeginPlay()
{
    Super::BeginPlay();

    if (auto tank = GetControlledTank(); tank)
        UE_LOG(LogTemp, Warning, TEXT("AI Tank %s"), *(tank->GetName()))

    else UE_LOG(LogTemp, Warning, TEXT("AI Not posessing a tank"))
}

ATank *ATankAIController::GetControlledTank() const
{
    return Cast<ATank>(GetPawn());
}

