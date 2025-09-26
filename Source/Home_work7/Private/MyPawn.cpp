
#include "MyPawn.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "MyPlayerController.h"
#include "GameFramework/PlayerController.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"

AMyPawn::AMyPawn()
{
    PrimaryActorTick.bCanEverTick = true;

    CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComp"));
    SetRootComponent(CapsuleComp);
    SkeletalMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComp"));
    SkeletalMeshComp->SetupAttachment(CapsuleComp);
    SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
    SpringArmComp->SetupAttachment(CapsuleComp);
    SpringArmComp->TargetArmLength = 300.0f;
    SpringArmComp->bUsePawnControlRotation = false;

    CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    CameraComp->SetupAttachment(SpringArmComp, USpringArmComponent::SocketName);
    CameraComp->bUsePawnControlRotation = false;
}

void AMyPawn::BeginPlay()
{
	Super::BeginPlay();
}

void AMyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
    {
        if (AMyPlayerController* PlayerController = Cast<AMyPlayerController>(GetController()))
        {
            if (PlayerController->MoveAction)
            {
                EnhancedInput->BindAction(PlayerController->MoveAction, ETriggerEvent::Triggered, this, &AMyPawn::Move);
            }
            if (PlayerController->FlyAction)
            {
                EnhancedInput->BindAction(PlayerController->FlyAction, ETriggerEvent::Triggered, this, &AMyPawn::Fly);
            }
            if (PlayerController->LookAction)
            {
                EnhancedInput->BindAction(PlayerController->LookAction, ETriggerEvent::Triggered, this, &AMyPawn::Look);
            }
            if (PlayerController->RollAction)
            {
                EnhancedInput->BindAction(PlayerController->RollAction, ETriggerEvent::Triggered, this, &AMyPawn::Roll);
            }
        }
    }
}

void AMyPawn::Move(const FInputActionValue& value)
{
    const FVector MoveInput = value.Get<FVector>();

    float DeltaTime = GetWorld()->GetDeltaSeconds();

    FVector LocalMove = FVector(MoveInput.X, MoveInput.Y, 0.0f) * MoveSpeed * DeltaTime;

    AddActorLocalOffset(LocalMove, true);
    
}

void AMyPawn::Look(const FInputActionValue& value)
{
    FVector2D LookInput = value.Get<FVector2D>();

    float DeltaTime = GetWorld()->GetDeltaSeconds();

    FRotator DeltaRot(0.f, LookInput.X * TurnSpeed * DeltaTime, 0.f);
    AddActorLocalRotation(DeltaRot);
    
    FRotator NewRot = SpringArmComp->GetRelativeRotation();
    NewRot.Pitch = FMath::Clamp(NewRot.Pitch + LookInput.Y * TurnSpeed * DeltaTime, -100.f, 100.f);
    SpringArmComp->SetRelativeRotation(NewRot);

}