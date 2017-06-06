//
// Created by pbeerken on 5/18/17.
//

#include <iostream>

#include <gtest/gtest.h>


int main(int argc, char **argv) {
    std::cout<<"Hello from unit test main"<<std::endl;
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}