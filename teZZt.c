#include "teZZt.h"
#include <stdio.h>


static unsigned __tezzt__passed_tests_counter = 0;
static unsigned __tezzt__failed_tests_counter = 0;


void __tezzt__passed_test() {
	++__tezzt__passed_tests_counter;
}
void __tezzt__failed_test() {
	++__tezzt__failed_tests_counter;
}

void __tezzt__exit_program_with_report() {
  fprintf( stderr, "--- teZZT REPORT ---\n");
  fprintf( stderr, __ANSI_RED__ "%3d test(s) failed\n",   __tezzt__failed_tests_counter);
  fprintf( stderr, __ANSI_GRE__ "%3d test(s) passed\n",   __tezzt__passed_tests_counter);
  fprintf( stderr, __ANSI_NOR__ );
}