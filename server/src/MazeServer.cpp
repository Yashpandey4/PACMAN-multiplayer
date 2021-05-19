#include <server/MazeServer.h>
#include <server/Server.h>
#include<unistd.h>
#include <iostream>
#include <bits/stdc++.h>
#include <stdio.h>

/**
 * Each tile means something different.
 * 0: Snack.
 * 1: Wall.
 * 2: Ghost House.
 * 3: Power snack.
 * 4: Empty.
 */
void generates();
void enlarges();
const int height = 10;
int grids[height][5];
int temps[height*3][15];
int final_paths[height*3][30];
int final_tiles2[height*3][30];
int temp_cells2[height*3 + 4][30];
int temps2[30][height*3 + 4];
int z = 10;

/**
 * Constructor or initialiser for Maze
 * Give codes to the randomly generated maze
 */
MazeServer::MazeServer(){
    srand((unsigned)time(0));
    generates();
    enlarges();
    for(int i = 0; i < height*3; i++){
        for(int j = 0; j < 30; j++){
            temp_cells2[i + 2][j] = final_tiles2[i][j];
        }
    }
    for(int j = 0; j < 30; j++){
        temp_cells2[0][j] = 4;
        temp_cells2[1][j] = 4;
        temp_cells2[height*3 + 2][j] = 4;
        temp_cells2[height*3 + 3][j] = 4;
    }
    for(int i = 0; i < height*3 + 4; i++){
        for(int j = 0; j < 30; j++){
            cells[j][i] = temp_cells2[i][j];
            temps2[j][i] = temp_cells2[i][j];
        }
    }
    for(int i = 10; i < 20; i++){
        cells[i][16] = 1;
        cells[i][19] = 1;
        temps2[i][16] = 1;
        temps2[i][19] = 1;
    }
    for(int j = 16; j < 20; j++){
        cells[10][j] = 1;
        cells[19][j] = 1;
        temps2[10][j] = 1;
        temps2[19][j] = 1;
    }
    for(int j = 2; j < height*3 + 2; j++){
        for(int i = 0; i < 30; i++){
            if(i == 0 || i == 29 || j == 2 || j == height*3 + 1){
                cells[i][j] = 1;
                temps2[i][j] = 1;
            }
            else if(j == 3 || j == height*3 || i == 1 || i == 28){
                cells[i][j] = 0;
                temps2[i][j] = 0;
            }
            else if(cells[i][j] == 2 || cells[i][j] == 4){
                cells[i][j] = 0;
            }
            else if(cells[i][j] == 0){
                
            }
            else if(cells[i][j] != 0){
                cells[i][j] = 1;
                temps2[i][j] = 1;
            }
        }
    }
    cells[16][16] = 2;
    cells[14][16] = 2;
    cells[15][16] = 2;
    cells[29][17] = 4;
    cells[0][17] = 4;
    temps2[16][16] = 2;
    temps2[14][16] = 2;
    temps2[15][16] = 2;
    temps2[29][17] = 4;
    temps2[0][17] = 4;
    for(int i = 11; i < 19; i++){
        for(int j = 17; j < 19; j++){
            cells[i][j] = 4;
            temps2[i][j] = 4;
        }
    }
    int power = 0;
    while(power < 5){
        int i = rand()%29;
        int j = rand()%33;
        if(cells[i][j] == 0){
            cells[i][j] = 3;
            temps2[i][j] = 3;
            power++;
        }
    }
}

/**
 * returns the cell type (orientation of walls) at a particular (x,y) co-ordinate
 * @param x - coordinate
 * @param y - coordinate
 * @return a number from 1-32 corresponding to wall orientation
 */
int MazeServer::getCellCode(int x, int y) {
    return cells[x][y];
}

/**
 * Determines if character movement is blocked by cell of a specific type - this is done since Pacman and the Ghosts
 * Should be able to move around in the maze but shouldn't be able to go through the walls
 * @param x coordinate
 * @param y coordinate
 * @return True if character is blocked
 */
bool MazeServer::isCellBlockingCharacter(int x, int y) {
    return (cells[x][y] == 1 || cells[x][y] == 2);
}

/**
 * Identifies intersection tiles in maze
 * @param x coordinate
 * @param y coordinate
 * @return True if intersection
 */
bool MazeServer::isMazeIntersection(int i, int j)
{
    if((temps2[i][j + 1] == 0 || temps2[i][j + 1] == 3 || temps2[i][j + 1] == 4 || temps2[i][j - 1] == 0 || temps2[i][j - 1] == 3 || temps2[i][j - 1] == 4)
        && (temps2[i + 1][j] == 0 || temps2[i + 1][j] == 3 || temps2[i + 1][j] == 4 || temps2[i - 1][j] == 0 || temps2[i - 1][j] == 3 || temps2[i - 1][j] == 4)
        && (temps2[i][j] == 0 || temps2[i][j] == 3 || temps2[i][j] == 4)){
        return true;
    }
    else{
        return false;
    }
}

