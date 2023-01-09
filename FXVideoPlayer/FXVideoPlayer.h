
// itoa - https://wiki.planet-casio.com/en/Syscalls
#include "fxlib.h"
#define SCA 0xD201D002
#define SCB 0x422B0009
#define SCE 0x80010070
typedef int(*sc_iv)(void);
typedef void(*sc_viuc)( int, unsigned char* );
typedef void(*sc_vpuc)(unsigned char*);
const unsigned int sc0541[] = { SCA, SCB, SCE, 0x0541 };
#define itoa (*(sc_viuc)sc0541)

//https://www.liquisearch.com/nibble/extracting_a_nibble_from_a_byte
#define HI_NIBBLE(b) (((b) >> 4) & 0x0F)
#define LO_NIBBLE(b) ((b) & 0x0F)


//char  Menu[][5] = {"One","Two","Three","Four","Five","Six"};
//char  Menu[][5] = {"One","Two"};


unsigned char Compressed_frame[1024];
unsigned long Frame[256];


int FrameCount =  0;

FONTCHARACTER PathName[]={'\\' ,'\\','c','r','d','0','\\','v','i','d','.','c','a','l',0};
//FONTCHARACTER PathName[]={'\\' ,'\\','f','l','s','0','\\','n','u','m','.','j','o','e',0};

unsigned char viewnumber[8];
int handle,bf,index,bitCount,j,output;
int drawIndex = 0;
int debug_Count = 0;
unsigned char highNibble,lowNibble;
char play = 1;

void decode_frame(){
	int rep,bits,i=0;
	int x =0;
	int y =0;

	for(i =0;i < 2000; ++i){
		int repititions = HI_NIBBLE(Compressed_frame[i]);
		char data = LO_NIBBLE(Compressed_frame[i]);
		int BitOrder[4];
		if(!Compressed_frame[i]){
				FrameCount += i+1;
				return;
		}
		for(bits =3; bits > -1; --bits){
			if(data & 0x1){
				BitOrder[bits] = 1;
			}
			else{
				BitOrder[bits] = 0;
			}
			data= data >> 1;
		}
		
		for(rep =0;rep < repititions; ++rep){
			
			for(bits = 0; bits < 4; ++bits){
				//Had a funny problem where the bottem four pixels where at the wrong place 
				//and had to shuffle everything around
				if(y < 60){
					Bdisp_SetPoint_VRAM(x,y+4,BitOrder[bits]);
				}
				else{
					Bdisp_SetPoint_VRAM(x,y-60,BitOrder[bits]);
				}
				
				y++;
				if(y==64){
					y= 0;
					x++;
				}
			}
		}
	}
}

void print_Frame(){
	int x,i,y;
	for(x=0; x < 256;  ++x)			
	{
		if(x%2 ==0){
			for(bitCount =32; bitCount>1; --bitCount) 
			{
				 if (Frame[x] & 0x01) {
					Bdisp_SetPoint_VRAM(x/2,bitCount,1);
				}
				else	
				{
					Bdisp_SetPoint_VRAM(x/2,bitCount,0);		
				}
				Frame[x] = Frame[x] >> 1;
					
			}
		}
		else
		{
			for(bitCount = 64; bitCount>32; --bitCount) 
			{
				 if (Frame[x] & 0x01) {
					Bdisp_SetPoint_VRAM(x/2,bitCount,1);
				}
				else	
				{
					Bdisp_SetPoint_VRAM(x/2,bitCount,0);		
				}
				Frame[x] = Frame[x] >> 1;
					
			}
		}
	}
}
void make_Frame(){
	int x,y;
	for(x=0; x < 128; ++x){
		for(y= 0; y < 8; ++y){
			if(y < 4){	
				//Frame[x][y] = 0x1A;
			}
			else{
				//Frame[x][y] = 0x1A;
			}
		}
	}
}
/*void draw_menu() {
	int i;
	int maxLoop = 3;
	int MenuSize = sizeof(Menu) / sizeof(Menu[0]);
	if(MenuSize < 3)
	{
		maxLoop = MenuSize;
	}
	for(i = 0; i < maxLoop; ++i){
		
		Bdisp_AreaReverseVRAM(3,(i)*21,125,(i+1)*21);
		locate(2,(i*3)+2);
		//PrintRev(Menu[i]);
	}
	Bdisp_AreaReverseVRAM(6,((drawIndex)*21),122,((drawIndex+1)*21));
}*/