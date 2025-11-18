#include<iostream>
#include<fstream>
#include<cmath>
#include<conio.h>
#include<ctime>
#include <windows.h>
using namespace std;
void clearscreen()
{
    system("cls");
}
void storehscore(int msize,int move)
{
    msize=sqrt(msize);
    ofstream f("score.bin",ios::binary|ios::app);
    if(!f)
    cout<<"Error in saving score";
    else
    {
    f.write((char*)&msize,sizeof(msize));
    f.write((char*)&move,sizeof(move));
    }
    f.close();

}
void disphscore()
{
    clearscreen();
    ifstream f("score.bin",ios::binary);
    if(!f)
    cout<<"No high score found.\n";
    else
    {
        cout<<"==========================================\n";
        cout<<"|             High Score                 |\n";
        cout<<"==========================================\n";
        cout<<"  Size            |        Moves          \n";
        int size,move;
        while(f.read((char*)&size,sizeof(size)))
        {
            f.read((char*)&move,sizeof(size));
            cout<<"| "<<size<<"x"<<size<<"                      "<<move<<"             |\n";
        }
        f.close();
    }
}
bool loadgame(char*& matrix,bool*& rev, int& msize, int& move)
{
    ifstream fin("match.txt");
    if (!fin) 
     return false;
    else
    {
        fin >> msize >> move;
        matrix=new char[msize];
        rev=new bool[msize];
        for (int i = 0; i <msize; i++) 
        fin >> matrix[i];
        for (int i = 0; i <msize; i++)
        {
            int v; 
            fin >> v;
            if(v==1)
            rev[i]=true;
            else
            rev[i]=false;
        }
        fin.close();
        return true;
    }
}
void savegame(char* matrix,bool* rev,int msize,int move)
{
    int n=1,m=0;
    ofstream fout("match.txt");
    if (!fout) 
     cout<<"File not opened"<<endl;
    fout << msize <<" "<< move <<"\n";
    for (int i=0;i<msize; i++) 
    fout <<matrix[i] << " ";
    fout << "\n";
    for (int i=0;i<msize;i++)
     {
        if(rev[i]==true)
         fout<<n<<" ";
        else
        fout<<m<<" ";
     }
    fout<<"\n";
    fout.close();
    cout << "Game saved.\n";
}
void dispmatrix(char*matrix, bool* rev, int row, int col)
{
    cout << "\n";
    cout << "    ";
    cout<<"  ";
    for (int i= 0; i< col; i++)
    {
        
         if (i<10) 
         cout << "  " << i;
        else 
         cout << " " << i;
    }
    cout<<endl;
    for (int i=0;i<row;i++)
    {
        cout << "   ";
        if (i<10) 
        cout << " " << i<< " ";
        else
         cout << i<< " ";

        for (int j=0; j<col;j++)
        {
            int ind=(i*col)+j;
            if (rev[ind])
            {
                
                cout << "  " << matrix[ind];
            }
            else
            {
                cout << "  *" ;
            }
        }
        cout <<endl;
    }
    cout <<endl;
}
void gameheader(int move,int pfound,int tpair)
{
    cout << "\n";
    cout<<"==========================================\n";
    cout << "|  Moves:   " << move;
    cout << "    |   Pairs Found:   "<< pfound << "/" << tpair;
    cout << "  |\n";
    cout<<"==========================================\n";
}
void shufflematrix(char* matrix,int size)
{
    char temp;
    for(int i=0;i<size;i++)
    {
        int a=rand()% size;
        int b=rand()% size;
        temp = matrix[a];
        matrix[a] = matrix[b];
        matrix[b] = temp;
    }
}
void initmatrix(char* matrix,int size)
{
    int n=size/2;
    char c='A';
    for (int i=0; i<n;i++)
    {
        matrix[i]= c;
        c++;
    }
    for (int i =n; i < size; i++)
    {
        matrix[i] =matrix[i-n];
    }
}
int getcard(char *matrix,bool* rev,int row,int col)
{
    int i,j;
    while(true)
    {
        cout<<"Enter the position  (row col) or -1 -1 to exit :";
        cin>>i>>j;
        if(i==-1 || j==-1)
        return -1;
        while(i<0 || j<0 ||i>=row||j>=col)
        {
            cout<<"\n Invalid input.Try again:";
            cin>>i>>j;
        }
        int ind=(i*col)+j;
        while(rev[ind])
        {
            cout<<"Already opened. Try other:";
            cin>>i>>j;
            ind=(i*col)+j;
        }
        return ind;
    }
}
bool ismatch(char a,char b)
{
    if(a==b)
    return true;
   else
   return false;
}
bool won(bool* rev,int size)
{    bool r=true;
    for(int i=0;i<size;i++)
    {
        if(!rev[i])
        r=false;
    }
    return r;
}
void startgame()
{
    clearscreen();
    int msize;
    int move;
    char* matrix;
    char loadch;
    bool* rev;
    cout << "\n Do you want to play saved game (y/n): ";
    cin>>loadch;
    bool isload;
    if(loadch=='y'|| loadch=='Y')
    {
        isload=loadgame(matrix,rev,msize,move);
        if(!isload)
        {
           
            cout << "\n  No saved game found starting new game.\n";
        }
    }
    if(!isload)
    {
        
        cout<<"Enter the borad size (only even and upto 6 e.g;2 for(2x2)):";
        cin>>msize;
        while(msize%2!=0 || msize<0 ||msize>6)
        {
            cout<<"Invalid input take even positive number upto 6:";
            cin>>msize;
        }
        msize=msize*msize;
        matrix=new char[msize];
        rev = new bool[msize];
        for (int i = 0; i <msize; i++)
        {
            rev[i] = false;
        }
        initmatrix(matrix,msize);
        shufflematrix(matrix,msize);
        move=0;
    }
    int row=sqrt(msize);
    int col=row;
    int tpair=msize/2;
    int pfound=0;
    if(isload)
    {
        for(int i=0;i<msize;i++)
        {
            if (rev[i])
            {
                pfound++;
            }
        }
        pfound = pfound/2;
    }
    while (!won(rev, msize))
    {
        clearscreen();
        gameheader(move, pfound, tpair);
        dispmatrix(matrix, rev, row, col);
        int fcard=getcard(matrix,rev,row,col);
        if (fcard == -1) 
        {
            char sel;
            cout << "\n want to save game before exit (y/n): ";
            cin >> sel;
            if (sel=='y' || sel=='Y')
            {
                savegame(matrix,rev,msize,move);
            }
            break;
        }
        rev[fcard]=true;
        clearscreen();
        gameheader(move, pfound, tpair);
        dispmatrix(matrix, rev, row, col);
        int scard=getcard(matrix,rev,row,col);
        if (scard==-1) 
        {
            char sel;
            cout << "\n want to save game before exit (y/n): ";
            cin >> sel;
            if (sel=='y' || sel=='Y')
            {
                savegame(matrix,rev,msize,move);
            }
            break;
        }
        rev[scard]=true;
        move++;
        clearscreen();
        gameheader(move, pfound, tpair);
        dispmatrix(matrix, rev, row, col);
        
         if (ismatch(matrix[fcard],matrix[scard]))
        {
            
            cout << "\n     MATCHED!   \n";
            pfound++;
            cout<<"Press any key to continue...";
             _getch();
        }
        else
        {
            char a;
            cout << "\n    Not matched! try other.  \n";
            
            rev[fcard] = false;
            rev[scard] = false;
            cout<<"Press any key to continue...";
            _getch();
        }
    }
    if (won(rev,msize))
    {
        clearscreen();
        cout<<"==========================================\n";
        cout << "|         CONGRATULATIONS!             |\n";
        cout << "|       You completed the game         |\n";
        cout<<"==========================================\n";
        cout << "\n    Total moves: " << move << "\n";
       
        cout << "Do you want to save final state? (y/n): ";
        char s; 
        cin >> s;
        if(s=='y'||s=='Y') 
        storehscore(msize,move);
    }
    delete [] matrix;
    delete [] rev;
}
void dispmenu()
{
    clearscreen();
    cout<<"\n";
    cout<<"==========================================\n";
    cout<<"|           Memory Match Game            |\n";
    cout<<"==========================================";
    cout<<"\n \n 1.Start Game";
    cout<<"\n 2.View highscore";
    cout<<"\n 3.Exit";
    cout<<"\n==========================================";
    cout<<"\n Enter your choice:";
}
int main(){
    int ch;
    while(true)
    {
        srand(time(0));
        dispmenu();
        cin>>ch;
        while(ch>3 || ch<1)
        {
                cout << "   Invalid choice! Please try again:\n";
                cin>>ch;
        }
        if(ch==1)
        {
            startgame();
        }
        else if(ch==2)
        {
            char a;
            disphscore();
            cout<<"Press 'Y' to go main menu or 'N' to exit:";
            cin>>a;
            if(a=='y'||a=='Y')
            {
                continue;
            }
            else
             break;
        }
        else if(ch==3)
        {
            cout<<"Thanks for playing \n";
            break;
        }
    }
}