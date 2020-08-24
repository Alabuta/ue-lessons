// MIT License Copyright(c) 2020 Almaz Kinziabulatov

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:

	UPROPERTY(VisibleAnywhere)
	float openAngle{-64.f};

	UPROPERTY(EditAnywhere)
	ATriggerVolume *pressurePlate{nullptr};

	UPROPERTY(EditAnywhere)
	AActor *actorThatOpens{nullptr};

	void OpenDoor();
};