#include <iostream>
#include <conio.h>
#include "BSTSet.hpp"
#include <vector>

#define COUNT 10 

using BSTSeti = CommonUtilities::BSTSet<int>;

void print2DUtil(const CU::BSTSetNode<int>* root, int space)
{
    // Base case  
    if (root == nullptr)
        return;

    // Increase distance between levels  
    space += COUNT;

    // Process right child first  
    print2DUtil(root->GetRight(), space);

    // Print current node after space  
    // count  
    std::cout << std::endl;
    for (int i = COUNT; i < space; i++)
        std::cout << " ";
    std::cout << root->GetData() << "\n";

    // Process left child  
    print2DUtil(root->GetLeft(), space);
}
int main()
{
	BSTSeti tree;
    
    tree.Insert(3);
    tree.Insert(5);
    tree.Insert(8);
    tree.Insert(10);
    tree.Insert(11);
    tree.Insert(12);
    tree.Insert(-12);
    tree.Insert(-13);
    tree.Insert(-10);

    tree.DSWBalance();


	_getch();
}