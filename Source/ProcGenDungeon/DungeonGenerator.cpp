// DungeonGenerator.cpp

#include "DungeonGenerator.h"
#include "Engine/World.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ADungeonGenerator::ADungeonGenerator()
{
 PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ADungeonGenerator::BeginPlay()
{
 Super::BeginPlay();
}

// Called every frame
void ADungeonGenerator::Tick(float DeltaTime)
{
 Super::Tick(DeltaTime);
}

void ADungeonGenerator::SetSize(float NewWidth, float NewHeight, float NewDepth)
{
 Width = NewWidth;
 Height = NewHeight;
 Depth = NewDepth;
 Size = FVector(Width, Height, Depth);
}

void ADungeonGenerator::GenerateDungeon()
{
 // Clear any previously spawned dungeon pieces
 SpawnedDungeonPieces.Empty();

 // Generate the dungeon layout using wave function collapse algorithm
 for (int32 i = 0; i < NumDungeonPieces; i++)
 {
  ADungeonPiece* NewDungeonPiece = GetWorld()->SpawnActor<ADungeonPiece>(ADungeonPiece::StaticClass());
  SpawnedDungeonPieces.Add(NewDungeonPiece);
 }

 // Spawn the dungeon pieces
 SpawnDungeonPieces();
}

void ADungeonGenerator::SpawnDungeonPieces()
{
 for (ADungeonPiece* DungeonPiece : SpawnedDungeonPieces)
 {
  // Find a valid location to place the dungeon piece
  bool bPlaced = false;
  while (!bPlaced)
  {
   FVector Location = FVector(FMath::RandRange(0.0f, Width), FMath::RandRange(0.0f, Height), FMath::RandRange(0.0f, Depth));
   DungeonPiece->SetActorLocation(Location);

   // Check if the dungeon piece can be placed at the location
   bPlaced = true;
   for (ADungeonPiece* OtherDungeonPiece : SpawnedDungeonPieces)
   {
    if (OtherDungeonPiece != DungeonPiece && !CanPlaceDungeonPiece(DungeonPiece, OtherDungeonPiece))
    {
     bPlaced = false;
     break;
    }
   }
  }
 }
}

bool ADungeonGenerator::CanPlaceDungeonPiece(ADungeonPiece* DungeonPiece, ADungeonPiece* OtherDungeonPiece)
{
 // Check if the sides and biome type match
 return CheckSides(DungeonPiece, OtherDungeonPiece) && CheckBiomeType(DungeonPiece, OtherDungeonPiece);
}

bool ADungeonGenerator::CheckSides(ADungeonPiece* DungeonPiece, ADungeonPiece* OtherDungeonPiece)
{
 // Check if the sides of the dungeon piece match with the sides of the other dungeon pieces
 for (int32 i = 0; i < DungeonPiece->Sides.Num(); i++)
 {
  if (DungeonPiece->Sides[i] != OtherDungeonPiece->Sides[i])
  {
   return false;
  }
 }
 return true;
}

bool ADungeonGenerator::CheckBiomeType(ADungeonPiece* DungeonPiece, ADungeonPiece* OtherDungeonPiece)
{
 // Check if the biome type of the dungeon piece matches with the biome type of the other dungeon piece
 for (int32 BiomeType : DungeonPiece->BiomeTypes)
 {
  if (BiomeType == OtherDungeonPiece->BiomeType)
  {
   int32 Dice = FMath::RandRange(0, 100);
   if (Dice >= 70)
   {
    return true;
   }
  }
 }
 return false;
}

void ADungeonGenerator::RotateDungeonPiece(ADungeonPiece* DungeonPiece, int32 Rotation)
{
 FRotator NewRotation = FRotator(0.0f, Rotation, 0.0f);
 DungeonPiece->SetActorRotation(NewRotation);
}