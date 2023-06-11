#include <cxxtest/TestSuite.h>
#include "bintree.h"
#include <fstream>
#include <algorithm>
class MyTestSuite : public CxxTest::TestSuite
{
public:
  //
  // Insert
  //

  // tests insert of a tree size 1
  void test_insert ( void ){
      Node *x = nullptr;
      insert(x, 50, 10);
      TS_ASSERT(x -> key == 50);
      TS_ASSERT(x -> data == 10);

      Node *y = nullptr;
      insert(y, -24, -10.24);
      TS_ASSERT(y -> key == -24);
      TS_ASSERT(y -> data == -10.24);

      delete_tree(x);
      delete_tree(y);
  }

  // tests insert of a tree size > 1
  void test_insert_multiple ( void ){
      Node *x = nullptr;
      insert(x, 50, 10);
      insert(x, 25, 12);
      insert(x, 75, 2);
      insert(x, 33, 1);
      insert(x, 111, 10);
      insert(x, 150, 210);
      insert(x, -12, 44.2);

      TS_ASSERT(x -> key == 50 && x -> data == 10);
      TS_ASSERT(x -> left -> key == 25 && x -> left -> data == 12);
      TS_ASSERT(x -> left -> right -> key == 33 && x -> left -> right -> data == 1);
      TS_ASSERT(x -> right -> key == 75 && x -> right -> data == 2);
      TS_ASSERT(x -> right -> right -> key == 111 && x -> right -> right -> data == 10);
      TS_ASSERT(x -> right -> right -> right -> key == 150 && x -> right -> right -> right -> data == 210);
      TS_ASSERT(x -> left -> left -> key == -12 && x -> left -> left -> data == 44.2);

      delete_tree(x);
  }

  //
  // Remove
  //

  // tests remove of empty tree
  void test_remove_empty ( void ){
      Node *x = nullptr;
      TS_ASSERT_THROWS(remove(x, 11), std::out_of_range);
  }

  // tests remove of a tree size 1
  void test_remove_single ( void ){
      Node *x = nullptr;
      insert(x, 50, 10);
      remove(x, 50);
      TS_ASSERT(x == nullptr);

  }

  // tests remove of a tree size > 1
  void test_remove_root_multinode ( void ){
      Node *x = nullptr;
      insert(x, 100, 10);
      insert(x, 50, 10);
      insert(x, 150, 10);
      insert(x, 25, 10);
      insert(x, 125, 10);
      insert(x, 75, 10);
      insert(x, 175, 10);
      insert(x, 90, 15);
      insert(x, 80, 15);
      insert(x, 78, 12);
      insert(x, 82, 16);
      remove(x, 100);

      TS_ASSERT(x != nullptr);
      TS_ASSERT(x -> key == 90);
      TS_ASSERT(x -> data == 15);
      TS_ASSERT(x -> right -> key == 150);
      TS_ASSERT(x -> left -> right -> right -> key == 80);
      TS_ASSERT(x -> left -> right -> right -> left -> key == 78);
      TS_ASSERT(x -> left -> right -> right -> right -> key == 82);

      delete_tree(x);
  }

  // tests remove node that is not the root of a tree size > 1
  void test_remove_nonroot_node_multinode ( void ){
      Node *x = nullptr;
      insert(x, 100, 10);
      insert(x, 50, 10);
      insert(x, 150, 10);
      insert(x, 25, 10);
      insert(x, 125, 10);
      insert(x, 75, 10);
      insert(x, 175, 10);
      insert(x, 90, 15);
      insert(x, 80, 15);
      insert(x, 78, 12);
      insert(x, 82, 16);
      insert(x, 95, 33);

      remove(x, 90);

      Node *y = x -> left -> right -> right;
      TS_ASSERT(y != nullptr);
      TS_ASSERT(y -> key == 82);
      TS_ASSERT(y -> data == 16);
      TS_ASSERT(y -> right -> key == 95);
      TS_ASSERT(y -> left -> key == 80);
      TS_ASSERT(y -> left -> left -> key == 78);
      TS_ASSERT(y -> left -> right == nullptr);


      delete_tree(x);
  }

