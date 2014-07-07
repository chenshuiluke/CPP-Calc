#include <iostream>
#include <sstream>
#include <string>
#include <stack>
#include <queue>
#include <vector>
#include <stdlib.h>
#include <map>
#include <algorithm>
#include <math.h>
#include <iomanip>
#include <limits>
using namespace std;

class operatorClass
{
public:
    operatorClass(char&,int&);
    void addOperands(long double&, long double&);
    bool operator < (const operatorClass& str) const;
    int value;
    char actualoperatorClass;

    long double* pointer_To_leftOperand;
    long double* pointer_To_rightOperand;

};
operatorClass::operatorClass(char &receivedoperatorClass, int &receivedValue)
{
    actualoperatorClass = receivedoperatorClass;
    value =  receivedValue;
}
void operatorClass::addOperands(long double &receivedleft, long double &receivedright)
{
pointer_To_leftOperand=&receivedleft;
//std::cout << " LEFT " << *pointer_To_leftOperand << std::endl;
    pointer_To_rightOperand=&receivedright;
//std::cout << " RIGHT " << *pointer_To_rightOperand << std::endl;
}
bool operatorClass::operator < (const operatorClass& str) const
{
    return (value < str.value);
}
inline void printOperatorVector(std::vector<operatorClass> VectorToPrint)
{
    for(unsigned int index = 0; index < VectorToPrint.size(); index++)
    {
     //std::cout << "Element #" << index <<": " << VectorToPrint[index].actualoperatorClass << std::endl;
    }
}
class Parenthesis
{
    public:
    Parenthesis(unsigned int,char);
    char typeOfParenthesis;
    unsigned int position;
    private:

};
Parenthesis::Parenthesis(unsigned int receivedPosition, char parenthesisType)
{
    position = receivedPosition;
    typeOfParenthesis = parenthesisType;
}
class Expression
{
    public:
    Expression(std::string,bool);
    long double result;
    private:



    bool hasBrackets;
    std::vector <Expression> subExpressions;
    std::vector<Parenthesis> vector_parentheses; //If the position of a parenthesis in a vector
    //is 'n', then the position of the closing parenthesis should be vectorSize-n in the
    //same vector
    void containsBrackets();//Checks to see if the expression contains parentheses
    void getParentheses(); //Gets position and types of parentheses in the expression
    void getSubExpressions(); //Gets the contents between each parenthesis so that they may be evaluated

