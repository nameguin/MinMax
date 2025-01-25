/**
 * @file TicTacToe.cpp
 * @brief Implementation of the TicTacToe game logic.
 */

#include "TicTacToe.h"

/**
 * @brief Constructs a TicTacToe game instance.
 * @param userIsStarting A boolean indicating if the user is the starting player.
 */
TicTacToe::TicTacToe(const bool userIsStarting) : board() , currentPlayer(userIsStarting ? PLAYER : AI) {
    for (auto & row : board) {
        for (int & cell : row) {
            cell = EMPTY;
        }
    }
}

/**
 * @brief Gets the current player in the game.
 * @return An integer representing the current player (AI or PLAYER).
 */
int TicTacToe::getCurrentPlayer() const
{
    return currentPlayer;
}

/**
 * @brief Displays the current state of the Tic-Tac-Toe board.
 */
void TicTacToe::display() const
{
    for (const auto& row : board)
    {
        for (const auto& cell : row)
        {
            if (cell == PLAYER) std::cout << "X ";
            else if (cell == AI) std::cout << "O ";
            else  std::cout << ". ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

/**
 * @brief Checks if the game is in a terminal state (win, lose, or draw).
 * @return true if the game is over, false otherwise.
 */
bool TicTacToe::isTerminal() const
{
    return getWinner() != 0 || getAvailableMoves().empty();
}

/**
 * @brief Gets all the available moves on the current board.
 * @return A vector of integers representing the indices of empty cells.
 */
std::vector<int> TicTacToe::getAvailableMoves() const
{
    std::vector<int> moves;
    for (int i = 0; i < BOARD_SIZE; ++i)
    {
        for (int j = 0; j < BOARD_SIZE; ++j)
        {
            if (board[i][j] == EMPTY) moves.emplace_back(i * BOARD_SIZE + j);
        }
    }
    return moves;
}

/**
 * @brief Makes a move at the specified position.
 * @param cellIndex The index of the cell where the move will be made.
 */
void TicTacToe::makeMove(const int cellIndex)
{
    if (cellIndex >= 0 && cellIndex < BOARD_SIZE * BOARD_SIZE
        && board[cellIndex / BOARD_SIZE][cellIndex % BOARD_SIZE] == EMPTY)
    {
        board[cellIndex / BOARD_SIZE][cellIndex % BOARD_SIZE] = currentPlayer; // Place the current player's marker
        currentPlayer = (currentPlayer == PLAYER) ? AI : PLAYER; // Switch the player
    }
}

/**
 * @brief Undoes the move at the specified position.
 * @param cellIndex The index of the cell to be cleared.
 */
void TicTacToe::undoMove(const int cellIndex)
{
    if (cellIndex >= 0 && cellIndex < BOARD_SIZE * BOARD_SIZE
        && board[cellIndex / BOARD_SIZE][cellIndex % BOARD_SIZE] != EMPTY)
    {
        board[cellIndex / BOARD_SIZE][cellIndex % BOARD_SIZE] = EMPTY; // Clear the cell
        currentPlayer = (currentPlayer == PLAYER) ? AI : PLAYER; // Switch back the player
    }
}

/**
 * @brief Evaluates the current board state to calculate a score.
 * @return A score representing the evaluation of the board:
 *         10 for an AI win, -10 for a player win, 0 for a draw or ongoing game.
 */
int TicTacToe::evaluate() const
{
    const int winner = getWinner();

    if (winner == AI) return 10; // AI wins
    if (winner == PLAYER) return -10; // Player wins
    return 0; // Draw or ongoing game
}

/**
 * @brief Determines the winner of the game.
 * @return 1 if the player wins, -1 if the AI wins, 0 if there is no winner.
 */
int TicTacToe::getWinner() const
{
    // Check rows for a winner
    for (const auto row : board)
    {
        if (row[0] != EMPTY && row[0] == row[1] && row[1] == row[2])
        {
            return row[0];
        }
    }

    // Check columns for a winner
    for (int j = 0; j < BOARD_SIZE; ++j)
    {
        if (board[0][j] != EMPTY && board[0][j] == board[1][j] && board[1][j] == board[2][j])
        {
            return board[0][j];
        }
    }

    // Check diagonals for a winner
    if (board[0][0] != EMPTY && board[0][0] == board[1][1] && board[1][1] == board[2][2])
    {
        return board[0][0];
    }

    if (board[0][2] != EMPTY && board[0][2] == board[1][1] && board[1][1] == board[2][0])
    {
        return board[0][2];
    }

    // No winner found
    return 0;
}

/**
 * @brief Validates the player's input to ensure it is a valid move.
 * @param input The input position provided by the player.
 * @return true if the input is valid, false otherwise.
 */
bool TicTacToe::checkInput(const int input) const
{
    return input >= 0 && input < BOARD_SIZE * BOARD_SIZE
    && board[input / BOARD_SIZE][input % BOARD_SIZE] == EMPTY;
}

/**
 * @brief Asks the player for their input.
 * @return The index of the cell chosen by the player.
 */
int TicTacToe::askInput() const
{
    int x;
    std::cout << "Enter your case: ";
    std::cin >> x;
    return x - 1;
}
