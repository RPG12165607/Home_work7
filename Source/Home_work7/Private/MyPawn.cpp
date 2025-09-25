
#include "MyPawn.h"
#include "EnhancedInputComponent.h" // EnhancedInputComponent 헤더 추가
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
        // PlayerInputComponent이 다양한 방식이 있어서 EnhancedInput 기능으로 Cast 한다를 한번 선언하는것
    {
        if (AMyPlayerController* PlayerController = Cast<AMyPlayerController>(GetController()))
            // 캐릭터를 조종하는 Controller을 가져오고 그걸 SpartaPlayerController로 Cast -> PlayerController에 변수로 진입
        {
            if (PlayerController->MoveAction)
            {
                EnhancedInput->BindAction(PlayerController->MoveAction, ETriggerEvent::Triggered, this, &AMyPawn::Move);
                // EnhancedInput->BindAction -> 이벤트랑 함수를 연결하는 핵심 코드
                // PlayerController->MoveAction -> >MoveAction을 가져온다
                // ETriggerEvent::Triggered -> 키가 눌려서 이벤트가 발생 했을때
                // this -> 호출된 함수의 객체 ( Character의 객체 )
                // &AMyPawn::Move -> 실제로 호출된 함수
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
    // value에서 FVector2D를 가져와서 MoveInput에 FVector2D 형태로 저장

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
