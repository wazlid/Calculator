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
   
#ifndef __FUNCTION__
#define __FUNCTION__
	#include "stack.h"
	int 
	is_int(double number);
	int 
	get_operator_priority(ListElmts *elmt);
	void
	print_error(char *errorMsg);
	ListElmts*
	construct_input_list(char *expression);
	ListElmts* 
	construct_output_list(ListElmts *inputList);
	void
	slist_append(ListElmts **__head, 
             double data,
             int type);
	double 
	read_number(char *expression, 
		        int *pst);
	ListElmts
	make_operation(ListElmts *x,
                   ListElmts *y,
                   ListElmts *oprt);
	double
	evaluate_expression(ListElmts *outputList);
#endif  
