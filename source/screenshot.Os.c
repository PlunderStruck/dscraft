#include "common/general.h"
#include "engine/files.h"

typedef struct {
	u16 type;
	u32 size;
	u16 reserved1, reserved2;
	u32 offset;
} PACKED HEADER;

typedef struct {
	u32 size;
	u32 width,height;
	u16 planes;
	u16 bits;
	u32 compression;
	u32 imagesize;
	u32 xresolution,yresolution;
	u32 ncolours;
	u32 importantcolours;
} PACKED INFOHEADER;

void wait();
int scrnum;

void D3D_SaveScreen(const char* filename, u16* buffer);

void screenshotbmp2(const char* filename, u16* vram1, u16* vram2)//, u16 bgcolor)
{

	FILE* file=fopen(filename, "wb");
	
	// u8* temp=(u8*)malloc(256*192*3+sizeof(INFOHEADER)+sizeof(HEADER));
	u8* temp=(u8*)malloc(sizeof(INFOHEADER)+sizeof(HEADER));

	HEADER* header=(HEADER*)temp;
	INFOHEADER* infoheader=(INFOHEADER*)(temp+sizeof(HEADER));

	header->type=0x4D42;
	header->size=256*192*3+sizeof(INFOHEADER)+sizeof(HEADER);
	header->offset=sizeof(INFOHEADER)+sizeof(HEADER);
	header->reserved1=0;
	header->reserved2=0;

	infoheader->bits=24;
	infoheader->size=sizeof(INFOHEADER);
	infoheader->compression=0;
	infoheader->width=256;
	infoheader->height=192;
	infoheader->planes=1;
	infoheader->imagesize=256*192*3;
	infoheader->xresolution=0;
	infoheader->yresolution=0;
	infoheader->importantcolours=0;
	infoheader->ncolours=0;
	fwrite(temp, 1, sizeof(INFOHEADER)+sizeof(HEADER), file);
	int y,x;
	for(y=0;y<192;y++)
	{
		for(x=0;x<256;x++)
		{
			// u16 color=VRAM_D[256*192-y*256+x];
			u16 color=vram2[256*192-y*256+x];
			// if(color==bgcolor)color=vram1[256*192-y*256+x];
			if(!((color>>15)&1)){color=vram1[256*192-y*256+x];}

			u8 b=(color&31)<<3;
			u8 g=((color>>5)&31)<<3;
			u8 r=((color>>10)&31)<<3;

			// temp[((y*256)+x)*3+sizeof(INFOHEADER)+sizeof(HEADER)]=r;
			// temp[((y*256)+x)*3+1+sizeof(INFOHEADER)+sizeof(HEADER)]=g;
			// temp[((y*256)+x)*3+2+sizeof(INFOHEADER)+sizeof(HEADER)]=b;
			fwrite(&r,1,sizeof(u8),file);
			fwrite(&g,1,sizeof(u8),file);
			fwrite(&b,1,sizeof(u8),file);
		}
	}

	DC_FlushAll();
	// fwrite(temp, 1, 256*192*3+sizeof(INFOHEADER)+sizeof(HEADER), file);
	fclose(file);
	free(temp);
}

char bmpname[256];

