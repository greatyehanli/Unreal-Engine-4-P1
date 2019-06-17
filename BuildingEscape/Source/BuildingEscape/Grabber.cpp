// Copyright Yehan 2019

#include "Grabber.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "DrawDebugHelpers.h"

//这个OUT没啥用，就是放的out_的parameter前面来提醒自己这个parameter直接会改variable value by reference
//Out会被忽略掉在compile time
#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	// ...
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPonitRotation;
	//每一帧需要得到player看的什么方向，往哪看
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPonitRotation
	);
	//UE_LOG(LogTemp, Warning, TEXT("Grabber Reporting: PlayerViewPointLocation= %s PlayerViewPonitRotation= %s "),
	//	*PlayerViewPointLocation.ToString(),
	//	*PlayerViewPonitRotation.ToString()
	//);

	//pawn站的空间坐标系的坐标为起始点， 加上视角转动的方向的unit vector， 然后镜头转到哪， 这个debug线就转到哪
	FVector LineTracedEnd = PlayerViewPointLocation + Reach*PlayerViewPonitRotation.Vector();

	//画一个红色的线代表我们眼睛看的方向
	DrawDebugLine(
		GetWorld(),
		PlayerViewPointLocation,
		LineTracedEnd,
		FColor(255, 0, 0),
		false,//是否持续存在，就是每一帧这个debugline都存在，最后满屏幕都是，下面定义的是存在时间
		0.f,//生命时间或者是多久之后这个线消失
		0.f,//DepthPriority
		10.f
	);
	//向外发射矢量线条去探测前方的范围

	//看看我们撞到了什么东西
	FHitResult Hit;

	//false是说我们只在乎简单的撞击体积，不是一个物体细节的撞击体积，然后我们要忽略自己，因为
	//trace光线是从pawn的中心发出来的，不忽略自己的话光线就会第一个撞到自己，也就是defaultPawn，最后一个parameter是actor to ignore，就是GetOwner（）
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());

	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		PlayerViewPointLocation,//trace 开始坐标
		LineTracedEnd, //trace 结束坐标
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), //we want only look for physics bodies, 一个数列的objects
		TraceParameters // 定义怎么撞，什么算撞到，撞击体积是什么样子的，简单的还是复杂的
	);

	AActor* IsHit = Hit.GetActor();

	//如果是nullptr，跳过下面这段代码，如果不是就运行
	if (IsHit) {

		UE_LOG(LogTemp, Warning, TEXT("Grabber Reporting: Pawn Hit %s"), *IsHit->GetName());
	}


}

