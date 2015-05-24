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
#include "test_expr.h"
int 
delete_space(char *expr)
{
   char *expr_chng = NULL;
   int  current_char = 0,
        i = 0, 
        j = 0,
        k = 0
   ;
   expr_chng = calloc(strlen(expr)+1, sizeof(char));
   if (expr_chng != NULL)
   {
      while(expr[i] != '\0')
      {  
         current_char = expr[i];
         if (!isspace(current_char))
         {
            expr_chng[j++] = current_char;
         }
         else
         {
            for (k = i; expr[k] == ' '; ++k)
            {
               if (isdigit(expr[k+1]))
               {
                     if (isdigit(expr[i-1]))
                     {
                        return MALFORMETED_EXPRESSION;     
                     }
               }
            }
         }
         i++;
      }
      expr_chng[i] = '\0';
      strcpy(expr, expr_chng);
      return FALSE;
   }
   else
      return IMPOSSIBLE_TO_MALLOC;
}
int 
test_char(char *expr)
{
   char valid_char[] = " 0123456789+-/*%().,";
   int i;
   for (i = 0; expr[i] != '\0'; ++i)
   {
      if (!strchr(valid_char, expr[i]))
      {
         return TRUE;
      }
   }
   return FALSE;
}
int 
test_expression(char* expr)
{
   if (delete_space(expr)!=FALSE || test_char(expr))
   {
      return TRUE;
   }
   else
   {
      char *wrong_start_char = ")*/%";
      char *wrong_end_char = "+-*/%";
      if (strchr(wrong_start_char, expr[0]) || strchr(wrong_end_char, expr[strlen(expr)-1]))
      {
         return TRUE;
      }
      return FALSE;
   }
} 
