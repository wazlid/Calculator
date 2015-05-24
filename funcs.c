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
#include "funcs.h"
void
print_error(char *errorMsg)
{
   puts(errorMsg);
}
int 
is_int(double number)
{
   char buf[MAX_LENGHT];
   sprintf(buf, "%g", number);
   if (strchr(buf, '.'))
   {
      return FALSE;
   }
   else
      return TRUE;
}
int 
is_operator(ListElmts *elmt)
{
   if(elmt->type == 1)
      return TRUE;
   else
      return FALSE;
}
int 
is_operand(ListElmts *elmt)
{
   if(elmt->type == 0)
      return TRUE;
   else
      return FALSE;
}
int 
get_operator_priority(ListElmts *elmt)
{
      switch((int)(elmt->data))
      {
         case '%': case '*': case '/':
            return 2;
         case '-': case '+':
            return 1;
         default:
            return 0;
      }
}
double 
read_number(char *__math_expression, 
            int *pst)
{
   double number = 0;
   while(isdigit(__math_expression[(*pst)]))
   {
      number = number*10 + (__math_expression[(*pst)] - '0');
      (*pst)++;
   }
   if (__math_expression[(*pst)] == '.' || __math_expression[(*pst)] == ',')
   {
      double i = 10;
      (*pst)++;
      while(isdigit(__math_expression[(*pst)]))
      {  
         number += (__math_expression[(*pst)] - '0')/i;
         i *=10; 
         (*pst)++;
      }
   }
   return number;
}
void
slist_append(ListElmts **__head, 
             double data,
             int type)
{
   ListElmts *current,
             *nwElmt
   ;
   nwElmt = malloc(sizeof(*nwElmt));
   if (!nwElmt) {
      print_error("Malloc");
      exit(0);
   }
   nwElmt->data = data;
   nwElmt->type = type;
   nwElmt->next = NULL;
   if (*__head == NULL)
   {
      *__head = nwElmt;
   }
   else
   {
      current = *__head;
      while(current->next != NULL)
      {
         current = current->next;
      }
      current->next = nwElmt;
   }
}
ListElmts*
construct_input_list(char *expression)
{
   ListElmts *head = NULL;
   int i = 0,
       unary_sgn = FALSE,
       lenghtExp = strlen(expression),
       type
   ;
   double value;
   while(i < lenghtExp)
   {
      if (expression[i] == '.' || expression[i] == ',' || isdigit(expression[i]))
      {
         if(!isdigit(expression[i-1]))
         {
            value = read_number(expression, &i);
            i--;
            if (unary_sgn)
            {
               if (value != 0)
               {
                  value = type*value;  
               }
               unary_sgn = FALSE;
            }
            type = 0;  
         }
         else
         {
            print_error("Expression mal formée");
            exit(0);
         }
      }
      else if(expression[i] == '-' && (expression[i+1] == '+' || expression[i+1] == '-') && (i == 0 || expression[i-1] =='(') && isdigit(expression[i+2]))
      {
         slist_append(&head, -1, 0);
         slist_append(&head, '*', 1);
         type = -1;
      }
      else if((expression[i] == '+' || expression[i] == '-') && !isdigit(expression[i-1]) && expression[i-1]!=')' && (isdigit(expression[i+1]) || expression[i+1]=='.' || expression[i+1]==','))
      {
         if (expression[i] == '-')
         {
            unary_sgn = TRUE; 
         }
         type = -1;
      }
      else if((expression[i] == '/' || expression[i] =='%') && ((expression[i+1] == '-' || expression[i+1] =='+')) && expression[i+2] =='(')
      {
         type = -1;
      }
      else if((expression[i] == '+' || expression[i] == '-') && expression[i+1] == '(' && expression[i-1]!=')' && !isdigit(expression[i-1]))
      {
         if (expression[i] == '+')
         {
            print_error("Expression mal formée ");
            exit(0);
         }
         else
         {
            type = -1;
         }
      }
      else if(expression[i] == '(')
      {
         if(i > 1)
         {
            if(isdigit(expression[i-1]) || expression[i-1] == ')')
            {
               slist_append(&head, '*', 1);
            }
            else if (expression[i-1] == '-')
            {
               if (expression[i-2] == '/' || expression[i-2] == '%')
               {
                  slist_append(&head, '*', 1);
                  slist_append(&head, -1, 0);
                  slist_append(&head, expression[i-2], 1);
               }
               else if (expression[i-2] == '-' || expression[i-2] =='+' || expression[i-2] == '*' || expression[i-2] =='(')
               {
                  slist_append(&head, -1, 0);
                  slist_append(&head, '*', 1);
               }
            }
         }
         else
         {            
            if(expression[i-1] == '-')
            {
               slist_append(&head, -1, 0);
               slist_append(&head, '*', 1); 
            }
            else if(isdigit(expression[i-1]))
            {
               slist_append(&head, '*', 1);
            }
         }
         value = '(';
         type = 2;
      }
      else
      {
         value = expression[i];
         if (expression[i] == ')')
         {
            if(isdigit(expression[i+1]))
            {
               print_error("Expression mal formée ");
               exit(0);
            }
            type = 2;
         }
         else
         {
            type = 1;
         }
      }
      if(type >= 0)
      {
         slist_append(&head, value, type);
      }
      i++;
   }
   return head;
}
ListElmts* 
construct_output_list(ListElmts *inputList)
{
   ListElmts *stack = NULL;
   ListElmts *outputList = NULL,
             *current
   ;
   current = inputList;
   while(current != NULL)
   {
      if (is_operand(current))
      {
         slist_append(&outputList, current->data, current->type);
      }
      else if (current->data == '(')
      {
         if (push_stack(&stack, current) != TRUE)
         {
            print_error("Malloc");
            exit(0);
         }
      }
      else if (is_operator(current))
      {
         while(stack != NULL && is_operator(stack) && (get_operator_priority(current) <= get_operator_priority(stack)))
         {
            slist_append(&outputList, stack->data, stack->type);
            pop_stack(&stack);
         }
         if (push_stack(&stack, current) != TRUE)
         {
            print_error("Malloc");
            exit(0);
         }
      }
      else if (current->data == ')')
      {  
         if (!stack)
         {
            print_error("Mauvaise parenthésage de l'expression");
            exit(0);
         }
         while(stack != NULL && stack->data != '(')
         {
            slist_append(&outputList, stack->data, stack->type);
            if (!(stack->next))
            {
               print_error("Mauvaise parenthésage de l'expression");
               exit(0);
            }
            pop_stack(&stack);
         }
         pop_stack(&stack);
      }
      current = current->next;
   }
   while(stack != NULL)
   {
      if (stack->data == '(')
      {
         print_error("Mauvaise parenthésage de l'expression");
         exit(0);
      }
      slist_append(&outputList, stack->data, stack->type);
      pop_stack(&stack);
   }
   return outputList;
}
double
evaluate_expression(ListElmts *outputList)
{
   if(!outputList || outputList->type !=0)
   {
     print_error("Expression mal formée");
     exit(0); 
   }
   ListElmts *current,
             *stack = NULL,
             rslt
   ;
   current = outputList;
   while(current != NULL)
   {
      if(is_operand(current))
      {
         if(push_stack(&stack, current)!= TRUE)
         {
            print_error("Malloc");
            exit(0);
         }
      }
      else
      {

         if(stack->next == NULL)
         {
            print_error("Expression mal formée");
            exit(0);
         }
         rslt = make_operation(stack->next, stack, current);
         pop_stack(&stack);
         pop_stack(&stack);
         if(push_stack(&stack, &rslt)!=TRUE)
         {
            print_error("Malloc");
            exit(0);
         }
      }
      current = current->next;
   }
   return stack->data;
}
ListElmts 
make_operation(ListElmts *x,
               ListElmts *y,
               ListElmts *oprt)
{
   if(x->type!=0 || y->type!=0)
   {
      print_error("Expression mal formée.");
      exit(0);
   }
   ListElmts rslt;
   rslt.type = 0;
   rslt.next = NULL;
   switch((int)oprt->data)
   {
      case '+':
         rslt.data = x->data + y->data;
      break;
      case '-':
         rslt.data = x->data - y->data;
      break;
      case '%':
         if (!is_int(x->data) || !is_int(y->data))
         {
            print_error("L'opération modulo n'est définie que pour les nombres entiers");
            exit(0);
         }
         else
         {
            if (y->data == 0)
            {
               print_error("Division par zéro impossible");
               exit(0);
            }
         }
         rslt.data = (int)x->data % (int)y->data;
      break;
      case '*':
         rslt.data = x->data * y->data;
      break;
      case '/':
         if (y->data == 0)
         {
            print_error("Division par zéro impossible");
            exit(0);
         }
         rslt.data = x->data / y->data;
      break;
   }
   return rslt;
}
