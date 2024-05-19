#include <stdio.h>
#include <stdint.h>
#include "..\inc\test.h"

int main()
{
    test_result eTestResult = TEST_PASSED;
    eTestResult = test1();
    eTestResult = (eTestResult == TEST_PASSED) ? test2() : TEST_FAILED;
    if (eTestResult == TEST_FAILED)
    {
        printf("Driver Implementation failed\n");
    }
    else
    {
        printf("Driver Implementation Succefull\n");
    }
    return 0;
}