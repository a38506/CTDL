#include <iostream>
#include <stack>
#include <cmath>

using namespace std;

struct Node
{
    char data;
    Node *left;
    Node *right;

    Node(char value)
    {
        data = value;
        left = nullptr;
        right = nullptr;
    }
};

bool isOperator(char c)
{
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}

int order(char op)
{
    if (op == '^')
        return 3;
    else if (op == '*' || op == '/')
        return 2;
    else if (op == '+' || op == '-')
        return 1;
    return 0;
}

bool isHigherPriority(char op1, char op2)
{
    return order(op1) > order(op2);
}

Node *Tree(string infix)
{
    stack<Node *> s;
    stack<char> operators;

    for (char c : infix)
    {
        if (isalnum(c))
        {
            Node *operand = new Node(c);
            s.push(operand);
        }
        else if (isOperator(c))
        {
            while (!operators.empty() && isHigherPriority(operators.top(), c))
            {
                char op = operators.top();
                operators.pop();

                Node *operand2 = s.top();
                s.pop();
                Node *operand1 = s.top();
                s.pop();

                Node *newNode = new Node(op);
                newNode->left = operand1;
                newNode->right = operand2;

                s.push(newNode);
            }
            operators.push(c);
        }
    }

    while (!operators.empty())
    {
        char op = operators.top();
        operators.pop();

        Node *operand2 = s.top();
        s.pop();
        Node *operand1 = s.top();
        s.pop();

        Node *newNode = new Node(op);
        newNode->left = operand1;
        newNode->right = operand2;

        s.push(newNode);
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
        return root->data ;
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
    string infixExpression = "5 + 3 * 8 ^ 4 - 2";

    Node *expressionTree = Tree(infixExpression);

    double result = ExpressionTree(expressionTree);

    cout << "Gia tri cua bieu thuc la: " << result << endl;

    return 0;
}
