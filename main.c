#include <stdio.h>
#include "gera_func.h"

double pow1 (double x, double y, double z)
{
	double a = x + y + z;
	return a; 
}

typedef double (*func_ptr) (double);

int main (void) {
    Parametro params[3];
    func_ptr f_quadrado = NULL;
	
	double d = 0;
	int i;
    
    params[0].tipo = DOUBLE_PAR;
    params[0].amarrado = 1;
	params[0].valor.v_double = 2.5;
    params[1].tipo = DOUBLE_PAR;
    params[1].amarrado = 0;
    params[2].tipo = DOUBLE_PAR;
	params[2].amarrado = 1;
	params[2].valor.v_double = 2.25;
    
    f_quadrado = (func_ptr) gera_func (pow1, 3, params);

	printf("\n");

   for (i = 1; i <= 10; i++) {
		d = f_quadrado(120.0);
        printf("%d = %f\n", i, d);
    }

    libera_func(f_quadrado);
	return 0;
}
