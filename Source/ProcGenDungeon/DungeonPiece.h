// DungeonPiece.h
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "DungeonPiece.generated.h"

USTRUCT(BlueprintType)
struct FTileConnector
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 North = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 East = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 South = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 West = 0;
};

UCLASS()
class PROCGENDUNGEON_API ADungeonPiece : public AActor
{
	GENERATED_BODY()

public:
	ADungeonPiece();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dungeon Piece")
	UBoxComponent* BoxCollision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dungeon Piece")
	int32 BiomeType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dungeon Piece")
	FTileConnector Connections;

	void Rotate90Degrees();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
};