/**
 * Generates 5 x 9 grid of random tetris
 */
void generates(){
    int i = 0;
    int j = 0;
    while(j < 5){
        while(i < height){
            z++;
            if(grids[i][j] != 0){
                i++;
                continue;
            }
            int random = (rand()%19) + 1;

            if(random == 1){
                if(i == height - 1 || j == 4){
                    continue;
                }
                if(grids[i + 1][j] != 0 || grids[i][j + 1] != 0){
                    continue;
                }
                else{
                    grids[i][j] = z;
                    grids[i + 1][j] = z;
                    grids[i][j + 1] = z;
                }
            }

            else if(random == 2){
                if(i == 0 || j == 4){
                    continue;
                }
                if(grids[i - 1][j + 1] != 0 || grids[i][j + 1] != 0){
                    continue;
                }
                else{
                    grids[i][j] = z;
                    grids[i - 1][j + 1] = z;
                    grids[i][j + 1] = z;
                }
            }

            else if(random == 3){
                if(i == height - 1 || j == 4){
                    continue;
                }
                if(grids[i + 1][j + 1] != 0 || grids[i][j + 1] != 0){
                    continue;
                }
                else{
                    grids[i][j] = z;
                    grids[i + 1][j + 1] = z;
                    grids[i][j + 1] = z;
                }
            }

            else if(random == 4){
                if(i == height - 1 || j == 4){
                    continue;
                }
                if(grids[i + 1][j] != 0 || grids[i + 1][j + 1] != 0){
                    continue;
                }
                else{
                    grids[i][j] = z;
                    grids[i + 1][j] = z;
                    grids[i + 1][j + 1] = z;
                }
            }

            else if(random == 5){
                if(i == height - 1 || j >= 3){
                    continue;
                }
                if(grids[i][j + 1] != 0 || grids[i][j + 2] != 0 || grids[i + 1][j] != 0){
                    continue;
                }
                else{
                    grids[i][j] = z;
                    grids[i][j + 1] = z;
                    grids[i][j + 2] = z;
                    grids[i + 1][j] = z;
                }
            }

            else if(random == 6){
                if(i == 0 || j >= 3){
                    continue;
                }
                if(grids[i][j + 1] != 0 || grids[i][j + 2] != 0 || grids[i - 1][j + 2] != 0){
                    continue;
                }
                else{
                    grids[i][j] = z;
                    grids[i][j + 1] = z;
                    grids[i][j + 2] = z;
                    grids[i - 1][j + 2] = z;
                }
            }

            else if(random == 7){
                if(i == height - 1 || j >= 3){
                    continue;
                }
                if(grids[i][j + 1] != 0 || grids[i][j + 2] != 0 || grids[i + 1][j + 2] != 0){
                    continue;
                }
                else{
                    grids[i][j] = z;
                    grids[i][j + 1] = z;
                    grids[i][j + 2] = z;
                    grids[i + 1][j + 2] = z;
                }
            }

            else if(random == 8){
                if(i == height - 1 || j >= 3){
                    continue;
                }
                if(grids[i + 1][j + 1] != 0 || grids[i + 1][j + 2] != 0 || grids[i + 1][j] != 0){
                    continue;
                }
                else{
                    grids[i][j] = z;
                    grids[i + 1][j + 1] = z;
                    grids[i + 1][j + 2] = z;
                    grids[i + 1][j] = z;
                }
            }

            else if(random == 9){
                if(i == height - 1 || j == 3 || j == 4){
                    continue;
                }
                if(grids[i][j + 1] != 0 || grids[i][j + 2] != 0 || grids[i + 1][j + 1] != 0){
                    continue;
                }
                grids[i][j] = z;
                grids[i][j + 1] = z;
                grids[i][j + 2] = z;
                grids[i + 1][j + 1] = z;
            }

            else if(random == 10){
                if(i == 0 || j == 3 || j == 4){
                    continue;
                }
                if(grids[i][j + 1] != 0 || grids[i][j + 2] != 0 || grids[i - 1][j + 1] != 0){
                    continue;
                }
                grids[i][j] = z;
                grids[i][j + 1] = z;
                grids[i][j + 2] = z;
                grids[i - 1][j + 1] = z;
            }

            else if(random == 11){
                if( i == 0 || i == height - 1 || j == 4){
                    continue;
                }
                if(grids[i + 1][j + 1] != 0 || grids[i - 1][j + 1] != 0 || grids[i][j + 1] != 0){
                    continue;
                }
                grids[i][j] = z;
                grids[i + 1][j + 1] = z;
                grids[i - 1][j + 1] = z;
                grids[i][j + 1] = z;
            }

            else if(random == 12){
                if( i == height - 2 || i == height - 1 || j == 4){
                    continue;
                }
                if(grids[i + 1][j] != 0 || grids[i + 2][j] != 0 || grids[i + 1][j + 1] != 0){
                    continue;
                }
                grids[i][j] = z;
                grids[i + 1][j] = z;
                grids[i + 2][j] = z;
                grids[i + 1][j + 1] = z;
            }

            else if(random == 13){
                if(i >= height - 2 || j == 4){
                    continue;
                }
                if(grids[i + 1][j] != 0 || grids[i + 2][j] != 0 || grids[i][j + 1] != 0){
                    continue;
                }
                grids[i][j] = z;
                grids[i + 1][j] = z;
                grids[i + 2][j] = z;
                grids[i][j + 1] = z;
            }

            else if(random == 14){
                if(i >= height - 2 || j == 4){
                    continue;
                }
                if(grids[i + 1][j + 1] != 0 || grids[i + 2][j + 1] != 0 || grids[i][j + 1] != 0){
                    continue;
                }
                grids[i][j] = z;
                grids[i + 1][j + 1] = z;
                grids[i + 2][j + 1] = z;
                grids[i][j + 1] = z;
            }

            else if(random == 15){
                if(i >= height - 2 || j == 4){
                    continue;
                }
                if(grids[i + 1][j] != 0 || grids[i + 2][j] != 0 || grids[i + 2][j + 1] != 0){
                    continue;
                }
                grids[i][j] = z;
                grids[i + 1][j] = z;
                grids[i + 2][j] = z;
                grids[i + 2][j + 1] = z;
            }

            else if(random == 16){
                if(i <= 1 || j == 4){
                    continue;
                }
                if(grids[i - 1][j + 1] != 0 || grids[i - 2][j + 1] != 0 || grids[i][j + 1] != 0){
                    continue;
                }
                grids[i][j] = z;
                grids[i - 1][j + 1] = z;
                grids[i - 2][j + 1] = z;
                grids[i][j + 1] = z;
            }

            else if(random == 17){
                if(rand()%2 == 0){
                    continue;
                }
                if(j == 4){
                    continue;
                }
                else if(grids[i][j + 1] != 0){
                    continue;
                }
                else{
                    grids[i][j] = z;
                    grids[i][j + 1] = z;
                }
            }

            else if(random == 18){
                if(rand()%2 == 0){
                    continue;
                }
                if(i == height - 1){
                    continue;
                }
                else if(grids[i + 1][j] != 0){
                    continue;
                }
                else{
                    grids[i][j] = z;
                    grids[i + 1][j] = z;
                }
            }
            else if(random == 19){
                if(rand()%2 == 0){
                    continue;
                }
                    grids[i][j] = -1;
            }
            i++;
        }
        i = 0;
        j++;
    }
}

