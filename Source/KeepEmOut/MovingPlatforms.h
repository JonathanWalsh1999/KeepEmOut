// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingPlatforms.generated.h"

const float STATIONARY_ALLOCATION = 10.0f;

UCLASS()
class KEEPEMOUT_API AMovingPlatforms : public AActor
{
	GENERATED_BODY()

	
public:	
	// Sets default values for this actor's properties
	AMovingPlatforms();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


private:
	FVector PlatformLocation;

	float MovementSpeed = 100.0f;
	float UpperLimit = 2000.0f;
	float LowerLimit = 20.0f;
	bool IsGoingUp = true;

	float StationaryTime = STATIONARY_ALLOCATION;
	bool IsStationary = true;

	//UFUNCTION(BlueprintCallable, Category="AA")
	//AActor* Enemy(const FString& className, FTransform actorTransform);

};
