#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DungeonPiece.h"
#include "DungeonGenerator.generated.h"

USTRUCT()
struct FGridCell
{
    GENERATED_BODY()

    TArray<TSubclassOf<ADungeonPiece>> PossiblePieces;
    TArray<int32> PossibleRotations;
    ADungeonPiece* PlacedPiece;
    bool bCollapsed;

    FGridCell() : PlacedPiece(nullptr), bCollapsed(false) {}
};

UCLASS()
class PROCGENDUNGEON_API ADungeonGenerator : public AActor
{
    GENERATED_BODY()

public:
    ADungeonGenerator();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dungeon Generation")
    TArray<TSubclassOf<ADungeonPiece>> DungeonPieces;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dungeon Generation")
    int32 GridSizeX = 10;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dungeon Generation")
    int32 GridSizeY = 10;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dungeon Generation")
    float TileSize = 1200.0f;

protected:
    virtual void BeginPlay() override;

private:
    TArray<TArray<FGridCell>> Grid;
    
    void InitializeGrid();
    void CollapseWaveFunction();
    FGridCell* GetLowestEntropyCell();
    void PropagateConstraints(int32 X, int32 Y);
    bool IsValidPlacement(const TSubclassOf<ADungeonPiece>& Piece, int32 Rotation, int32 X, int32 Y);
    void CollapseCellAndPropagate(FGridCell& Cell, int32 X, int32 Y);
    bool AreConnectionsCompatible(const FTileConnector& A, const FTileConnector& B, int32 Direction);
    FTileConnector GetRotatedConnections(const FTileConnector& Original, int32 Rotations);
};