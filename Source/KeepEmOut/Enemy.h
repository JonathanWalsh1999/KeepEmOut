// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "MyPlayer.h"


#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Enemy.generated.h"


UCLASS()
class KEEPEMOUT_API AEnemy : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UCapsuleComponent* CapsuleComp;

	UPROPERTY(EditAnywhere)
		class USkeletalMeshComponent* MeshComp;


		AMyPlayer* Player;
		FVector newPos = FVector(4300.0f, -22600.0f, 0.0f);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//UFUNCTION(BlueprintCallable)
	//	USkeletalMesh* ImportSkeletalMesh(FString SourcePath, FString DestinationPath, bool& bOutSucess, FString& OutInforMessage);
	

	USceneComponent* Root;

	void LookAt(AEnemy& LookingActor, FVector TargetPosition, FVector WorldUp = FVector::UpVector);
};
