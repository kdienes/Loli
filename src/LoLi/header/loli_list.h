/*
 * =====================================================================================
 *
 *       Filename:  loli_list.h
 *
 *    Description:  The primitive list operations of LoLi
 *
 *        Version:  1.0
 *        Created:  04/08/2014 11:17:14 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Z.Shang (), shangzhanlin@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */


#ifndef __LOLI_LIST_
#define __LOLI_LIST_

#include "loli_types.h"
#include "loli_cons.h"
#include "loli_symbols.h"

extern loliObj* prim_length(loliObj* lst);
extern loliObj* prim_append(loliObj* lst);
extern loliObj* prim_list(loliObj* lst, loliObj* env);

#endif
