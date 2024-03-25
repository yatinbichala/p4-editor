#include "List.hpp"
#include "unit_test_framework.hpp"

using namespace std;

// Add your test cases here

TEST(test_list_default_ctor) {
    List<int> empty_list;
    ASSERT_TRUE(empty_list.empty());
}

TEST(test_list_copy_ctor) {
    List<int> orig_list;
    for (int i = 0; i < 5; ++i) {
        orig_list.push_back(i);
    }
    List<int> copy_list(orig_list);

    List<int>::Iterator o = orig_list.begin();
    List<int>::Iterator c = copy_list.begin();
    List<int>::Iterator orig_end = orig_list.end();
    List<int>::Iterator copy_end = copy_list.end();
    while (o != orig_end && c != copy_end) {
        ASSERT_TRUE(*o == *c);
        ++o;
        ++c;
    }
    ASSERT_EQUAL(orig_list.size(), copy_list.size());
    ASSERT_EQUAL(orig_list.front(), 0);
    ASSERT_EQUAL(orig_list.back(), 4);
}

TEST(test_traversal) {
    List<int> list;
    for (int i = 0; i < 5; ++i) {
        list.push_back(i);
    }
    int j = 0;
    for (List<int>::Iterator it = list.begin(); it != list.end(); ++it, ++j) {
        ASSERT_EQUAL(*it, j);
    }
    ASSERT_EQUAL(j, list.size());
    ASSERT_EQUAL(0, list.front());
    ASSERT_EQUAL(4, list. back());
}

TEST(test_traversal_reversal) {
    List<int> list;
    for (int i = 0; i < 5; ++i) {
        list.push_front(i);
    }
    int j = 0;
    for (List<int>::Iterator it = list.begin(); it != list.end(); ++it, ++j) {
        ASSERT_EQUAL(*it, list.size() - j - 1);
    }
    ASSERT_EQUAL(j, list.size());
    ASSERT_EQUAL(0, list.back());
    ASSERT_EQUAL(4, list.front());
}

TEST(test_assignment_overload) {
    List<int> list;
    for (int i = 0; i < 5; ++i) {
        list.push_front(i);
    }
    List<int> list2;
    list2 = list;

    List<int>::Iterator l1 = list.begin();
    List<int>::Iterator l2 = list2.begin();
    List<int>::Iterator list_end = list.end();
    List<int>::Iterator list2_end = list2.end();
    while (l1 != list_end && l2 != list2_end) {
        ASSERT_TRUE(*l1 == *l2);
        ++l1;
        ++l2;
    }
    ASSERT_EQUAL(list.size(), list2.size());
}

TEST(test_assignment_overload_empty) {
    List<int> list;
    List<int> list2;
    list2 = list;

    List<int>::Iterator l1 = list.begin();
    List<int>::Iterator l2 = list2.begin();
    List<int>::Iterator list_end = list.end();
    List<int>::Iterator list2_end = list2.end();
    while (l1 != list_end && l2 != list2_end) {
        ASSERT_TRUE(*l1 == *l2);
        ++l1;
        ++l2;
    }
    ASSERT_EQUAL(list.size(), list2.size());
}

TEST(test_assignment_overload_self) {
    List<int> list;
    List<int> &list_clone = list;
    for (int i = 0; i < 5; ++i) {
        list.push_front(i);
    }
    list = list_clone;

    List<int>::Iterator l1 = list.begin();
    List<int>::Iterator list_end = list.end();;
    while (l1 != list_end) {
        ASSERT_TRUE(*l1 == *l1);
        ++l1;
    }
    ASSERT_EQUAL(list.size(), list.size());
}

TEST(test_assignment_overload_self_empty) {
    List<int> list;
    List<int> &list_clone = list;
    
    list = list_clone;

    List<int>::Iterator l1 = list.begin();
    List<int>::Iterator list_end = list.end();;
    while (l1 != list_end) {
        ASSERT_TRUE(*l1 == *l1);
        ++l1;
    }
    ASSERT_EQUAL(list.size(), list.size());
}

TEST(test_remove_add_node_const_begin) {
    List<int> list;
    for (int i = 0; i < 5; ++i) {
        list.push_front(i);
    }
    List<int>::Iterator l = list.begin();
    l = list.insert(l, 10);
    l = list.insert(l, 11);
    l = list.insert(l, 12);
    ASSERT_EQUAL(list.size(), 8);
    l = list.erase(l);
    l = list.erase(l);
    l = list.erase(l);
    l = list.erase(l);
    ASSERT_EQUAL(list.size(), 4);
    ASSERT_EQUAL(list.front(), 3);
}


//adjust iterators to account for empty
TEST(test_remove_insert_node_const_end_empty) {
    List<int> list;
    List<int>::Iterator l = list.end();
    l = list.insert(l, 10);
    l = list.end();
    l = list.insert(l, 11);
    l = list.end();
    l = list.insert(l, 12);
    l = list.end();
    --l;
    ++l;
    l--;
    ASSERT_EQUAL(list.size(), 3);
    ASSERT_EQUAL(list.back(), 12);
    l = --list.erase(l);
    l = list.erase(l);
    ASSERT_TRUE(l == list.end());
    ASSERT_EQUAL(list.size(), 1);
    ASSERT_EQUAL(list.back(), list.front());
    ASSERT_EQUAL(list.back(), 10);
}

TEST(test_remove_insert_node_const_end) {
    List<int> list;
    for (int i = 0; i < 5; ++i) {
        list.push_front(i);
    }
    List<int>::Iterator l = list.end();
    l = list.insert(l, 10);
    l = list.end();
    l = list.insert(l, 11);
    l = list.end();
    l = list.insert(l, 12);
    l = list.end();
    --l;
    ++l;
    l--;
    ASSERT_EQUAL(list.size(), 8);
    ASSERT_EQUAL(list.back(), 12);
    l = --list.erase(l);
    l = list.erase(l);
    ASSERT_TRUE(l == list.end());
    ASSERT_EQUAL(list.size(), 6);
    ASSERT_EQUAL(list.back(), 10);
}

TEST(test_remove_insert_node_middle) {
    List<int> list;
    for (int i = 0; i < 2; ++i) {
        list.push_back(i);
    }
    List<int>::Iterator l = list.begin();
    l++;
    ASSERT_TRUE(l == --list.end());
    l = list.insert(l, -1);
    list.insert(l, -2);
    //0,-2,-1,1
    ASSERT_TRUE(list.size() == 4);
    //Iterator:            *
    //list should be 0,-2,-1,1,
    list.erase(l);
    //Iterator:           *
    //list should be 0,-2,1
}

TEST_MAIN()
