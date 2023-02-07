/*
  teZZt tiny test library by B. Bachelet et L. Yon
  Designed for gcc, not working with clang
  Septembre 2017
  Version : 0.1
*/

#ifndef teZZt_h
#define teZZt_h

#include<stdio.h>
#include<stdlib.h>
//#include<math.h>

// DO NOT COMPILE with -ansi -pedantic options
// https://gcc.gnu.org/onlinedocs/gcc/Nested-Functions.html

// TO DO : 
// * add support for memory hooks
//   https://www.gnu.org/software/libc/manual/html_node/Hooks-for-Malloc.html
// * __tezzt__exit_program_with_report() can be recorded more than one (one by group)


/*
 *  SYMBOLIC CONSTANTS
 */

#define __ANSI_RED__ "\033[31;1m"
#define __ANSI_GRE__ "\033[32;1m"
#define __ANSI_YEL__ "\033[33;1m"
#define __ANSI_NOR__ "\033[0m"

#define GROUP_COUNTER_LIMIT 50
#define EPSILON 1E-6

/*
 *  Prototypes of internals functions
 */

void __tezzt__exit_program_with_report();
void __tezzt__passed_test();
void __tezzt__failed_test();

/* math lib including or not, this is the question */
// #define EQ(A, B) (fabs(A-B)<1E-6)
#define EQ(A, B) (-EPSILON<(A-B) && (A-B)<EPSILON)
 
#define LOG(A) do {              \
    fprintf(stderr, "%s\n", A); \
} while(0) 

// ---------------

#define BEGIN_TEST_GROUP(NAME)                  \
 void __testgroup_##NAME##__(void) {            \
  static void (*__group_tests__[GROUP_COUNTER_LIMIT])(void);     \
  static unsigned __group_counter__;            \
                                                \
  static const char * __group_name__ = #NAME;   \
  static unsigned passed_tests = 0;             \
  static unsigned failed_tests = 0;             \
  __group_counter__=0;                          \
  atexit(__tezzt__exit_program_with_report);             \

/* -------------------------------------------------------------------------------END_TEST_GROUP */
#define END_TEST_GROUP(NO_USE)                                        \
  unsigned i      = 0;                                               \
                                                                     \
  while (i<__group_counter__) {                                      \
   __group_tests__[i++]();                                           \
  }                                                                  \
                                                                     \
  printf("[%s]",__group_name__);                                     \
 }    

#define RUN_TEST_GROUP(NAME) __testgroup_##NAME##__()


#define TEST(NAME, ...)\
auto void __test_##NAME(); \
if (__group_counter__< GROUP_COUNTER_LIMIT) \
__group_tests__[__group_counter__++]=&__test_##NAME; \
else fprintf(stderr, __ANSI_YEL__"[WARNING] "#NAME " test not registered\n"__ANSI_NOR__); \
void __test_##NAME()


#define CHECK(COND) do { \
  if (COND) { \
    ++passed_tests; \
    __tezzt__passed_test(); \
    fprintf(stderr, "%s:%4d | PASSED  : " __ANSI_GRE__ #COND "\n" __ANSI_NOR__, __FILE__, __LINE__ );  \
  } else {  \
    ++failed_tests; \
    __tezzt__failed_test(); \
    fprintf(stderr, "%s:%4d | EXPECT  : " __ANSI_YEL__ #COND "\n" __ANSI_NOR__, __FILE__, __LINE__ );  \
  } \
} while(0)

#define REQUIRE(COND) do {\
  if (COND) { \
    ++passed_tests;\
    __tezzt__passed_test(); \
    fprintf(stderr, "%s:%4d | CHECKED : " __ANSI_GRE__ #COND "\n" __ANSI_NOR__, __FILE__, __LINE__ );  \
  } else {  \
    ++failed_tests; \
    __tezzt__failed_test(); \
    fprintf(stderr, "%s:%4d | REQUIRE : " __ANSI_RED__ #COND "\n" __ANSI_NOR__, __FILE__, __LINE__ );  \
    return; \
  } \
} while(0)

#endif
