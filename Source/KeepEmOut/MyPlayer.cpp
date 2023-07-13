// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayer.h"
#include "EnhancedInputSubsystems.h" //Subsystems is plural!
#include "EnhancedInputComponent.h"
#include "Components/InputComponent.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AMyPlayer::AMyPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	
	// Instantiating your class Components

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));//Create the spring arm component (game object in Unity) and add it as a child to the character

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));//Create a component for camera and make it a child component of spring arm

	//Set the location and rotation of the Character Mesh Transform

	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -90.0f), FQuat(FRotator(0.0f, -90.0f, 0.0f))); // Get the mesh component that is attached to the characeter via Blueprint

	// Attaching your class Components to the default character's Skeletal Mesh Component.

	

	SpringArmComp->SetupAttachment(GetMesh());

	CameraComp->SetupAttachment(SpringArmComp, USpringArmComponent::SocketName);

	//Setting class variables of the spring arm

	SpringArmComp->bUsePawnControlRotation = true;

	//Setting class variables of the Character movement component

	GetCharacterMovement()->bOrientRotationToMovement = true;

	GetCharacterMovement()->bUseControllerDesiredRotation = true;

	GetCharacterMovement()->bIgnoreBaseRotation = true;

}

// Called when the game starts or when spawned
void AMyPlayer::BeginPlay()
{
	Super::BeginPlay();

	SetActorLocation(FVector(5500.0f, -22600.0f, 0.0f));//Set initial position for player

	APlayerController* playerController = Cast<APlayerController>(GetController()); //pointer to access subsystem
	if (playerController)
	{
		UEnhancedInputLocalPlayerSubsystem* subsystem = 
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(playerController->GetLocalPlayer());

		if (subsystem)
		{
			subsystem->AddMappingContext(playerMappingContext, 0);
		}
	}
	
}

void AMyPlayer::Move(const FInputActionValue& value)
{
	//Store the input value in a 2D vector so we have movement forward and backward as well as left and right
	const FInputActionValue::Axis2D currentValue = value.Get<FInputActionValue::Axis2D>();

	//Moving the player forwards and backwards
	if (currentValue.Y != 0.0f) //** W and S keys are stored in Y.
	{
		//Which way is forward
		const FRotator Rotation = Controller->GetControlRotation(); //Store rotation value
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		//Get facing vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);//Unreal's axes are different to Unity's. X = Z in Unity, Y = X in Unity, Z =  Y in Unity
		AddMovementInput(Direction, currentValue.Y);
	}

	//***This would have been movement for left and right, but I don't think this is necessary if you are always moving in the direction you are facing
	//if (currentValue.X != 0.0f)
	//{
	//	//Which way is forward
	//	const FRotator Rotation = Controller->GetControlRotation();
	//	const FRotator YawRotation(0, Rotation.Yaw, 0);

	//	//Get forward vector
	//	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	//	AddMovementInput(Direction, currentValue.X);
	//}


	
}

void AMyPlayer::Look(const FInputActionValue& value)
{
	const FInputActionValue::Axis2D currentValue = value.Get<FInputActionValue::Axis2D>();

	ACharacter::AddControllerYawInput(currentValue.X);
	ACharacter::AddControllerPitchInput(currentValue.Y);
}

void AMyPlayer::Jump(const FInputActionValue& value)
{
	const bool currentValue = value.Get<bool>();

	if (currentValue)
	{
		UE_LOG(LogTemp, Warning, TEXT("IA_Jump triggered"));

		ACharacter::Jump();
		
	}
	else
	{
		ACharacter::StopJumping();
	}
}

// Called every frame
void AMyPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	SpringArmComp->SetRelativeLocation(FVector(0.0f, 43.0f, 173.0f)); //43 173. Needs to be set at runtime, as position is updated every frame due to character movement

}

// Called to bind functionality to input
void AMyPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(moveAction, ETriggerEvent::Triggered, this, &AMyPlayer::Move);
		EnhancedInputComponent->BindAction(lookAction, ETriggerEvent::Triggered, this, &AMyPlayer::Look);
		EnhancedInputComponent->BindAction(jumpAction, ETriggerEvent::Triggered, this, &AMyPlayer::Jump);
	}

}

void AMyPlayer::SpawnActor()
{
	FActorSpawnParameters spawnParams;
	spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	GetWorld()->SpawnActor<AActor>(actorBPToSpawn, GetActorTransform(), spawnParams);
}

void AMyPlayer::SetPosition(FVector& pos)
{
	//SetActorLocation(pos);//Set initial position for player
	//UE_LOG(LogTemp, Warning, TEXT("hello from enemy :)"));
}
