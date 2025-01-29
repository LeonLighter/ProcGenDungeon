// DungeonGenerator.cpp
#include "DungeonGenerator.h"

ADungeonGenerator::ADungeonGenerator()
{
    PrimaryActorTick.bCanEverTick = false;
}

void ADungeonGenerator::BeginPlay()
{
    Super::BeginPlay();
    InitializeGrid();
    CollapseWaveFunction();
}

void ADungeonGenerator::InitializeGrid()
{
    Grid.SetNum(GridSizeX);
    for (int32 X = 0; X < GridSizeX; X++)
    {
        Grid[X].SetNum(GridSizeY);
        for (int32 Y = 0; Y < GridSizeY; Y++)
        {
            Grid[X][Y].PossiblePieces = DungeonPieces;
            Grid[X][Y].PossibleRotations = {0, 1, 2, 3}; // 0, 90, 180, 270 degrees
        }
    }
}

FGridCell* ADungeonGenerator::GetLowestEntropyCell()
{
    FGridCell* LowestEntropyCell = nullptr;
    int32 LowestEntropy = MAX_int32;

    for (int32 X = 0; X < GridSizeX; X++)
    {
        for (int32 Y = 0; Y < GridSizeY; Y++)
        {
            FGridCell& Cell = Grid[X][Y];
            if (!Cell.bCollapsed)
            {
                int32 Entropy = Cell.PossiblePieces.Num() * Cell.PossibleRotations.Num();
                if (Entropy > 0 && Entropy < LowestEntropy)
                {
                    LowestEntropy = Entropy;
                    LowestEntropyCell = &Cell;
                }
            }
        }
    }
    return LowestEntropyCell;
}

void ADungeonGenerator::CollapseWaveFunction()
{
    // Start with a random cell
    int32 StartX = FMath::RandRange(0, GridSizeX - 1);
    int32 StartY = FMath::RandRange(0, GridSizeY - 1);
    CollapseCellAndPropagate(Grid[StartX][StartY], StartX, StartY);

    // Continue collapsing cells until done
    while (FGridCell* Cell = GetLowestEntropyCell())
    {
        for (int32 X = 0; X < GridSizeX; X++)
        {
            for (int32 Y = 0; Y < GridSizeY; Y++)
            {
                if (&Grid[X][Y] == Cell)
                {
                    CollapseCellAndPropagate(Grid[X][Y], X, Y);
                }
            }
        }
    }
}

void ADungeonGenerator::CollapseCellAndPropagate(FGridCell& Cell, int32 X, int32 Y)
{
    if (Cell.PossiblePieces.Num() == 0) return;

    // Randomly select a piece and rotation
    int32 PieceIndex = FMath::RandRange(0, Cell.PossiblePieces.Num() - 1);
    int32 RotationIndex = FMath::RandRange(0, Cell.PossibleRotations.Num() - 1);

    // Spawn the piece
    FVector Location(X * TileSize, Y * TileSize, 0);
    ADungeonPiece* NewPiece = GetWorld()->SpawnActor<ADungeonPiece>(
        Cell.PossiblePieces[PieceIndex],
        Location,
        FRotator(0, Cell.PossibleRotations[RotationIndex] * 90, 0)
    );

    // Update cell state
    Cell.PlacedPiece = NewPiece;
    Cell.bCollapsed = true;
    Cell.PossiblePieces.Empty();
    Cell.PossibleRotations.Empty();

    // Propagate constraints
    PropagateConstraints(X, Y);
}

void ADungeonGenerator::PropagateConstraints(int32 X, int32 Y)
{
    TArray<TPair<int32, int32>> Directions = {
        {0, 1},  // North
        {1, 0},  // East
        {0, -1}, // South
        {-1, 0}  // West
    };

    for (const auto& Dir : Directions)
    {
        int32 NewX = X + Dir.Key;
        int32 NewY = Y + Dir.Value;

        if (NewX >= 0 && NewX < GridSizeX && NewY >= 0 && NewY < GridSizeY)
        {
            FGridCell& NeighborCell = Grid[NewX][NewY];
            if (!NeighborCell.bCollapsed)
            {
                TArray<TSubclassOf<ADungeonPiece>> ValidPieces;
                TArray<int32> ValidRotations;

                // Check each possible piece and rotation for compatibility
                for (auto& PossiblePiece : NeighborCell.PossiblePieces)
                {
                    for (int32 Rotation : NeighborCell.PossibleRotations)
                    {
                        if (IsValidPlacement(PossiblePiece, Rotation, NewX, NewY))
                        {
                            ValidPieces.AddUnique(PossiblePiece);
                            ValidRotations.AddUnique(Rotation);
                        }
                    }
                }

                // Update possible pieces and rotations
                NeighborCell.PossiblePieces = ValidPieces;
                NeighborCell.PossibleRotations = ValidRotations;
            }
        }
    }

    // Debug: Afficher la grille avec draw debug box
    DrawDebugBox(
        GetWorld(),
        FVector(X * TileSize, Y * TileSize, 0),
        FVector(TileSize/2, TileSize/2, 10),
        FColor::Yellow,
        true,
        -1,
        0,
        5
    );
    
}

bool ADungeonGenerator::IsValidPlacement(const TSubclassOf<ADungeonPiece>& Piece, int32 Rotation, int32 X, int32 Y)
{
    // Check compatibility with all placed neighbors
    TArray<TPair<int32, int32>> Directions = {
        {0, 1},  // North
        {1, 0},  // East
        {0, -1}, // South
        {-1, 0}  // West
    };

    ADungeonPiece* DefaultPiece = Cast<ADungeonPiece>(Piece.GetDefaultObject());
    if (!DefaultPiece) return false;

    FTileConnector RotatedConnections = GetRotatedConnections(DefaultPiece->Connections, Rotation);

    for (int32 Dir = 0; Dir < Directions.Num(); Dir++)
    {
        int32 CheckX = X + Directions[Dir].Key;
        int32 CheckY = Y + Directions[Dir].Value;

        if (CheckX >= 0 && CheckX < GridSizeX && CheckY >= 0 && CheckY < GridSizeY)
        {
            FGridCell& NeighborCell = Grid[CheckX][CheckY];
            if (NeighborCell.PlacedPiece)
            {
                if (!AreConnectionsCompatible(RotatedConnections, NeighborCell.PlacedPiece->Connections, Dir))
                {
                    return false;
                }
            }
        }
    }

    return true;
}

FTileConnector ADungeonGenerator::GetRotatedConnections(const FTileConnector& Original, int32 Rotations)
{
    FTileConnector Result = Original;
    for (int32 i = 0; i < Rotations; i++)
    {
        int32 Temp = Result.North;
        Result.North = Result.West;
        Result.West = Result.South;
        Result.South = Result.East;
        Result.East = Temp;
    }
    return Result;
}

bool ADungeonGenerator::AreConnectionsCompatible(const FTileConnector& A, const FTileConnector& B, int32 Direction)
{
    switch (Direction)
    {
    case 0: // North
        return A.North == B.South;
    case 1: // East
        return A.East == B.West;
    case 2: // South
        return A.South == B.North;
    case 3: // West
        return A.West == B.East;
    default:
        return false;
    }
}