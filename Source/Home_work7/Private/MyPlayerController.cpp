
#include "MyPlayerController.h"
#include "EnhancedInputSubsystems.h"

AMyPlayerController::AMyPlayerController():InputMappingContext(nullptr), MoveAction(nullptr), LookAction(nullptr)
	// InputMappingContext�� �� InputAction �ʱ�ȭ
{
}

void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (ULocalPlayer* Localplayer = GetLocalPlayer()) // ���� �÷��̾ Localplaer(�Է��̳� ȭ��並 �����ϴ�)��ü�� �����Ͷ�
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = Localplayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
			//UEnhancedInputLocalPlayerSubsystem -> IMC�� �����ϴ� ���� �ý���
			//UEnhancedInputLocalPlayerSubsystem* SubSystem -> IMC�� �����ϴ� ���� �ý����� SubSystem�̶� �̸����� ������
		{
			if (InputMappingContext) // InputMappingContext�� �����Ҷ� ( Ȯ�ο� )
			{
				Subsystem->AddMappingContext(InputMappingContext, 0);
				// AddMappingContext�� InputMappingContext�� Ȱ��ȭ ( 0�� �켱���� )
			}
		}
	}
}