  // tests remove root of a tree with nodes only left of root and tree size > 1
  void test_remove_root_multinode_left ( void ){
      Node *x = nullptr;
      insert(x, 100, 10);
      insert(x, 50, 10);
      insert(x, 25, 10);
      insert(x, 75, 10);
      insert(x, 90, 15);
      insert(x, 80, 15);
      insert(x, 78, 12);
      insert(x, 82, 16);
      remove(x, 100);

      TS_ASSERT(x != nullptr);
      TS_ASSERT(x -> key == 90);
      TS_ASSERT(x -> data == 15);
      TS_ASSERT(x -> left -> right -> right -> key == 80);
      TS_ASSERT(x -> left -> right -> right -> left -> key == 78);
      TS_ASSERT(x -> left -> right -> right -> right -> key == 82);

      delete_tree(x);
  }

  // tests remove root of a tree with nodes only right of root and tree size > 1
  void test_remove_root_multinode_right ( void ){
      Node *x = nullptr;
      insert(x, 100, 10);
      insert(x, 150, 10);
      insert(x, 125, 10);
      insert(x, 175, 10);
      insert(x, 190, 15);
      insert(x, 135, 15);
      insert(x, 110, 12);
      insert(x, 120, 16);
      insert(x, 115, 16);
      insert(x, 123, 16);
      remove(x, 100);

      TS_ASSERT(x != nullptr);
      TS_ASSERT(x -> key == 110);
      TS_ASSERT(x -> data == 12);
      TS_ASSERT(x -> right -> left -> left -> key == 120);
      TS_ASSERT(x -> right -> left -> left -> left -> key == 115);
      TS_ASSERT(x -> right -> left -> left -> right -> key == 123);

      delete_tree(x);
  }

  // tests remove with non valid key of a tree with size > 1
  void test_remove_nonvalid_key_multinode ( void ){
      Node *x = nullptr;
      insert(x, 100, 10);
      insert(x, 80, 15);
      insert(x, 150, 12);
      insert(x, 82, 16);
      TS_ASSERT_THROWS(remove(x, 125), std::out_of_range);

      delete_tree(x);
  }

  //
  // Find
  //

  // Tests find on empty tree
  void test_find_empty ( void ){
      Node *x = nullptr;
      TS_ASSERT_THROWS(find(x, 11), std::out_of_range);
  }

  // tests find of a tree size 1
  void test_find_single ( void ){
      Node *x = nullptr;
      insert(x, 50, 10);
      double val1 = find(x, 50);
      TS_ASSERT(val1 == 10);
      val1 = val1 - 4;
      TS_ASSERT(find(x, 50) == 10);

      Node *y = nullptr;
      insert(y, 50, 13.22);
      double val2 = find(y, 50);
      TS_ASSERT(val2 == 13.22);
      val2 = val2 - 1.22;
      TS_ASSERT(find(y, 50) == 13.22);

      delete_tree(x);
      delete_tree(y);
  }


  // tests find of a tree size > 1
  void test_find_multinode ( void ){
      Node *x = nullptr;
      insert(x, 100, 14);
      insert(x, 50, 26);
      insert(x, 150, 132);
      insert(x, 25, 155);
      insert(x, 125, 11);
      insert(x, 75, 18);
      insert(x, 175, 52);
      insert(x, 90, 34);
      insert(x, 80, 96);
      insert(x, 78, 29);
      insert(x, 82, 54);

      double val = find(x, 25);
      TS_ASSERT(val == 155);
      val = val*12;
      TS_ASSERT(find(x, 25) == 155);

      delete_tree(x);
  }

  //
  // Edit
  //

