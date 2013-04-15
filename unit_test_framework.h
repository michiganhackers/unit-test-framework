#ifndef UNIT_TEST_FRAMEWORK_H
#define UNIT_TEST_FRAMEWORK_H

#include "inttypes.h"

#ifdef __cplusplus
	#define _BOOL_RETURN_TYPE bool
#else
	#define _BOOL_RETURN_TYPE uint8_t
#endif

// Typedef the comparison function for ease of use. This function uses the
// convention of returning.
// <1 : arg1 < arg2 | 0 : arg1 == arg2 | >1 : arg1 > arg2
typedef int(*cmp_fn_t)(const void*, const void*);

// Typedefs for setup / takedown / test functions for ease of use.
typedef void (*setup_fn_t)(void);

// Typedef for a test function
typedef setup_fn_t test_fn_t;

// Output logging helper functions
void test_description(const char * const);
void test_passed(const char * const);
void test_failed(const char * const);
void start_suite(const char * const);
void end_suite(void);

// Prototypes for the checking functions
_BOOL_RETURN_TYPE assertEqual(const int, const int);
_BOOL_RETURN_TYPE assertEqualCmp(const void*, const void*, cmp_fn_t cmp);

_BOOL_RETURN_TYPE assertNotEqual(const int, const int);
_BOOL_RETURN_TYPE assertNotEqualCmp(const void*, const void*, cmp_fn_t cmp);

_BOOL_RETURN_TYPE assertLess(const int, const int);
_BOOL_RETURN_TYPE assertLessCmp(const void*, const void*, cmp_fn_t cmp);

_BOOL_RETURN_TYPE assertLessEqual(const int, const int);
_BOOL_RETURN_TYPE assertLessEqualCmp(const void*, const void*, cmp_fn_t cmp);

_BOOL_RETURN_TYPE assertGreater(const int, const int);
_BOOL_RETURN_TYPE assertGreaterCmp(const void*, const void*, cmp_fn_t cmp);

_BOOL_RETURN_TYPE assertGreaterEqual(const int, const int);
_BOOL_RETURN_TYPE assertGreaterEqualCmp(const void*, const void*, cmp_fn_t cmp);

_BOOL_RETURN_TYPE assertIsNull(const void*);
_BOOL_RETURN_TYPE assertNotNull(const void*);

// Prototypes for test runner functions
void setBeforeFunc(setup_fn_t setup);
void runTest(test_fn_t test, const char* const test_name);
void setAfterFunc(setup_fn_t takedown);

#endif

