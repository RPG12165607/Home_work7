
#include "MyPlayerController.h"
#include "EnhancedInputSubsystems.h"

AMyPlayerController::AMyPlayerController():InputMappingContext(nullptr), MoveAction(nullptr), LookAction(nullptr)
	// InputMappingContext와 각 InputAction 초기화
{
}

void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (ULocalPlayer* Localplayer = GetLocalPlayer()) // 현재 플레이어에 Localplaer(입력이나 화면뷰를 관리하는)개체를 가져와라
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = Localplayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
			//UEnhancedInputLocalPlayerSubsystem -> IMC를 관리하는 서브 시스템
			//UEnhancedInputLocalPlayerSubsystem* SubSystem -> IMC를 관리하는 서브 시스템을 SubSystem이란 이름으로 가져옴
		{
			if (InputMappingContext) // InputMappingContext가 존재할때 ( 확인용 )
			{
				Subsystem->AddMappingContext(InputMappingContext, 0);
				// AddMappingContext로 InputMappingContext을 활성화 ( 0은 우선순위 )
			}
		}
	}
}