  // Tests edit on empty tree
  void test_edit_empty ( void ){
      Node *x = nullptr;
      TS_ASSERT_THROWS(edit(x, 0), std::out_of_range);
  }

  // tests edit of a tree size 1
  void test_edit_single ( void ){
      Node *x = nullptr;
      insert(x, 50, 10);
      double val1 = edit(x, 50);
      TS_ASSERT(val1 == 10);
      edit(x, 50) = val1 - 3;
      TS_ASSERT(find(x, 50) == 7);

      Node *y = nullptr;
      insert(y, 50, 13.22);
      double val2 = edit(y, 50);
      TS_ASSERT(val2 == 13.22);
      edit(y, 50) = val2 - 1.22;
      TS_ASSERT(find(y, 50) == 12);

      delete_tree(x);
      delete_tree(y);
  }


  // tests edit of a tree size > 1
  void test_edit_multinode ( void ){
      Node *x = nullptr;
      insert(x, 100, 14);
      insert(x, 50, 26);
      insert(x, 150, 132);
      insert(x, 25, 155);
      insert(x, 125, 11);
      insert(x, 75, 18);
      insert(x, 175, 52);
      insert(x, 90, 34);
      insert(x, 80, 96);
      insert(x, 78, 29);
      insert(x, 82, 54);

      double val = edit(x, 80);
      TS_ASSERT(val == 96);
      edit(x, 80) = val*13;
      TS_ASSERT(find(x, 80) == 1248);

      delete_tree(x);
  }

  //
  // Delete
  //

  // The delete function gets tested better by running all the tests with valgrind

  // tests delete_tree of a tree size 1
  void test_delete_single ( void ){
      Node *x = nullptr;
      insert(x, 50, 10);
      delete_tree(x);
      TS_ASSERT(x == nullptr);


      Node *y = nullptr;
      insert(y, 50, 13);
      delete_tree(y);
      TS_ASSERT(y == nullptr);
  }


  // tests delete_tree of a tree size > 1
  void test_delete_multinode ( void ){
      Node *x = nullptr;
      insert(x, 100, 14);
      insert(x, 50, 26);
      insert(x, 150, 132);
      insert(x, 25, 155);
      insert(x, 125, 11);
      insert(x, 75, 18);

      //Node *t1 = x -> left;
      //Node *t2 = x -> left -> left;
      //Node *t3 = x -> left -> right;
      //Node *t4 = x -> right;
      //Node *t5 = x -> right -> left;

      delete_tree(x);
      TS_ASSERT(x == nullptr);
      //TS_ASSERT(t1 == nullptr);
      //TS_ASSERT(t2 == nullptr);
      //TS_ASSERT(t3 == nullptr);
      //TS_ASSERT(t4 == nullptr);
      //TS_ASSERT(t5 == nullptr);
  }

  //
  // Max height
  //

  // tests max_height of a empty tree
  void test_max_height_empty ( void ){
      Node *x = nullptr;
      TS_ASSERT(max_height(x) == 0);

      Node *y = nullptr;
      TS_ASSERT(max_height(y) == 0);

      delete_tree(x);
      delete_tree(y);
  }

  // tests max_height of a tree size 1
  void test_max_height_single ( void ){
      Node *x = nullptr;
      insert(x, 50, 10);
      TS_ASSERT(max_height(x) == 0);

      Node *y = nullptr;
      insert(y, -50, 13);
      TS_ASSERT(max_height(y) == 0);

      delete_tree(x);
      delete_tree(y);
  }

  // tests max_height of a tree size 1
  void test_max_height_multinode ( void ){
      Node *x = nullptr;
      insert(x, 100, 10);
      insert(x, 50, 10);
      insert(x, 150, 10);
      insert(x, 25, 10);
      insert(x, 125, 10);
      insert(x, 75, 10);
      insert(x, 175, 10);
      insert(x, 90, 15);
      insert(x, 80, 15);
      insert(x, 78, 12);
      insert(x, 82, 16);

      TS_ASSERT(max_height(x) == 5);
      delete_tree(x);
  }

