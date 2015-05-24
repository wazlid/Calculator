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
   
#ifndef __STACK__
	#define __STACK__
	#define MAX_LENGHT 2000
	#define TRUE 1
	#define FALSE 0
	#define MALFORMETED_EXPRESSION 2
	#define IMPOSSIBLE_TO_MALLOC 3
	typedef struct ListElmts ListElmts;
	struct ListElmts
	{
	  double data;
	  int type;
	  ListElmts *next;
	};
	int push_stack(ListElmts **stack,
               	   ListElmts *stackElmt);
	void 
	pop_stack(ListElmts **stack);
#endif
