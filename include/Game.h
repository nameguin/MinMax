/**
 * @file Game.h
 * @brief Declaration of the Game interface.
 *
 * This interface defines the common structure and methods that all games must implement.
 */

#ifndef GAME_H
#define GAME_H

#include <vector>

/**
 * @class Game
 * @brief Abstract base class for all games.
 *
 * The `Game` class defines an interface for implementing various games,
 * such as Connect 4, Tic-Tac-Toe, and others. It provides pure virtual methods
 * that subclasses must override to define specific game logic.
 */
class Game {
public:
    const int AI = -1;     ///< Represents the AI player.
    const int PLAYER = 1;  ///< Represents the human player.
    const int EMPTY = 0;   ///< Represents an empty cell or spot in the game.

    /**
     * @brief Gets the current player in the game.
     * @return An integer representing the current player (AI or PLAYER).
     */
    [[nodiscard]] virtual int getCurrentPlayer() const = 0;

    /**
     * @brief Displays the current state of the game.
     *
     * Subclasses must implement this method to visually represent the game's state.
     */
    virtual void display() const = 0;

    /**
     * @brief Checks if the game is in a terminal state.
     *
     * A terminal state occurs when the game is over, either because a player has won
     * or there are no more valid moves.
     * @return true if the game is over, false otherwise.
     */
    [[nodiscard]] virtual bool isTerminal() const = 0;

    /**
     * @brief Gets all valid moves available in the current game state.
     *
     * Subclasses must implement this method to return a list of all valid moves
     * that can be made.
     * @return A vector of integers representing the available moves.
     */
    [[nodiscard]] virtual std::vector<int> getAvailableMoves() const = 0;

    /**
     * @brief Makes a move in the game.
     *
     * Subclasses must implement this method to modify the game state based on the specified move.
     * @param x The move to be made.
     */
    virtual void makeMove(int x) = 0;

    /**
     * @brief Undoes a previously made move in the game.
     *
     * Subclasses must implement this method to revert the game state to before the specified move was made.
     * @param x The move to be undone.
     */
    virtual void undoMove(int x) = 0;

    /**
     * @brief Evaluates the current state of the game.
     *
     * Subclasses must implement this method to return a score evaluating the current game state.
     * Positive scores typically favor the AI, while negative scores favor the player.
     * @return An integer representing the evaluation of the game state.
     */
    [[nodiscard]] virtual int evaluate() const = 0;

    /**
     * @brief Determines the winner of the game.
     *
     * Subclasses must implement this method to identify if there is a winner.
     * @return The winner of the game (e.g., AI, PLAYER, or 0 if there is no winner).
     */
    [[nodiscard]] virtual int getWinner() const = 0;

    /**
     * @brief Checks if the player's input is valid.
     *
     * Subclasses must implement this method to validate the player's input.
     * @param input The input to validate.
     * @return true if the input is valid, false otherwise.
     */
    [[nodiscard]] virtual bool checkInput(int input) const = 0;

    /**
     * @brief Prompts the player for their input.
     *
     * Subclasses must implement this method to handle player input during their turn.
     * @return The input provided by the player.
     */
    [[nodiscard]] virtual int askInput() const = 0;

    /**
     * @brief Virtual destructor for the Game interface.
     *
     * Ensures proper cleanup of resources in derived classes.
     */
    virtual ~Game() = default;
};

#endif // GAME_H
