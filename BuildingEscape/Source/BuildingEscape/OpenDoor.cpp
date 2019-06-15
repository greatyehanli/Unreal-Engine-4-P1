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
	//AActor* Owner = GetOwner();  // find the owner, 这个class抬头看看，哟！我是Door的一个component，我的owner是Door
	//FRotator NewRotation = FRotator(0.f, 90.f, 0.f); //set rotation factor
	Owner->SetActorRotation(FRotator(0.f, 0.f, 0.f)); //start rotating
}

// Called when the game starts
void UOpenDoor::BeginPlay()
{

	Super::BeginPlay();
	Owner = GetOwner();  // find the owner, 这个class抬头看看，哟！我是Door的一个component，我的owner是Door

	// 从世界里面找第一个Player Controller然后得到操作的小兵，然后把开门和压力板连起来
	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
	
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//一直请求trigger volume, 每一帧都请求
	//看看是不是有人踩上去了， 如果是，开门

	if (pressurePlate->IsOverlappingActor(ActorThatOpens)) {
		//看看是不是ActorThatOpens站到了trigger volume上面， returns a bool every frame
		OpenDoor();
		LastDoorOpenTime = GetWorld()->GetTimeSeconds();
	}

	//检查是不是不该关门了， 时间到了没有
	
	if (LastDoorOpenTime + CloseDelayOfDoor < GetWorld()->GetTimeSeconds())
	{
		CloseDoor();
	}
}

