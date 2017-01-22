#include <iomanip>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void parkarr(string parkdat[50][2], ifstream & fin1)
{
    string type, name;
    int pos;
    for (int i=0; i<50; i++) {
        parkdat[i][0]="None";
        parkdat[i][1]="Unoccupied";
    }
    
    while(fin1>>type>>name>>pos)
    {
        parkdat[pos][0]=type;
        parkdat[pos][1]=name;
    }
}

int addre(ifstream &fin2, string addre[][2])
{
    string type, name;
    int a=0;
    
    while (fin2>>type>>name) {
        addre[a][0]=type;
        addre[a][1]=name;
        a++;
    }
    return a;
}

void delper(string parkdat[][2], string nameper)
{
    for (int i=0; i<50; i++) {
        if(parkdat[i][1]==nameper)
        {
            parkdat[i][0]="None";
            parkdat[i][1]="Unoccupied";
        }
    }
}

bool SpotAvail(string parkdat[][2], string status)
{
    for (int i =0; i<50; i++)
    {if (status=="1" && parkdat[i][0]=="None")
        return true;
    else if (parkdat[i][0]=="None" && i>24)
        return true;
    }
    return false;
}

void assper(string parkdat[][2], string nameper, string type)
{
    if (SpotAvail(parkdat, type))
    {
        if (type=="1")
        {
            int i=0;
            while (parkdat[i][0]!="None")
                i++;
            
            parkdat[i][0]=type;
            parkdat[i][1]=nameper;
        }
        
        else
        {
            int i;
            for (i=25; parkdat[i][0]!="None"; i++);
            
            parkdat[i][0]=type;
            parkdat[i][1]=nameper;
        }
    }
}

void teachSort(string parkdat[][2])
{
    for (int i=0; i<25; i++)
    {
        if (parkdat[i][0]=="None")
        {
            for (int j=25; j<50; j++)
            {
                if (parkdat[j][0]=="1")
                {
                    string a =  parkdat[j][1], b=parkdat[j][0];
                    delper(parkdat, parkdat[j][1]);
                    assper(parkdat, a, b);
                }
            }
        }
    }
    
}


void printout (ofstream &fout, string parkdat[][2])
{
    fout<<"Spot Number"<<setw(9)<<"Type"<<setw(25)<<"Names"<<endl;
    for (int i=0; i<50; i++)
    {
        fout<<setw(7)<<i<<setw(13)<<parkdat[i][0]<<setw(25)<<parkdat[i][1]
        <<endl;
    }
}



int main()
{
    ifstream fin1("parkingW14.txt");
    ifstream fin2("removeS14.txt");
    ifstream fin3("assignS14.txt");
    ofstream fout("final.txt");
    
    if(!fin1 && !fin2 && !fin3)
    {
        cout<<"One of the files did not open";
        system("PAUSE");
        return -1;
    }
    
    string parkdat[50][2], add[10][2], del[10][2];
    
    parkarr(parkdat, fin1);

    int num1 = addre(fin2, del);
    int num2 = addre(fin3, add);
    
    
    
    for(int i=0; i<num1; i++)
    {
        delper(parkdat, del[i][1]);
    }
    
    for(int i=0; i<num2; i++)
    {
        assper(parkdat, add[i][1], add[i][0]);
    }
    
    teachSort(parkdat);
    
    printout (fout, parkdat);
    
    system("PAUSE");
    return 0;
}