/**
 * Converts 5 x 9 grids to 15 x 27 grids and then takes reflection, size of final grids is 30 x 27
 */
void enlarges(){
    grids[height/2 - 1][0] = 2;
    grids[height/2 - 1][1] = 2;
    grids[height/2][0] = 2;
    grids[height/2][1] = 2;
    int y = -2;
    for(int i = 0; i < height*3; i++){
        for(int j = 0; j < 15; j++){
            temps[i][j] = grids[i/3][j/3];
        }
    }
    for(int i = 0; i < height*3; i++){
        for(int j = 15; j < 30; j++){
            final_paths[i][j] = temps[i][j - 15];
        }
    }
    for(int i = 0; i < height*3; i++){
        for(int j = 0; j < 15; j++){
            final_paths[i][j] = temps[i][14 - j]*2;
        }
    }
    for(int i = 0; i < height*3; i++){
        for(int j = 0; j < 30; j++){
            int flag = 0;
            if(i == 0){
                final_tiles2[i][j] = 0;
                continue;
            }
            if(i == height*3){
                final_tiles2[i][j] = 0;
                continue;
            }
            if(j == 29){
                final_tiles2[i][j] = 0;
                continue;
            }
            if(j == 0){
                final_tiles2[i][j] = 0;
                continue;
            }
            if(final_paths[i][j] == final_paths[i][j - 1] && final_paths[i][j] == final_paths[i][j + 1] 
                && final_paths[i][j] == final_paths[i + 1][j] && final_paths[i][j] == final_paths[i - 1][j]
                && final_paths[i][j] == final_paths[i + 1][j + 1] && final_paths[i][j] == final_paths[i + 1][j - 1]
                && final_paths[i][j] == final_paths[i - 1][j + 1] && final_paths[i][j] == final_paths[i - 1][j - 1]){
                final_tiles2[i][j] = final_paths[i][j];
            }
            else{
                final_tiles2[i][j] = 0;
            }
        }
    }
}