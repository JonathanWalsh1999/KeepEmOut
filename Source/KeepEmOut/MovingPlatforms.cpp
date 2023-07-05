// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatforms.h"

#include "Components/ActorComponent.h"

//#include "Kismet/KismetMathLibrary.h"
//#include "Kismet/GameplayStatics.h"
//#include <Runtime/Engine/Public/GeneratedCodeHelpers.h>
//#include "GeneratedCodeHelpers.h"

// Sets default values
AMovingPlatforms::AMovingPlatforms()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	
}

// Called when the game starts or when spawned
void AMovingPlatforms::BeginPlay()
{
	Super::BeginPlay();
	PlatformLocation = GetActorLocation();
	
}

// Called every frame
void AMovingPlatforms::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (!IsStationary)
	{
		if (IsGoingUp)
		{
			if (PlatformLocation.Z > 2000.0f)
			{
				IsGoingUp = false;
				IsStationary = true;
			}

			PlatformLocation.Z += DeltaTime * MovementSpeed;
			SetActorLocation(PlatformLocation);
		}
		else
		{
			if (PlatformLocation.Z < 20.0f)
			{
				IsGoingUp = true;
				IsStationary = true;
			}

			PlatformLocation.Z -= DeltaTime * MovementSpeed;
			SetActorLocation(PlatformLocation);
		}
	}
	else
	{
		if (StationaryTime > 0.0f)
		{
			StationaryTime -= DeltaTime;
		}
		else
		{
			StationaryTime = STATIONARY_ALLOCATION;
			IsStationary = false;
		}
	}



}

//AActor* AMovingPlatforms::Enemy(const FString& className, FTransform actorTransform)
//{
//	UClass* asActor = nullptr;
//	AActor * oSpawnedActor = nullptr;
//	bool bIsOK = false;
//
//	UClass* FoundClass = LoadObject <UClass>(NULL, *className, NULL, LOAD_None, NULL);
//
//	if (FoundClass->IsChildOf(AActor::StaticClass()))
//	{
//		bIsOK = true;
//
//	}
//	else
//	{
//		FoundClass = nullptr;
//		bIsOK = false;
//	}
//
//	if (bIsOK)
//	{
//		asActor = AActor::StaticClass(), FoundClass;
//		bIsOK = (asActor != nullptr);
//	}
//
//	if (bIsOK)
//	{
//		AActor* oStatrtSpawnedActor = UGameplayStatics::BeginDeferredActorSpawnFromClass
//		(
//			this,
//			asActor,
//			actorTransform,
//			ESpawnActorCollisionHandlingMethod::Undefined,
//			((AActor*)nullptr)
//		);
//
//		oSpawnedActor = UGameplayStatics::FinishSpawningActor
//		(
//			oStatrtSpawnedActor,
//			actorTransform
//		);
//
//	}
//
//	return oSpawnedActor;
//}

