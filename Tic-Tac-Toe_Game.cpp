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
        // checks if the given symbol has won
        // TODO: check rows, columns, diagonals for win
    }

    bool isFull() const //--Abdelmasih--
    {
        // checks if no moves are left
        // TODO: return true if board has no empty cells
    }

    char getCell(int row, int col) const //--Abdelmasih--
    {
        // returns the symbol at given cell
        // TODO: return the symbol at row, col
    }

    void reset() //--Abdelmasih--
    {
        // clears the board back to empty state
        // TODO: clear all cells to empty state
    }

    int getSize() const //--Farah--
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
        // TODO: assign name and symbol
    }

    virtual void getMove(const Board &board, int &row, int &col) = 0; // asks player for next move
    // TODO: HumanPlayer will ask user input, AIPlayer will calculate move

    string getName() const //--Mazen--
    {
        // returns player's name
        // TODO: return name
    }

    char getSymbol() const //--Salma--
    {
        // returns player's symbol
        // TODO: return symbol_
        return symbol;
    }

    void setName(const string &name) //--Mina--
    {
        // updates player's name
        // TODO: update name
    }
};

class HumanPlayer : public Player //  extra class for clean oop
{
public:
    HumanPlayer(const string &name, char symbol) //--Mazen--
    {
        // constructor for human player
        // TODO: call base class constructor
    }

    void getMove(const Board &board, int &row, int &col) override //--Mazen--
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
    AIPlayer(const string &name, char symbol, Difficulty diff) //--Mina--
    {
        // constructor for AI
        // TODO: initialize AI with difficulty
    }

    void getMove(const Board &board, int &row, int &col) override
    { //--Mina--
      // gets move based on difficulty
      // TODO: choose random move (easy) or best move (hard)
    }

    void setDifficulty(Difficulty d) //--Mina--
    {
        // updates AI difficulty
        // TODO: update difficulty
    }

    void getRandomMove(const Board &board, int &row, int &col) const //--Mazen--
    {
        // selects random empty spot
        // TODO: pick a random available move
    }
    void getBestMove(const Board &board, int &row, int &col) const //--Mina--
    {
        // uses minimax to find best move
        // TODO: implement minimax search
    }

    int evaluateBoard(const Board &board) const //--Salma--
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
    Game() : board_(3) //--Salma--
    {
        // constructor: initializes board
        // TODO: create board and set players to nullptr

        player1_ = nullptr;
        player2_ = nullptr;
        current_ = nullptr;
    }

    void start() //--Salma--
    {
        // starts the whole game loop
        // TODO: run menu, setup game, play rounds until quit
        showMenu();
        int mode;
        cout << "Select Game Mode: ";
        cin >> mode;
    }

    void showMenu() //--Abdelmasih--
    {
        // displays menu options (PvP, PvC, Quit)
        // TODO: print menu and take user input
    }

    void setupPvP() //--Salma--
    {
        // setup player vs player game
        // TODO: create two HumanPlayer objects
        string name_p1, name_p2;
        cout << "Enter First player's name (player symbol X): ";
        cin >> name_p1;

        cout << "Enter Second player's name (player symbol O): ";
        cin >> name_p2;

        player1_ = new HumanPlayer(name_p1, 'X');
        player2_ = new HumanPlayer(name_p2, 'O');
        current_ = player1_;
    }

    void setupPVC(Difficulty diff) //--Salma--
    {
        // setup player vs AI game
        // TODO: create HumanPlayer and AIPlayer
        string name;
        cout << "Enter player's name (player symbol X): ";
        cin >> name;

        player1_ = new HumanPlayer(name, 'X');
        player2_ = new AIPlayer("Computer", 'O', diff);
        current_ = player1_;
    }

    void switchPlayer() //--Mina--
    {
        // switch turns between players
        // TODO: change current_ to the other player
    }

    void handleHumanMove(Player player) //--Mazen--
    {
        // TODO: Get move from human and apply to board
    }

    void handleAIMove(AIPlayer aiplayer) //--Farah--
    {
        // TODO: Get move from AI and apply to board
    }

    bool checkGameEnd() //--Abdelmasih--
    {
        // checks if the game has ended (win or draw)
        // TODO: return true if someone wins or if the board is full
    }

    void displayResult() const //--Mazen--
    {
        // show game result
        // TODO: announce winner or draw
    }
    void reset() //--Salma--
    {
        // TODO: rest game;
        if (player1_)
        {
            delete player1_;
            player1_ = nullptr;
        }
        if (player2_)
        {
            delete player2_;
            player2_ = nullptr;
        }

        current_ = nullptr;
        board_.reset();
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