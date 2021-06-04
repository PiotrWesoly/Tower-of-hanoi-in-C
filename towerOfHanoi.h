#include "primlib.h"
#include "towerOfHanoi.h"
#include "logicalPart.c"
#include "graphicalPart.c"

#define NUMBER_OF_PEGS 3
#define NUMBER_OF_DISKS 3
#define GROUND_LEVEL screenHeight()
#define X_POSITION_OF_PEG screenWidth()/(1+NUMBER_OF_PEGS)
#define WIDTH_OF_PEG 10
#define HEIGHT_OF_PEG 20*NUMBER_OF_DISKS
#define WIDTH_OF_DISK 10/NUMBER_OF_PEGS
#define HEIGHT_OF_DISK 20/NUMBER_OF_DISKS

void logicLevel();
void drawingPegs();
void drawingDisks();
void moveDisk(int fromPeg, int toPeg, int logicMap[NUMBER_OF_DISKS][NUMBER_OF_PEGS]);
int win();
