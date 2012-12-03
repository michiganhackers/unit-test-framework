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

#endif

