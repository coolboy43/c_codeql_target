    #include <stdio.h>
    #include <stdlib.h>

    void * (*malloc_ptr)(size_t) = malloc;
    void (*free_ptr)(void*) = free;

    void test1() {
        char* buf = (char*) malloc(100);
        free(buf);

        buf[10] = 'a';
    }

    void test2() {
        char* buf1 = (char*) malloc(100);
        char* buf2 = buf1;
        free(buf1);

        buf2[10] = 'a';
    }

    void test3() {
        char* buf = (char*) malloc_ptr(100);
        free_ptr(buf);

        buf[10] = 'a';
    }

    void* test4_inner_1() {
        return malloc(100);
    }
    void test4_inner_2(void* p) {
        return free_ptr(p);
    }
    void test4() {
        char* buf1 = (char*) test4_inner_1();
        char* buf2 = buf1;
        test4_inner_2(buf1);
        buf2[9] = 0;
    }

    int get_minus_two() {
        return -2;
    }
    void test5() {
        char* buf1 = (char*) malloc_ptr(100);
        char* buf2 = buf1;
        buf2[get_minus_two()] = 0;
    }

    void test6_inner(char* buf) {
        printf("%c\n", buf[87 * 2]);
    }
    void test6() {
        char* buf1 = (char*) malloc_ptr(100);
        char* buf2 = buf1;
        test6_inner(buf2);
    }
    void test7() {
        char* buf1 = (char*) malloc_ptr(100);
        int index = 0;
        while (index + 1) {
            printf("%c\n", buf1[index]);
            index = index + 1;
        }
    }

    void test8() {
        char* buf1 = (char*) malloc_ptr(100);
        buf1[0] = 1;
        for (int i = 0; i < 100; i++) {
            buf1[i + 1] =  buf1[0];
        }
    }
    void test9() {
        char* buf1 = (char*) malloc_ptr(100);
        free(buf1);
        free(buf1);
    }
    void test10() {
        char* buf1 = (char*) malloc_ptr(100);
    }

    int main() {
        test1();
        test2();
        test3();
        test4();
        test5();
        test6();
        test7();
        test8();
        test9();
        test10();

        return 0;
    }