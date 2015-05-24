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
#include "stack.h"
int push_stack(ListElmts **stack,
               ListElmts *stackElmt)
{
   
   ListElmts *nwElmt = malloc(sizeof(*nwElmt));
   if (!nwElmt) 
      return IMPOSSIBLE_TO_MALLOC;
   nwElmt->data = stackElmt->data;
   nwElmt->type = stackElmt->type;
   nwElmt->next = *stack;
   *stack = nwElmt;
   return TRUE;
}
void pop_stack(ListElmts **stack)
{
   if ((*stack) != NULL)
   {
      ListElmts *tmp;
      tmp = *stack;
      *stack = tmp->next;
      free(tmp);  
   }
} 
