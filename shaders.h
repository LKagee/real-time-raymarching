#pragma once
#include <stdlib.h>


static void* getVertexShader() {
		FILE *fptr = fopen(VERTSHADERPATH, "rb");
		if(fptr == NULL) return NULL;
		char *vertBuffer;
		fseek(fptr, 0, SEEK_END);
		int vertSize = ftell(fptr);
		fseek(fptr, 0, SEEK_SET);

		vertBuffer = (char*)malloc(vertSize+1);
		fread(vertBuffer, vertSize/sizeof(char), sizeof(char), fptr);
		vertBuffer[vertSize] = '\0';	
	return vertBuffer;

}

static void* getFragShader() {
		FILE *fptr = fopen(FRAGSHADERPATH, "rb");
		if(fptr == NULL) return NULL;
		char *fragBuffer;
		fseek(fptr, 0, SEEK_END);
		int fragSize = ftell(fptr);
		fseek(fptr, 0, SEEK_SET);

		fragBuffer = (char*)malloc(fragSize+1);
		fread(fragBuffer, fragSize/sizeof(char), sizeof(char), fptr);
		fragBuffer[fragSize] = '\0';	
	return fragBuffer;
}

