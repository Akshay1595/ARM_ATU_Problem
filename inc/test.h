#ifndef TEST_H
#define TEST_H

typedef enum
{
    TEST_PASSED,
    TEST_FAILED
} test_result;

extern test_result test1(void);
extern test_result test2(void);

#endif /* TEST_H */