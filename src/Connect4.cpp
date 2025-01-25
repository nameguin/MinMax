/**
 * @file Connect4.cpp
 * @brief Implementation of the Connect 4 game logic.
 */

#include "Connect4.h"
#include <iostream>
#include <vector>

/**
 * @brief Gets the current player in the game.
 * @return An integer representing the current player (AI or PLAYER).
 */
int Connect4::getCurrentPlayer() const
{
    return currentPlayer;
}

/**
 * @brief Displays the current state of the Connect 4 board.
 *
 * The board is displayed with X for the player, O for the AI, and . for empty cells.
 * Column numbers are displayed below the board for reference.
 */
void Connect4::display() const
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
    for (int i = 0; i < BOARD_LENGTH; ++i)
    {
        std::cout << i + 1 << " "; // Display column numbers
    }
    std::cout << "\n";
}

/**
 * @brief Checks if the game is in a terminal state.
 *
 * A terminal state occurs when there is a winner or no more moves are available.
 * @return true if the game is over, false otherwise.
 */
bool Connect4::isTerminal() const
{
    return getWinner() != 0 || getAvailableMoves().empty();
}

/**
 * @brief Gets all valid moves (columns) in the current game state.
 *
 * A valid move is any column that is not full.
 * @return A vector of integers representing the indices of available columns.
 */
std::vector<int> Connect4::getAvailableMoves() const
{
    std::vector<int> moves;
    for (int col = 0; col < BOARD_LENGTH; ++col)
    {
        if (board[0][col] == EMPTY) moves.push_back(col);
    }
    return moves;
}

/**
 * @brief Makes a move in the specified column.
 *
 * The move is applied to the lowest available row in the column.
 * @param col The index of the column where the move is made.
 */
void Connect4::makeMove(const int col)
{
    for (int row = BOARD_HEIGHT - 1; row >= 0; --row)
    {
        if (board[row][col] == EMPTY)
        {
            board[row][col] = currentPlayer;
            currentPlayer = (currentPlayer == PLAYER) ? AI : PLAYER;
            break;
        }
    }
}

/**
 * @brief Undoes the last move made in the specified column.
 *
 * The topmost occupied row in the column is cleared.
 * @param col The index of the column to undo the move.
 */
void Connect4::undoMove(const int col)
{
    for (auto & row : board)
    {
        if (row[col] != EMPTY)
        {
            row[col] = EMPTY;
            currentPlayer = (currentPlayer == PLAYER) ? AI : PLAYER;
            break;
        }
    }
}

/**
 * @brief Evaluates the current board state.
 *
 * @return 10 if the AI wins, -10 if the player wins, 0 otherwise.
 */
int Connect4::evaluate() const
{
    const int winner = getWinner();
    if (winner == AI) return 10; // AI wins
    if (winner == PLAYER) return -10; // Player wins
    return 0; // Draw or ongoing game
}

/**
 * @brief Determines the winner of the game.
 *
 * Checks for four consecutive identical markers in any direction (horizontal, vertical, diagonal).
 * @return The marker of the winner (PLAYER or AI), or 0 if there is no winner.
 */
int Connect4::getWinner() const
{
    // Define directions: horizontal, vertical, and two diagonals
    constexpr int directions[4][2] = {{0, 1}, {1, 0}, {1, 1}, {-1, 1}};

    for (int row = 0; row < BOARD_HEIGHT; ++row)
    {
        for (int col = 0; col < BOARD_LENGTH; ++col)
        {
            if (board[row][col] == 0) continue; // Skip empty cells

            for (const auto& dir : directions)
            {
                const int dr = dir[0];
                const int dc = dir[1];
                int count = 1; // Include the current cell

                for (int k = 1; k < 4; ++k)
                {
                    // Check the next 3 cells in the direction
                    const int nr = row + k * dr;
                    const int nc = col + k * dc;

                    // Ensure indices are within bounds and values match
                    if (nr >= 0 && nr < BOARD_HEIGHT && nc >= 0 && nc < BOARD_LENGTH
                        && board[nr][nc] == board[row][col]) count++;
                    else break;
                }

                if (count == 4) return board[row][col]; // Return the winner (1 or -1)
            }
        }
    }
    return 0; // No winner
}

/**
 * @brief Checks if the player's input column is valid.
 *
 * A valid column is one that exists and is not full.
 * @param col The index of the column to check.
 * @return true if the input is valid, false otherwise.
 */
bool Connect4::checkInput(const int col) const
{
    return col >= 0 && col < BOARD_LENGTH && board[0][col] == EMPTY;
}

/**
 * @brief Prompts the player for their input.
 *
 * @return The index of the column chosen by the player.
 */
int Connect4::askInput() const
{
    int col;
    std::cout << "Enter the column number (between 1 and " << BOARD_LENGTH << "): ";
    std::cin >> col;
    return col - 1;
}
