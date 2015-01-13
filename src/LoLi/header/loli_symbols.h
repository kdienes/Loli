/*
 * =====================================================================================
 *
 *       Filename:  loli_symbols.h
 *
 *    Description:  The Internal Symols of LoLi
 *
 *        Version:  1.0
 *        Created:  04/05/2014 01:25:34 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Z.Shang (), shangzhanlin@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef __LOLI_SYMS_
#define __LOLI_SYMS_

#include "loli_types.h"

extern loliObj *nil;
extern loliObj *t;
extern loliObj *lambda;
extern loliObj *set;
extern loliObj *quote;
extern loliObj *anon;
extern loliObj *ldef;
extern loliObj *lif;
extern loliObj *llet;

 
extern bool nilp(loliObj* o);
extern void cleanUp();

#endif
