// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerComponent.h"


UTriggerComponent::UTriggerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTriggerComponent::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Display, TEXT("Logging Trigger triggered"));
}

void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// if (Actors.Num() > 0)
	// {
	// 	UE_LOG(LogTemp, Display, TEXT("First Overlapping Actor: %s"), *Actors[0]->GetActorNameOrLabel());
	// }

	// int index = 0;
	// while (index < Actors.Num())
	// {
	// 	UE_LOG(LogTemp, Display, TEXT("First Overlapping Actor: %s"), *Actors[index]->GetActorNameOrLabel());
	// 	++index;
	// }

	// TArray<AActor*> Actors;
	// GetOverlappingActors(Actors);

	// for (AActor* Actor : Actors)
	// {
	// 	if (Actor->ActorHasTag(TagName))
	// 	{
	// 		UE_LOG(LogTemp, Display, TEXT("Unlocking"));
	// 	}
	// }

	AActor* Actor = GetAcceptableActor();

	if (!Actor)
	{
		Mover->SetShouldMove(false);
	}
	else
	{
		UPrimitiveComponent* Component = Cast<UPrimitiveComponent>(Actor->GetRootComponent());
		if (Component)
		{
			Actor->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);
			Component->SetSimulatePhysics(false);
		}

		Mover->SetShouldMove(true);
	}
	

}

void UTriggerComponent::SetMover(UMover* NewMover)
{
	Mover = NewMover;
}

AActor* UTriggerComponent::GetAcceptableActor() const
{
	TArray<AActor*> Actors;
	GetOverlappingActors(Actors);

	for (AActor* Actor : Actors)
	{
		if (Actor->ActorHasTag(TagName) && !Actor->ActorHasTag("Grabbed"))
		{
			return Actor;
		}
	}

	return nullptr;
}

