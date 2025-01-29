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

	//draw debug lines to visualize the connections if they are = 1
	if (Connections.North == 1)
	{
		DrawDebugLine(GetWorld(), GetActorLocation(), GetActorLocation() + FVector(0, 1200, 0), FColor::Red, true, -1, 0, 10);
	}
	if (Connections.East == 1)
	{
		DrawDebugLine(GetWorld(), GetActorLocation(), GetActorLocation() + FVector(1200, 0, 0), FColor::Red, true, -1, 0, 10);
	}
	if (Connections.South == 1)
	{
		DrawDebugLine(GetWorld(), GetActorLocation(), GetActorLocation() + FVector(0, -1200, 0), FColor::Red, true, -1, 0, 10);
	}
	if (Connections.West == 1)
	{
		DrawDebugLine(GetWorld(), GetActorLocation(), GetActorLocation() + FVector(-1200, 0, 0), FColor::Red, true, -1, 0, 10);
	}
}

// Called every frame
void ADungeonPiece::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

