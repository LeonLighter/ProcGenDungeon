// Fill out your copyright notice in the Description page of Project Settings.
// actor that will generate a dungeon.
// We will use the wave function collapse algorithm to generate the dungeon.
// The algorithm will take a set of dungeon pieces and will generate a dungeon using those pieces.




#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DungeonPiece.h"
#include "DungeonGenerator.generated.h"


UCLASS()
class PROCGENDUNGEON_API ADungeonGenerator : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    ADungeonGenerator();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // The dungeon pieces that will be used to generate the dungeon
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dungeon Generator")
    TArray<TSubclassOf<ADungeonPiece>> DungeonPieces;

    // The width of the dungeon
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dungeon Generator")
    float Width;

    // The height of the dungeon
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dungeon Generator")
    float Height;

    // The depth of the dungeon
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dungeon Generator")
    float Depth;

    // The size of the dungeon
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dungeon Generator")
    FVector Size;

    // The number of dungeon pieces that will be spawned in the dungeon
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dungeon Generator")
    int32 NumDungeonPieces;

    // The dungeon pieces that will be spawned in the dungeon
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dungeon Generator")
    TArray<ADungeonPiece*> SpawnedDungeonPieces;

    // function to set the size of the dungeon using the width, height and depth
    UFUNCTION(BlueprintCallable, Category = "Dungeon Generator")
    void SetSize(float NewWidth, float NewHeight, float NewDepth);

    // function to generate the dungeon
    UFUNCTION(BlueprintCallable, Category = "Dungeon Generator")
    void GenerateDungeon();

    // function to spawn the dungeon pieces in the dungeon
    UFUNCTION(BlueprintCallable, Category = "Dungeon Generator")
    void SpawnDungeonPieces();

    // function to check if a dungeon piece can be placed at a certain location based on the biome type of the dungeon piece and if the sides of the dungeon piece match with the sides of the other dungeon pieces
    // returns true if the dungeon piece can be placed at the location, false otherwise and rotates the dungeon piece then checks again if it can be placed until it has checked all possible rotations
    UFUNCTION(BlueprintCallable, Category = "Dungeon Generator")
    static bool CanPlaceDungeonPiece(ADungeonPiece* DungeonPiece, ADungeonPiece* OtherDungeonPiece);
    
    // function to check if the sides of the dungeon piece match with the sides of the other dungeon pieces
    UFUNCTION(BlueprintCallable, Category = "Dungeon Generator")
    static bool CheckSides(ADungeonPiece* DungeonPiece, ADungeonPiece* OtherDungeonPiece);

    // function to check if the dungeon piece can be placed at the location based on the biome type of the dungeon piece
    UFUNCTION(BlueprintCallable, Category = "Dungeon Generator")
    static bool CheckBiomeType(ADungeonPiece* DungeonPiece, ADungeonPiece* OtherDungeonPiece);

    // function that will rotate the dungeon piece
    UFUNCTION(BlueprintCallable, Category = "Dungeon Generator")
    static void RotateDungeonPiece(ADungeonPiece* DungeonPiece, int32 Rotation);
};
