#include "brokenpipe.h"
#include "mock.h"
#include "mocksystem.h"
#include <check.h>

#define TEST_FD 6

void setup_handlers(void) { system_mock_init(); }

void teardown_handlers(void) {
    // Do nothing yet
}

START_TEST(brokenPipe_byDefault_callsCloseOnFd) {
    broken_pipe(TEST_FD);
    ck_assert_int_eq(6, mock_was_called_with(close));
}
END_TEST

TCase *tcase_handler(void) {
    TCase *tc;

    tc = tcase_create("handlers");
    tcase_add_checked_fixture(tc, setup_handlers, teardown_handlers);

    tcase_add_test(tc, brokenPipe_byDefault_callsCloseOnFd);

    return tc;
}

Suite *suite_handler(void) {

    Suite *s;

    s = suite_create("handlers");
    suite_add_tcase(s, tcase_handler());

    return s;
}