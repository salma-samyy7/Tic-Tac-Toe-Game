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
        grid = vector<vector<char>>(size, vector<char>(size, ' '));
    }

    void display() const //--Farah--
    {
        // prints the current board to console
        // TODO: print board with row/col formatting
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                cout << grid[i][j];
                if (j < size - 1)
                    cout << "|";
            }
            cout << "\n";
            if (i < size - 1)
            {
                for (int j = 0; j < size; j++)
                {
                    cout << "-";
                    if (j < size - 1)
                        cout << "+";
                }
                cout << "\n";
            }
        }
    }

    bool makeMove(int row, int col, char symbol) //--Farah--
    {
        // attempts to place symbol on board
        // TODO: if valid, place symbol and return true, else return false
        if (isValidMove(row, col))
        {
            grid[row][col] = symbol;
            return true;
        }
        return false;
    }

    bool isValidMove(int row, int col) const //--Farah--
    {
        // checks if a move can be made at given coordinates
        // TODO: check if row and col are within bounds and cell is empty
        return (row >= 0 && row < size && col >= 0 && col < size && grid[row][col] == ' ');
    }

    bool checkWin(char symbol) const //--Abdelmasih--
    {
        for (int i = 0; i < size; i++)
        {
            bool rowWin = true;
            for (int j = 0; j < size; j++)
            {
                if (grid[i][j] != symbol)
                {
                    rowWin = false;
                    break;
                }
            }
            if (rowWin)
                return true;
        }

        for (int j = 0; j < size; j++)
        {
            bool colWin = true;
            for (int i = 0; i < size; i++)
            {
                if (grid[i][j] != symbol)
                {
                    colWin = false;
                    break;
                }
            }
            if (colWin)
                return true;
        }

        bool diag1Win = true;
        for (int i = 0; i < size; i++)
        {
            if (grid[i][i] != symbol)
            {
                diag1Win = false;
                break;
            }
        }
        if (diag1Win)
            return true;

        bool diag2Win = true;
        for (int i = 0; i < size; i++)
        {
            if (grid[i][size - 1 - i] != symbol)
            {
                diag2Win = false;
                break;
            }
        }
        if (diag2Win)
            return true;

        return false;
    }

    bool isFull() const //--Abdelmasih--
    {
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                if (grid[i][j] == ' ')
                    return false;
            }
        }
        return true;
    }

    char getCell(int row, int col) const //--Abdelmasih--
    {
        return grid[row][col];
    }

    void reset() //--Abdelmasih--
    {
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                grid[i][j] = ' ';
            }
        }
    }

    int getSize() const //--Farah--
    {
        // returns the board size
        return size; // TODO: return size
    }

    vector<pair<int, int>> availableMoves() const // helper function    //--Farah--
    {
        // lists all empty cells
        vector<pair<int, int>> moves;
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                if (grid[i][j] == ' ')
                    moves.push_back({i, j});
            }
        }
        return moves;
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
        symbol = sym;
    }

    virtual void getMove(const Board &board, int &row, int &col) = 0; // asks player for next move
    // TODO: HumanPlayer will ask user input, AIPlayer will calculate move

    string getName() const //--Mazen--
    {
        // returns player's name
        // TODO: return name
        return name;
    }

    char getSymbol() const //--Salma--
    {
        // returns player's symbol
        // TODO: return symbol_

        return symbol;
    }

    void setName(const string &n) //--Mina--

    {
        // updates player's name

        name = n;
    }
};

class HumanPlayer : public Player //  extra class for clean oop
{
public:
    HumanPlayer(const string &name, char symbol) //--Mazen--
    {
        this->name = name;
        this->symbol = symbol;
    }

    void getMove(const Board &board, int &row, int &col) override //--Mazen--
    {
        // gets move from user
        cout << name << "'s turn (" << symbol << "). Enter your move (row col): ";
        cin >> row >> col;
        row--;
        col--;
    }
};

class AIPlayer : public Player
{
private:
    Difficulty difficulty; // AI difficulty level
public:
    AIPlayer(const string &name, char symbol, Difficulty diff) : Player(name, symbol), difficulty(diff) {} //--Mina--

    void getMove(const Board &board, int &row, int &col) override
    { //--Mina--
        // gets move based on difficulty
        cout << name << "'s turn (" << symbol << ")...\n";

        if (difficulty == EASY)
        {
            getRandomMove(board, row, col);
        }
        else
        {
            getBestMove(board, row, col);
        }

        cout << name << " chooses position (" << row << ", " << col << ")\n";
    }

    void setDifficulty(Difficulty d) //--Mina--
    {
        // updates AI difficulty
        difficulty = d;
    }

    void getRandomMove(const Board &board, int &row, int &col) const //--Mazen--
    {
        // selects random empty spot
        // TODO: pick a random available move

        vector<pair<int, int>> moves = board.availableMoves();
        if (!moves.empty())
        {
            int randomindex = rand() % moves.size();
            row = moves[randomindex].first;
            col = moves[randomindex].second;
            /* code */
        }
    }

