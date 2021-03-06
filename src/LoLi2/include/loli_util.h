/*
 * =====================================================================================
 *
 *       Filename:  loli_util.h
 *
 *    Description:  Utilities of LoLi
 *
 *        Version:  1.0
 *        Created:  06/26/2014 06:52:14 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Z.Shang (), shangzhanlin@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef __LOLI_UTIL_
#define __LOLI_UTIL_

#include <string>
#include "loli_obj.h"

extern void loli_err(std::string err);
extern std::string pairUp(std::string str);
extern bool is_spchar(char c);

#endif
