

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MyPawn.generated.h"

struct FInputActionValue; // Enhanced Input���� �׼� ���� ���� �� ����ϴ� ����ü


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

    /** �̵� �ӵ� */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
    float MoveSpeed = 300.f;

    /** ȸ�� �ӵ� */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
    float TurnSpeed = 100.f;

    /** �Է� ó�� */
    UFUNCTION()
    void Move(const FInputActionValue& Value);
    UFUNCTION()
    void Look(const FInputActionValue& Value);
};
