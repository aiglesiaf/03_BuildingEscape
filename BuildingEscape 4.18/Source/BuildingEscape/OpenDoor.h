// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/TriggerVolume.h"
#include "Engine/World.h"
#include "Engine/LocalPlayer.h"
#include <iostream>
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

	void OpenDoor();
	void CloseDoor();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


private:
	UPROPERTY(EditAnywhere)
	float OpenAngle=90.f;

	UPROPERTY(EditAnywhere)
	ATriggerVolume* PressurePlatform;

	UPROPERTY(EditAnywhere)
	float OpenDoorDelayInSec=2.f;
	
	float DoorOpenLastTime=0;
	//AActor* CurrentActor;
	AActor *DoorOwner = GetOwner();
	float OpenDoorAngle = 90.f;
	bool IsDoorOpen = false;
	float WeightToOpenDoors = 16.f;

	float GetTotalMassOfActorsOnPlate();
	
};
