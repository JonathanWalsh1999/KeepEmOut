// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"

#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"

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
	Super::BeginPlay();
	
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//USkeletalMesh* AEnemy::ImportSkeletalMesh(FString SourcePath, FString DestinationPath, bool& bOutSucess, FString& OutInforMessage)
//{
//	//USkeletalMesh* asset = Cast<USkeletalMesh>()
//	U_3_Import
//}