    long double evaluate();
    std::string expressionString;
};
Expression::Expression(std::string expression, bool sub) //NOTE: being a sub means that it was surrounded
//by brackets '(' ')'
{


    hasBrackets = false;
    expressionString = expression;
    containsBrackets();
    // //std::cout << "Successfully complete 'containsBrackets' function" << std::endl;
    if (hasBrackets == true)
    {
     getParentheses();
     // //std::cout << "Successfully complete 'getParentheses()' function" << std::endl;
    getSubExpressions();
    // //std::cout << "Successfully complete 'getSubExpressions()' function" << std::endl;
    }
    evaluate();
    // //std::cout << "Successfully complete 'evaluate()' function" << std::endl;


}
long double Expression::evaluate()
{
std::map<char, unsigned int> operatorClassMap;
operatorClassMap['*']=2;
operatorClassMap['/']=2;
operatorClassMap['+']=1;
operatorClassMap['-']=1;
std::vector<long double> numbers;
std::vector<operatorClass> operatorClasss;
long double number = 0;
std::string numberString = ""; //For having multi-digit numbers
// //std::cout << "Working expression: " << expressionString << std::endl;

for(unsigned int index = 0; index<=expressionString.size(); index++)
{
    if(expressionString[index] != '+' && expressionString[index] != '-' && expressionString[index] != '*' && expressionString[index] != '/' && expressionString[index] != ' ')
    {
        numberString+= expressionString[index];
    }
    if (expressionString.size() == index)
    {
    number= strtod(numberString.c_str(), NULL);
    numbers.push_back(number);
    numberString = "";

    }
    if(expressionString[index] == '+' || expressionString[index] == '-' || expressionString[index] == '*' || expressionString[index] == '/' || expressionString[index] == ' ')
    {
    number= strtod(numberString.c_str(), NULL);
    numbers.push_back(number);
    numberString = "";

    }
}
//std::cout << "SIZE" << numbers.size() << std::endl;
for(unsigned int index = 0; index < numbers.size(); index++)
{
//std::cout  << "NUMBER" << numbers[index] << std::endl;
}

for(unsigned int index = 0; index<expressionString.size(); index++)
{
//std::cout << "Index :" << index << std::endl;
    if(expressionString[index] == '+' || expressionString[index] == '-' || expressionString[index] == '*' || expressionString[index] == '/' || expressionString[index] == ' ')
    {
     int value = operatorClassMap[expressionString[index]];
     if(numbers.size() > 2)
     {
         operatorClass tempoperatorClass(expressionString[index],value);
         operatorClasss.push_back(tempoperatorClass);
     }

     else
     {
        operatorClass tempoperatorClass(expressionString[index],value);
        operatorClasss.push_back(tempoperatorClass);
     }

    }
    else
    {

    }
}
for(unsigned int index = 0; index < operatorClasss.size(); index++)
{
if(numbers.size() >= 2)
operatorClasss[index].addOperands(numbers[index],numbers[index+1]);
else
operatorClasss[index].addOperands(numbers[0],numbers[1]);
}

std::sort(operatorClasss.begin(),operatorClasss.end());



for(unsigned int index = 0; index < numbers.size(); index++)
{
//std::cout << numbers[index] << std::endl;
}
printOperatorVector(operatorClasss);
//std::cout << 7 << std::endl;
std::stack<long double> numberStack;
std::stack<operatorClass> operatorClassStack;

for (unsigned int index = 0; index < operatorClasss.size(); index++)
{
operatorClassStack.push(operatorClasss[index]);
}
// //std::cout << "Successfully added operatorClasss and numbers to stacks" << std::endl;
long double Result = 0;
for(unsigned int index = operatorClassStack.size();index>0;index--)
{
    unsigned int previousValue = operatorClassMap[operatorClassStack.top().actualoperatorClass];
    if (operatorClassStack.top().actualoperatorClass == '*')
    {

         //std::cout << "Top number: " << *operatorClassStack.top().pointer_To_leftOperand << std::endl;

         //std::cout << "operatorClass: " << operatorClassStack.top().actualoperatorClass;

         //std::cout << "Other number: " << *operatorClassStack.top().pointer_To_rightOperand << std::endl;
//change stack to vector
        Result = *operatorClassStack.top().pointer_To_leftOperand* *operatorClassStack.top().pointer_To_rightOperand;
        numberStack.push(Result);
        if(operatorClassStack.empty() == false)
        operatorClassStack.pop();

          //std::cout << "RESULT! : "<< Result << std::endl;
    }
    else if (operatorClassStack.top().actualoperatorClass == '/')
    {

         //std::cout << "Top number: " << *operatorClassStack.top().pointer_To_leftOperand << std::endl;

        //std::cout << "operatorClass: " << operatorClassStack.top().actualoperatorClass;

         //std::cout << "Other number: " << *operatorClassStack.top().pointer_To_rightOperand << std::endl;

        // //std::cout << 1+1;
        Result = *operatorClassStack.top().pointer_To_leftOperand/ *operatorClassStack.top().pointer_To_rightOperand;
        numberStack.push(Result);
        // //std::cout << Result;
        if(operatorClassStack.empty() == false)
        operatorClassStack.pop();

          //std::cout << "RESULT! : "<< Result << std::endl;
    }

    else if (operatorClassStack.top().actualoperatorClass == '+')
    {

         //std::cout << "Top number: " << *operatorClassStack.top().pointer_To_leftOperand << std::endl;

         //std::cout << "operatorClass: " << operatorClassStack.top().actualoperatorClass;

         //std::cout << "Other number: " << *operatorClassStack.top().pointer_To_rightOperand << std::endl;

        Result = *operatorClassStack.top().pointer_To_leftOperand + *operatorClassStack.top().pointer_To_rightOperand;
        numberStack.push(Result);
        if(operatorClassStack.empty() == false)
        operatorClassStack.pop();

          //std::cout << "RESULT! : "<< Result << std::endl;


    }
    else if (operatorClassStack.top().actualoperatorClass == '-')
    {

         //std::cout << "Top number: " << *operatorClassStack.top().pointer_To_leftOperand << std::endl;

         //std::cout << "operatorClass: " << operatorClassStack.top().actualoperatorClass;

         //std::cout << "Other number: " << *operatorClassStack.top().pointer_To_rightOperand << std::endl;

        Result = *operatorClassStack.top().pointer_To_leftOperand- *operatorClassStack.top().pointer_To_rightOperand;
        numberStack.push(Result);
        if(operatorClassStack.empty() == false)
        operatorClassStack.pop();

          //std::cout << "RESULT! : "<< Result << std::endl;
    }
    if(operatorClassStack.size() > 0)
    {
        if(operatorClassMap[operatorClassStack.top().actualoperatorClass] > previousValue)
        operatorClassStack.top().pointer_To_leftOperand =  &Result;

        if(operatorClassMap[operatorClassStack.top().actualoperatorClass] <= previousValue)
        operatorClassStack.top().pointer_To_rightOperand =  &Result;
    }




}
// //std::cout << "Successfully evaluated expression" << std::endl;
result = numberStack.top();
// //std::cout << result;
// //std::cout << "Successfully evaluated expression" << std::endl;
}
void Expression::containsBrackets()
{
    for(unsigned int index = 0; index < expressionString.size(); index++)
    {
        if (expressionString[index]=='(' ||expressionString[index]==')' )
        {
            hasBrackets = true;
        }
    }
}
void Expression::getParentheses() //Finds the parentheses and their positions in the expression
//so that their contents can be converted to sub expressions.
{
    for (unsigned int index = 0; index < expressionString.size(); index++)
    {
        if (expressionString[index] == '(' || expressionString[index] == ')')
        {
            Parenthesis temporary(index, expressionString[index]); //Stores the position and type of the parenthesis
            vector_parentheses.push_back(temporary);
        }
    }

    /*for (unsigned int index = 0; index < vector_parentheses.size(); index++)
    {
        // //std::cout << vector_parentheses[index].typeOfParenthesis << std::endl;
        // //std::cout << vector_parentheses[index].position << std::endl;
    }
    */
}
void Expression::getSubExpressions()
{
    for(unsigned int index = 0; index < vector_parentheses.size(); index++)
    {
        if(vector_parentheses[index].typeOfParenthesis == '(')
        {
            std::string subExpression = "";
            // | ( | ( | ( | ) | ) | ) |
            //   *   -   -   -   -   *
            //  n=0                 =size-n
            //in an array of parentheses, corresponding closing parenthesis for an opening bracket at position in is
            // at [size-n]

            unsigned int positionOfOpeningParenthesis = vector_parentheses[index].position;
            // //std::cout << "Opening parenthesis: " << positionOfOpeningParenthesis << std::endl;
            // //std::cout << "successfully got opening parenthesis position" << std::endl;
            unsigned int positionOfClosingParenthesis = vector_parentheses[vector_parentheses.size()-1 - index].position;
            // //std::cout << "Closing parenthesis: " << positionOfClosingParenthesis << std::endl;
            // //std::cout << "successfully got closing parenthesis position" << std::endl;
            for(unsigned int index2 = positionOfOpeningParenthesis+1; index2 < positionOfClosingParenthesis;index2++)
            {
                subExpression+=expressionString[index2]; //gets stuff found between each bracket
            }
            // //std::cout << "successfully got expression" << std::endl;
            // //std::cout << "Sub expression: " << subExpression;
            Expression temporaryExpression(subExpression, true); //creates a new sub expression
            // //std::cout << "successfully created new expression" << std::endl;
            int digits_before = 1 + (int)floor(log10(fabs(temporaryExpression.result)));
            int digits_after = std::numeric_limits<long double>::digits10 - digits_before;

            long double whole = floor(pow(10, digits_after) * fabs(temporaryExpression.result) + 0.5);
            while (digits_after > 0 && (whole/10.0 - floor(whole/10.0)) < 0.05)
            {
                --digits_after;
                whole = floor(whole / 10.0 + 0.5);
            }
            if (digits_after < 0) digits_after = 0;

            std::stringstream ss;
            ss << std::fixed << std::setprecision(digits_after) << temporaryExpression.result;

            std::string stringResult = ss.str();
            //std::cout << "successfully converted " << temporaryExpression.result <<" long double to string" << std::endl;
            //std::cout << stringResult;
            // //std::cout << "size of expression: " << expressionString.size() << "Position of opening parenthesis: " << positionOfOpeningParenthesis << "Position of closing parenthesis: " << positionOfClosingParenthesis << std::endl;
            if(expressionString.size() <= positionOfOpeningParenthesis)
            {
             for (unsigned int index = expressionString.size(); index <= positionOfOpeningParenthesis+stringResult.size();index++)
             {
              expressionString+=' ';
             }
            }
            else
            {
             expressionString.replace(positionOfOpeningParenthesis,positionOfClosingParenthesis-positionOfOpeningParenthesis +1,stringResult);
            }
            //GETS RESULT AND PLACES IT BACK IN THE ORIGINAL EXPRESSION //
            // //std::cout << "successfully placed result of subexpression in string" << std::endl;
            // //std::cout << "NEW EXPRESSION: " << expressionString;
        }
      evaluate(); //Evaluates new expression containing the result of the sub expression
    }
}
int main() {

    std::cout << "To do list: " << std::endl;
    std::cout << "Validate equal bracket numbers" << std::endl;
    std::cout << "Add support for negative input numbers" << std::endl;
    while(true)
    {
     std::cout << "Please enter your expression: " ;
    std::string expression;
    std::cin >> expression;
    if(expression == "exit")
        break;
    Expression expressionToEvaluate(expression, false);
    std::cout << "RESULT: " << std::fixed <<  expressionToEvaluate.result<< std::endl;
    }

    return 0;
}
