//Created By Mehedi Ahamed

#include<iostream>
#include<conio.h>
#include <windows.h>
#include <time.h>
#include<stdlib.h>

#define SCREEN_WIDTH 95
#define SCREEN_HEIGHT 26
#define WIN_WIDTH 74

using namespace std;


//cursor position
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;


int missileY[3];
int missileX[3];
int missileFlag[3];
char man[4][3] = { ' ',' ',' ',
                   ' ',' ',' ',
                   ' ','|',' ',
                   '=','-','=' };






int manPos = WIN_WIDTH/2; //set Man starting point
int scoreES;//initial scoreES




//input coordinate
void gotoxy(int x, int y);

// set bool visible = 0(invisible), bool visible = 1(visible)


void setcursor(bool visible, DWORD size) ;
void drawBorderES();

//missile fall down
void genMissile(int ind);

//missile shape
void drawMissile(int ind);
//erase missile
void eraseMissile(int ind);
void resetMissile(int ind);
//draw man
void drawMan();
//after colliding
void eraseMan();

//During collisionES
int collisionES();

void gameoverES();
//print scoreES
void updatescoreES();
void instructionsES();

void playES();
int serialES(int x, FILE *fp);
int deserialES(int x, FILE *fp);

int main()
{

	setcursor(0,0);
	srand( (unsigned)time(NULL));



	do{
		system("cls");
		system("color 1E");
		gotoxy(43,9); cout<<" -------------------------- ";
		gotoxy(43,10); cout<<" |   >>Dare to Escape<<   | ";
		gotoxy(43,11); cout<<" --------------------------";
		 gotoxy(45, 13);
        cout << "1. START GAME";
        gotoxy(45, 15);
        cout << "2. INSTRUCTIONS";
        gotoxy(45, 17);
        cout << "3. QUIT";
        gotoxy(45, 19);
        cout << "Select an Option- ";
		char op = getch();

		if( op=='1')
        {
            Beep(1459,105);
            playES();

        }
		else if( op=='2')
        {
            Beep(1459,105);
            instructionsES();

        }

		else if( op=='3')
         {
            system("cls");
            system("color 1");

            Beep(1459,105);
            exit(0);
        }

	}while(1);

	return 0;
}



//input coordinate
void gotoxy(int x, int y){
	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(console, CursorPosition);
}

// set bool visible = 0(invisible), bool visible = 1(visible)


void setcursor(bool visible, DWORD size) {
	if(size == 0)
		size = 20;  //size is 0 to 20

	CONSOLE_CURSOR_INFO lpCursor;
	lpCursor.bVisible = visible;
	lpCursor.dwSize = size;
	SetConsoleCursorInfo(console,&lpCursor);
}


void drawBorderES(){


	for(int i=22; i<=SCREEN_WIDTH; i++){
		gotoxy(i,1);
		printf("%c",193);

	}

	for(int i=22; i<=SCREEN_WIDTH; i++){
		gotoxy(i,SCREEN_HEIGHT+1);
		printf("%c",193);

	}

	for(int i=1; i<=SCREEN_HEIGHT; i++){
		gotoxy(22,i);
		printf("%c",208);

		gotoxy(SCREEN_WIDTH,i);
		printf("%c",208);

	}
	for(int i=1; i<=SCREEN_HEIGHT; i++){
		gotoxy(WIN_WIDTH,i);

		printf("%c",208);
	}
}



//missile fall down
void genMissile(int ind){
	missileX[ind] = 23 + rand()%(49);
}

//missile shape
void drawMissile(int ind){

    system("color 2");

	if( missileFlag[ind] == true ){



		gotoxy(missileX[ind], missileY[ind]+1);
		cout<<"|**|";
		gotoxy(missileX[ind], missileY[ind]+2);
		cout<<" ||";
		gotoxy(missileX[ind], missileY[ind]+3);
		printf(" %c%c",4,4);



	}
	setcursor(0,0);
}

//erase missile
void eraseMissile(int ind){
	if( missileFlag[ind] == true ){

            gotoxy(missileX[ind], missileY[ind]+1);
		cout<<"    ";
		gotoxy(missileX[ind], missileY[ind]+2);
		cout<<"   ";
		gotoxy(missileX[ind], missileY[ind]+3);
		printf("   ");




	}
}
void resetMissile(int ind){
	eraseMissile(ind);
	missileY[ind] = 1;
	genMissile(ind);
}

//draw man
void drawMan(){
	for(int i=0; i<4; i++){
		for(int j=0; j<3; j++){
			gotoxy(j+manPos, i+22);
			if(i==0 && j==1)
			printf("%c",2);
			if(i==1 && j==0)
			printf("%c",201);
			if(i==1 && j==2)
			printf("%c",187);


			cout<<man[i][j];
		}
	}
	setcursor(0,0);
}
//after colliding


void eraseMan()
{

	for(int i=0; i<4; i++){
		for(int j=0; j<4; j++){
			gotoxy(j+manPos, i+22);
			cout<<" ";
		}
	}

}

