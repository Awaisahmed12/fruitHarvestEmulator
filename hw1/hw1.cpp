#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "ArgumentManager.h"

using namespace std;
//global vars
int rows;
int cols;
int globalRotten;
int globalHarvest;
int**matrix;


//declare functions
void harvest(bool inc);
void read_matrix(string filename);
void runDays();
void writeFile(string filename);
//functions
void read_matrix(string filename)
{
    ifstream readingIT(filename);

    if (!readingIT.is_open()){
        cout << "FILE IS EMPTY" << endl;
    }


    readingIT >> rows;
    cols = rows;
   // cout << "ROWS: " << rows << endl;;

    matrix = new int *[rows];


    for (int i = 0; i < rows; i++)
        matrix[i] = new int[cols];

 
    for (int t = 0; t < rows; t++)
    {
        for (int j = 0; j < cols; j++)
        {
            readingIT >> matrix[t][j];
        }
    }
    readingIT.close();
}

void harvest(bool inc)
{
    int harvestKiwi;

        for (int p = 0; p < rows; p++)
    {
        harvestKiwi = 0;
            for (int q = 0; q < rows; q++)
            {

                if (matrix[p][q] >= 6) 
                {
                    harvestKiwi++;
                }

            }
        if (harvestKiwi >= rows/2)
        {
            for (int c=0; c<cols; c++)
            {

                if (matrix[p][c] > 8)
                {
                    globalRotten++;
                }
                else if (matrix[p][c] >= 6 and matrix[p][c] <= 8)
                {
                    globalHarvest++;
                }
                matrix[p][c] =0;
            }
        }
        else if(inc==1){
            for(int x=0;x<rows;x++){
                matrix[p][x]++;
            }
        }
    }
}

void runDays()
{
    //run days
    bool inc=true;
    for (int days=0; days < 7; days++)
    {harvest(inc);
    }
    inc = false;
    harvest(inc);
}

void writeFile(string filename)
{
    ofstream outFile(filename);
    for (int writeRows = 0; writeRows < rows; writeRows++)
    {
        for (int writeCols=0; writeCols<cols; writeCols++)
        {
           outFile << matrix[writeRows][writeRows] << " ";
        }
        outFile << endl;
    }
    outFile << endl;
    outFile << "Harvested kiwis: " << globalHarvest << endl;
    outFile << "Rotten kiwis: " << globalRotten << endl;
    outFile.close();
}
int main(int argc, char * argv[])
{
   ArgumentManager am(argc, argv);
    string infilename = am.get("input");
    string outfilename = am.get("output");

    read_matrix(infilename);

    runDays();
    writeFile(outfilename);

  return 0;
}