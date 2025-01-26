// Fill out your copyright notice in the Description page of Project Settings.
// Actor that will represent a piece of the dungeon that will be spawned in the world with the help of the DungeonGenerator class.
// the width and height of the dungeon piece will be determined by the size of the mesh that is attached to this actor.
// this size will be randomized when the dungeon piece is spawned in the world.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "DungeonPiece.generated.h"

UCLASS()
class PROCGENDUNGEON_API ADungeonPiece : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADungeonPiece();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// The mesh that will be attached to this actor
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dungeon Piece")
	UStaticMeshComponent* DungeonMesh;

	// The box component that will be used to check for collision with other dungeon pieces
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dungeon Piece")
	UBoxComponent* BoxCollision;

	// The width of the dungeon piece
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dungeon Piece")
	float Width;

	// The height of the dungeon piece
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dungeon Piece")
	float Height;

	// The depth of the dungeon piece
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dungeon Piece")
	float Depth;

	// The size of the dungeon piece
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dungeon Piece")
	FVector Size;

	// function to set the size of the dungeon piece using the width, height and depth
	UFUNCTION(BlueprintCallable, Category = "Dungeon Piece")
	void SetSize(float NewWidth, float NewHeight, float NewDepth);
	
};
