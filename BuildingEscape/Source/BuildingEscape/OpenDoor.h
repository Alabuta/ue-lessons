// MIT License Copyright(c) 2020 Almaz Kinziabulatov

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "OpenDoor.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDoorOpenRequest);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	

	UOpenDoor();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:

	UPROPERTY(BlueprintAssignable)
	FOnDoorOpenRequest onDoorOpenRequest;

protected:

	virtual void BeginPlay() override;

private:

	void OpenOrCloseDoor(bool open);

	float GetTotalMassOfActorsOnPlate() const;

private:

	UPROPERTY(EditAnywhere)
	float openAngle{-64.f};

	UPROPERTY(EditAnywhere)
	float doorCloseDelay{1.f};

	float lastTimeDoorOpened{0.f};

	UPROPERTY(EditAnywhere)
	float doorOpenMassValue{10.f};

	UPROPERTY(EditAnywhere)
	ATriggerVolume *pressurePlate{nullptr};
};