//During collisionES
int collisionES(){
    system("color 4");
	if( missileY[0]+3 >=23 ){
		if( missileX[0] + 4 - manPos >= 0 && missileX[0] + 4 - manPos < 8  ){
			return 1;

		}
	}

	return 0;
}

void gameoverES(){

    Beep(6059,80);

    system("cls");
    system("color 4F");
    char ch;
	cout<<endl;

	gotoxy(44, 10);
    cout << "---->>>> Game Over <<<<----" << endl;
    gotoxy(44, 11);
    cout << "___________________________" ;

	FILE *fp=fopen("escape.txt","r");
	int hs=deserialES(scoreES,fp);

    gotoxy(45, 14);
	cout<<"Your score :"<<scoreES<<endl;
	gotoxy(45,15);
	cout<<"High score :"<<hs<<endl;
	gotoxy(45,18);
	cout << "Retry?(y/n) = ";                      //if wannna playES agian
    cin >> ch;
    ch=tolower(ch);
    if(ch=='y')
    {
        playES();

    }

    else
        exit(0);
	getch();
}
//print scoreES
void updatescoreES(){
	gotoxy(WIN_WIDTH+5, 10);
	cout<<"score: "<<scoreES<<endl;

     //Beep(700,80);

     FILE *fp=fopen("escape.txt","a+");
         serialES(scoreES,fp);


}

void instructionsES(){

	system("cls");
    gotoxy(43,9);
	system("color 27");
	cout<<"INSTRUCTIONS";
	gotoxy(41,10);
	cout<<"----------------";
	gotoxy(41,12);
	cout<<"1. Avoid missile by moving left or right. ";
	gotoxy(41,13);
	cout<<"2. Press '<-' to move left";
	gotoxy(41,14);
	cout<<"3. Press '->' to move right";
	gotoxy(41,15);
	cout<<"4. Press 'escape' to exit";
	gotoxy(41,17);
	cout<<"Press any key to go back to menu";
	getch();
}

void playES(){


    system("cls");
    system("color 4");
	manPos = 10 + WIN_WIDTH/2;
	scoreES = 0;
	missileFlag[0] = 1;
	missileFlag[1] = 0;
	missileY[0] = missileY[1] = 1;

	system("cls");
	drawBorderES();
	updatescoreES();
	genMissile(0);
	genMissile(1);
	genMissile(2);




	gotoxy(WIN_WIDTH + 5, 13);cout<<"Control ";
	gotoxy(WIN_WIDTH + 5, 14);cout<<"-------- ";
	gotoxy(WIN_WIDTH + 5, 15);cout<<"<- Key - Left";
	gotoxy(WIN_WIDTH + 5, 16);cout<<"-> Key - Right";

	gotoxy(36, 13);cout<<"Press Any Key To Start...";
	getch();
	gotoxy(36, 13);cout<<"                              ";

	while(1){
		if(kbhit()){
			char ch = getch();
			if( ch==75 )       //left arrow ascii 75

            {
				if( manPos > 26 )  //screen start at 22
					manPos -= 3;
			}
			if( ch==77 )          //right arrow ascii 75
			{
				if( manPos <=67 )  //screen width 70
					manPos += 3;
			}
			if(ch==27){
				break;
			}
		}

		drawMan();
		drawMissile(0);
		drawMissile(1);
		drawMissile(2);
		if( collisionES() == 1  ){
			gameoverES();
			return;
		}

         Sleep(8);
		eraseMan();
		eraseMissile(0);
		eraseMissile(1);
		eraseMissile(2);

		if( missileY[0] == 5 )
			if( missileFlag[1] == 0 )
				missileFlag[1] = 1;

		if( missileFlag[0] == 1 )
			missileY[0] += 1;

		if( missileFlag[1] == 1 )
			missileY[1] += 1;

		if( missileY[0] > SCREEN_HEIGHT-4 ){
			resetMissile(0);
			scoreES++;
            updatescoreES();

		}
		if( missileY[1] > SCREEN_HEIGHT-4 ){
			resetMissile(1);
			scoreES++;
			updatescoreES();
		}

	}



}
//store data
int serialES(int x, FILE *fp)
{
    fp=fopen("escape.txt","a+");
    fprintf(fp,"%d ",x);
    fclose(fp);

}
//show data
int deserialES(int x,FILE *fp)
{
    int i=0;
    int num[100000];
    char ch;

    fp=fopen("escape.txt","r");


    while(!feof(fp))
    {
         fscanf(fp,"%d ",&num[i]);

         i++;

    }
    remove("escape.txt");
    fclose(fp);



   for(int k=0;k<i-1;k++)
    {

        for(int j=0;j<i-k-1;j++)
        {

            if(num[j+1]>num[j])
            {
                int temp=num[j];
                num[j]=num[j+1];
                num[j+1]=temp;
            }
        }
    }

   FILE *fp1=fopen("escape.txt","w");
   for(int k=0;k<i;k++)
   {
        fprintf(fp1,"%d ",num[k]);
   }



    fclose(fp1);
    return num[0];
}

