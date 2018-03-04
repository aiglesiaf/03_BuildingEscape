// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#include "DrawDebugHelpers.h"

#define OUT


// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("Grabber has started..."));
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle)
	{
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("PhysicsHandle in %s not found!!"), *(GetOwner()->GetName()))
	}

	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("InputComponent found :: "), *(InputComponent->GetName()))
		InputComponent->BindAction(FName("GrabAction"), EInputEvent::IE_Pressed, this, &UGrabber::Grab);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("InputComponent in %s not found!!"), *(GetOwner()->GetName()))
	}
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector PlayerViewPointVector;
	FRotator PlayerViewPointRotator;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		PlayerViewPointVector, PlayerViewPointRotator);
	
	// UE_LOG(LogTemp, Warning, TEXT("FVector: %s. FRotator: %s"),
	//	*PlayerViewPointVector.ToString(), *PlayerViewPointRotator.ToString());

	/// Create the current vector.
	FVector EndPointPlayerViewPointVector = PlayerViewPointVector + PlayerViewPointRotator.Vector() * RangeDebugRay;

	// Debug the current vector.
	DrawDebugLine(
		GetWorld(),
		PlayerViewPointVector,
		EndPointPlayerViewPointVector,
		FColor(255, 0, 0),
		false,
		0.f,
		0.f,
		10.f
	);

	FHitResult Hit;
	FCollisionQueryParams TraceCollisionQueryParams(FName(TEXT("")), false, GetOwner());
	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		PlayerViewPointVector,
		EndPointPlayerViewPointVector,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceCollisionQueryParams
	);

	AActor* ColActor = Hit.GetActor();
	if (ColActor)
	{
		UE_LOG(LogTemp, Warning, TEXT("We are colliding with: %s"), *(ColActor->GetName()))
	}
}

void UGrabber::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("We have found the event!! "))
}

