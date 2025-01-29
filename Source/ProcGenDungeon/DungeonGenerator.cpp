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

    // Set random size for the dungeon
    SetSize(FMath::RandRange(3000.0f, 10000.0f), FMath::RandRange(3000.0f, 10000.0f), 0.0f);

    // Set random number of dungeon pieces between 50 and 100
    NumDungeonPieces = FMath::RandRange(50, 100);

    // Generate the dungeon
    GenerateDungeon();
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

    // Check if there are any Blueprints in the array
    if (DungeonPieces.Num() == 0)
    {
        UE_LOG(LogTemp, Error, TEXT("No DungeonPiece Blueprints found"));
        return;
    }

    // Generate the dungeon layout using wave function collapse algorithm
    for (int32 i = 0; i < NumDungeonPieces; i++)
    {
        // Select a random Blueprint from the array
        int32 RandomIndex = FMath::RandRange(0, DungeonPieces.Num() - 1);
        TSubclassOf<ADungeonPiece> SelectedBlueprint = DungeonPieces[RandomIndex];

        // Spawn the dungeon piece using the selected Blueprint
        ADungeonPiece* NewDungeonPiece = GetWorld()->SpawnActor<ADungeonPiece>(SelectedBlueprint);
        if (NewDungeonPiece)
        {
            // Place the first piece around the origin
            if (i == 0)
            {
                NewDungeonPiece->SetActorLocation(FVector(FMath::RandRange(-100.0f, 100.0f), FMath::RandRange(-100.0f, 100.0f), 0.0f));
            }
            SpawnedDungeonPieces.Add(NewDungeonPiece);
        }
    }

    // Spawn the dungeon pieces
    SpawnDungeonPieces();
}

void ADungeonGenerator::SpawnDungeonPieces()
{
    TSet<FVector> OccupiedLocations;

    for (int32 i = 0; i < SpawnedDungeonPieces.Num(); i++)
    {
        ADungeonPiece* DungeonPiece = SpawnedDungeonPieces[i];
        bool bPlaced = false;

        while (!bPlaced)
        {
            FVector Location;
            if (i == 0)
            {
                // Place the first piece around the origin
                Location = FVector(FMath::RandRange(-100.0f, 100.0f), FMath::RandRange(-100.0f, 100.0f), 0.0f);
            }
            else
            {
                // Find a valid location next to an already placed piece (no diagonals)
                ADungeonPiece* PreviousPiece = SpawnedDungeonPieces[FMath::RandRange(0, i - 1)];
                FVector Offset;
                switch (FMath::RandRange(0, 3))
                {
                case 0: Offset = FVector(PreviousPiece->BoxCollision->GetScaledBoxExtent().X * 2, 0, 0); break; // East
                case 1: Offset = FVector(-PreviousPiece->BoxCollision->GetScaledBoxExtent().X * 2, 0, 0); break; // West
                case 2: Offset = FVector(0, PreviousPiece->BoxCollision->GetScaledBoxExtent().Y * 2, 0); break; // North
                case 3: Offset = FVector(0, -PreviousPiece->BoxCollision->GetScaledBoxExtent().Y * 2, 0); break; // South
                }
                Location = PreviousPiece->GetActorLocation() + Offset;
            }

            if (!OccupiedLocations.Contains(Location))
            {
                DungeonPiece->SetActorLocation(Location);
                OccupiedLocations.Add(Location);
                bPlaced = true;
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
        int32 OtherSideIndex = (i + 2) % 4; // Opposite side index
        if (DungeonPiece->Sides[i] != OtherDungeonPiece->Sides[OtherSideIndex])
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
    FRotator NewRotation = FRotator(0.0f, Rotation * 90.0f, 0.0f);
    DungeonPiece->SetActorRotation(NewRotation);
}