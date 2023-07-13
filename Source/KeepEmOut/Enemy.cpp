// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"


#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include <Kismet/KismetMathLibrary.h>
#include <Kismet/GameplayStatics.h>
#include <string>


// Sets default values
AEnemy::AEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComp"));
	CapsuleComp->AttachToComponent(Root, FAttachmentTransformRules::KeepWorldTransform);
	 FName objName = "TutorialTPP";
	 
	MeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshComp"));


	MeshComp->AttachToComponent(CapsuleComp, FAttachmentTransformRules::KeepWorldTransform);
	//USkeletalMesh* mesh;
	//	MeshComp->SetSkeletalMesh(mesh);




}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Player = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	
	//Player = Cast<AMyPlayer>(UGameplayStatics::GetActorOfClass(GetWorld(), 0));
	SetActorLocation(newPos);//Set initial position for enemy
	Super::BeginPlay();
	
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//Player = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (Player != nullptr)
	{
		MyLookAt(Player->GetTargetLocation(), FVector::UpVector);
	}


	//Which way is forward

	const FRotator Rotation = this->GetActorRotation(); //Store rotation value
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	//Get facing vector
	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);//Unreal's axes are different to Unity's. X = Z in Unity, Y = X in Unity, Z =  Y in Unity
	
}

void AEnemy::MyLookAt(FVector TargetPosition, FVector WorldUp = FVector::UpVector)
{
	FVector Forward =  TargetPosition - this->GetActorLocation() * 200; //Get forward facing vector
	FRotator Rot = UKismetMathLibrary::MakeRotFromXZ(Forward, WorldUp); //Get rotation
	//this->SetActorRotation(Rot);
	MeshComp->SetWorldRotation(Rot);
	UE_LOG(LogTemp, Warning, TEXT("Rotation is %s"));
	//UE_LOG(LogTemp, Warning, TEXT("Rotation is %s"), Rot);
}
