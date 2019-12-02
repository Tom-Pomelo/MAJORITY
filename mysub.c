#include <stdbool.h>

/* * * * * * * * * * * * * * *
 * * * * GLOBAL VARIABLE * * *
 * * * * * * * * * * * * * * */
int type_one_index_1 = 0;
int type_one_index_2 = 0;
int type_two_index_1 = 0;
int type_two_index_2 = 0;
int type_one_cnt = 0;
int type_two_cnt = 0;
int visited_cnt = 0;
int mid = 0;
int depth = 0;

/* * * * * * * * * * * * * * *
 * * * * HELPER FUNCTION * * *
 * * * * * * * * * * * * * * */
void init() {
    type_one_index_1 = 0;
    type_one_index_2 = 0;
    type_two_index_1 = 0;
    type_two_index_2 = 0;
    type_one_cnt = 0;
    type_two_cnt = 0;
    visited_cnt = 0;
}

bool test_if_a_winner() {
    return type_one_cnt >= mid || type_two_cnt >= mid;
}

int diff(int a, int b) {
    return a >= b ? (a - b) : (b - a);
}

void classify(int n, int depth) {
    int p = 0, q = 0;
    if (depth == 0) {
        int a[4] = {1, 2, 3, 4}, b[4] = {2, 3, 4, 5};
        p = QCOUNT(1, a), q = QCOUNT(1, b);
    } else {
        int a[4] = {depth + 2, depth + 3, depth + 4, depth + 5};
        p = 4, q = QCOUNT(1, a);
    }
    if (p == 0 && q == 0) {
        // 0 1 0 1 0
        type_one_index_1 = 1;
        type_one_index_2 = 5;
        int combination[3][3] = {{2, 3}, {2, 4}, {3, 4}};
        for (int i = 0; i < 3; ++i) {
            int a[4] = {1, combination[i][0], combination[i][1], 5};
            int res = QCOUNT(1, a);
            if (res == 0) {
                type_two_index_1 = combination[i][0];
                type_two_index_2 = combination[i][1];
                break;
            }
        }
        type_one_cnt = 3;
        type_two_cnt = 2;
        visited_cnt = 5;
    } else if (p == 0 && q == 2) {
        // 0 1 0 1 1
        type_one_index_1 = 5;
        type_two_index_1 = 1;
        int combination[3][3] = {{2, 3}, {2, 4}, {3, 4}};
        for (int i = 0; i < 3; ++i) {
            int a[4] = {1, combination[i][0], combination[i][1], 5};
            int res = QCOUNT(1, a);
            if (res == 2) {
                type_one_index_2 = combination[i][0];
                type_two_index_2 = combination[i][2];
                break;
            }
        }
        type_one_cnt = 3;
        type_two_cnt = 2;
        visited_cnt = 5;
    } else if (p == 2 && q == 0) {
        // 0 0 0 1 1
        type_one_index_1 = 1;
        type_two_index_1 = 5;
        int combination[3][3] = {{2, 3, 4}, {2, 4, 3}, {3, 4, 2}};
        for (int i = 0; i < 3; ++i) {
            int a[4] = {1, combination[i][0], combination[i][1], 5};
            int res = QCOUNT(1, a);
            if (res == 2) {
                type_one_index_2 = combination[i][0];
                type_two_index_2 = combination[i][2];
                break;
            }
        }
        type_one_cnt = 3;
        type_two_cnt = 2;
        visited_cnt = 5;
    } else if (p == 2 && q == 2) {
        // 0 1 0 0 0
        type_one_index_1 = 1;
        type_one_index_2 = 5;
        int combination[3][3] = {{2, 3, 4}, {2, 4, 3}, {3, 4, 2}};
        bool flag = false;
        for (int i = 0; i < 3; ++i) {
            int a[4] = {1, combination[i][0], combination[i][1], 5};
            int res = QCOUNT(1, a);
            if (res == 4) {
                flag = true;
                type_two_index_1 = combination[i][2];
                break;
            }
        }
        if (!flag) {
            // 0 1 1 1 0
            type_two_index_1 = 2;
            type_two_index_2 = 3;
            type_one_cnt = 2;
            type_two_cnt = 3;
        } else {
            type_one_cnt = 4;
            type_two_cnt = 1;
        }
        visited_cnt = 5;
    } else if (p == 2 && q == 4) {
        // 1 0 0 0 0
        type_two_index_1 = 1;
        type_one_index_1 = 2;
        type_one_index_2 = 3;
        type_one_cnt = 4;
        type_two_cnt = 1;
        visited_cnt = 5;
    } else if (p == 4 && q == 2) {
        // 0 0 0 0 1
        type_one_index_1 = 1;
        type_one_index_2 = 2;
        type_two_index_1 = depth + 5;
        type_one_cnt += depth + 4;
        type_two_cnt += 1;
        visited_cnt += depth + 5;
    } else if (p == 4 && q == 4) {
        // 0 0 0 0 0
        int mid = n / 2 + 1;
        if (depth + 5 <= mid) {
            classify(n, depth + 1);
        } else {
            visited_cnt = mid;
            type_one_cnt = mid;
            type_one_index_1 = 1;
            type_one_index_2 = 2;
        }
    }
}

