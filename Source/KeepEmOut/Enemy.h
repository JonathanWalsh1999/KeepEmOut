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


		APlayerController* Player;
		FVector newPos = FVector(6300.0f, -21600.0f, 660.0f);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//UFUNCTION(BlueprintCallable)
	//	USkeletalMesh* ImportSkeletalMesh(FString SourcePath, FString DestinationPath, bool& bOutSucess, FString& OutInforMessage);
	

	USceneComponent* Root;

	void MyLookAt(FVector TargetPosition, FVector WorldUp);
};