  // tests max_height of a tree with nodes only left of root and tree size > 1
  void test_max_height_multinode_left ( void ){
      Node *x = nullptr;
      insert(x, 100, 10);
      insert(x, 50, 10);
      insert(x, 25, 10);
      insert(x, 75, 10);
      insert(x, 90, 15);
      insert(x, 80, 15);
      insert(x, 78, 12);
      insert(x, 82, 16);

      TS_ASSERT(max_height(x) == 5);

      delete_tree(x);
  }

  // tests max_height of a tree with nodes only right of root and tree size > 1
  void test_max_height_multinode_right ( void ){
      Node *x = nullptr;
      insert(x, 100, 10);
      insert(x, 150, 10);
      insert(x, 125, 10);
      insert(x, 175, 10);
      insert(x, 190, 15);
      insert(x, 135, 15);
      insert(x, 110, 12);
      insert(x, 120, 16);
      insert(x, 115, 16);
      insert(x, 123, 16);

      TS_ASSERT(max_height(x) == 5);

      delete_tree(x);
  }

  //
  // max_node_height
  //

  // tests max_node_height of a empty tree
  void test_max_node_height_empty ( void ){
      Node *x = nullptr;
      TS_ASSERT(max_node_height(x) == 0);

      Node *y = nullptr;
      TS_ASSERT(max_node_height(y) == 0);

      delete_tree(x);
      delete_tree(y);
  }

  // tests max_node_height of a tree size 1
  void test_max_node_height_single ( void ){
      Node *x = nullptr;
      insert(x, 50, 10);
      TS_ASSERT(max_node_height(x) == 1);

      Node *y = nullptr;
      insert(y, -50, 13);
      TS_ASSERT(max_node_height(y) == 1);

      delete_tree(x);
      delete_tree(y);
  }

  // tests max_node_height of a tree size 1
  void test_max_node_height_multinode ( void ){
      Node *x = nullptr;
      insert(x, 100, 10);
      insert(x, 50, 10);
      insert(x, 150, 10);
      insert(x, 25, 10);
      insert(x, 125, 10);
      insert(x, 75, 10);
      insert(x, 175, 10);
      insert(x, 90, 15);
      insert(x, 80, 15);
      insert(x, 78, 12);
      insert(x, 82, 16);

      TS_ASSERT(max_node_height(x) == 6);
      delete_tree(x);
  }

  // tests max_node_height of a tree with nodes only left of root and tree size > 1
  void test_max_node_height_multinode_left ( void ){
      Node *x = nullptr;
      insert(x, 100, 10);
      insert(x, 50, 10);
      insert(x, 25, 10);
      insert(x, 75, 10);
      insert(x, 90, 15);
      insert(x, 80, 15);
      insert(x, 78, 12);
      insert(x, 82, 16);

      TS_ASSERT(max_node_height(x) == 6);

      delete_tree(x);
  }

  // tests max_node_height of a tree with nodes only right of root and tree size > 1
  void test_max_node_height_multinode_right ( void ){
      Node *x = nullptr;
      insert(x, 100, 10);
      insert(x, 150, 10);
      insert(x, 125, 10);
      insert(x, 175, 10);
      insert(x, 190, 15);
      insert(x, 135, 15);
      insert(x, 110, 12);
      insert(x, 120, 16);
      insert(x, 115, 16);
      insert(x, 123, 16);

      TS_ASSERT(max_node_height(x) == 6);

      delete_tree(x);
  }

  //
  // min_height
  //

  // tests min_height of a empty tree
  void test_min_height_empty ( void ){
      Node *x = nullptr;
      TS_ASSERT(min_height(x) == 0);

      Node *y = nullptr;
      TS_ASSERT(min_height(y) == 0);

      delete_tree(x);
      delete_tree(y);
  }

