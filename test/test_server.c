#include "mocksystem.h"
#include "server.h"
#include <check.h>
#include <stdlib.h>
#include <sys/socket.h>

#define TEST_PORT 5150
#define SOCKET_FD 27

START_TEST(makeSocket_byDefault_createsInternetStreamSocket) {
    socket_will_return(SOCKET_FD);
    make_socket(TEST_PORT);

    ck_assert_int_eq(PF_INET, socket_called_with_domain());
    ck_assert_int_eq(SOCK_STREAM, socket_called_with_type());
}
END_TEST

START_TEST(makeSocket_byDefault_returnsFdFromSocket) {
    socket_will_return(SOCKET_FD);
    ck_assert_int_eq(SOCKET_FD, make_socket(TEST_PORT));
}
END_TEST

START_TEST(makeSocket_onError_ExitsWithError) {
    socket_will_return(-1);
    make_socket(TEST_PORT);
}
END_TEST

TCase *tcase_server(void) {
    TCase *tc;

    tc = tcase_create("server");
    tcase_add_test(tc, makeSocket_byDefault_createsInternetStreamSocket);
    tcase_add_test(tc, makeSocket_byDefault_returnsFdFromSocket);
    tcase_add_exit_test(tc, makeSocket_onError_ExitsWithError, EXIT_FAILURE);
    return tc;
}

Suite *suite_server(void) {
    Suite *s;

    s = suite_create("server");
    suite_add_tcase(s, tcase_server());

    return s;
}