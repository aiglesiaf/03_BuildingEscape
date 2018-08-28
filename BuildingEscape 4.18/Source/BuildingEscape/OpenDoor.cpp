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
	if(!PressurePlatform)
	{
		UE_LOG(LogTemp, Error, TEXT("PressurePlatform in %s not found!!"), *(GetOwner()->GetName()))
	}
	//OpenDoor();
	
	//const FString ObjectName = CurrentActor->GetFullName();
	//UE_LOG(LogTemp, Warning, TEXT("CurrentActor: %"), *ObjectName);
}



// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	// THIS IS THE CODE THAT IS CAUSING THE UE CRASHING. PressurePlatform WAS NOT FILLED IN IN THE UI!!!!!!!!!!!!!! 
	//if (IsDoorOpen == false)

	if (GetTotalMassOfActorsOnPlate() > TriggerMass)
	{
		OnOpen.Broadcast();
	}
	else
	{
		const FString ObjMass = FString::FromInt(GetTotalMassOfActorsOnPlate());
		UE_LOG(LogTemp, Warning, TEXT("Total mass : %s "), *ObjMass);
		OnClose.Broadcast();
	}
}


float UOpenDoor::GetTotalMassOfActorsOnPlate()
{
	// PressurePlatform->IsOverlappingActor(CurrentActor)
	TArray<AActor *> OverlappingActors;
	float result = 0;
	if (!PressurePlatform) { return 0; }
	PressurePlatform->GetOverlappingActors(OverlappingActors);
	for (AActor* actor: OverlappingActors)
	{
		TArray<UStaticMeshComponent*> meshComponents;
		actor->GetComponents<UStaticMeshComponent>(meshComponents);
		for (UStaticMeshComponent* mesh : meshComponents)
		{
			FBodyInstance* BodyInst = mesh->GetBodyInstance();
			if (!BodyInst) break;
			result += BodyInst->GetBodyMass();
		}
	}
	return result;
}

