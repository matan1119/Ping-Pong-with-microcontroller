
//Lab 3- LCD Display
//PingPong game
//Controlling the bars using the keypad and display the score on 7seg

#include <stdio.h>  
#include <string.h>
#include "NUC1xx.h"
#include "DrvSYS.h"
#include "DrvGPIO.h"
#include "NUC1xx-LB_002\LCD_Driver.h"
#include "2D_Graphic_Driver.h"
#include "Seven_Segment.h"
#include "scankey.h"


#define X0 15       // Circle initial X 
#define Y0 10       // Circle initial Y
#define R_BAR_X 120 // Right-Bar X-position
#define L_BAR_X 7   // Left-Bar  X-position

unsigned char DisplayBuf [128*8];

int32_t main (void)
{
    int dirX, dirY; // direction of movement of ball in x and y pos
    int movX, movY; // the step size the ball do
    int dir1, dir2; //get the direction to move the bar from player
    int y1 = 30,y2 = 30; // inti point in y axis of bars
    int scr1 = 0, scr2 = 0; // inti the players score to zero
    
    uint8_t r;
    uint8_t x, y;
    
    int n = 0; // used for loops in program
    
    UNLOCKREG();
    DrvSYS_Open(48000000);
    LOCKREG();
    
    Initial_panel();   // init LCD panel for using
    clr_all_panel();                            
    
    OpenKeyPad();    // init keypad for using
    
    x = X0;    // circle center x
    y = Y0;    // circle center y
    r = 5;    // circle radius
    movX = 3;  // x movement
    movY = 3;  // y movement
    dirX = 1;  // x direction
    dirY = 1;  // y direction
    
    while(1) 
    {
            
        dir1 = Scankey(); // get from player1 were to move bar
        dir2 = Scankey(); // get from player2 were to move bar
        
        if(dir1 == 7 && y1 < 50) // if player1 press 7 mean down,
                                                        //and the location in screen limit
            y1 = y1 + 3;                    // moving the bar 3 steps down
        else if(dir1 == 1 && y1 > 10) // if player1 press 7 mean down,
                                                                    //and the location in screen limit
            y1 = y1 -3;        // moving the bar 3 steps up
        
                
        if(dir2 == 9 && y2 < 50) // if player2 press 9 mean down,
                                                        // and the location in screen limit
            y2 = y2 + 3;                    // moving the bar 3 steps down
        else if(dir2 == 3 && y2 > 10) // if player2 press 3 mean down,
                                                                    // and the location in screen limit
            y2 = y2 -3;                                 // moving the bar 3 steps up
        
        
        LineBresenham(R_BAR_X,y2-7, R_BAR_X,y2+7,1);   // draw a line bar
        LineBresenham(L_BAR_X,y1-7, L_BAR_X,y1+7,1);   // draw a line   bat
        CircleBresenham(x, y, r, 1); // draw a circle into display buffer
            
      //cheack if player2 scored
        if((x-r-movX) < L_BAR_X && (y1-7 > y || y > y1+7)){ 
        
        scr1 = scr1 + 1;  // inc player2 score
            
        do{ // display the score 10 time using loop for better display
        
        show_seven_segment(0,scr1);// display number on 7-segment LEDs
        DrvSYS_Delay(500000);   // delay time for keeping 7-segment display 
        close_seven_segment();    // turn off 7-segment LEDs
        n = n + 1;
        
            } while(n<10);
            
        n = 0;      
            
        while(n == 0){  // init the bars and the ball 
                                        //to zero point for replay
            
        LineBresenham(R_BAR_X,y2-7, R_BAR_X,y2+7,0);   // erase a line
        LineBresenham(L_BAR_X,y1-7, L_BAR_X,y1+7,0);   // erase a line          
        CircleBresenham(x, y, r, 0); // erase a circle into display buffer
        DrvSYS_Delay(50000);  
            
        x = 12;     // place the ball on left bar
        y = 30;     //
        y2 = 30;    // init right bar to middle
        y1 = 30;    // init left bar to middle
            
        LineBresenham(R_BAR_X,y2-7, R_BAR_X,y2+7,1);   // draw a line
        LineBresenham(L_BAR_X,y1-7, L_BAR_X,y1+7,1);   // draw a line           
        CircleBresenham(x, y, r, 1); // draw a circle into display buffer
        draw_LCD(DisplayBuf);   
        DrvSYS_Delay(50000);  
        
                n = Scankey(); // if the the player didn't press any number
            }                // the game don't start
        
            n = 0;
        }
        
        //cheack if player1 scored
        // the same func that was described
        // for player2
        if((x+r+movX) > R_BAR_X && (y2-7 > y || y > y2+7)){ 
                                                                                                                
        scr2 = scr2 + 1;                                    
            
        do{
        
        show_seven_segment(3,scr1); // display number on 7-segment LEDs
        DrvSYS_Delay(50000);     // delay time for keeping 7-segment display 
        close_seven_segment();     // turn off 7-segment LEDs
        n = n + 1;
        
            } while(n<10);
        
        n = 0;  
            
        CircleBresenham(x, y, r, 0);//erase a circle from display buffer    
            
        while(n == 0){
        
        LineBresenham(R_BAR_X,y2-7, R_BAR_X,y2+7,0);   // draw a line
        LineBresenham(L_BAR_X,y1-7, L_BAR_X,y1+7,0);   // draw a line           
        CircleBresenham(x, y, r, 0); // draw a circle into display buffer
        DrvSYS_Delay(50000);  
            
        x = 115;
        y = 30;
        y2 = 30;
        y1 = 30;
                
        LineBresenham(R_BAR_X,y2-7, R_BAR_X,y2+7,1);   // draw a line
        LineBresenham(L_BAR_X,y1-7, L_BAR_X,y1+7,1);   // draw a line           
        CircleBresenham(x, y, r, 1); // draw a circle into display buffer
        draw_LCD(DisplayBuf);   
        DrvSYS_Delay(5000);  
        
                n = Scankey();
            }   
            n = 0;
        }
    
    
       draw_LCD(DisplayBuf);             // from display buffer to LCD
       DrvSYS_Delay(50000);         // adjustable delay for vision          
        
       CircleBresenham(x, y, r, 0); // erase a circle from display buffer
     LineBresenham(R_BAR_X,y2-7,R_BAR_X,y2+7,0);   // erase a line
     LineBresenham(L_BAR_X,y1-7,L_BAR_X,y1+7,0);   // erase a line          
            
       x = x + dirX * movX;         // change x of circle center
     y = y + dirY * movY;         // change y of circle center
     if      ((x-r-movX) < L_BAR_X) dirX=1;  // boundary check for changing direction
       else if ((x+r+movX) > R_BAR_X) dirX=-1;
       else if ((y-r)<0)  dirY=1;  
       else if ((y+r)>63) dirY=-1;                  
   }
}



