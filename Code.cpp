#include <iostream>
using namespace std;

char space[3][3] = {{'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', '9'}};
int row;
int column;
char token = 'x';
bool gameTie = false; 
string player1 = "";
string player2 = "";

void functionone()
{
    cout << player1 << " is player 1 so he will play first. \n";
    cout << player2 << " is player 2 so he will play Second. \n";

    cout << "    |    |   \n";
    cout << space[0][0] << "   | " << space[0][1] << "  |  " << space[0][2] << "\n";
    cout << "----" << "----" << "-----" << " \n";
    cout << "    |    |   \n";
    cout << space[1][0] << "   | " << space[1][1] << "  |  " << space[1][2] << "\n";
    cout << "----" << "----" << "-----" << " \n";
    cout << "    |    |   \n";
    cout << space[2][0] << "   | " << space[2][1] << "  |  " << space[2][2] << "\n";
    cout << "----" << "----" << "-----" << " \n";
}

void functiontwo()
{
    int digit;
    if (token == 'x')
    {
        cout << player1 << " Enter The Digit: \n";
        cin >> digit;
    }
    else if (token == '0')
    {
        cout << player2 << " Enter The Digit: \n";
        cin >> digit;
    }

    if (digit == 1)
    {
        row = 0;
        column = 0;
    }
    else if (digit == 2)
    {
        row = 0;
        column = 1;
    }
    else if (digit == 3)
    {
        row = 0;
        column = 2;
    }
    else if (digit == 4)
    {
        row = 1;
        column = 0;
    }
    else if (digit == 5)
    {
        row = 1;
        column = 1;
    }
    else if (digit == 6)
    {
        row = 1;
        column = 2;
    }
    else if (digit == 7)
    {
        row = 2;
        column = 0;
    }
    else if (digit == 8)
    {
        row = 2;
        column = 1;
    }
    else if (digit == 9)
    {
        row = 2;
        column = 2;
    }
    else
    {
        cout << "Invalid !!" << endl;
        functiontwo();
        return;
    }

    if (token == 'x' && space[row][column] != 'x' && space[row][column] != '0')
    {
        space[row][column] = 'x';
        token = '0';
    }
    else if (token == '0' && space[row][column] != 'x' && space[row][column] != '0')
    {
        space[row][column] = '0';
        token = 'x';
    }
    else
    {
        cout << "There is not empty Space." << endl;
        functiontwo();
        return;
    }

    functionone();
}

bool functionthree()
{
    for (int i = 0; i < 3; i++)
    {
        if (space[i][0] == space[i][1] && space[i][1] == space[i][2])
            return true;

        if (space[0][i] == space[1][i] && space[1][i] == space[2][i])
            return true;
    }

    if (space[0][0] == space[1][1] && space[1][1] == space[2][2])
        return true;

    if (space[0][2] == space[1][1] && space[1][1] == space[2][0])
        return true;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (space[i][j] != 'x' && space[i][j] != '0')
                return false;
        }
    }

    gameTie = true; 
    return false;
}

int main()
{
    cout << "Enter Player Name: \n";
    getline(cin, player1);

    cout << "Enter Player Name: \n";
    getline(cin, player2);

    functionone();

    while (!functionthree())
    {
        functiontwo();
    }

    if (token == 'x' && gameTie == false)  
    {
        cout << player2 << " Wins.\n";
    }
    else if (token == '0' && gameTie == false)  
    {
        cout << player1 << " Wins \n";
    }
    else
    {
        cout << "It's a Draw!!\n";
    }

    return 0;
}
