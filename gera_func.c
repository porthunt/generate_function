/* Igor Domingues de Freitas 	- 1010310 - 3WA */
/* João Pedro Portela Gómez Vaz - 1011141 - 3WA */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "gera_func.h"

char * lilvec (int val)
{
	char v[4];
	char* ret;
	int i = 0;
	
	while(i<4)
	{
		v[i] = val;
		val = val >> 8;
		i++;
	}
	ret = v;
	
	return ret;
}

char * lilptr (void * ptr)
{
	char v[4];
	char* ret;
	int val = (int) ptr;
	int i = 0;
	
	while(i<4)
	{
		v[i] = val;
		val =  val >> 8;
		i++;
	}
	ret = v;
	
	return ret;
}

char * lildouble (double val)
{		
	char v[8];
	char* ret;
	int i = 0;
	int* dd;        
	int high;
	int low;
		

	dd = &val;
	high = dd[0];
	low = dd[1];
	

	while(i<8)
	{
		if(i > 4)
		{
			v[i] = high;
			high = high >> 8;
		}
		else
		{
			v[i] = low;
			low = low >> 8;
		}
		i++;
	}
	ret = v;
	
	return ret;
}

void* gera_func (void* f, int n, Parametro params[]) 
{
	unsigned char *fc;
	int i, aux, end;
	int num=13;
	char* v;
	int livre = 0;

	for (i=0; i<n;i++)
	{
		if( params[i].amarrado == 1)
		{
			if (params[i].tipo == INT_PAR || params[i].tipo == PTR_PAR || params[i].tipo == CHAR_PAR)
			{
				num += 5;
			}	
			else
			{
				num +=3;
			}


			if (params[i].tipo == DOUBLE_PAR)
			{
				num += 10;
			}	
		}
		else
		{
			if(params[i].tipo == INT_PAR || params[i].tipo == PTR_PAR || params[i].tipo == CHAR_PAR)
			{	
				num +=3;
			}
			else
			{
				num += 6;
			}
		}

	}
	
	fc = (unsigned char *) malloc (num*sizeof(unsigned char));
	fc[0] = 0x55;
	fc[1] = 0x89;
	fc[2] = 0xe5;

	aux = 3;

	for (i = n-1; i >=0; i--)
	{
		
		if (params[i].tipo == INT_PAR)
		{
			if (params[i].amarrado == 1)
			{
					fc[aux] = 0x68;
					v = lilvec(params[i].valor.v_int);
					fc[aux+1] = v[0];
					fc[aux+2] = v[1];
					fc[aux+3] = v[2];
					fc[aux+4] = v[3];
					aux+=5;
			}
			else
			{
				fc[aux] = 0xff;
				fc[aux+1] = 0x75;
				fc[aux+2] = 0x08+(livre*0x04);
				livre++;
				aux+=3;
			}
		}

		if (params[i].tipo == PTR_PAR)
		{
			if (params[i].amarrado == 1)
			{
					fc[aux] = 0x68;
					v = lilptr(params[i].valor.v_ptr);
					fc[aux+1] = v[0];
					fc[aux+2] = v[1];
					fc[aux+3] = v[2];
					fc[aux+4] = v[3];
					aux+=5;
			}
			else
			{
				fc[aux] = 0xff;
				fc[aux+1] = 0x75;
				fc[aux+2] = 0x08+(livre*0x04);
				livre++;
				aux+=3;
			}
		}

		if (params[i].tipo == CHAR_PAR)
		{

			if (params[i].amarrado == 1)
			{
					fc[aux] = 0x68;
					v = lilvec(params[i].valor.v_char);
					fc[aux+1] = v[0];
					fc[aux+2] = v[1];
					fc[aux+3] = v[2];
					fc[aux+4] = v[3];
					aux+=5;
			}
			else
			{
				fc[aux] = 0xff;
				fc[aux+1] = 0x75;
				fc[aux+2] = 0x08+(livre*0x04);
				livre++;
				aux+=3;
			}
		}

		if (params[i].tipo == DOUBLE_PAR)
		{

			if (params[i].amarrado == 1)
			{								
				fc[aux] = 0x68;
				v = lildouble(params[i].valor.v_double);
				fc[aux+1] = v[0];
				fc[aux+2] = v[1];
				fc[aux+3] = v[2];
				fc[aux+4] = v[3];
				aux+=5;	
				fc[aux] = 0x68;
				fc[aux+1] = v[4];
				fc[aux+2] = v[5];
				fc[aux+3] = v[6];
				fc[aux+4] = v[7];
				aux+=5;	
			}
			else
			{
				fc[aux] = 0xff;
				fc[aux+1] = 0x75;
				fc[aux+2] = 0x0c + (livre*0x08);
				fc[aux+3] = 0xff;
				fc[aux+4] = 0x75;
				fc[aux+5] = 0x08 + (livre*0x08);
				livre++;
				aux+=6;
			}
			
		}
		
		
	}

	end = (int) f - (int) &fc[aux+5];
	
	fc[aux] = 0xe8;
	fc[aux+1] = end&(0xFF);
	fc[aux+2] = (end>>8)&(0xFF);
	fc[aux+3] = (end>>16)&(0xFF);
	fc[aux+4] = (end>>24)&(0xFF);
	fc[aux+5] = 0x89;
	fc[aux+6] = 0xec;
	fc[aux+7] = 0x5d;
	fc[aux+8] = 0xc3;
	
	return fc;
	
}

void libera_func (void* func) 
{
	free(func);
}
