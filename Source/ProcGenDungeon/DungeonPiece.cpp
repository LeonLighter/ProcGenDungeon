// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonPiece.h"




// Sets default values
ADungeonPiece::ADungeonPiece()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create the mesh component
	DungeonMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Dungeon Mesh"));
	RootComponent = DungeonMesh;

	// Create the box collision component
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));
	BoxCollision->SetupAttachment(DungeonMesh);
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

// function to set the size of the dungeon piece using the width, height and depth
void ADungeonPiece::SetSize(float NewWidth, float NewHeight, float NewDepth)
{
	Width = NewWidth;
	Height = NewHeight;
	Depth = NewDepth;
	Size = FVector(Width, Height, Depth);
}

