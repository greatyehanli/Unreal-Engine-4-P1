// Copyright Yehan 2019

#include "Grabber.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "DrawDebugHelpers.h"

//���OUTûɶ�ã����Ƿŵ�out_��parameterǰ���������Լ����parameterֱ�ӻ��variable value by reference
//Out�ᱻ���Ե���compile time
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
	//ÿһ֡��Ҫ�õ�player����ʲô�������Ŀ�
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPonitRotation
	);
	//UE_LOG(LogTemp, Warning, TEXT("Grabber Reporting: PlayerViewPointLocation= %s PlayerViewPonitRotation= %s "),
	//	*PlayerViewPointLocation.ToString(),
	//	*PlayerViewPonitRotation.ToString()
	//);

	//pawnվ�Ŀռ�����ϵ������Ϊ��ʼ�㣬 �����ӽ�ת���ķ����unit vector�� Ȼ��ͷת���ģ� ���debug�߾�ת����
	FVector LineTracedEnd = PlayerViewPointLocation + Reach*PlayerViewPonitRotation.Vector();

	//��һ����ɫ���ߴ��������۾����ķ���
	DrawDebugLine(
		GetWorld(),
		PlayerViewPointLocation,
		LineTracedEnd,
		FColor(255, 0, 0),
		false,//�Ƿ�������ڣ�����ÿһ֡���debugline�����ڣ��������Ļ���ǣ����涨����Ǵ���ʱ��
		0.f,//����ʱ������Ƕ��֮���������ʧ
		0.f,//DepthPriority
		10.f
	);
	//���ⷢ��ʸ������ȥ̽��ǰ���ķ�Χ

	//��������ײ����ʲô����
	FHitResult Hit;

	//false��˵����ֻ�ں��򵥵�ײ�����������һ������ϸ�ڵ�ײ�������Ȼ������Ҫ�����Լ�����Ϊ
	//trace�����Ǵ�pawn�����ķ������ģ��������Լ��Ļ����߾ͻ��һ��ײ���Լ���Ҳ����defaultPawn�����һ��parameter��actor to ignore������GetOwner����
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());

	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		PlayerViewPointLocation,//trace ��ʼ����
		LineTracedEnd, //trace ��������
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), //we want only look for physics bodies, һ�����е�objects
		TraceParameters // ������ôײ��ʲô��ײ����ײ�������ʲô���ӵģ��򵥵Ļ��Ǹ��ӵ�
	);

	AActor* IsHit = Hit.GetActor();

	//�����nullptr������������δ��룬������Ǿ�����
	if (IsHit) {

		UE_LOG(LogTemp, Warning, TEXT("Grabber Reporting: Pawn Hit %s"), *IsHit->GetName());
	}


}

