/*
 * =====================================================================================
 *
 *       Filename:  loli_main.cpp
 *
 *    Description:  The main part (aka. the entrance of LoLi)
 *
 *        Version:  1.0
 *        Created:  04/05/2014 01:45:34 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Z.Shang (), shangzhanlin@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <iostream>
#include <string>
#include <cstring>

#include "header/loli.h"

#define VERSION "developing alpha 2"

void showHelp();

void loli_init_tl(){
//	top_env = addToEnv(top_env, cons(mksym("a"), mkflt(10.0011011)));
	top_env = addToEnv(top_env, cons(t, t));
	top_env = addToEnv(top_env, cons(nil, nil));
	top_env = addToEnv(top_env, cons(quote, quote));
	//top_env = addToEnv(top_env, cons(mksym("top_env"), top_env));

	//Creating Primitive Operators
	loliObj* loli_sum = mkproc(proc_sum);
	loliObj* loli_mul = mkproc(proc_mul);
	loliObj* loli_sub = mkproc(proc_sub);
	loliObj* loli_div = mkproc(proc_div);
	loliObj* loli_add1 = mkproc(proc_add1);
	loliObj* loli_sub1 = mkproc(proc_sub1);
	loliObj* loli_mod = mkproc(proc_mod);
	loliObj* loli_greater = mkproc(proc_greater);
	loliObj* loli_lesser = mkproc(proc_lesser);
	loliObj* loli_exit = mkproc(proc_exit);
	loliObj* loli_cons = mkproc(prim_cons);
	loliObj* loli_atom = mkproc(proc_atom);
	loliObj* loli_head = mkproc(prim_head);
	loliObj* loli_tail = mkproc(prim_tail);
	loliObj* loli_eq = mkproc(prim_equals);
	loliObj* loli_get_cons = mkproc(get_cons);
	loliObj* loli_get_int= mkproc(get_int);
	loliObj* loli_get_flt = mkproc(get_flt);
	loliObj* loli_get_sym= mkproc(get_sym);
	loliObj* loli_get_proc = mkproc(get_proc);
	loliObj* loli_get_lambda= mkproc(get_lambda);
	loliObj* loli_list = mkproc(prim_list);
	
	top_env = addToEnv(top_env, cons(mksym("+"), loli_sum));
	top_env = addToEnv(top_env, cons(mksym("*"), loli_mul));
	top_env = addToEnv(top_env, cons(mksym("-"), loli_sub));
	top_env = addToEnv(top_env, cons(mksym("/"), loli_div));
	top_env = addToEnv(top_env, cons(mksym("add1"), loli_add1));
	top_env = addToEnv(top_env, cons(mksym("sub1"), loli_sub1));
	top_env = addToEnv(top_env, cons(mksym("mod"), loli_mod));
	top_env = addToEnv(top_env, cons(mksym(">?"), loli_greater));
	top_env = addToEnv(top_env, cons(mksym("<?"), loli_lesser));
	top_env = addToEnv(top_env, cons(mksym("exit"), loli_exit));
	top_env = addToEnv(top_env, cons(mksym("cons"), loli_cons));
	top_env = addToEnv(top_env, cons(mksym("atom?"), loli_atom));
	top_env = addToEnv(top_env, cons(mksym("head"), loli_head));
	top_env = addToEnv(top_env, cons(mksym("tail"), loli_tail));
	top_env = addToEnv(top_env, cons(mksym("eq?"), loli_eq));
	top_env = addToEnv(top_env, cons(mksym("get-int"), loli_get_int));
	top_env = addToEnv(top_env, cons(mksym("get-cons"), loli_get_cons));
	top_env = addToEnv(top_env, cons(mksym("get-flt"), loli_get_flt));
	top_env = addToEnv(top_env, cons(mksym("get-sym"), loli_get_sym));
	top_env = addToEnv(top_env, cons(mksym("get-proc"), loli_get_proc));
	top_env = addToEnv(top_env, cons(mksym("get-lambda"), loli_get_lambda));
	top_env = addToEnv(top_env, cons(mksym("list"), loli_list));

	top_env = addToEnv(top_env, cons(mksym("TOP-ENV"), top_env));
//	loliObj* test = cons(mkint(1), cons(mkflt(2.5), cons(mkint(5), nil)));

//	std::cout<<toString(apply(loli_sum, test))<<"\t"<<toString(apply(loli_mul, test))<<"\n"<<toString(apply(loli_sub, test))<<"\t"<<toString(apply(loli_div, test))<<std::endl;

//	std::cout<<toString(top_env)<<std::endl;

}

int main(int argc, char * argv[]){
	loli_init_tl();
	if(argc >= 2){
		if(strcmp(argv[1] , "--eval") == 0){
			std::cout<<toString(eval(parse(argv[2]), top_env))<<std::endl;
			exit(0);
		}else if(strcmp(argv[1] , "--help") == 0){
			showHelp();
			exit(0);
		}else if(strcmp(argv[1] , "--version") == 0){
			std::cout<<"LoLi version: "<<VERSION<<std::endl;
			exit(0);
		}else if(strcmp(argv[1] , "--file") == 0){
			if(argc == 2){
				std::cout<<"No File Name!"<<std::endl;
				exit(0);
			}else if(argc == 3){
				if(!readFile(argv[2], top_env)){
					exit(0);
				}
				//exit(0);
			}
		}else if(strcmp(argv[1] , "--repl") == 0){
			//DO NOTHING
		}
	}
//	guitest(argc, argv);
	std::cout<<"LoLi PRPR!\nLoLi is a Free Software and you can do whatever you want with it under the licence GPLv3 or any later version"<<std::endl;
	while(true){
		repl(top_env);
	}
	exit(0);
}

void showHelp(){
	std::cout<<"LoLi is a free software, you can find the licence from GNU's website\nUsage: loli [option] ...\nOptions: \n\t--eval\tevaluate an expression\n\t--file [FILE]\tevaluate a file\n\t--help\tdisplay this help\n\t--version\tShow the version\n\t--repl (blank)\tenter the repl\n\nContact the developer:\tMail to shangzhanlin@gmail.com"<<std::endl;
}
