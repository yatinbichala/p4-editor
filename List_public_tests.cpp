#include "List.hpp"
#include "unit_test_framework.hpp"

using namespace std;


TEST(test_list_default_ctor) {
    List<int> empty_list;
    ASSERT_TRUE(empty_list.empty());
}

TEST(test_traversal) {
    List<int> list;
    for (int i = 0; i < 5; ++i) {
        list.push_back(i);
    }
    int j = 0;
    List<int>::Iterator begin = list.begin();
    List<int>::Iterator end = list.end();
    for (List<int>::Iterator it = begin; it != end; ++it, ++j) {
        ASSERT_EQUAL(*it, j);
    }
    ASSERT_EQUAL(j, list.size());
}

TEST_MAIN()
