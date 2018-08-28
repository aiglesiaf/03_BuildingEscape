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

}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	// The PhysicsHandle will be the component which will grab the other objects in the room.
	LoadPhysicsHandle();
	// InputComponent is needed to read keyboard input configured in Project Settings -> Input
	LoadInputComponent();
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	// PhysicsHandle can 'grab' and 'release' components
	if (!PhysicsHandle) { return; }
	if (PhysicsHandle->GrabbedComponent)
	{
		// SetTargetLocation set the position of the grabbed component
		PhysicsHandle->SetTargetLocation(GetReachLineEnd());
	}

	/* Leave this call here in case it is needed in the future
	/// Debug the current vector.
	DrawDebugLine(
		GetWorld(),
		GetReachLineStart(),
		GetReachLineEnd(),
		FColor(255, 0, 0),
		false,
		0.f,
		0.f,
		10.f
	);*/
	
}

void UGrabber::Grab()
{
	/// UE_LOG(LogTemp, Warning, TEXT("Grabbing!! "))
	auto HitResult = GetFirstPhysicsBodyInReach();
	auto ComponentToGrab = HitResult.GetComponent();
	auto ActorHit = HitResult.GetActor();

	if (ActorHit)
	{
		// TODO: Use GrabComponent?
		//PhysicsHandle->GrabComponentAtLocation(ComponentToGrab,
		//	NAME_None,
		//	ComponentToGrab->GetOwner()->GetActorLocation());
		if (!PhysicsHandle) { return; }
		PhysicsHandle->GrabComponent(ComponentToGrab,
			NAME_None,
			ComponentToGrab->GetOwner()->GetActorLocation(),
			true);
	}
}

void UGrabber::Release()
{
	UE_LOG(LogTemp, Warning, TEXT("Releasing!! "))
	if (!PhysicsHandle) { return; }
	if (PhysicsHandle->GrabbedComponent)
	{
		PhysicsHandle->ReleaseComponent();
	}
}

void UGrabber::LoadPhysicsHandle()
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (!PhysicsHandle)
	{
		UE_LOG(LogTemp, Error, TEXT("PhysicsHandle in %s not found!!"), *(GetOwner()->GetName()))
	}
}

void UGrabber::LoadInputComponent()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("InputComponent found :: "), *(InputComponent->GetName()))
		InputComponent->BindAction(FName("GrabAction"), EInputEvent::IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction(FName("ReleaseAction"), EInputEvent::IE_Released, this, &UGrabber::Release);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("InputComponent in %s not found!!"), *(GetOwner()->GetName()))
	}
}

FHitResult UGrabber::GetFirstPhysicsBodyInReach()
{
	FHitResult Hit;
	FCollisionQueryParams TraceCollisionQueryParams(FName(TEXT("")), false, GetOwner());
	// Notice that to get the collision we are using the World Actor
	// Also notice that we are using object channel with PhysicsBody
	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		GetReachLineStart(),
		GetReachLineEnd(),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceCollisionQueryParams
	);

	AActor* ColActor = Hit.GetActor();
	if (ColActor)
	{
		UE_LOG(LogTemp, Warning, TEXT("We are colliding with: %s"), *(ColActor->GetName()))
	}
	return Hit;
}


FVector UGrabber::GetReachLineStart()
{
	FVector PlayerViewPointVector;
	FRotator PlayerViewPointRotator;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointVector, 
		OUT PlayerViewPointRotator);

	/// Create the current vector.
	return PlayerViewPointVector;
}

FVector UGrabber::GetReachLineEnd()
{
	FVector PlayerViewPointVector;
	FRotator PlayerViewPointRotator;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointVector, 
		OUT PlayerViewPointRotator);

	/// Create the current vector.
	return PlayerViewPointVector + PlayerViewPointRotator.Vector() * RangeDebugRay;
}

