#include<iostream>
#include<conio.h>
#include<Windows.h>
#include<cstdlib>
#include<ctime>
#include<cstring>
using namespace std;

int x_food;
int y_food;
int ch;
int xy_keyboard = 10;
int count;
int now = 0;
char keyboard[10][10];


struct body
{
	int x;
	int y;
	int now;
};
body S[110];

void body();//贪吃蛇身体的跟踪
bool error(int x,int y);//判断有无越界
void creatfood();//产生食物
void operation();//用户操作
void print(int x_where,int y_where);//打印棋盘

int main()
{
 	ch =0;
    while(ch!=27)
    {
        count = 0;
        srand((unsigned)time(0));
        S[count].x = rand()%10;
        srand((unsigned)time(0));
        S[count].y = rand()%10;
        count++;
		creatfood();
        while(1)
		{
			cout<<"Mister_TT"<<endl;
			print(S[0].x,S[0].y);
        	Sleep(50);
			operation();
			if(error(S[0].x,S[0].y))break;
            body();
        	system("cls");
        }

		cout<<"ESC out or Enter continue"<<endl;
		ch = _getch();
        while(ch!=13&&ch!=27)ch = _getch();
		system("cls");
    }
}

void operation()
{
	if(kbhit() != 0) 
 	{   
  		while(kbhit() != 0)  
      	ch = getch(); 
 	}
	   
    switch(ch)
    {
        case 72:
            S[0].now = 1;
            S[0].x--;
            break;
        case 80:
            S[0].now = 2;
            S[0].x++;
            break;
        case 75:
            S[0].now = 3;
            S[0].y--;
            break;
        case 77:
            S[0].now = 4;
            S[0].y++;
            break;
    }
    
}

void print(int x,int y)
{
    memset(keyboard,'.',sizeof(keyboard));
    keyboard[x][y] = '@';
   	
    
    if( x == x_food && y == y_food)//如果遇到了食物
    {
        switch(S[count-1].now)
        {
            case 1:
                S[count].x = S[count - 1].x+1;
                S[count].y = S[count - 1].y;
                break;
            case 2:
                S[count].x = S[count - 1].x-1;
                S[count].y = S[count - 1].y;
                break;
            case 3:
                S[count].x = S[count - 1].x;
                S[count].y = S[count - 1].y+1;
                break;
            case 4:
                S[count].x = S[count - 1].x;
                S[count].y = S[count - 1].y-1;
                break;
        }
        
        count++;
        creatfood();
    }
   	

    else
    {
        keyboard[x_food][y_food]='#';
    }

	for(int i=1;i<count;i++)
    {
	    keyboard[S[i].x][S[i].y] = '1';
    }
	    
    for(int a=0;a<10;a++)
    {
        for(int b=0;b<10;b++)
        {
            cout<<keyboard[a][b];
        }
        cout<<endl;
    }
}

void creatfood()//创造食�?
{
    int SW = 0;

    while(SW == 0)
    { 
		srand(time(0)*rand());
        x_food = rand()%10;
        srand(time(0)*rand());
        y_food = rand()%10;
    	
		SW = 1;
    	
    	if(x_food == S[0].x && y_food == S[0].y)SW = 0;
    	
		for(int a=1;a<count;a++)
		{
			if(S[a].x == x_food && S[a].y == y_food)
			{
				SW = 0;
			}
		}

    }
}

bool error(int x,int y)//判断有无越界
{
	if(x>9||x<0||y>9||y<0)return true;//判断有无超出棋盘
	
	for(int i=1;i<count;i++)//判断有无碰到身体
	{
		if(x == S[i].x && y==S[i].y )return true;
	}
	return false;
}

void body()
{
    if (count == 1)return;//只有头的时候，没有身体，count==1
    
    //改变身体的位置
    else
    {
    	for(int i =count;i>=1;i--)
        {
        	S[i].now = S[i-1].now;//转移上一个身体的操作到后一个身体
        }
    	
        for(int i =count;i>=1;i--)
        {   
        	if(i!=1)//后一个身体走到前一个身体的地方
        	{
	            S[i].x = S[i-1].x;
                S[i].y = S[i-1].y;
       		}
       		
       		else
       		{
			    switch(S[0].now)//第一个身体需要通过知道头的位置的前一状态来判断下一步往哪里走
	            {
	                case 1:
	                    S[i].x = S[0].x+1;
	                    S[i].y = S[0].y;
	                    break;
	                
	                case 2:
	                    S[i].x = S[0].x-1;
	                    S[i].y = S[0].y;
	                    break;
	
	                case 3:
	                    S[i].x = S[0].x;
	                    S[i].y = S[0].y+1;
	                    break;
	
	                case 4:
	                    S[i].x = S[0].x;
	                    S[i].y = S[0].y-1;
	                    break;
	            }
	        }
        }
    }
}
