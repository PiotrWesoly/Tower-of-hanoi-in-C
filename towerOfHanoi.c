#include "primlib.h"


#define NUMBER_OF_PEGS 10
#define NUMBER_OF_DISKS 3
#define COLOR GREEN
#define GROUND_LEVEL screenHeight()
#define WIDTH_OF_PEG 15.0/NUMBER_OF_PEGS
#define X_POSITION_OF_PEG screenWidth()/(1+NUMBER_OF_PEGS)
#define CENTER_OF_PEG X_POSITION_OF_PEG+WIDTH_OF_PEG/2
#define WIDTH_OF_DISK ((X_POSITION_OF_PEG/2)-2)/NUMBER_OF_DISKS
#define HEIGHT_OF_DISK 200/NUMBER_OF_DISKS
#define HEIGHT_OF_PEG HEIGHT_OF_DISK*(NUMBER_OF_DISKS+1)
#define MAX_HEIGHT 200
#define SPEED 0.001

void mapCreation();
void drawingPegs();
void drawingDisks();
void moveDisk(int fromPeg, int toPeg, int logicMap[NUMBER_OF_DISKS][NUMBER_OF_PEGS]);
void win(int logicMap[NUMBER_OF_DISKS][NUMBER_OF_PEGS]);
void validMove(int rows,int temporar, int toPeg,int fromPeg, int logicMap[NUMBER_OF_DISKS][NUMBER_OF_PEGS],int* finishRowAddress,int* canAnimate);
void animations(int startRowAddress, int finishRowAddress, int fromPeg, int toPeg, int logicMap[NUMBER_OF_DISKS][NUMBER_OF_PEGS], int diskValue,int canAnimate);
int main()
{

    if(initGraph())
	{
		exit(3);
	}

    int logicMap[NUMBER_OF_DISKS][NUMBER_OF_PEGS];
    int fromPeg;
    int toPeg;
     
    mapCreation(logicMap);
    while(0==isKeyDown(SDLK_ESCAPE))
    {
        drawingPegs();
        drawingDisks(logicMap);
        updateScreen();
        fromPeg= getkey();
        toPeg= getkey();
        fromPeg-='0';
        toPeg-='0';
        if( fromPeg==0) fromPeg=10;
        if( toPeg==0) toPeg=10;
        if (pollkey()==SDLK_ESCAPE || toPeg==SDLK_ESCAPE || fromPeg==SDLK_ESCAPE) break;
        moveDisk(fromPeg, toPeg,logicMap);
        updateScreen();
        win(logicMap);


    }
}


/******************************************LOGICAL PART******************************************/
void mapCreation(int logicMap[NUMBER_OF_DISKS][NUMBER_OF_PEGS])
{

    int rows,columns;
    int diskNumber=0;

    for(diskNumber=0;diskNumber<NUMBER_OF_DISKS;diskNumber++)
    {logicMap[diskNumber][0]=diskNumber+1;
    }
    for(columns=1;columns<NUMBER_OF_PEGS;columns++)
	{
        for(rows=0;rows<NUMBER_OF_DISKS;rows++)
        {
            logicMap[rows][columns]=0;
        }
    }
}

