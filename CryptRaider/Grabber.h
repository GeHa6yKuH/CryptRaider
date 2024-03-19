// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Grabber.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CRYPTRAIDER_API UGrabber : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void Release();

	UFUNCTION(BlueprintCallable)
	void Grab();

private:
	UPROPERTY(EditAnywhere)
	float MaxGrabDistance = 400.0f;

	UPROPERTY(EditAnyWhere)
	float GrabRadius = 100;

	UPROPERTY(EditAnywhere)
	float HoldingDistance = 150.0f;

	UPhysicsHandleComponent* GetPhysicsComponent() const;

	bool HasHit(FHitResult& HitResult) const;
};
