/// WRITTEN BY : MeLlamoArroz

#include<bits/stdc++.h>
#include"lodepng.h"

using namespace std;

int main(int argc, char** argv)
{
	char* name = argv[1];
	ifstream my_file(name, ifstream::binary);

	my_file.seekg(0, my_file.end);
   	uint32_t size = my_file.tellg();
	my_file.seekg(0, my_file.beg);


	uint8_t* buff = new uint8_t[size];
	my_file.read((char*)buff, size);
	my_file.close();

	uint8_t* temporal = new uint8_t[4096*3072];
	
	/// 12bits -> 8bits
	int pos = 0;
	for(int i=0;i<size;i+=3)
	{
		temporal[pos] = buff[i];
		temporal[pos+1] = buff[i+1] << 4 | buff[i+2] >> 4;
		pos+=2;
	}

	uint8_t* red = new uint8_t[2048*1536];
	uint8_t* green1 = new uint8_t[2048*1536];
	uint8_t* green2 = new uint8_t[2048*1536];
	uint8_t* blue = new uint8_t[2048*1536];
	uint8_t* color = new uint8_t[4096*3072*3];

	/// SPLIT LAYERS
	for(long long int i=0, j=0, k=0; i+j<4096*3072; i+=2)
	{
		if(i==4096) ///4096
		{
			j+=2*4096; ///8192
			i=-2;
		}
		else
		{
			red[k] = temporal[j+i];
			green1[k] = temporal[j+i+1];
			green2[k] = temporal[j+4096+i];
			blue[k] = temporal[j+4096+i+1]; 
			++k;
		}
	}
	
	/// BILINEAR INTERPOLATION 
	for(long long int i=0, j=0, k=0, l=0; i+j<4096*3072; i+=2)
	{
		if(i==4096)
		{
			j+=2*4096;
			l+=2*3*4096;
			k=0;
			i=-2;
		}
		else
		{
			color[k+l] = temporal[j+i];
			color[k+l+1] = temporal[j+i+1]>>2 + temporal[j+i-1]>>2 + temporal[j+i-4096]>>2 + temporal[j+i-4096]>>2;
			color[k+l+2] = temporal[j+i+1+4096]>>2 + temporal[j+i-1+4096]>>2 + temporal[j+i+1-4096]>>2 + temporal[j+i-1-4096]>>2;

			color[k+l+3] = temporal[j+i]>>1 + temporal[j+i+2]>>1;
			color[k+l+4] = temporal[j+i+1];
			color[k+l+5] = temporal[j+i+1+4096]>>1 + temporal[j+i+1-4096];
			
			color[k+l+3*4096] = temporal[j+i]>>1 + temporal[j+i+2*4096]>>1;
			color[k+l+3*4096+1] = temporal[j+i+4096];
			color[k+l+3*4096+2] = temporal[j+i+4096+1]>>1 + temporal[j+i+4096-1]>>1;
			
			color[k+l+3*4096+3] = temporal[j+i]>>2 + temporal[j+i+2]>>2 + temporal[j+i+2*4096]>>2 + temporal[j+i+2*4096+2];
			color[k+l+3*4096+4] = temporal[j+i+4096]>>2 + temporal[j+i+4096+2]>>2 + temporal[j+i+1]>>2 + temporal[j+i+1+2*4096]>>2;
			color[k+l+3*4096+5] = temporal[j+i+4096+1];
			
			k+=6;
		}
	}
	


	lodepng::encode("red.png", red, 2048, 1536, LCT_GREY);
	lodepng::encode("green1.png", green1, 2048, 1536, LCT_GREY);
	lodepng::encode("green2.png", green2, 2048, 1536, LCT_GREY);
	lodepng::encode("blue.png", blue, 2048, 1536, LCT_GREY);
	lodepng::encode("color.png", color, 4096, 3072, LCT_RGB);
}
