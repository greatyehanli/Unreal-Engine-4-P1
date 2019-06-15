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
	//这个UPROPERTY（）必须要加在每个你想要在property window里显示的变量前面
	UPROPERTY(EditAnywhere)
	float openAngle = -90.f;

	UPROPERTY(EditAnywhere)
	float CloseDelayOfDoor = 1.f;

	UPROPERTY(EditAnywhere)
	ATriggerVolume* pressurePlate;

	UPROPERTY(EditAnywhere)
	AActor* ActorThatOpens; //pawn 继承了 actor, 所以type的话是AActor也行， APawn也行

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