  // tests min_height of a tree size 1
  void test_min_height_single ( void ){
      Node *x = nullptr;
      insert(x, 50, 10);
      TS_ASSERT(min_height(x) == 0);

      Node *y = nullptr;
      insert(y, -50, 13);
      TS_ASSERT(min_height(y) == 0);

      delete_tree(x);
      delete_tree(y);
  }

  // tests min_height of a tree size 1
  void test_min_height_multinode ( void ){
      Node *x = nullptr;
      insert(x, 100, 10);
      insert(x, 50, 10);
      insert(x, 150, 10);
      insert(x, 25, 10);
      insert(x, 125, 10);
      insert(x, 75, 10);
      insert(x, 175, 10);
      insert(x, 90, 15);
      insert(x, 80, 15);
      insert(x, 78, 12);
      insert(x, 82, 16);

      TS_ASSERT(min_height(x) == 2);
      delete_tree(x);
  }

  // tests min_height of a tree with nodes only left of root and tree size > 1
  void test_min_height_multinode_left ( void ){
      Node *x = nullptr;
      insert(x, 100, 10);
      insert(x, 50, 10);
      insert(x, 25, 10);
      insert(x, 75, 10);
      insert(x, 90, 15);
      insert(x, 80, 15);
      insert(x, 78, 12);
      insert(x, 82, 16);

      TS_ASSERT(min_height(x) == 2);

      delete_tree(x);
  }

  // tests min_height of a tree with nodes only right of root and tree size > 1
  void test_min_height_multinode_right ( void ){
      Node *x = nullptr;
      insert(x, 100, 10);
      insert(x, 150, 10);
      insert(x, 125, 10);
      insert(x, 175, 10);
      insert(x, 190, 15);
      insert(x, 135, 15);
      insert(x, 110, 12);
      insert(x, 120, 16);
      insert(x, 115, 16);
      insert(x, 123, 16);

      TS_ASSERT(min_height(x) == 3);

      delete_tree(x);
  }

  //
  // size
  //

  // tests size of a empty tree
  void test_size_empty ( void ){
      Node *x = nullptr;
      TS_ASSERT(size(x) == 0);

      Node *y = nullptr;
      TS_ASSERT(size(y) == 0);

      delete_tree(x);
      delete_tree(y);
  }

  // tests size of a tree size 1
  void test_size_single ( void ){
      Node *x = nullptr;
      insert(x, 50, 10);
      TS_ASSERT(size(x) == 1);

      Node *y = nullptr;
      insert(y, -50, 13);
      TS_ASSERT(size(y) == 1);

      delete_tree(x);
      delete_tree(y);
  }

  // tests size of a tree size > 1
  void test_size_multinode ( void ){
      Node *x = nullptr;
      insert(x, 100, 10);
      insert(x, 50, 10);
      insert(x, 150, 10);
      insert(x, 25, 10);
      insert(x, 125, 10);
      insert(x, 75, 10);
      insert(x, 175, 10);
      insert(x, 90, 15);
      insert(x, 80, 15);
      insert(x, 78, 12);
      insert(x, 82, 16);

      TS_ASSERT(size(x) == 11);
      delete_tree(x);
  }

  // tests size of a tree with nodes only left of root and tree size > 1
  void test_size_multinode_left ( void ){
      Node *x = nullptr;
      insert(x, 100, 10);
      insert(x, 50, 10);
      insert(x, 25, 10);
      insert(x, 75, 10);
      insert(x, 90, 15);
      insert(x, 80, 15);
      insert(x, 78, 12);
      insert(x, 82, 16);

      TS_ASSERT(size(x) == 8);

      delete_tree(x);
  }