void moveDisk(int fromPeg, int toPeg, int logicMap[NUMBER_OF_DISKS][NUMBER_OF_PEGS])
{
    int rows=0;
    int temporar=0;
    int startRowAddress=0;
    int finishRowAddress=0;
    int canAnimate=0;

    if(fromPeg<=0 || fromPeg>NUMBER_OF_PEGS || toPeg<=0 || toPeg>NUMBER_OF_PEGS) return;
    while (rows<NUMBER_OF_DISKS)
    {
        if  (logicMap[rows][fromPeg-1]!=0)
            {   temporar=logicMap[rows][fromPeg-1];
                validMove(rows,temporar, toPeg, fromPeg, logicMap, &finishRowAddress, &canAnimate);
                startRowAddress=rows;
                break;}
        else rows++;
    }
    
   animations(startRowAddress,finishRowAddress, fromPeg, toPeg, logicMap, temporar, canAnimate);
       rows=0;

    while(rows<NUMBER_OF_DISKS)
    {   if (logicMap[rows][toPeg-1]<temporar && logicMap[rows][toPeg-1]!=0)break;
        else if(logicMap[rows][toPeg-1]>temporar && rows>0) {logicMap[rows-1][toPeg-1]=temporar;break;}
        else if(logicMap[NUMBER_OF_DISKS-1][toPeg -1]==0){logicMap[NUMBER_OF_DISKS-1][toPeg-1]=temporar; break;}
        if(logicMap[rows][toPeg-1]==0 )rows++;
         else break;
}
}


void validMove(int rows,int temporar, int toPeg,int fromPeg, int logicMap[NUMBER_OF_DISKS][NUMBER_OF_PEGS], int* finishRowAddress, int* canAnimate)
{
    int canMove;
     for(canMove=0;canMove<NUMBER_OF_DISKS;canMove++)
            { if (logicMap[canMove][toPeg-1]<temporar && logicMap[canMove][toPeg-1]!=0)break;
                    else if(logicMap[NUMBER_OF_DISKS-1][toPeg-1]==0 )
                    {logicMap[rows][fromPeg-1]=0;
                        *finishRowAddress=canMove+NUMBER_OF_DISKS-1;
                        *canAnimate=1;
                        break;
                    }
                    else if(logicMap[canMove][toPeg-1]>temporar){logicMap[rows][fromPeg-1]=0; *finishRowAddress=canMove-1;
                        *canAnimate=1;
                    break;}
                    }
}


void win(int logicMap[NUMBER_OF_DISKS][NUMBER_OF_PEGS])
{
     if(logicMap[NUMBER_OF_DISKS-1][NUMBER_OF_PEGS-1]==NUMBER_OF_DISKS && logicMap[0][NUMBER_OF_PEGS-1]==1){
         do
        {
            drawingDisks(logicMap);
            filledRect(0,0,screenWidth()/2,screenHeight()/2,BLACK);
            textout(screenWidth()/4, screenHeight()/3, "Conratulations, you won! press Esc to exit", YELLOW) ;
            updateScreen();
            
        }while(0==isKeyDown(SDLK_ESCAPE));       
    
}
    }


/*****************************************GRAPHICAL PART***********************************/



void drawingPegs()
{
    filledRect(0,0,screenWidth()-1,screenHeight()-1,BLACK);
    
    int pegNumber=1;
    
     
    for(pegNumber=1; pegNumber<=NUMBER_OF_PEGS;pegNumber++)
    {
        filledRect(X_POSITION_OF_PEG*pegNumber, GROUND_LEVEL,X_POSITION_OF_PEG*pegNumber+WIDTH_OF_PEG, GROUND_LEVEL-HEIGHT_OF_PEG,WHITE);
    }

}


void drawingDisks(int diskPosition[NUMBER_OF_DISKS][NUMBER_OF_PEGS])
    {
        int diskNumber;
        int pegNumber;
        int decrement;

        for(pegNumber=0;pegNumber<NUMBER_OF_PEGS;pegNumber++)
        {
        for(diskNumber=0 , decrement=NUMBER_OF_DISKS;(diskNumber<NUMBER_OF_PEGS) & (decrement>0);diskNumber++ ,decrement --)
        {
            if(diskPosition[0][0]==1)
            textout(screenWidth()/5, screenHeight()/4, "Use keys '0-9' to move, press Esc to exit",YELLOW);
            if(diskPosition[diskNumber][pegNumber]==0)continue;
            filledRect ((pegNumber+1)*CENTER_OF_PEG-(WIDTH_OF_DISK*diskPosition[diskNumber][pegNumber]),
                        GROUND_LEVEL-HEIGHT_OF_DISK*(decrement),
                        (pegNumber+1)*CENTER_OF_PEG+(WIDTH_OF_DISK*diskPosition[diskNumber][pegNumber]),
                        GROUND_LEVEL-(decrement-1)*HEIGHT_OF_DISK,
                        COLOR);
    }
    }
    }
    
    
    
