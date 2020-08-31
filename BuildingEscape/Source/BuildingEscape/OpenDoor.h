// MIT License Copyright(c) 2020 Almaz Kinziabulatov

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "OpenDoor.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDoorEvent);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	

	UOpenDoor();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:

	UPROPERTY(BlueprintAssignable)
	FDoorEvent onOpen;

	UPROPERTY(BlueprintAssignable)
	FDoorEvent onClose;

protected:

	virtual void BeginPlay() override;

private:

	float GetTotalMassOfActorsOnPlate() const;

private:

	UPROPERTY(EditAnywhere)
	float triggerMassValue{10.f};

	UPROPERTY(EditAnywhere)
	ATriggerVolume *pressurePlate{nullptr};
};
