
#include "MyPawn.h"
#include "EnhancedInputComponent.h" // EnhancedInputComponent ��� �߰�
#include "EnhancedInputSubsystems.h"
#include "MyPlayerController.h"
#include "GameFramework/PlayerController.h"

AMyPawn::AMyPawn()
{
    PrimaryActorTick.bCanEverTick = true;
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
        // PlayerInputComponent�� �پ��� ����� �־ EnhancedInput ������� Cast �Ѵٸ� �ѹ� �����ϴ°�
    {
        if (AMyPlayerController* PlayerController = Cast<AMyPlayerController>(GetController()))
            // ĳ���͸� �����ϴ� Controller�� �������� �װ� SpartaPlayerController�� Cast -> PlayerController�� ������ ����
        {
            if (PlayerController->MoveAction)
            {
                EnhancedInput->BindAction(PlayerController->MoveAction, ETriggerEvent::Triggered, this, &AMyPawn::Move);
                // EnhancedInput->BindAction -> �̺�Ʈ�� �Լ��� �����ϴ� �ٽ� �ڵ�
                // PlayerController->MoveAction -> >MoveAction�� �����´�
                // ETriggerEvent::Triggered -> Ű�� ������ �̺�Ʈ�� �߻� ������
                // this -> ȣ��� �Լ��� ��ü ( Character�� ��ü )
                // &AMyPawn::Move -> ������ ȣ��� �Լ�
            }
            if (PlayerController->LookAction)
            {
                EnhancedInput->BindAction(PlayerController->LookAction, ETriggerEvent::Triggered, this, &AMyPawn::Look);
            }
        }
    }
}

void AMyPawn::Move(const FInputActionValue& value)
{
    const FVector2D MoveInput = value.Get<FVector2D>();
    // value���� FVector2D�� �����ͼ� MoveInput�� FVector2D ���·� ����

    float DeltaTime = GetWorld()->GetDeltaSeconds();

    FVector LocalMove = FVector(MoveInput.X, MoveInput.Y, 0.f) * MoveSpeed * DeltaTime;

    AddActorLocalOffset(LocalMove, true);
    
}

void AMyPawn::Look(const FInputActionValue& value)
{
    FVector2D LookInput = value.Get<FVector2D>();

    float DeltaTime = GetWorld()->GetDeltaSeconds();

    FRotator DeltaRot(0.f, LookInput.X * TurnSpeed * DeltaTime, 0.f);
    AddActorLocalRotation(DeltaRot);
}