void update_cnt_two(int n, int* array_n, int cnt_n) {
    for (int i = 0; i < cnt_n; ++i) {
        int p = array_n[i];
        int q = array_n[i] + 1;
        int a[4] = {p, q, type_one_index_1, type_one_index_2};
        int res = QCOUNT(1, a);
        switch (res) {
            case 0: {
                // 0 0 || 1 1 1 0
                type_one_cnt += 1;
                type_two_cnt += 3;
                break;
            }
            case 2: {
                // 0 0 || 0 1 x x
                type_one_cnt += 1;
                type_two_cnt += 1;
                int first = array_n[i] + 2;
                int second = array_n[i] + 3;
                int b[4] = {first, second, type_one_index_1, type_one_index_2};
                int v = QCOUNT(1, b);
                switch (v) {
                    case 0: {
                        // 0 0 || 1 1
                        type_two_cnt += 2;
                        break;
                    }
                    case 4: {
                        // 0 0 || 00
                        type_one_cnt += 2;
                        break;
                    }
                }
                break;
            }
            case 4: {
                // 0 0 || 0 0 0 1
                type_one_cnt += 3;
                type_two_cnt += 1;
                break;
            }
        }
        if (test_if_a_winner()) return;
    }
}

void update_cnt_four(int n, int* array_n, int cnt_n) {
    bool is_remaining = true;
    for (int i = 0; i <= cnt_n - 2; i += 2) {
        if (i == cnt_n - 2) {
            is_remaining = false;
        }
        int first = array_n[i];
        int second = array_n[i + 1];
        int a[4] = {first, second, type_one_index_1, type_one_index_2};
        int res = QCOUNT(1, a);
        switch (res) {
            case 0: {
                type_two_cnt += 8;
                break;
            }
            case 2: {
                type_one_cnt += 4;
                type_two_cnt += 4;
                break;
            }
            case 4: {
                type_one_cnt += 8;
                break;
            }
        }
        if (test_if_a_winner()) return;
    }
    if (is_remaining) {
        int p = array_n[cnt_n - 1];
        int q = array_n[cnt_n - 1] + 1;
        int b[4] = {p, q, type_one_index_1, type_one_index_2};
        int res = QCOUNT(1, b);
        switch (res) {
            case 0: {
                // 0 0 || 1 1 1 1
                type_two_cnt += 4;
                break;
            }
            case 4: {
                // 0 0 || 0 0 0 0
                type_one_cnt += 4;
                break;
            }
        }
    }
}

void update_cnt_leftover(int n) {
    bool is_remaining = true;
    while (visited_cnt + 2 <= n) {
        if (visited_cnt + 2 == n) {
            is_remaining = false;
        }
        int a[4] = {visited_cnt + 1, visited_cnt + 2, type_one_index_1, type_one_index_2};
        int res = QCOUNT(1, a);
        switch (res) {
            case 0: {
                // 0 0 || 1 1
                type_two_cnt += 2;
                break;
            }
            case 2: {
                // 0 0 || 0 1
                type_one_cnt += 1;
                type_two_cnt += 1;
                break;
            }
            case 4: {
                // 0 0 || 0 0
                type_one_cnt += 2;
                break;
            }
        }
        visited_cnt += 2;
        if (test_if_a_winner()) return;
    }
    if (is_remaining) {
        // a
        int d = diff(type_one_cnt, type_two_cnt);
        if (d > 1) return;
        int a[4] = {type_one_index_1, type_one_index_2, type_two_index_1, visited_cnt + 1};
        int res = QCOUNT(1, a);
        switch (res) {
            case 0: {
                // 0 0 1 || 1
                type_two_cnt += 1;
                break;
            }
            case 2: {
                // 0 0 1 || 0
                type_one_cnt += 1;
                break;
            }
        }
    }
}

void update_cnt(int n, int* array_two, int* array_four, int cnt_two, int cnt_four) {
    if (cnt_four > 0) update_cnt_four(n, array_four, cnt_four);
    if (cnt_two > 0) update_cnt_two(n, array_two, cnt_two);
}

void forward_check_by_four(int n) {
    int leftover = n - visited_cnt;
    int remainder = leftover % 4;
    int groups = leftover / 4;

    int groups_with_start_index[groups];
    memset(groups_with_start_index, -1, sizeof(groups_with_start_index));
    for (int i = visited_cnt, j = 0; i + 4 <= n; i += 4, ++j) {
        groups_with_start_index[j] = i + 1;
    }

    int array_two[groups];
    int array_four[groups];
    memset(array_two, -1, sizeof(array_two));
    memset(array_four, -1, sizeof(array_four));
    int cnt_two = 0, cnt_four = 0;

    for (int i = 0; i < groups; ++i) {
        int a[4] = {groups_with_start_index[i], groups_with_start_index[i] + 1, groups_with_start_index[i] + 2,
                    groups_with_start_index[i] + 3};
        int res = QCOUNT(1, a);
        switch (res) {
            case 0: {
                type_one_cnt += 2;
                type_two_cnt += 2;
                break;
            }
            case 2: {
                array_two[cnt_two++] = a[0];
                break;
            }
            case 4: {
                array_four[cnt_four++] = a[0];
                break;
            }
            default:
                break;
        }
        if (test_if_a_winner()) return;
    }
    update_cnt(n, array_two, array_four, cnt_two, cnt_four);
    visited_cnt = n - remainder;
}

/* * * * * * * * * * * * * * *
 * * * * MYSUB FUNCTION  * * *
 * * * * * * * * * * * * * * */
int mysub(int n) {
    depth = 0;
    mid = n / 2 + 1;

    init();

    classify(n, depth);

    forward_check_by_four(n);
    if (type_one_cnt < mid && type_two_cnt < mid && visited_cnt < n) {
        update_cnt_leftover(n);
    }
    if (type_one_cnt > type_two_cnt) {
        return type_one_index_1;
    }
    if (type_one_cnt < type_two_cnt) {
        return type_two_index_1;
    }
    return 0;
}