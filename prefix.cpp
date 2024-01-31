#include <iostream>
#include <stack>
#include <cmath>

using namespace std;

struct Node
{
    char data;
    Node *left;
    Node *right;

    Node(char value) {
    data = value;
    left = nullptr;
    right = nullptr;
}

};

bool isOperator(char c)
{
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}

Node *Tree(string prefix)
{
    stack<Node *> s;

    for (int i = prefix.length() ; i >= 0; i--)
    {
        char c = prefix[i];

        if (!isOperator(c))
        {
            Node *operand = new Node(c);
            s.push(operand);
        }
        else
        {

            Node *operand1 = s.top();
            s.pop();
            Node *operand2 = s.top();
            s.pop();

            Node *newNode = new Node(c);
            newNode->left = operand1;
            newNode->right = operand2;

            s.push(newNode);
        }
    }

    return s.top();
}

double ExpressionTree(Node *root)
{
    if (root == nullptr)
    {
        return 0;
    }

    if (!isOperator(root->data))
    {
       return root->data;
    }
    double leftValue = ExpressionTree(root->left);
    double rightValue = ExpressionTree(root->right);

    switch (root->data)
    {
    case '+':
        return leftValue + rightValue;
    case '-':
        return leftValue - rightValue;
    case '*':
        return leftValue * rightValue;
    case '/':
        return leftValue / rightValue;
    case '^':
        return pow(leftValue, rightValue);
    default:
        return 0;
    }
}

int main()
{

    string prefix ="* / + 5 3 - 8 ^ 4 2";

    Node *expressionTree = Tree(prefix);

    double result = ExpressionTree(expressionTree);

    cout << "Gia tri cua bieu thuc la: " << result << endl;

    return 0;
}
