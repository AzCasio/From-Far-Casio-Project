/*****************************************************************/
/*                                                               */
/*   CASIO fx-9860G SDK Library                                  */
/*                                                               */
/*   File name : [ProjectName].c                                 */
/*                                                               */
/*   Copyright (c) 2006 CASIO COMPUTER CO., LTD.                 */
/*                                                               */
/*****************************************************************/
#include "fxlib.h"
#include "stdio.h"
#include "math.h"
#include "MonochromeLib.h"
void userInterface();
void display();
void generateOutputs();
void useOutputs();
void displayExternal();
//****************************************************************************
//  AddIn_main (Sample program main function)
//
//  param   :   isAppli   : 1 = This application is launched by MAIN MENU.
//                        : 0 = This application is launched by a strip in eACT application.
//
//              OptionNum : Strip number (0~3)
//                         (This parameter is only used when isAppli parameter is 0.)
//
//  retval  :   1 = No error / 0 = Error
//
//****************************************************************************
int output1, output2, output3;
int const X0=1580160; // les trois seed sont considerees comme origines de l'espace. MULTIPLES DE 128, X0-1580160/128 donne le cube actuel(je crois)
int const Y0=2144640;
int const Z0=2745088;
int X=0;         // coordonees    X%128 donne donc x dans le cube actuel
int Y=0;
int Z=0;
int sunStorageX[10];
int sunStorageY[10];
int sunStorageZ[10];
int astralStorageX1[90];
int astralStorageY1[90];
int astralStorageZ1[90];
char i, o, p, x, y, z;
int systemDensity = 0;
int planetDensity = 0;
int planetX, planetY, planetZ, sunX, sunY, sunZ, planetCount;
int AddIn_main(int isAppli, unsigned short OptionNum){
    //userInterface();
    generateOutputs();                                   //normalement on apelle juste userInterface mais ca provoque le bug: Lignes de planentes 
    displayExternal(0,0,0,0);
    while(!IsKeyDown(KEY_CTRL_EXIT)){
        if(IsKeyDown(KEY_CTRL_UP)){
            --y;
            displayExternal(0,x,y,z);
        }
        if(IsKeyDown(KEY_CTRL_DOWN)){
            ++y;
            displayExternal(0,x,y,z);
        }
        if(IsKeyDown(KEY_CTRL_LEFT)){
            --x;
            displayExternal(0,x,y,z);
        }
        if(IsKeyDown(KEY_CTRL_RIGHT)){
            ++x;
            displayExternal(0,x,y,z);
        }
        if(IsKeyDown(KEY_CTRL_SHIFT)){
            --z;
            displayExternal(0,x,y,z);
        }
        if(IsKeyDown(KEY_CTRL_ALPHA)){
            ++z;
            displayExternal(0,x,y,z);
        }
    }
        Sleep(10);
}
void userInterface(){
    int x, y, z;
    x =X%128;
    y =Y%128;
    z =Z%128;
    ML_display_vram();
    while(!(X%128 == 64 && Y%128 == 64 && Z%128 == 64)){   //deplacements           //Sys error quand gauche et droite
        if(IsKeyDown(KEY_CTRL_UP)){
            --Y;
            display(1,x,y,z);
        }
        if(IsKeyDown(KEY_CTRL_DOWN)){
            ++Y;
            display(1,x,y,z);
        }
        if(IsKeyDown(KEY_CTRL_LEFT)){
            --X;
            display(1,x,y,z);
        }
        if(IsKeyDown(KEY_CTRL_RIGHT)){
            ++X;
            display(1,x,y,z);
        }
        if(IsKeyDown(KEY_CTRL_SHIFT)){
            --Z;
            display(1,x,y,z);
        }
        if(IsKeyDown(KEY_CTRL_ALPHA)){
            ++Z;
            display(1,x,y,z);
        }
    }
    display(0,x,y,z);
}
void display(call,x,y,z){
    if(call){
        generateOutputs();
        useOutputs();
        displayExternal(0,x,y,z);  //cube central
        Z = Z-128;
        generateOutputs();
        useOutputs();
        displayExternal(-1,x,y,z); //cube central arriere
        Z = Z+128;
        //if(x<=64 && y<=64){            //VVV cubes lateraux , n'existent pas encore dans dispExternal, les integrer depuis la v 0.1
        //    for (i = 0; i < 1; ++i){
        //        X = X-128;
        //        generateOutputs();
        //        useOutputs();
        //        displayExternal(1+i);
        //        Y = Y-128;
        //        generateOutputs();
        //        useOutputs();
        //        displayExternal(3+i);
        //        X = X+128;
        //        generateOutputs();
        //        useOutputs();
        //        displayExternal(5+i);
        //        Y = Y+128;
        //        Z = Z-128;
        //    }
        //    Z = Z+128;
        //}
        //if(x>=64 && y<=64){
        //    for (i = 0; i < 1; ++i){
        //        X = X+128;
        //        generateOutputs();
        //        useOutputs();
        //        displayExternal(1+i);
        //        Y = Y-128;
        //        generateOutputs();
        //        useOutputs();
        //        displayExternal(3+i);
        //        X = X-128;
        //        generateOutputs();
        //        useOutputs();
        //        displayExternal(5+i);
        //        Y = Y+128;
        //        Z = Z-128;
        //    }
        //    Z = Z+128;
        //}
        //if(x<=64 && y>=64){
        //    for (i = 0; i < 1; ++i){
        //        X = X-128;
        //        generateOutputs();
        //        useOutputs();
        //        displayExternal(1+i);
        //        Y = Y+128;
        //        generateOutputs();
        //        useOutputs();
        //        displayExternal(3+i);
        //        X = X+128;
        //        generateOutputs();
        //        useOutputs();
        //        displayExternal(5+i);
        //        Y = Y-128;
        //        Z = Z-128;
        //    }
        //    Z = Z+128;
        //}
        //if(x>=64 && y>=64){
        //    for (i = 0; i < 1; ++i){
        //        X = X+128;
        //        generateOutputs();
        //        useOutputs();
        //        displayExternal(1+i);
        //        Y = Y+128;
        //        generateOutputs();
        //        useOutputs();
        //        displayExternal(3+i);
        //        X = X-128;
        //        generateOutputs();
        //        useOutputs();
        //        displayExternal(5+i);
        //        Y = Y-128;
        //        Z = Z-128;
        //    }
        //    Z = Z+128;
        //}
    
    } //determine le cube a generer et apelle External 
}
void displayExternal(call,x,y,z){
    if(call==0){
        ML_clear_vram();
        for (i = 0; i < systemDensity-1; ++i){
            ML_circle(x+sunStorageX[i], y+sunStorageY[i], z+sunStorageZ[i], 1);
        }
        for (i = 0; i < planetCount-1; ++i){
            ML_filled_circle(x+astralStorageX1[i], y+astralStorageY1[i], z+astralStorageZ1[i], 1);
        }
    }
    ML_display_vram();
}
void generateOutputs(){// genere 3 constantes en fonc de X Y Z et des seed X0 Y0 Z0
    //int local, local1;
    //local = X0-(X/128);
    //while (local>1000){
    //    local /= 10;
    //}
    srand(X);
    output1 = rand() % 999;
    //output1 = local;
    //local = Y0-(Y/128);
    //while (local>1000){
    //    local /= 10;
    //}
    srand(Y+1);
    output2 = rand() % 999;
    //output2 = local;
    //local = Z0-(Z/128);
    //while (local>1000){
    //    local /= 10;
    //}
    srand(Z);
    output3 = rand() % 999;
    //output3 = local;
    //output1=output1*X;
    //output2=output2*Y;
    //output3=output3*Z;
    //do{                               // les outputs sont redimenssiones a un maximum de 999 
    //    local1 = output1%10;
    //    output1 = (output1-local1)/10;
    //} while (output1>1000);
    //do{
    //    local1 = output2%10;
    //    output2 = (output2-local1)/10;
    //} while (output2>1000);
    //do
    //{
    //    local1 = output3%10;
    //    output3 = (output3-local1)/10;
    //} while (output3>1000);

    useOutputs();
}
void useOutputs(){// rempli les listes d'infos des planetes grace aux outputs (a refaire si systemes solaires)
    srand(output1);
    systemDensity = 5;
    planetX, planetY, planetZ;
    planetCount=0;
    for (i = 0; i <= systemDensity; ++i){
        //create suns

        output1= output1*i;
        srand(output1+i);
        sunX = (rand() % 120)+8;//X
        srand(output2+i);
        sunY = (rand() % 120)+8;//Y
        srand(output3+i);
        sunZ = (rand() % 7)+2;//Z
        sunStorageX[i] = sunX;   //fill storage
        sunStorageY[i] = sunY;
        sunStorageZ[i] = sunZ;
        planetDensity = (rand() % 20)+1;    // create density
        for (o = 0; o < planetDensity; ++o){
            //create planets around sun

            //X
            srand(output1+sunX+o);
            planetX = (rand() % 47) -15;
            if(planetX <= 9 && planetX >= 0){
                planetX = planetX+9;
            }
            if(planetX >= -9 && planetX <= 0){
                planetX = planetX-9;
            }
            planetX = sunX+planetX;

            //Y
            srand(output2+sunY+o);
            planetY = (rand() % 47) -15;
            if(planetY <= 9 && planetY >= 0){
                planetY = planetY+9;
            }
            if(planetY >= -9 && planetY <= 0){
                planetY = planetY-9;
            }
            planetY = sunY+planetY;
            //while(sqrt(pow(planetX-sunX,2)+pow(planetY-sunY,2))>20){
            //    --planetX;
            //    --planetY;
            //}

            //Z
            srand(output3+sunZ+o);
            planetZ = (rand() % 3)+1;
            astralStorageX1[o] = planetX;   //fill storage
            astralStorageY1[o] = planetY;
            astralStorageZ1[o] = planetZ;
            ++planetCount;
            for (p = o-1; p > 0; --p){
                while(fabs(astralStorageX1[p]-astralStorageX1[o]) <= (astralStorageZ1[p]+astralStorageZ1[o]+1)){
                    ++astralStorageX1[p];
                }
                astralStorageZ1[100] = planetZ;
                while(fabs(astralStorageY1[p]-astralStorageY1[o]) <= (astralStorageZ1[p]+astralStorageZ1[o]+1)){
                    ++astralStorageY1[p];
                }
                
            }
            
        }
    }
}




//****************************************************************************
//**************                                              ****************
//**************                 Notice!                      ****************
//**************                                              ****************
//**************  Please do not change the following source.  ****************
//**************                                              ****************
//****************************************************************************


#pragma section _BR_Size
unsigned long BR_Size;
#pragma section


#pragma section _TOP

//****************************************************************************
//  InitializeSystem
//
//  param   :   isAppli   : 1 = Application / 0 = eActivity
//              OptionNum : Option Number (only eActivity)
//
//  retval  :   1 = No error / 0 = Error
//
//****************************************************************************
int InitializeSystem(int isAppli, unsigned short OptionNum)
{
    return INIT_ADDIN_APPLICATION(isAppli, OptionNum);
}

#pragma section