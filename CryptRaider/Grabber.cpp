// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"

#include "Engine/World.h"

#include "DrawDebugHelpers.h"


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
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UPhysicsHandleComponent* PhysicsHandle = GetPhysicsComponent();

	

	if (PhysicsHandle && PhysicsHandle->GetGrabbedComponent())
	{
		FVector VectorSet = GetComponentLocation() + (GetForwardVector() * HoldingDistance);
		PhysicsHandle->SetTargetLocationAndRotation(
		VectorSet,
		GetComponentRotation()
		);
	}
	else
	{
		return;
	}
	

	// FRotator ComponentRotation = GetComponentRotation();

	// UE_LOG(LogTemp, Display, TEXT("My rotation: %s"), *(ComponentRotation.ToCompactString()));

	// UWorld* World = GetWorld();
	// float MyTimeSeconds = World->UnpausedTimeSeconds;

	// UE_LOG(LogTemp, Display, TEXT("Time after start in seconds: %f"), MyTimeSeconds);]

}

// void UGrabber::PrintDamage(const float& Damage)
// {
// 	UE_LOG(LogTemp, Display, TEXT("Damage: %f"), Damage); 
// }

// bool UGrabber::HasDamage(float& OutDamage)
// {
// 	OutDamage = 7;
// 	return true;
// }

void UGrabber::Release()
{
	UPhysicsHandleComponent* PhysicsHandle = GetPhysicsComponent();


	
	if (PhysicsHandle && PhysicsHandle->GetGrabbedComponent())
	{
		PhysicsHandle->GetGrabbedComponent()->GetOwner()->Tags.Remove("Grabbed");
		PhysicsHandle->GetGrabbedComponent()->WakeAllRigidBodies();
		PhysicsHandle->ReleaseComponent();
	}
}

bool UGrabber::HasHit(FHitResult& HitResult) const
{
	FVector Start = GetComponentLocation();
	FVector End = Start + (GetForwardVector() * MaxGrabDistance);
	DrawDebugLine(GetWorld(), Start, End, FColor::Red);

	FCollisionShape Sphere = FCollisionShape::MakeSphere(GrabRadius);
	return GetWorld()->SweepSingleByChannel(HitResult, Start, End, FQuat::Identity, ECC_GameTraceChannel2, Sphere);
}

void UGrabber::Grab()
{
	
	UPhysicsHandleComponent* PhysicsHandle = GetPhysicsComponent();

	if (PhysicsHandle == nullptr)
	{
		return;
	}
	
	FHitResult HitResult;
	bool HasHitVar = HasHit(HitResult);

	
	
	if (HasHitVar)
	{
		UPrimitiveComponent* HitComponent = HitResult.GetComponent();
		HitComponent->WakeAllRigidBodies();
		HitComponent->SetSimulatePhysics(true);
		HitResult.GetActor()->Tags.Add("Grabbed");
		HitResult.GetActor()->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		PhysicsHandle->GrabComponentAtLocationWithRotation(
			HitComponent,
			NAME_None, 
			HitResult.ImpactPoint, 
			GetComponentRotation()
		);

		// DrawDebugSphere(GetWorld(), HitResult.Location, 10, 10, FColor::Blue, false, 5);
		// DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10, 10, FColor::Green, false, 5);
		// AActor* Actor = HitResult.GetActor();
		// UE_LOG(LogTemp, Display, TEXT("Actor hit: %s"), *(Actor->GetActorNameOrLabel()));
	}
}

UPhysicsHandleComponent* UGrabber::GetPhysicsComponent() const
{
	return GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
}
