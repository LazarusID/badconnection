#include "mocksystem.h"
#include "server.h"
#include <check.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <sys/socket.h>

#define TEST_PORT 5150
#define SOCKET_FD 27

void setup(void) { socket_will_return(SOCKET_FD); }

void teardown(void) {
    // Do Nothing
}

START_TEST(makeSocket_byDefault_createsInternetStreamSocket) {
    make_socket(TEST_PORT);

    ck_assert_int_eq(PF_INET, socket_called_with_domain());
    ck_assert_int_eq(SOCK_STREAM, socket_called_with_type());
}
END_TEST

START_TEST(makeSocket_byDefault_returnsFdFromSocket) {
    ck_assert_int_eq(SOCKET_FD, make_socket(TEST_PORT));
}
END_TEST

START_TEST(makeSocket_onError_ExitsWithError) {
    socket_will_return(-1);
    make_socket(TEST_PORT);
}
END_TEST

START_TEST(makeSocket_byDefault_bindsSocketToSpecifiedPortOnAllInterfaces) {
    struct sockaddr_in *bound_add;
    make_socket(TEST_PORT);

    ck_assert_int_eq(SOCKET_FD, bind_called_with_socket());
    ck_assert_int_eq(htons(TEST_PORT), bind_called_with_port());
    ck_assert_int_eq(AF_INET, bind_called_with_family());
    ck_assert_int_eq(INADDR_ANY, bind_called_with_address());
}
END_TEST

TCase *tcase_server(void) {
    TCase *tc;

    tc = tcase_create("server");
    tcase_add_checked_fixture(tc, setup, teardown);

    tcase_add_test(tc, makeSocket_byDefault_createsInternetStreamSocket);
    tcase_add_test(tc, makeSocket_byDefault_returnsFdFromSocket);
    tcase_add_exit_test(tc, makeSocket_onError_ExitsWithError, EXIT_FAILURE);
    tcase_add_test(
        tc, makeSocket_byDefault_bindsSocketToSpecifiedPortOnAllInterfaces);
    return tc;
}

Suite *suite_server(void) {
    Suite *s;

    s = suite_create("server");
    suite_add_tcase(s, tcase_server());

    return s;
}