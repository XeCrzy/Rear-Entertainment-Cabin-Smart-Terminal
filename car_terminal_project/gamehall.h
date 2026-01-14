#ifndef GAMEHALL_H
#define GAMEHALL_H

#include <QWidget>
#include <QPaintEvent>
#include <QKeyEvent>
#include <QPoint>
#include <QList>
#include <QTimer>
#include <QLabel>

QT_BEGIN_NAMESPACE
namespace Ui { class GameHall; }
QT_END_NAMESPACE

class GameHall : public QWidget
{
    Q_OBJECT

public:
    explicit GameHall(QWidget *parent = nullptr);
    ~GameHall();

    // Override paint event
    void paintEvent(QPaintEvent* event) override;

    // Override key press event
    void keyPressEvent(QKeyEvent *event) override;

    // Override key release event
    void keyReleaseEvent(QKeyEvent *event) override;

    // Override focus in event to ensure keyboard focus
    void focusInEvent(QFocusEvent *event) override;

    // Override focus out event
    void focusOutEvent(QFocusEvent *event) override;

    // Override show event to set focus
    void showEvent(QShowEvent *event) override;

signals:
    void returnToMain();  // Signal to return to main window

private slots:
    void updateGame();  // Update game state

private:
    Ui::GameHall *ui;
    void initGame();      // Initialize game
    void resetGame();     // Reset game
    void generateFood();  // Generate food
    void onGameOver();    // Handle game over

    // Game related variables
    enum Direction { UP, DOWN, LEFT, RIGHT };
    Direction currentDirection;
    Direction nextDirection;

    QTimer *gameTimer;
    QList<QPoint> snake;  // Snake body segments
    QPoint food;          // Food position
    int score;            // Score
    bool gameRunning;     // Is game running
    bool gamePaused;      // Is game paused
    int gameSpeed;        // Game speed in milliseconds

    // Game area parameters
    const int GRID_SIZE = 20;
    const int GRID_WIDTH = 30;    // 600 pixels / 20 = 30 cells
    const int GRID_HEIGHT = 24;   // 480 pixels / 20 = 24 cells

    // Key handling
    void handleKeyPress(int key);
    bool keyUpPressed;
    bool keyDownPressed;
    bool keyLeftPressed;
    bool keyRightPressed;

    // Focus management
    bool hasFocusNow;
};

#endif // GAMEHALL_H
