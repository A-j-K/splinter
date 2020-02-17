/*********************************************************************************
 *   Copyright (c) 2008-2017 Andy Kirkham  All rights reserved.
 *
 *   Permission is hereby granted, free of charge, to any person obtaining a copy
 *   of this software and associated documentation files (the "Software"),
 *   to deal in the Software without restriction, including without limitation
 *   the rights to use, copy, modify, merge, publish, distribute, sublicense,
 *   and/or sell copies of the Software, and to permit persons to whom
 *   the Software is furnished to do so, subject to the following conditions:
 *
 *   The above copyright notice and this permission notice shall be included
 *   in all copies or substantial portions of the Software.
 *
 *   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 *   THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *   FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 *   IN THE SOFTWARE.
 ***********************************************************************************/

#include <check.h>
#include <stdlib.h>

#include "../src/utils/longhash.h"

#define STR0 "1Test Me1"
#define STR1 "2Test Me2"
#define STR33 "3Test Me3"

longhash_pt p = NULL;

void setup(void)
{
	p = longhash_ctor(32, free);
	longhash_insert(p,  0, strdup(STR0));
	longhash_insert(p,  1, strdup(STR1));
	longhash_insert(p, 33, strdup(STR33));
}

void teardown(void)
{
	longhash_dtor(&p);
}

START_TEST(test_longhash_find)
{
	char *actual = NULL;
	ck_assert(longhash_count(p) == 3);
	actual = longhash_find(p, 0);
	ck_assert(actual);
	ck_assert_str_eq(STR0, actual);
	actual = longhash_find(p, 1);
	ck_assert(actual);
	ck_assert_str_eq(STR1, actual);
	actual = longhash_find(p, 33);
	ck_assert(actual);
	ck_assert_str_eq(STR33, actual);
}
END_TEST

START_TEST(test_longhash_delete)
{
	char *actual = NULL;
	ck_assert(longhash_count(p) == 3);
	longhash_delete(p, 0);
	ck_assert(longhash_count(p) == 2);
}
END_TEST

START_TEST(test_longhash_remove)
{
	char *actual = NULL;
	ck_assert(longhash_count(p) == 3);
	actual = longhash_remove(p, 0);
	ck_assert(longhash_count(p) == 2);
	ck_assert_str_eq(STR0, actual);
	free(actual);
	actual = longhash_remove(p, 1);
	ck_assert(longhash_count(p) == 1);
	ck_assert_str_eq(STR1, actual);
	free(actual);
	actual = longhash_remove(p, 33);
	ck_assert(longhash_count(p) == 0);
	ck_assert_str_eq(STR33, actual);
	free(actual);
}
END_TEST

Suite *suite()
{
	Suite *s;
	TCase *tc_core;

	s = suite_create("LONGHASH");

	tc_core = tcase_create("Core");
	tcase_add_checked_fixture(tc_core, setup, teardown);
	tcase_add_test(tc_core, test_longhash_find);
	tcase_add_test(tc_core, test_longhash_delete);
	tcase_add_test(tc_core, test_longhash_remove);
	suite_add_tcase(s, tc_core);

	return s;
}

int 
main(void)
{
	int number_failed;
	Suite *s;
	SRunner *sr;
	s = suite();
	sr = srunner_create(s);
	srunner_set_log (sr, "longhash.log");
	srunner_run_all(sr, CK_NORMAL);
	number_failed = srunner_ntests_failed(sr);
	srunner_free(sr);
	return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

