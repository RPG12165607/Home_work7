

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MyPawn.generated.h"

struct FInputActionValue; // Enhanced Input에서 액션 값을 받을 때 사용하는 구조체


UCLASS()
class HOME_WORK7_API AMyPawn : public APawn
{
	GENERATED_BODY()

public:
	AMyPawn();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent);

    /** 이동 속도 */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
    float MoveSpeed = 300.f;

    /** 회전 속도 */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
    float TurnSpeed = 100.f;

    /** 입력 처리 */
    UFUNCTION()
    void Move(const FInputActionValue& Value);
    UFUNCTION()
    void Look(const FInputActionValue& Value);
};
