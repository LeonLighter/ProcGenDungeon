Dungeon Generator README

Overview

This project implements a procedural dungeon generation system using the Wave Function Collapse (WFC) algorithm in Unreal Engine. The system generates a grid-based dungeon layout by selecting and placing dungeon pieces based on predefined constraints. 
 
Key Components

ADungeonGenerator

The ADungeonGenerator class is responsible for generating the dungeon layout. It contains methods to initialize the grid, collapse the wave function, and propagate constraints.  

Properties:  

	- DungeonPieces: Array of possible dungeon piece blueprints.
	- GridSizeX, GridSizeY: Dimensions of the grid.
	- TileSize: Size of each tile in the grid.
Methods:
  
	- BeginPlay(): Initializes the grid and starts the WFC algorithm.
	- InitializeGrid(): Sets up the grid with all possible pieces and rotations.
	- CollapseWaveFunction(): Main loop of the WFC algorithm, collapses cells with the lowest entropy.
	- CollapseCellAndPropagate(FGridCell& Cell, int32 X, int32 Y): Collapses a cell and propagates constraints to neighbors.
	- PropagateConstraints(int32 X, int32 Y): Updates neighboring cells based on the placed piece.
	- GetLowestEntropyCell(): Finds the cell with the lowest entropy.
	- IsValidPlacement(const TSubclassOf<ADungeonPiece>& Piece, int32 Rotation, int32 X, int32 Y): Checks if a piece can be placed at 	  a given location.
	- GetRotatedConnections(const FTileConnector& Original, int32 Rotations): Rotates the connections of a piece.
	- AreConnectionsCompatible(const FTileConnector& A, const FTileConnector& B, int32 Direction): Checks if the connections of two 	  pieces are compatible.

FGridCell

The FGridCell structure represents a cell in the grid. It stores possible pieces, possible rotations, the placed piece, and whether the cell has been collapsed. 
 
Properties:

	- PossiblePieces: Array of possible dungeon piece blueprints.
	- PossibleRotations: Array of possible rotations (0, 90, 180, 270 degrees).
	- PlacedPiece: The piece placed in this cell.
	- bCollapsed: Whether the cell has been collapsed.

ADungeonPiece

The ADungeonPiece class represents a dungeon piece. It contains properties for collision, biome type, and connections.  

Properties:  

	- BoxCollision: Box component for collision detection.
	- BiomeType: Type of biome for the piece.
	- Connections: Structure defining the connections on each side (North, East, South, West).

Methods:  

	- BeginPlay(): Initializes the piece and draws debug lines for connections.
	- Tick(float DeltaTime): Called every frame.

FTileConnector

The FTileConnector structure defines the connections on each side of a dungeon piece.  

Properties:

	- North, East, South, West: Connection values for each side.

How It Works

1. Initialization:  

	- The grid is initialized with all possible pieces and rotations.
	- Each cell starts with the same entropy (number of possible pieces and rotations).

2. Wave Function Collapse:  

	- The algorithm selects a cell with the lowest entropy.
	- A random piece and rotation are chosen for the cell.
	- The cell is collapsed, and constraints are propagated to neighboring cells.

3. Propagation:  

	- Constraints are propagated to neighboring cells, reducing their possible pieces and rotations.
	- The process continues until all cells are collapsed.

4. Placement:  

	- Dungeon pieces are placed in the world based on the final grid configuration.
	- Debug boxes and lines are drawn to visualize the layout and connections.

Visualization

- Debug Boxes: Drawn at the location of each dungeon piece to visualize the layout.
- Debug Lines: Drawn to visualize the connections of each piece.

This system ensures that the generated dungeon layout is consistent and adheres to the predefined constraints, creating a coherent and visually appealing dungeon.