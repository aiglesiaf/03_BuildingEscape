// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor.h"
//#include "GameFramework/Actor.h"


// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	//OpenDoor();
	CurrentActor = GetWorld()->GetFirstPlayerController()->GetPawn();
	
	const FString ObjectName = CurrentActor->GetFullName();
	//UE_LOG(LogTemp, Warning, TEXT("CurrentActor: %"), *ObjectName);
}

void UOpenDoor::OpenDoor()
{

	FRotator Rotator = FRotator(0.f, OpenDoorAngle, 0.f);

	DoorOwner->SetActorRotation(Rotator);
	IsDoorOpen = true;
	DoorOpenLastTime = GetWorld()->GetTimeSeconds();
	const FString ObjDoorOpenTime = FString::FromInt(GetWorld()->GetTimeSeconds());
	UE_LOG(LogTemp, Warning, TEXT("DoorOpenLastTime: %s "), *ObjDoorOpenTime);

}

void UOpenDoor::CloseDoor()
{
	if (IsDoorOpen == true)
	{
		FRotator Rotator = FRotator(0.f, 180.f, 0.f);

		DoorOwner->SetActorRotation(Rotator);
		IsDoorOpen = false;
	}

}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	// THIS IS THE CODE THAT IS CAUSING THE UE CRASHING. PressurePlatform WAS NOT FILLED IN IN THE UI!!!!!!!!!!!!!! 
	//if (IsDoorOpen == false)

	if (IsDoorOpen == false && PressurePlatform->IsOverlappingActor(CurrentActor))
	{
		OpenDoor();
	}
	else if(IsDoorOpen == true && !PressurePlatform->IsOverlappingActor(CurrentActor) && DoorOpenLastTime + OpenDoorDelayInSec < GetWorld()->GetTimeSeconds())
	{
		CloseDoor();
	}
}

