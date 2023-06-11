// mytest.h
#include <cxxtest/TestSuite.h>
#include "count_if_followed_by.h"

class MyTestSuite : public CxxTest::TestSuite
{
public:
  void test_stop_before_end( void )
  {
    char const data[4] = {'a','b','a','b'};
    int  const result  = count_if_followed_by (data, 3, 'a', 'b');

    TS_ASSERT( result == 1);
  }

  void test_empty_list( void )
  {
    char const data[0] = {};
    int  const result  = count_if_followed_by (data, 0, 'a', 'b');

    TS_ASSERT( result == 0);
  }

  void test_singe_element( void )
  {
    char const data[1] = {'a'};
    int  const result  = count_if_followed_by (data, 1, 'a', 'b');

    TS_ASSERT( result == 0);
  }

  void testCount_if_followed_by( void )
  {
    char const data[4] = {'a','b','a','b'};
    int  const result  = count_if_followed_by (data, 3, 'b', 'a');

    TS_ASSERT( result == 1 );
  }
};
