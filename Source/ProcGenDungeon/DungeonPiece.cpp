// DungeonPiece.cpp

#include "DungeonPiece.h"

// Sets default values
ADungeonPiece::ADungeonPiece()
{
	PrimaryActorTick.bCanEverTick = true;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));
	RootComponent = BoxCollision;
	BoxCollision->SetBoxExtent(FVector(600, 600, 0));
	BoxCollision->SetConstraintMode(EDOFMode::XZPlane);
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

