/* 
   Copyright (C) 2014.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>. */

/* Written by Walid Chokki <wazlid@programmerenc.com>.  */
   
#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <float.h>
#include "stack.h"
#include "funcs.h"
#include "test_expr.h"
int main(int argc, char const *argv[])
{
	char expression[100];
	ListElmts *outputList;
	puts("Entrer une expression");
	fgets(expression, 100, stdin);
	char *i = NULL;
	if ( (i = strchr(expression, '\n')) != NULL)
	   *i = '\0';
	if (strlen(expression)!=0)
	{
		if (test_expression(expression) == FALSE)
		{
			outputList = construct_output_list(construct_input_list(expression));
			printf("%s =  %.*g\n",  expression, DBL_DIG,  evaluate_expression(outputList));
		}
		else
			puts("Expression mal formée");	
	}
	return 0;
}
