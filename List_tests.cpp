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

    list2.push_front(100);
    list2.push_front(100);
    list2.push_front(100);
    list2.push_front(1);
    list2.push_front(100);

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
    List<int>::Iterator lc1 = list_clone.begin();
    List<int>::Iterator list_end = list.end();
    List<int>::Iterator listc_end = list_clone.end();
    while (l1 != list_end && lc1 != listc_end) {
        ASSERT_TRUE(*l1 == *lc1);
        ++l1;
        ++lc1;
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

TEST(test_push_pop_func) {
    List<int> list;
    list.push_back(1);
    //1
    List<int>::Iterator l = list.begin();
    List<int>::Iterator l2 = --list.end();
    ASSERT_EQUAL(l, l2);
    ASSERT_TRUE(list.front() == list.back());
    ASSERT_TRUE(list.front() == 1);

    list.push_back(2);
    //1,2
    list.push_front(3);
    //3,1,2
    list.pop_front();
    //1,2
    list.push_front(4);
    //4,1,2

    ASSERT_FALSE(list.begin() == list.end());
    ASSERT_FALSE(list.front() == list.back());
    ASSERT_TRUE(list.front() == 4);
    ASSERT_TRUE(list.back() == 2);
    l = ++list.begin(); //*
    //   *
    //4, 1, 2
    l2 = --(--list.end()); //+
    //   *
    //   +
    //4, 1, 2
    ASSERT_TRUE(*l2 == *l);
    list.pop_front();
    // *
    // +
    // 1, 2
    list.pop_front();
    // * //cant use iterators as they are now invalidated
    // +
    //   2
    ASSERT_TRUE(list.size() == 1);
    list.pop_back();
    // *
    // +
    // 
    ASSERT_TRUE(list.empty());
}

TEST(test_all_func_together) {
    List<std::string> list;
    list.push_back("1");
    list.push_back("2");
    list.push_back("3");
    //1,2,3

    List<std::string> list2;
    list2 = list;

    List<std::string>::Iterator l1 = list.begin();
    List<std::string>::Iterator l2 = list2.begin();
    List<std::string>::Iterator list_end = list.end();
    List<std::string>::Iterator list2_end = list2.end();
    while (l1 != list_end && l2 != list2_end) {
        ASSERT_TRUE(*l1 == *l2);
        ++l1;
        ++l2;
    }
    ASSERT_EQUAL(list.size(), list2.size());

    List<std::string> list3(list2);
    List<std::string>::Iterator l3 = list3.begin();
    List<std::string>::Iterator list3_end = list3.end();
    while (l1 != list_end && l3 != list3_end) {
        ASSERT_TRUE(*l1 == *l3);
        ++l1;
        ++l3;
    }
    ASSERT_EQUAL(list.size(), list3.size());

    List<std::string> list4;
    list2 = list4;
    ASSERT_TRUE(list2.empty());

    //list3 is the same as list, list2 and list4 are empty
    //working with list

    list.pop_back();
    ASSERT_EQUAL(list.back(), "2");

    l1 = list.begin();
    ASSERT_EQUAL(*l1, "1");
    list.pop_front();
    l1 = list.begin();
    ASSERT_EQUAL(list.begin(), --list.end());
    ASSERT_EQUAL(*l1, "2");

    std::string banana = "banana";
    list.push_front(banana);
    l1 = list.begin();
    List<std::string>::Iterator ltest = l1;
    ASSERT_EQUAL(list.size(), 2);
    ASSERT_EQUAL(*l1, banana);
    l1++;
    l1--;
    ASSERT_EQUAL(*l1, *ltest);
}
TEST_MAIN()