//
// Created by Shimmy on 1/13/2019.
//
#include <string>
#include <cstdlib>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <iostream>
#include <vector>
#include <stack>
#include <ctime>
#include <chrono>
#include "Complex.h"
#include "Matrix.hpp"
#include <eigen3/Eigen/Dense>

#define BAD_INPUT "bad input size"
#define BAD_ARGS "wrong amount of args given"

using namespace std;
typedef Eigen::MatrixXd MatrixXd;
std::stack<std::chrono::time_point<std::chrono::system_clock>> tictoc_stack;

/**
 * starts the clock
 */
void tic()
{
    //tictoc_stack.push(clock());
    tictoc_stack.push(std::chrono::system_clock::now());
}

/**
 * ends the clock
 * @return the times elapsed
 */
double toc()
{
    // std::cout << "Time elapsed: "
    // 		<< ((double)(clock() - tictoc_stack.top())) / CLOCKS_PER_SEC
    // 		<< std::endl;
    // tictoc_stack.pop();
    std::chrono::duration<double> elapsed_seconds = std::chrono::system_clock::now() - tictoc_stack.top();
//    std::cout << "Time elapsed: " << elapsed_seconds.count() << "sec\n";
    tictoc_stack.pop();
    return elapsed_seconds.count();
}

/**
 * main function, runs time checks on add and mult for eigen matrices and my matrices.
 * throws exception if given size n (from args[1[) is out of range [1,500] or if build, add
 * or mult were given wrongs args
 * @param argc number of arguments
 * @param argv list of argument, where args[1] is size of n*n matrix to build and apply add and
 * mult on
 * @return 0 if all applications were successful without exception, 1 otherwise
 */
int main(int argc, char*argv[])
{
    if (argc == 2)
    {
        int n = stoi(argv[1]);
        if (n >= 1 && n <= 500)
        {
            MatrixXd eig_m1 = MatrixXd::Random(n, n);
            MatrixXd eig_m2 = MatrixXd::Random(n, n);
            vector<int> cells(n * n, 1);
            Matrix<int> my_m1 = Matrix<int>(n, n, cells);
            Matrix<int> my_m2 = Matrix<int>(n, n, cells);

            tic();
            eig_m1 * eig_m2;
            double eigen_mult = toc();

            tic();
            eig_m1 + eig_m2;
            double eigen_add = toc();

            tic();
            my_m1 * my_m2;
            double my_mult = toc();

            tic();
            my_m1 + my_m2;
            double my_add = toc();

            cout << "size " << n << "\n";
            cout << "eigen mult " << eigen_mult << "\n";
            cout << "eigen add " << eigen_add << "\n";
            cout << "matlib mult " << my_mult << "\n";
            cout << "matlib add " << my_add << "\n";
        }
        else
        {
            throw length_error(BAD_INPUT);
        }
    }
    else
    {
        throw invalid_argument(BAD_ARGS);
    }

    return 0;
}
