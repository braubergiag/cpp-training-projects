
#include "../core/include/vector.h"
#include <gtest/gtest.h>
#include <vector>

TEST(ConstructorsTest,OneArgCtr){

    const size_t sz = 10;
    Vector<int> v(sz);
    
    ASSERT_EQ(v.size(),sz);
}

TEST(ConstructorsTest,TwoArgCtr){
    const size_t sz = 5;
    const int default_val = 10;
    Vector<int> v(sz,default_val);

    for (auto i{0}; i < v.size(); ++i){
        ASSERT_EQ(v[i],default_val);
    }

    ASSERT_EQ(v.size(),sz);
}

TEST(ConstructorsTest,InitListCtr){
    std::vector<int> v_test{2,3,4,5,6};

    Vector<int> v{2,3,4,5,6};
    for (auto i{0}; i < v.size(); ++i){
        ASSERT_EQ(v[i],v_test[i]);
    }
    ASSERT_EQ(v.size(), v_test.size());
}


