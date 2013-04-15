#include "stdlib.h"
#include "stdio.h"

#include "./unit_test_framework.h"

// NOTE - These are for readability and portability, and should not be used 
// outside of this file. Ever.
#ifdef __cplusplus
	#define _TRUE true
	#define _FALSE false
#else
	#define _TRUE 1
	#define _FALSE 0
#endif

// Defines the color codes
#define _RED "\033[31m"
#define _GREEN "\033[32m"
#define _YELLOW "\033[33m"
#define _WHITE "\033[37m"
#define _BLUE  "\x1B[34m"

// Helper prototypes
static void print_error(const int, const int, const char * const);
static _BOOL_RETURN_TYPE negate(const _BOOL_RETURN_TYPE);
static int int_cmp(const int*, const int*);
static void reset_color(void);
static void setup();
static void takedown();

// Global static variables
static uint32_t num_passed_g;
static uint32_t num_failed_g;
static uint32_t test_number_g;

// Global static function pointers, set to their defaults
static setup_fn_t test_setup    = setup;
static setup_fn_t test_takedown = takedown;

// Test start and end functions
void start_suite(const char * const log_msg) {
	num_passed_g = num_failed_g = test_number_g = 0;
	fprintf(stderr, "\n\033[33m[Start Suite] %s\n", log_msg);
	reset_color();
}

void end_suite() {
	static const char * const out_fmt = "\n%sPassed: %i\n%sFailed: %i\n\n";
	fprintf(stderr, out_fmt, _GREEN, num_passed_g, _RED, num_failed_g);
	reset_color();
}

void test_description(const char * const log_msg) {
	static const char * const out_fmt = "\n%s[Test %i] %s\n";
	fprintf(stderr, out_fmt, _YELLOW, ++test_number_g, log_msg);
	reset_color();
}

void test_passed(const char * const log_msg) {
	static const char * const out_fmt = "%s[PASS]%s %s\n";
	fprintf(stderr, out_fmt, _GREEN, _WHITE, log_msg);
	reset_color();
	++num_passed_g;
}

void test_failed(const char * const log_msg) {
	static const char * const out_fmt = "%s[FAIL]%s %s\n";
	fprintf(stderr, out_fmt, _RED, _WHITE, log_msg);
	reset_color();
	++num_failed_g;
}

// Prototypes for the checking functions
_BOOL_RETURN_TYPE 
assertEqual(const int arg1, const int arg2) {
	_BOOL_RETURN_TYPE res = assertEqualCmp(&arg1, &arg2, (cmp_fn_t)int_cmp);
	if(res == _FALSE) { print_error(arg1, arg2, "does not equal"); }
	return res;
}

_BOOL_RETURN_TYPE 
assertEqualCmp(const void *arg1, const void *arg2, cmp_fn_t cmp) {
	return cmp(arg1, arg2) == 0 ? _TRUE : _FALSE;
}

_BOOL_RETURN_TYPE 
assertNotEqual(const int arg1, const int arg2) {
	_BOOL_RETURN_TYPE res = negate(assertEqualCmp(&arg1, &arg2, (cmp_fn_t)int_cmp));
	if(res == _FALSE) { print_error(arg1, arg2, "equals"); }
	return res;
}

_BOOL_RETURN_TYPE 
assertNotEqualCmp(const void *arg1, const void *arg2, cmp_fn_t cmp) {
	return negate(assertEqualCmp(arg1, arg2, cmp));
}

_BOOL_RETURN_TYPE 
assertLess(const int arg1, const int arg2) {
	_BOOL_RETURN_TYPE res = assertLessCmp(&arg1, &arg2, (cmp_fn_t)int_cmp);
	if(res == _FALSE) { print_error(arg1, arg2, "not less than"); }
	return res;
}

_BOOL_RETURN_TYPE 
assertLessCmp(const void *arg1, const void *arg2, cmp_fn_t cmp) {
	return cmp(arg1, arg2) < 0 ? _TRUE : _FALSE;
}

_BOOL_RETURN_TYPE 
assertLessEqual(const int arg1, const int arg2) {
	_BOOL_RETURN_TYPE res = assertLessEqualCmp(&arg1, &arg2, (cmp_fn_t)int_cmp);
	if(res == _FALSE) { print_error(arg1, arg2, "not less than or equal to"); }
	return res;
}

_BOOL_RETURN_TYPE 
assertLessEqualCmp(const void *arg1, const void *arg2, cmp_fn_t cmp) {
	return cmp(arg1, arg2) <= 0 ? _TRUE : _FALSE;
}

_BOOL_RETURN_TYPE 
assertGreater(const int arg1, const int arg2) {
	_BOOL_RETURN_TYPE res = negate(assertLessEqualCmp(&arg1, &arg2, (cmp_fn_t)int_cmp));
	if(res == _FALSE) { print_error(arg1, arg2, "not greater than"); }
	return res;
}

_BOOL_RETURN_TYPE 
assertGreaterCmp(const void *arg1, const void *arg2, cmp_fn_t cmp) {
	return negate(assertLessEqualCmp(arg1, arg2, cmp));
}

_BOOL_RETURN_TYPE 
assertGreaterEqual(const int arg1, const int arg2) {
	_BOOL_RETURN_TYPE res = negate(assertLessCmp(&arg1, &arg2, (cmp_fn_t)int_cmp));
	if(res == _FALSE) { print_error(arg1, arg2, "not greater or equal to"); }
	return res;
}

_BOOL_RETURN_TYPE 
assertGreaterEqualCmp(const void *arg1, const void *arg2, cmp_fn_t cmp) {
	return negate(assertLessCmp(arg1, arg2, cmp));
}

_BOOL_RETURN_TYPE 
assertIsNull(const void* arg1) {
	return arg1 == NULL ? _TRUE : _FALSE;
}

_BOOL_RETURN_TYPE 
assertIsNotNull(const void* arg1) {
	return arg1 != NULL ? _TRUE : _FALSE;
}

void setBeforeFunc(setup_fn_t setup) {
	test_setup = setup;
}

void setAfterFunc(setup_fn_t takedown) {
	test_takedown = takedown;
}

void runTest(test_fn_t test, const char* const test_name) {
	fprintf(stderr, "\n" _BLUE "[Start Test] %s\n", test_name);
	reset_color();
	test_setup();
	test();
	test_takedown();
	fprintf(stderr, "\n" _BLUE "[End Test] %s\n", test_name);
	reset_color();
}

// Default setup function, does nothing
void setup() {
	return;
}

// Default takedown function, does nothing
void takedown() {
	return;
}

// Default compare function for ints
int int_cmp(const int *arg1, const int *arg2) {
	return *arg1 - *arg2;
}

// Returns the correct logical opposite of the given input
_BOOL_RETURN_TYPE negate(const _BOOL_RETURN_TYPE val) {
	return val == _TRUE ? _FALSE : _TRUE;
}

// Resets the terminal's color to white
void reset_color() {
	fprintf(stderr, "%s", _WHITE);
}

void print_error(const int arg1, const int arg2, const char * const log_msg) {
	fprintf(stderr, "%s%i %s %i\n", _RED, arg1, log_msg, arg2);
	reset_color();
}


