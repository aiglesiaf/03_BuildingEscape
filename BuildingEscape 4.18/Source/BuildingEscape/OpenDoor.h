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

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDoorEvent);

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
	UPROPERTY(BlueprintAssignable)
	FDoorEvent OnOpen;

	UPROPERTY(BlueprintAssignable)
	FDoorEvent OnClose;

private:

	UPROPERTY(EditAnywhere)
	ATriggerVolume* PressurePlatform = nullptr;

	UPROPERTY(EditAnywhere)
	float TriggerMass = 30.f;
	
	float DoorOpenLastTime=0;
	//AActor* CurrentActor;
	AActor *DoorOwner = GetOwner();
	float OpenDoorAngle = 90.f;
	bool IsDoorOpen = false;

	float GetTotalMassOfActorsOnPlate();
	
};
