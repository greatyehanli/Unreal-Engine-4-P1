// Copyright Yehan 2019

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

private:
	//���UPROPERTY��������Ҫ����ÿ������Ҫ��property window����ʾ�ı���ǰ��
	UPROPERTY(EditAnywhere)
	float openAngle = -90.f;

	UPROPERTY(EditAnywhere)
	float CloseDelayOfDoor = 1.f;

	UPROPERTY(EditAnywhere)
	ATriggerVolume* pressurePlate;

	UPROPERTY(EditAnywhere)
	AActor* ActorThatOpens; //pawn �̳��� actor, ����type�Ļ���AActorҲ�У� APawnҲ��

	AActor* Owner;
	float LastDoorOpenTime;

public:	
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	void OpenDoor();
	void CloseDoor();
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
