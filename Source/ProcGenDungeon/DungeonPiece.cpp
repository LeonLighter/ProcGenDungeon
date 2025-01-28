// DungeonPiece.cpp

#include "DungeonPiece.h"

// Sets default values
ADungeonPiece::ADungeonPiece()
{
	PrimaryActorTick.bCanEverTick = true;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));
	RootComponent = BoxCollision;
	BoxCollision->SetBoxExtent(Size);
	BoxCollision->SetCollisionProfileName(TEXT("BlockAllDynamic"));
	BoxCollision->SetNotifyRigidBodyCollision(true);
	BoxCollision->SetSimulatePhysics(true);
	BoxCollision->SetEnableGravity(false);
	BoxCollision->SetConstraintMode(EDOFMode::XZPlane);
	BoxCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

// Called when the game starts or when spawned
void ADungeonPiece::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ADungeonPiece::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ADungeonPiece::SetSize(float NewWidth, float NewHeight, float NewDepth)
{
	Width = NewWidth;
	Height = NewHeight;
	Depth = NewDepth;
	Size = FVector(Width, Height, Depth);
	BoxCollision->SetBoxExtent(Size);
}