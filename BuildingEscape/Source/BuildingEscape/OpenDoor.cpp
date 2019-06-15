// Copyright Yehan 2019

#include "OpenDoor.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UOpenDoor::OpenDoor()
{
	//FRotator NewRotation = FRotator(0.f, -90.f, 0.f); //set rotation factor
	Owner->SetActorRotation(FRotator(0.f, openAngle, 0.f)); //start rotating
}

void UOpenDoor::CloseDoor()
{
	//AActor* Owner = GetOwner();  // find the owner, ���clasşͷ������Ӵ������Door��һ��component���ҵ�owner��Door
	//FRotator NewRotation = FRotator(0.f, 90.f, 0.f); //set rotation factor
	Owner->SetActorRotation(FRotator(0.f, 0.f, 0.f)); //start rotating
}

// Called when the game starts
void UOpenDoor::BeginPlay()
{

	Super::BeginPlay();
	Owner = GetOwner();  // find the owner, ���clasşͷ������Ӵ������Door��һ��component���ҵ�owner��Door

	// �����������ҵ�һ��Player ControllerȻ��õ�������С����Ȼ��ѿ��ź�ѹ����������
	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
	
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//һֱ����trigger volume, ÿһ֡������
	//�����ǲ������˲���ȥ�ˣ� ����ǣ�����

	if (pressurePlate->IsOverlappingActor(ActorThatOpens)) {
		//�����ǲ���ActorThatOpensվ����trigger volume���棬 returns a bool every frame
		OpenDoor();
		LastDoorOpenTime = GetWorld()->GetTimeSeconds();
	}

	//����ǲ��ǲ��ù����ˣ� ʱ�䵽��û��
	
	if (LastDoorOpenTime + CloseDelayOfDoor < GetWorld()->GetTimeSeconds())
	{
		CloseDoor();
	}
}

