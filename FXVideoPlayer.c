#include "fxlib.h"
#include "FXVideoPlayer.h"


int AddIn_main(int isAppli, unsigned short OptionNum)
{
	unsigned int key;

	Bdisp_AllClr_DDVRAM();

	handle = Bfile_OpenFile(PathName,_OPENMODE_READWRITE);

	
	PrintXY(0, 0, "hold + to pause",1);
	PrintXY(0, 8, "- to quit", 1);
	PrintXY(0, 16, "0 to restart", 1);
	PrintXY(0, 56, "Any Key to start", 1);
	GetKey(&key);
	bf = Bfile_ReadFile(handle, &Compressed_frame, 2000, 0);
	decode_frame();
	while (1) {
		if (IsKeyDown(KEY_CHAR_0) == 1) 
			FrameCount = 0;
		if (IsKeyDown(KEY_CHAR_PLUS) == 1) 
			play = 0;
		if (IsKeyUp(KEY_CHAR_PLUS) == 1) 
			play = 1;
		if (IsKeyDown(KEY_CHAR_MINUS) == 1) 
			break;
		
		if (play == 1) {
			bf = Bfile_ReadFile(handle, &Compressed_frame, 2000, FrameCount);
			decode_frame();
			Bdisp_PutDisp_DD();
			Sleep(100);
		}
	}
	//Old Frame By Frame Debug Code
	/*GetKey(&key);
	switch(key){
		case  KEY_CTRL_UP:
			bf = Bfile_ReadFile(handle,&Compressed_frame,2000,FrameCount);
			decode_frame();
			Sleep(150);
			break;	
		case KEY_CHAR_0:
			FrameCount = 0;
			bf = Bfile_ReadFile(handle,&Compressed_frame,2000,FrameCount);
			decode_frame();
			break;
		}
	}*/
    return 1;
}



//**************  Please do not change the following source.  ****************


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