    void getBestMove(const Board &board, int &row, int &col) const //--Mina--
    {
        int bestScore = -1000;
        vector<pair<int, int>> bestMoves;

        vector<pair<int, int>> moves = board.availableMoves();

        for (const auto &move : moves)
        {
            Board tempBoard = board;
            tempBoard.makeMove(move.first, move.second, symbol);

            int score = minimax(tempBoard, 0, false);

            if (score > bestScore)
            {
                bestScore = score;
                bestMoves.clear();
                bestMoves.push_back(move);
            }
            else if (score == bestScore)
            {
                bestMoves.push_back(move);
            }
        }

        if (!bestMoves.empty())
        {
            int randomIndex = rand() % bestMoves.size();
            row = bestMoves[randomIndex].first;
            col = bestMoves[randomIndex].second;
        }
    }

private:
    int minimax(Board board, int depth, bool isMaximizing) const
    {
        int score = evaluateBoard(board); // use function

        if (score != 0)
        {
            return score - depth; // Terminal state: adjust score by depth so AI prefers quick wins and delays losses
        }

        if (board.isFull())
        {
            return 0;
        }

        char opponent = (symbol == 'X') ? 'O' : 'X';

        if (isMaximizing)
        {
            int bestScore = -1000;
            vector<pair<int, int>> moves = board.availableMoves();

            for (const auto &move : moves)
            {
                Board tempBoard = board;
                tempBoard.makeMove(move.first, move.second, symbol);
                int score = minimax(tempBoard, depth + 1, false);
                bestScore = max(score, bestScore);
            }
            return bestScore;
        }
        else
        {
            int bestScore = 1000;
            vector<pair<int, int>> moves = board.availableMoves();

            for (const auto &move : moves)
            {
                Board tempBoard = board;
                tempBoard.makeMove(move.first, move.second, opponent);
                int score = minimax(tempBoard, depth + 1, true);
                bestScore = min(score, bestScore);
            }
            return bestScore;
        }
    }

    int evaluateBoard(const Board &board) const //--Salma--
    {
        // evaluates current board state
        // TODO: +10 if AI wins, -10 if opponent wins, 0 if draw
        char opponent = (symbol == 'X') ? 'O' : 'X';

        if (board.checkWin(symbol))
            return +10;
        if (board.checkWin(opponent))
            return -10;
        return 0; // draw or not terminal
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

    void showMenu() //--Abdelmasih--

    {
        // displays menu options (PvP, PvC, Quit)

        cout << "TIC-TAC-TOE GAME\n";
        cout << "1. Player vs Player\n";
        cout << "2. Player vs Computer (Easy)\n";
        cout << "3. Player vs Computer (Hard)\n";
        cout << "4. Exit\n";
        cout << "Select game mode: ";
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
        current_ = (current_ == player1_) ? player2_ : player1_;
    }

    void playRound()
    {
        board_.display();

        while (true)
        {
            if (dynamic_cast<HumanPlayer *>(current_)) // check if current is Human
            {
                handleHumanMove(current_);
            }
            else if (dynamic_cast<AIPlayer *>(current_)) // check if current is AI
            {
                handleAIMove(static_cast<AIPlayer *>(current_));
            }

            board_.display();

            if (checkGameEnd())
            {
                break;
            }

            switchPlayer();
        }
    }

    void handleHumanMove(Player *player) //--Mazen-- //Mina:updated as a pointer
    {
        int row, col;
        player->getMove(board_, row, col);
        board_.makeMove(row, col, player->getSymbol());

        // TODO: Get move from human and apply to board
    }

    void handleAIMove(AIPlayer *aiplayer) //--Farah-- //Mina:updated as a pointer
    {
        int row, col;
        aiplayer->getMove(board_, row, col);
        board_.makeMove(row, col, aiplayer->getSymbol()); // TODO: Get move from AI and apply to board
    }

    bool checkGameEnd() //--Abdelmasih--
    {
        // checks if the game has ended (win or draw)
        if (board_.checkWin(current_->getSymbol()))
        {
            cout << current_->getName() << " wins!\n";
            return true;
        }
        if (board_.isFull())
        {
            cout << "It's a draw!\n";
            return true;
        }
        return false;
    }

    void displayResult() const //--Mazen--
    {
        // show game result
        // TODO: announce winner or draw
        if (board_.checkWin(player1_->getSymbol()))
        {
            cout << player1_->getName() << " wins!\n";
        }
        else if (board_.checkWin(player2_->getSymbol()))
        {
            cout << player2_->getName() << " wins!\n";
        }
        else if (board_.isFull())
        {
            cout << "It's a draw!\n";
        }
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

    void start() //--Salma--
    {
        while (true)
        {
            showMenu(); // prints the menu only

            int choice;
            cin >> choice;

            switch (choice)
            {
            case 1:
                setupPvP();
                break;
            case 2:
                setupPVC(Difficulty::EASY); // directly Easy
                break;
            case 3:
                setupPVC(Difficulty::HARD); // directly Hard
                break;
            case 4:
                cout << "Exiting game...\n";
                return;
            default:
                cout << "Invalid choice\n";
                continue;
            }

            playRound();

            // cleanup before next game
            reset();

            char again;
            cout << "Play again? (y/n): ";
            cin >> again;
            if (again != 'y' && again != 'Y')
            {
                cout << "Thanks for playing!\n";
                break;
            }
        }
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
