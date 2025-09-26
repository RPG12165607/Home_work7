

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MyPawn.generated.h"

struct FInputActionValue; // Enhanced Input에서 액션 값을 받을 때 사용하는 구조체
class USpringArmComponent; // 스프링 암 관련 클래스 헤더
class UCameraComponent; // 카메라 관련 클래스 전방 선언
class UCapsuleComponent; // 카메라 관련 클래스 전방 선언


UCLASS()
class HOME_WORK7_API AMyPawn : public APawn
{
	GENERATED_BODY()

public:
	AMyPawn();

protected:
	virtual void BeginPlay() override;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MyPawnPlate|Components") // 에디터에서 위치 확인 가능하지만 수정은 불가
    UCapsuleComponent* CapsuleComp;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyPawnPlate|Components") // 에디터에서 선택/변경 가능
    USkeletalMeshComponent* SkeletalMeshComp;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera") // 스프링 암 컴포넌트
    USpringArmComponent* SpringArmComp;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera") // 카메라 컴포넌트
    UCameraComponent* CameraComp;

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