  // tests size of a tree with nodes only right of root and tree size > 1
  void test_size_multinode_right ( void ){
      Node *x = nullptr;
      insert(x, 100, 10);
      insert(x, 150, 10);
      insert(x, 125, 10);
      insert(x, 175, 10);
      insert(x, 190, 15);
      insert(x, 135, 15);
      insert(x, 110, 12);
      insert(x, 120, 16);
      insert(x, 115, 16);
      insert(x, 123, 16);

      TS_ASSERT(size(x) == 10);

      delete_tree(x);
  }

  //
  // is_balanced
  //

  // tests is_balanced of a empty tree
  void test_is_balanced_empty ( void ){
      Node *x = nullptr;
      TS_ASSERT(is_balanced(x) == true);

      Node *y = nullptr;
      TS_ASSERT(is_balanced(y) == true);

      delete_tree(x);
      delete_tree(y);
  }

  // tests is_balanced of a tree size 1
  void test_is_balanced_single ( void ){
      Node *x = nullptr;
      insert(x, 50, 10);
      TS_ASSERT(is_balanced(x) == true);

      Node *y = nullptr;
      insert(y, -50, 13);
      TS_ASSERT(is_balanced(y) == true);

      delete_tree(x);
      delete_tree(y);
  }

  // tests is_balanced of a tree size > 1
  void test_is_balanced_multinode ( void ){
      Node *x = nullptr;
      insert(x, 100, 10);
      insert(x, 50, 10);
      insert(x, 150, 10);
      insert(x, 25, 10);
      insert(x, 125, 10);
      insert(x, 75, 10);
      insert(x, 175, 10);
      insert(x, 90, 15);
      insert(x, 80, 15);
      insert(x, 78, 12);
      insert(x, 82, 16);
      TS_ASSERT(is_balanced(x) == false);

      Node *y = nullptr;
      insert(y, 100, 10);
      insert(y, 50, 10);
      insert(y, 150, 10);
      insert(y, 25, 10);
      insert(y, 125, 10);
      insert(y, 75, 10);
      insert(y, 175, 10);
      insert(y, 80, 15);
      TS_ASSERT(is_balanced(y) == true);

      delete_tree(x);
      delete_tree(y);
  }

  void test_is_balanced_symmetrical_multinode ( void ){
      Node *x = nullptr;
      insert(x, 100, 10);
      insert(x, 50, 10);
      insert(x, 150, 10);
      insert(x, 25, 10);
      insert(x, 125, 10);
      insert(x, 75, 10);
      insert(x, 175, 10);
      insert(x, 35, 15);
      insert(x, 165, 15);
      insert(x, 15, 12);
      insert(x, 200, 16);
      insert(x, 10, 12);
      insert(x, 250, 16);
      TS_ASSERT(is_balanced(x) == false);
      TS_ASSERT(is_balanced(x -> left) == false);
      TS_ASSERT(is_balanced(x -> right) == false);

      delete_tree(x);
  }

  // tests is_balanced of a tree with nodes only left of root and tree size > 1
  void test_is_balanced_multinode_left ( void ){
      Node *x = nullptr;
      insert(x, 100, 10);
      insert(x, 50, 10);
      insert(x, 25, 10);
      insert(x, 75, 10);
      insert(x, 90, 15);
      insert(x, 80, 15);
      insert(x, 78, 12);
      insert(x, 82, 16);

      TS_ASSERT(is_balanced(x) == false);

      delete_tree(x);
  }

  // tests is_balanced of a tree with nodes only right of root and tree size > 1
  void test_is_balanced_multinode_right ( void ){
      Node *x = nullptr;
      insert(x, 100, 10);
      insert(x, 150, 10);
      insert(x, 125, 10);
      insert(x, 175, 10);
      insert(x, 190, 15);
      insert(x, 135, 15);
      insert(x, 110, 12);
      insert(x, 120, 16);
      insert(x, 115, 16);
      insert(x, 123, 16);

      TS_ASSERT(is_balanced(x) == false);

      delete_tree(x);
  }
};
