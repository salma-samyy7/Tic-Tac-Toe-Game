#include <iostream>
#include <vector>
#include <string>

using namespace std;

enum Difficulty
{
    EASY,
    HARD
};

class Board
{
private:
    vector<vector<char>> grid; // 2D grid for board state
    const int size;            // board size (default: 3)
public:
    Board(int s = 3) : size(s) //--Farah--
    {                          // constructor: creates board of given size
                               // TODO: initialize board with empty spaces given size
    }

    void display() const //--Farah--
    {
        // prints the current board to console
        // TODO: print board with row/col formatting
    }

    bool makeMove(int row, int col, char symbol) //--Farah--
    {
        // attempts to place symbol on board
        // TODO: if valid, place symbol and return true, else return false
    }

    bool isValidMove(int row, int col) const //--Farah--
    {
        // checks if a move can be made at given coordinates
        // TODO: check if row and col are within bounds and cell is empty
    }

    bool checkWin(char symbol) const //--Abdelmasih--
    {
       for (int i = 0; i < size; i++) {
        bool rowWin = true;
        for (int j = 0; j < size; j++) {
            if (board[i][j] != symbol) {
                rowWin = false;
                break;
            }
        }
        if (rowWin) return true;
    }

    for (int j = 0; j < size; j++) {
        bool colWin = true;
        for (int i = 0; i < size; i++) {
            if (board[i][j] != symbol) {
                colWin = false;
                break;
            }
        }
        if (colWin) return true;
    }

    bool diag1Win = true;
    for (int i = 0; i < size; i++) {
        if (board[i][i] != symbol) {
            diag1Win = false;
            break;
        }
    }
    if (diag1Win) return true;

    bool diag2Win = true;
    for (int i = 0; i < size; i++) {
        if (board[i][size - 1 - i] != symbol) {
            diag2Win = false;
            break;
        }
    }
    if (diag2Win) return true;

    return false;
    }

    bool isFull() const //--Abdelmasih--
    {
      for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (board[i][j] == ' ') return false; 
        }
    }
    return true;
    }

    char getCell(int row, int col) const //--Abdelmasih--
    {
       return board[row][col];
    }

    void reset() //--Abdelmasih--
    {
        for (int i = 0; i < size; i++) {
          for (int j = 0; j < size; j++) {
            board[i][j] = ' ';
           }
        }
       
    }

    int getSize() const    //--Farah--
    {
        // returns the board size
        // TODO: return size
    }

    vector<pair<int, int>> availableMoves() const // helper function    //--Farah--
    {
        // lists all empty cells
        // TODO: return vector of free cell positions
    }
};

class Player
{
protected:
    string name; // player's name
    char symbol; // 'X' or 'O'
public:
    Player()
    { // defualt constructor
        name = "";
        symbol = ' ';
    }

    Player(const string &n, char sym) //--Abdelmasih--
    {
        // constructor: sets name and symbol
        name = n;
        symbol = sym ;
    }

    virtual void getMove(const Board &board, int &row, int &col) = 0; // asks player for next move
    // TODO: HumanPlayer will ask user input, AIPlayer will calculate move

    string getName() const     //--Mazen--
    {
        // returns player's name
        // TODO: return name
    }

    char getSymbol() const     //--Salma--
    {
        // returns player's symbol
        // TODO: return symbol_
    }

    void setName(const string &name)     //--Mina--
    {
        // updates player's name
        // TODO: update name
    }
};

class HumanPlayer : public Player //  extra class for clean oop
{
public:
    HumanPlayer(const string &name, char symbol)     //--Mazen--
    {
        // constructor for human player
        // TODO: call base class constructor
    }

    void getMove(const Board &board, int &row, int &col) override     //--Mazen--
    {
        // gets move from user
        // TODO: ask user for row, col input and validate
    }
};

class AIPlayer : public Player
{
private:
    Difficulty difficulty; // AI difficulty level
public:
    AIPlayer(const string &name, char symbol, Difficulty diff)     //--Mina--
    {
        // constructor for AI
        // TODO: initialize AI with difficulty
    }

    void getMove(const Board &board, int &row, int &col) override 
    {     //--Mina--
        // gets move based on difficulty
        // TODO: choose random move (easy) or best move (hard)
    }

    void setDifficulty(Difficulty d)     //--Mina--
    {
        // updates AI difficulty
        // TODO: update difficulty
    }

    void getRandomMove(const Board &board, int &row, int &col) const     //--Mazen--
    {
        // selects random empty spot
        // TODO: pick a random available move
    }
    void getBestMove(const Board &board, int &row, int &col) const      //--Mina--
    {
        // uses minimax to find best move
        // TODO: implement minimax search
    }

    int evaluateBoard(const Board &board) const     //--Salma--
    {
        // evaluates current board state
        // TODO: +10 if AI wins, -10 if opponent wins, 0 if draw
    }
};

class Game
{
private:
    Board board_;     // the game board
    Player *player1_; // first player
    Player *player2_; // second player
    Player *current_; // currently active player
public:
    Game()     //--Salma--
    {
        // constructor: initializes board
        // TODO: create board and set players to nullptr
    }

    void start()     //--Salma--
    {
        // starts the whole game loop
        // TODO: run menu, setup game, play rounds until quit
    }

    void showMenu()     //--Abdelmasih--
    { 
        // displays menu options (PvP, PvC, Quit)
      int choice;
       cout << "==== Tic-Tac-Toe ====\n";
       cout << "1. Player vs Player (PvP)\n";
       cout << "2. Player vs Computer (PvC)\n";
       cout << "3. Quit\n";
       cout << "Choose option: ";
       cin >> choice;

       switch (choice)
      {
       case 1:
            setupPvP();
         break;
       case 2:
     {
        int diffChoice;
        cout << "Select difficulty: 1. Easy 2. Hard: ";
        cin >> diffChoice;
        Difficulty diff = (diffChoice == 1) ? Difficulty::Easy : Difficulty::Hard;
        setupPvC(diff);
        break;
     }
       case 3:
        cout << "Exiting game...\n";
        exit(0);
       default:
        cout << "Invalid choice\n";
        showMenu();
     }  
    }

    void setupPvP()     //--Salma--
    {
        // setup player vs player game
        // TODO: create two HumanPlayer objects
    }

    void setupPVC(Difficulty diff)     //--Salma--
    {
        // setup player vs AI game
        // TODO: create HumanPlayer and AIPlayer
    }

    void switchPlayer()     //--Mina--
    {
        // switch turns between players
        // TODO: change current_ to the other player
    }

    void handleHumanMove(Player player)     //--Mazen--
    {
        // TODO: Get move from human and apply to board
    }

    void handleAIMove(AIPlayer aiplayer)    //--Farah--
    {  
        // TODO: Get move from AI and apply to board
    }

    bool checkGameEnd()    //--Abdelmasih--
    {
        // checks if the game has ended (win or draw)
      if (board.checkWin(currentPlayer->getSymbol()))
     {
        cout << currentPlayer->getName() << " wins!\n";
        return true;
     }
      if (board.isFull())
     {
        cout << "It's a draw!\n";
        return true;
     }
     return false;   
    }

    void displayResult() const     //--Mazen--
    {
        // show game result
        // TODO: announce winner or draw
    }
    void rest()     //--Salma--
    {
        // TODO: rest game;
    }
};

// -------------------- main --------------------
int main()
{
    // TODO: create Game object and call start()
    Game game;
    game.start();
    return 0;
}