void animations(int startRowAddress, int finishRowAddress, int fromPeg, int toPeg, int logicMap[NUMBER_OF_DISKS][NUMBER_OF_PEGS], int diskValue, int canAnimate)
  {
      
      
      if(canAnimate==0) return;
     
        /*UP ANIMATION*/
    
int move=0;

      do
      {  filledRect ((fromPeg)*CENTER_OF_PEG-(WIDTH_OF_DISK*diskValue),
                    GROUND_LEVEL-HEIGHT_OF_DISK*((NUMBER_OF_DISKS-1)-startRowAddress+move),
                    (fromPeg)*CENTER_OF_PEG+(WIDTH_OF_DISK*diskValue),
                    GROUND_LEVEL-HEIGHT_OF_DISK*((NUMBER_OF_DISKS)-startRowAddress+move),
                    COLOR);
                    SDL_Delay(SPEED);
                  updateScreen();
                  drawingPegs();
                  drawingDisks(logicMap);
                  move+=1;
      }
while((GROUND_LEVEL-HEIGHT_OF_DISK*((NUMBER_OF_DISKS)-startRowAddress+move))>MAX_HEIGHT);
                
         /*RIGHT ANIMATION*/       
move=0;

if(fromPeg<toPeg)
{
  do
  {  filledRect ((fromPeg)*CENTER_OF_PEG-(WIDTH_OF_DISK*diskValue)+move,
                MAX_HEIGHT+HEIGHT_OF_DISK,
                (fromPeg)*CENTER_OF_PEG+(WIDTH_OF_DISK*diskValue)+move,
                MAX_HEIGHT,
                COLOR);
                SDL_Delay(SPEED);
              updateScreen();
              drawingPegs();
              drawingDisks(logicMap);
              move+=1;
  }
  while(((fromPeg)*CENTER_OF_PEG+(WIDTH_OF_DISK*diskValue)+move)!=(toPeg)*CENTER_OF_PEG+(diskValue*WIDTH_OF_DISK));
            
}
else
{     /*LEFT ANIMATION*/
  do
  {  filledRect ((fromPeg)*CENTER_OF_PEG-(WIDTH_OF_DISK*diskValue)-move,
                MAX_HEIGHT+HEIGHT_OF_DISK,
                (fromPeg)*CENTER_OF_PEG+(WIDTH_OF_DISK*diskValue)-move,
                MAX_HEIGHT,
                COLOR);
                SDL_Delay(SPEED);
              updateScreen();
              drawingPegs();
              drawingDisks(logicMap);
              move+=1;
  }
  while(((fromPeg)*CENTER_OF_PEG+(WIDTH_OF_DISK*diskValue)-move)>(toPeg)*CENTER_OF_PEG+(diskValue*WIDTH_OF_DISK));
  
}
    /*DOWN ANIMATION*/
move=0;
  do
  {  filledRect ((toPeg)*CENTER_OF_PEG-(diskValue*WIDTH_OF_DISK),
                MAX_HEIGHT+move,
                (toPeg)*CENTER_OF_PEG+(diskValue*WIDTH_OF_DISK),
                MAX_HEIGHT+HEIGHT_OF_DISK+move,
                COLOR);
                SDL_Delay(SPEED);
              updateScreen();
              drawingPegs();
              drawingDisks(logicMap);
              move+=1;
  }
  while ((MAX_HEIGHT+move)!=GROUND_LEVEL-HEIGHT_OF_DISK*((NUMBER_OF_DISKS)-finishRowAddress));
   


}