void Debug_TakeScreenshotBMP(u16* vram1, u16* vram2)//, u16 bgcolor)
{
	scrnum++;
		#ifdef FATONLY
			if(scrnum<10)snprintf(bmpname, sizeof(bmpname), "screens/SCR_0000%d.bmp",scrnum);
			else if(scrnum<100)snprintf(bmpname, sizeof(bmpname), "screens/SCR_000%d.bmp",scrnum);
			else if(scrnum<1000)snprintf(bmpname, sizeof(bmpname), "screens/SCR_00%d.bmp",scrnum);
			else if(scrnum<10000)snprintf(bmpname, sizeof(bmpname), "screens/SCR_0%d.bmp",scrnum);
			else snprintf(bmpname, sizeof(bmpname), "screens/SCR_%d.bmp",scrnum);
		#else
			if(scrnum<10)snprintf(bmpname, sizeof(bmpname), "%s/%s/screens/SCR_0000%d.bmp",basePath,ROOT,scrnum);
			else if(scrnum<100)snprintf(bmpname, sizeof(bmpname), "%s/%s/screens/SCR_000%d.bmp",basePath,ROOT,scrnum);
			else if(scrnum<1000)snprintf(bmpname, sizeof(bmpname), "%s/%s/screens/SCR_00%d.bmp",basePath,ROOT,scrnum);
			else if(scrnum<10000)snprintf(bmpname, sizeof(bmpname), "%s/%s/screens/SCR_0%d.bmp",basePath,ROOT,scrnum);
			else snprintf(bmpname, sizeof(bmpname), "%s/%s/screens/SCR_%d.bmp",basePath,ROOT,scrnum);
		#endif
	// FILE* f=fopen(bmpname,"rb");
	while(!access(bmpname,R_OK))
	{
		// fclose(f);
		scrnum++;
			#ifdef FATONLY
				if(scrnum<10)snprintf(bmpname, sizeof(bmpname), "screens/SCR_0000%d.bmp",scrnum);
				else if(scrnum<100)snprintf(bmpname, sizeof(bmpname), "screens/SCR_000%d.bmp",scrnum);
				else if(scrnum<1000)snprintf(bmpname, sizeof(bmpname), "screens/SCR_00%d.bmp",scrnum);
				else if(scrnum<10000)snprintf(bmpname, sizeof(bmpname), "screens/SCR_0%d.bmp",scrnum);
				else snprintf(bmpname, sizeof(bmpname), "screens/SCR_%d.bmp",scrnum);
			#else
			if(scrnum<10)snprintf(bmpname, sizeof(bmpname), "%s/%s/screens/SCR_0000%d.bmp",basePath,ROOT,scrnum);
			else if(scrnum<100)snprintf(bmpname, sizeof(bmpname), "%s/%s/screens/SCR_000%d.bmp",basePath,ROOT,scrnum);
			else if(scrnum<1000)snprintf(bmpname, sizeof(bmpname), "%s/%s/screens/SCR_00%d.bmp",basePath,ROOT,scrnum);
			else if(scrnum<10000)snprintf(bmpname, sizeof(bmpname), "%s/%s/screens/SCR_0%d.bmp",basePath,ROOT,scrnum);
			else snprintf(bmpname, sizeof(bmpname), "%s/%s/screens/SCR_%d.bmp",basePath,ROOT,scrnum);
			#endif
		// FILE* f=fopen(bmpname,"rb");
	}
	screenshotbmp2(bmpname, vram1, vram2);//, bgcolor);
}

void D3D_TakeScreenshotBMP(u16* buffer)
{
	scrnum++;
	if(scrnum<10)snprintf(bmpname, sizeof(bmpname), "fat:/SCR_0000%d.bmp",scrnum);
	else if(scrnum<100)snprintf(bmpname, sizeof(bmpname), "fat:/SCR_000%d.bmp",scrnum);
	else if(scrnum<1000)snprintf(bmpname, sizeof(bmpname), "fat:/SCR_00%d.bmp",scrnum);
	else if(scrnum<10000)snprintf(bmpname, sizeof(bmpname), "fat:/SCR_0%d.bmp",scrnum);
	else snprintf(bmpname, sizeof(bmpname), "fat:/SCR_%d.bmp",scrnum);
	//sprintf(dirname, "prout%d",(int)(scrnum/99));
	//mkdir(dirname, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	//chdir(dirname);
	D3D_SaveScreen(bmpname, buffer);
	//chdir("..");
}


void D3D_SaveScreen(const char* filename, u16* buffer)
{
	u8* temp=(u8*)malloc(256*192*3+sizeof(INFOHEADER)+sizeof(HEADER));

	HEADER* header=(HEADER*)temp;
	INFOHEADER* infoheader=(INFOHEADER*)(temp+sizeof(HEADER));

	header->type=0x4D42;
	header->size=256*384*3+sizeof(INFOHEADER)+sizeof(HEADER);
	header->offset=sizeof(INFOHEADER)+sizeof(HEADER);
	header->reserved1=0;
	header->reserved2=0;

	infoheader->bits=24;
	infoheader->size=sizeof(INFOHEADER);
	infoheader->compression=0;
	infoheader->width=256;
	infoheader->height=384;
	infoheader->planes=1;
	infoheader->imagesize=256*384*3;
	infoheader->xresolution=0;
	infoheader->yresolution=0;
	infoheader->importantcolours=0;
	infoheader->ncolours=0;
	int y,x;
	for(y=0;y<384;y++)
	{
		for(x=0;x<256;x++)
		{
			u16 color=buffer[256*384-y*256+x];

			u8 b=(color&31)<<3;
			u8 g=((color>>5)&31)<<3;
			u8 r=((color>>10)&31)<<3;

			temp[((y*256)+x)*3+sizeof(INFOHEADER)+sizeof(HEADER)]=r;
			temp[((y*256)+x)*3+1+sizeof(INFOHEADER)+sizeof(HEADER)]=g;
			temp[((y*256)+x)*3+2+sizeof(INFOHEADER)+sizeof(HEADER)]=b;
		}
	}

	//DC_FlushAll();
	FILE* file=fopen(filename, "wb");
	fwrite(temp, 1, 256*384*3+sizeof(INFOHEADER)+sizeof(HEADER), file);
	fclose(file);
	free(temp);
}
