#include "gamehall.h"
#include "ui_gamehall.h"
#include <QPainter>
#include <QPixmap>
#include <QIcon>
#include <QPushButton>
#include <QFont>
#include <QTimer>
#include <QMessageBox>
#include <QLabel>
#include <QDebug>
#include <QShowEvent>
#include <QFocusEvent>
#include <QApplication>
#include <cstdlib>
#include <ctime>

GameHall::GameHall(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GameHall)
    , currentDirection(RIGHT)
    , nextDirection(RIGHT)
    , gameTimer(nullptr)
    , score(0)
    , gameRunning(false)
    , gamePaused(false)
    , gameSpeed(150)
    , keyUpPressed(false)
    , keyDownPressed(false)
    , keyLeftPressed(false)
    , keyRightPressed(false)
    , hasFocusNow(false)
{
    ui->setupUi(this);

    // Set window properties
    this->setFixedSize(800, 480);
    this->setWindowIcon(QIcon(":/res/ico.png"));
    this->setWindowTitle("Snake Game");

    // Enable keyboard input - use StrongFocus to get tab focus as well
    this->setFocusPolicy(Qt::StrongFocus);

    // Initialize random seed
    srand(static_cast<unsigned>(time(nullptr)));

    // Initialize game
    initGame();

    // Create game timer
    gameTimer = new QTimer(this);
    connect(gameTimer, &QTimer::timeout, this, &GameHall::updateGame);

    // Create control buttons with English labels
    QFont buttonFont("Arial", 12);

    // Start/Pause button
    QPushButton* startPauseBtn = new QPushButton("Start Game", this);
    startPauseBtn->move(650, 100);
    startPauseBtn->setFixedSize(120, 40);
    startPauseBtn->setFont(buttonFont);
    startPauseBtn->setStyleSheet(
        "QPushButton {"
        "   background-color: #4CAF50;"
        "   color: white;"
        "   border: none;"
        "   border-radius: 8px;"
        "   padding: 5px;"
        "}"
        "QPushButton:hover {"
        "   background-color: #45a049;"
        "}"
    );

    connect(startPauseBtn, &QPushButton::clicked, [=]() {
        if (!gameRunning) {
            // Start game
            gameRunning = true;
            gamePaused = false;
            startPauseBtn->setText("Pause Game");
            gameTimer->start(gameSpeed);
            this->setFocus();  // Get keyboard focus
            qDebug() << "Game started, focus requested";
        } else if (!gamePaused) {
            // Pause game
            gamePaused = true;
            startPauseBtn->setText("Resume Game");
            gameTimer->stop();
            qDebug() << "Game paused";
        } else {
            // Resume game
            gamePaused = false;
            startPauseBtn->setText("Pause Game");
            gameTimer->start(gameSpeed);
            this->setFocus();  // Get keyboard focus
            qDebug() << "Game resumed";
        }
    });

    // Restart button
    QPushButton* restartBtn = new QPushButton("Restart", this);
    restartBtn->move(650, 150);
    restartBtn->setFixedSize(120, 40);
    restartBtn->setFont(buttonFont);
    restartBtn->setStyleSheet(
        "QPushButton {"
        "   background-color: #2196F3;"
        "   color: white;"
        "   border: none;"
        "   border-radius: 8px;"
        "   padding: 5px;"
        "}"
        "QPushButton:hover {"
        "   background-color: #1976D2;"
        "}"
    );

    connect(restartBtn, &QPushButton::clicked, [=]() {
        resetGame();
        gameTimer->stop();
        gameRunning = false;
        gamePaused = false;
        startPauseBtn->setText("Start Game");
        this->setFocus();  // Get focus after restart
        qDebug() << "Game reset";
        update();
    });

    // Exit button
    QPushButton* exitBtn = new QPushButton("Exit Game", this);
    exitBtn->move(650, 200);
    exitBtn->setFixedSize(120, 40);
    exitBtn->setFont(buttonFont);
    exitBtn->setStyleSheet(
        "QPushButton {"
        "   background-color: #f44336;"
        "   color: white;"
        "   border: none;"
        "   border-radius: 8px;"
        "   padding: 5px;"
        "}"
        "QPushButton:hover {"
        "   background-color: #d32f2f;"
        "}"
    );

    connect(exitBtn, &QPushButton::clicked, [=]() {
        qDebug() << "Exiting game";
        this->close();
        emit returnToMain();
    });

    // Difficulty buttons
    QPushButton* easyBtn = new QPushButton("Easy", this);
    easyBtn->move(650, 270);
    easyBtn->setFixedSize(50, 30);
    easyBtn->setFont(QFont("Arial", 10));
    easyBtn->setStyleSheet(
        "QPushButton {"
        "   background-color: #8BC34A;"
        "   color: white;"
        "   border: none;"
        "   border-radius: 5px;"
        "}"
        "QPushButton:hover {"
        "   background-color: #7CB342;"
        "}"
    );

    connect(easyBtn, &QPushButton::clicked, [=]() {
        gameSpeed = 200;
        if (gameRunning && !gamePaused) {
            gameTimer->start(gameSpeed);
        }
        qDebug() << "Difficulty: Easy, Speed:" << gameSpeed;
    });

    QPushButton* normalBtn = new QPushButton("Normal", this);
    normalBtn->move(710, 270);
    normalBtn->setFixedSize(50, 30);
    normalBtn->setFont(QFont("Arial", 10));
    normalBtn->setStyleSheet(
        "QPushButton {"
        "   background-color: #FF9800;"
        "   color: white;"
        "   border: none;"
        "   border-radius: 5px;"
        "}"
        "QPushButton:hover {"
        "   background-color: #F57C00;"
        "}"
    );

    connect(normalBtn, &QPushButton::clicked, [=]() {
        gameSpeed = 150;
        if (gameRunning && !gamePaused) {
            gameTimer->start(gameSpeed);
        }
        qDebug() << "Difficulty: Normal, Speed:" << gameSpeed;
    });

    QPushButton* hardBtn = new QPushButton("Hard", this);
    hardBtn->move(770, 270);
    hardBtn->setFixedSize(50, 30);
    hardBtn->setFont(QFont("Arial", 10));
    hardBtn->setStyleSheet(
        "QPushButton {"
        "   background-color: #F44336;"
        "   color: white;"
        "   border: none;"
        "   border-radius: 5px;"
        "}"
        "QPushButton:hover {"
        "   background-color: #D32F2F;"
        "}"
    );

    connect(hardBtn, &QPushButton::clicked, [=]() {
        gameSpeed = 100;
        if (gameRunning && !gamePaused) {
            gameTimer->start(gameSpeed);
        }
        qDebug() << "Difficulty: Hard, Speed:" << gameSpeed;
    });

    // Direction control buttons
    QPushButton* upBtn = new QPushButton("↑", this);
    upBtn->move(690, 320);
    upBtn->setFixedSize(40, 40);
    upBtn->setFont(QFont("Arial", 16, QFont::Bold));
    upBtn->setStyleSheet(
        "QPushButton {"
        "   background-color: #9C27B0;"
        "   color: white;"
        "   border: none;"
        "   border-radius: 5px;"
        "}"
        "QPushButton:hover {"
        "   background-color: #7B1FA2;"
        "}"
    );

    connect(upBtn, &QPushButton::clicked, [=]() {
        if (currentDirection != DOWN) {
            nextDirection = UP;
        }
        qDebug() << "Button: Direction Up";
    });

    QPushButton* downBtn = new QPushButton("↓", this);
    downBtn->move(690, 400);
    downBtn->setFixedSize(40, 40);
    downBtn->setFont(QFont("Arial", 16, QFont::Bold));
    downBtn->setStyleSheet(
        "QPushButton {"
        "   background-color: #9C27B0;"
        "   color: white;"
        "   border: none;"
        "   border-radius: 5px;"
        "}"
        "QPushButton:hover {"
        "   background-color: #7B1FA2;"
        "}"
    );

    connect(downBtn, &QPushButton::clicked, [=]() {
        if (currentDirection != UP) {
            nextDirection = DOWN;
        }
        qDebug() << "Button: Direction Down";
    });

    QPushButton* leftBtn = new QPushButton("←", this);
    leftBtn->move(650, 360);
    leftBtn->setFixedSize(40, 40);
    leftBtn->setFont(QFont("Arial", 16, QFont::Bold));
    leftBtn->setStyleSheet(
        "QPushButton {"
        "   background-color: #9C27B0;"
        "   color: white;"
        "   border: none;"
        "   border-radius: 5px;"
        "}"
        "QPushButton:hover {"
        "   background-color: #7B1FA2;"
        "}"
    );

    connect(leftBtn, &QPushButton::clicked, [=]() {
        if (currentDirection != RIGHT) {
            nextDirection = LEFT;
        }
        qDebug() << "Button: Direction Left";
    });

    QPushButton* rightBtn = new QPushButton("→", this);
    rightBtn->move(730, 360);
    rightBtn->setFixedSize(40, 40);
    rightBtn->setFont(QFont("Arial", 16, QFont::Bold));
    rightBtn->setStyleSheet(
        "QPushButton {"
        "   background-color: #9C27B0;"
        "   color: white;"
        "   border: none;"
        "   border-radius: 5px;"
        "}"
        "QPushButton:hover {"
        "   background-color: #7B1FA2;"
        "}"
    );

    connect(rightBtn, &QPushButton::clicked, [=]() {
        if (currentDirection != LEFT) {
            nextDirection = RIGHT;
        }
        qDebug() << "Button: Direction Right";
    });

    // Help label
    QLabel* helpLabel = new QLabel(this);
    helpLabel->setGeometry(630, 450, 160, 30);
    helpLabel->setText("Controls: Arrow Keys or WASD");
    helpLabel->setFont(QFont("Arial", 9));
    helpLabel->setStyleSheet("color: #666666;");

    // Debug label to show key states
    QLabel* debugLabel = new QLabel(this);
    debugLabel->setGeometry(630, 420, 160, 30);
    debugLabel->setText("Keys: ");
    debugLabel->setFont(QFont("Arial", 8));
    debugLabel->setStyleSheet("color: #888888;");

    // Update debug label periodically
    QTimer* debugTimer = new QTimer(this);
    connect(debugTimer, &QTimer::timeout, [=]() {
        QString status = QString("Keys: U:%1 D:%2 L:%3 R:%4 Focus:%5")
            .arg(keyUpPressed ? "1" : "0")
            .arg(keyDownPressed ? "1" : "0")
            .arg(keyLeftPressed ? "1" : "0")
            .arg(keyRightPressed ? "1" : "0")
            .arg(hasFocusNow ? "Yes" : "No");
        debugLabel->setText(status);
    });
    debugTimer->start(100);  // Update every 100ms
}

GameHall::~GameHall()
{
    if (gameTimer && gameTimer->isActive()) {
        gameTimer->stop();
    }
    delete ui;
}

void GameHall::initGame()
{
    snake.clear();

    // Initialize snake with length 3
    int startX = 5;
    int startY = 12;
    for (int i = 0; i < 3; i++) {
        snake.append(QPoint(startX - i, startY));
    }

    // Generate first food
    generateFood();

    // Reset game state
    currentDirection = RIGHT;
    nextDirection = RIGHT;
    score = 0;
    gameRunning = false;
    gamePaused = false;

    // Reset key states
    keyUpPressed = false;
    keyDownPressed = false;
    keyLeftPressed = false;
    keyRightPressed = false;
}

void GameHall::resetGame()
{
    snake.clear();

    // Initialize snake with length 3
    int startX = 5;
    int startY = 12;
    for (int i = 0; i < 3; i++) {
        snake.append(QPoint(startX - i, startY));
    }

    // Generate new food
    generateFood();

    // Reset game state
    currentDirection = RIGHT;
    nextDirection = RIGHT;
    score = 0;
    gameRunning = false;
    gamePaused = false;

    // Reset key states
    keyUpPressed = false;
    keyDownPressed = false;
    keyLeftPressed = false;
    keyRightPressed = false;
}

void GameHall::generateFood()
{
    bool validPosition = false;
    int foodX, foodY;

    while (!validPosition) {
        // Generate random position
        foodX = rand() % GRID_WIDTH;
        foodY = rand() % GRID_HEIGHT;

        // Check if position overlaps with snake
        validPosition = true;
        for (const QPoint& segment : snake) {
            if (segment.x() == foodX && segment.y() == foodY) {
                validPosition = false;
                break;
            }
        }
    }

    food = QPoint(foodX, foodY);
}

void GameHall::updateGame()
{
    if (!gameRunning || gamePaused) {
        return;
    }

    // Check key states to determine direction
    // This allows holding keys for continuous movement
    if (keyUpPressed && currentDirection != DOWN) {
        nextDirection = UP;
    } else if (keyDownPressed && currentDirection != UP) {
        nextDirection = DOWN;
    } else if (keyLeftPressed && currentDirection != RIGHT) {
        nextDirection = LEFT;
    } else if (keyRightPressed && currentDirection != LEFT) {
        nextDirection = RIGHT;
    }

    // Update direction
    currentDirection = nextDirection;

    // Calculate new head position
    QPoint newHead = snake.first();

    switch (currentDirection) {
    case UP:
        newHead.ry() -= 1;
        break;
    case DOWN:
        newHead.ry() += 1;
        break;
    case LEFT:
        newHead.rx() -= 1;
        break;
    case RIGHT:
        newHead.rx() += 1;
        break;
    }

    // Check wall collision
    if (newHead.x() < 0 || newHead.x() >= GRID_WIDTH ||
        newHead.y() < 0 || newHead.y() >= GRID_HEIGHT) {
        onGameOver();
        return;
    }

    // Check self collision
    for (const QPoint& segment : snake) {
        if (segment == newHead) {
            onGameOver();
            return;
        }
    }

    // Add new head to snake
    snake.prepend(newHead);

    // Check if food is eaten
    if (newHead == food) {
        score += 10;
        generateFood();
        qDebug() << "Food eaten! Score:" << score;
    } else {
        // Remove tail if no food eaten
        snake.removeLast();
    }

    // Update display
    update();
}

void GameHall::onGameOver()
{
    gameRunning = false;
    if (gameTimer) {
        gameTimer->stop();
    }

    // Reset key states
    keyUpPressed = false;
    keyDownPressed = false;
    keyLeftPressed = false;
    keyRightPressed = false;

    QMessageBox::information(this, "Game Over",
        QString("Game Over!\nYour Score: %1").arg(score));

    qDebug() << "Game over, score:" << score;
}

void GameHall::handleKeyPress(int key)
{
    if (!gameRunning || gamePaused) {
        return;
    }

    switch (key) {
    case Qt::Key_Up:
    case Qt::Key_W:
        if (currentDirection != DOWN) {
            nextDirection = UP;
            keyUpPressed = true;
            qDebug() << "Key pressed: Up/W";
        }
        break;

    case Qt::Key_Down:
    case Qt::Key_S:
        if (currentDirection != UP) {
            nextDirection = DOWN;
            keyDownPressed = true;
            qDebug() << "Key pressed: Down/S";
        }
        break;

    case Qt::Key_Left:
    case Qt::Key_A:
        if (currentDirection != RIGHT) {
            nextDirection = LEFT;
            keyLeftPressed = true;
            qDebug() << "Key pressed: Left/A";
        }
        break;

    case Qt::Key_Right:
    case Qt::Key_D:
        if (currentDirection != LEFT) {
            nextDirection = RIGHT;
            keyRightPressed = true;
            qDebug() << "Key pressed: Right/D";
        }
        break;

    case Qt::Key_Space:
        // Space to pause/resume
        if (gameRunning) {
            gamePaused = !gamePaused;
            if (gamePaused) {
                if (gameTimer) gameTimer->stop();
                // Clear key states when paused
                keyUpPressed = keyDownPressed = keyLeftPressed = keyRightPressed = false;
                qDebug() << "Game paused with Space";
            } else {
                if (gameTimer) gameTimer->start(gameSpeed);
                qDebug() << "Game resumed with Space";
            }
        }
        break;

    case Qt::Key_Escape:
        qDebug() << "Escape key pressed, exiting game";
        this->close();
        emit returnToMain();
        break;

    default:
        break;
    }
}

void GameHall::keyPressEvent(QKeyEvent *event)
{
    // Check if this is an auto-repeat event
    if (event->isAutoRepeat()) {
        // For snake game, we want to handle auto-repeat
        // so the snake keeps moving when key is held
        handleKeyPress(event->key());
        event->accept();
        return;
    }

    // Handle the key press
    handleKeyPress(event->key());

    // Accept the event to prevent further propagation
    event->accept();

    qDebug() << "Key event received, key code:" << event->key()
             << ", text:" << event->text();
}

void GameHall::keyReleaseEvent(QKeyEvent *event)
{
    // Handle key release to clear key states
    switch (event->key()) {
    case Qt::Key_Up:
    case Qt::Key_W:
        keyUpPressed = false;
        qDebug() << "Key released: Up/W";
        break;

    case Qt::Key_Down:
    case Qt::Key_S:
        keyDownPressed = false;
        qDebug() << "Key released: Down/S";
        break;

    case Qt::Key_Left:
    case Qt::Key_A:
        keyLeftPressed = false;
        qDebug() << "Key released: Left/A";
        break;

    case Qt::Key_Right:
    case Qt::Key_D:
        keyRightPressed = false;
        qDebug() << "Key released: Right/D";
        break;

    default:
        break;
    }

    event->accept();
}

void GameHall::focusInEvent(QFocusEvent *event)
{
    Q_UNUSED(event);
    hasFocusNow = true;
    qDebug() << "Game window gained focus";
}

void GameHall::focusOutEvent(QFocusEvent *event)
{
    Q_UNUSED(event);
    hasFocusNow = false;
    // Clear key states when focus is lost
    keyUpPressed = keyDownPressed = keyLeftPressed = keyRightPressed = false;
    qDebug() << "Game window lost focus, keys cleared";
}

void GameHall::showEvent(QShowEvent *event)
{
    QWidget::showEvent(event);
    // Force focus when window is shown
    this->setFocus();
    hasFocusNow = true;
    qDebug() << "Game window shown, focus set and forced";

    // For embedded systems, try to grab keyboard input
    // This might help with keyboard issues on embedded platforms
    this->grabKeyboard();
    qDebug() << "Attempted to grab keyboard";
}

void GameHall::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // Draw background
    painter.fillRect(0, 0, width(), height(), QColor(240, 240, 240));

    // Draw game area border
    painter.setPen(QPen(QColor(180, 180, 180), 2));
    painter.drawRect(10, 10, GRID_WIDTH * GRID_SIZE, GRID_HEIGHT * GRID_SIZE);

    // Draw game area background
    painter.fillRect(11, 11, GRID_WIDTH * GRID_SIZE - 2, GRID_HEIGHT * GRID_SIZE - 2,
                    QColor(255, 255, 255));

    // Draw grid lines
    painter.setPen(QPen(QColor(230, 230, 230), 1));
    for (int i = 0; i <= GRID_WIDTH; i++) {
        painter.drawLine(10 + i * GRID_SIZE, 10, 10 + i * GRID_SIZE, 10 + GRID_HEIGHT * GRID_SIZE);
    }
    for (int i = 0; i <= GRID_HEIGHT; i++) {
        painter.drawLine(10, 10 + i * GRID_SIZE, 10 + GRID_WIDTH * GRID_SIZE, 10 + i * GRID_SIZE);
    }

    // Draw snake
    for (int i = 0; i < snake.size(); i++) {
        const QPoint& segment = snake[i];

        // Snake head
        if (i == 0) {
            QColor headColor;
            switch (currentDirection) {
            case UP:
                headColor = QColor(0, 150, 0);
                break;
            case DOWN:
                headColor = QColor(0, 180, 0);
                break;
            case LEFT:
                headColor = QColor(0, 120, 0);
                break;
            case RIGHT:
                headColor = QColor(0, 200, 0);
                break;
            }

            painter.setBrush(headColor);
            painter.setPen(QPen(QColor(0, 100, 0), 1));

            painter.drawEllipse(10 + segment.x() * GRID_SIZE + 2,
                               10 + segment.y() * GRID_SIZE + 2,
                               GRID_SIZE - 4, GRID_SIZE - 4);

            // Draw eyes
            painter.setBrush(Qt::white);
            if (currentDirection == RIGHT) {
                painter.drawEllipse(10 + segment.x() * GRID_SIZE + GRID_SIZE - 6,
                                   10 + segment.y() * GRID_SIZE + 4, 4, 4);
                painter.drawEllipse(10 + segment.x() * GRID_SIZE + GRID_SIZE - 6,
                                   10 + segment.y() * GRID_SIZE + GRID_SIZE - 8, 4, 4);
            } else if (currentDirection == LEFT) {
                painter.drawEllipse(10 + segment.x() * GRID_SIZE + 2,
                                   10 + segment.y() * GRID_SIZE + 4, 4, 4);
                painter.drawEllipse(10 + segment.x() * GRID_SIZE + 2,
                                   10 + segment.y() * GRID_SIZE + GRID_SIZE - 8, 4, 4);
            } else if (currentDirection == UP) {
                painter.drawEllipse(10 + segment.x() * GRID_SIZE + 4,
                                   10 + segment.y() * GRID_SIZE + 2, 4, 4);
                painter.drawEllipse(10 + segment.x() * GRID_SIZE + GRID_SIZE - 8,
                                   10 + segment.y() * GRID_SIZE + 2, 4, 4);
            } else if (currentDirection == DOWN) {
                painter.drawEllipse(10 + segment.x() * GRID_SIZE + 4,
                                   10 + segment.y() * GRID_SIZE + GRID_SIZE - 6, 4, 4);
                painter.drawEllipse(10 + segment.x() * GRID_SIZE + GRID_SIZE - 8,
                                   10 + segment.y() * GRID_SIZE + GRID_SIZE - 6, 4, 4);
            }
        }
        // Snake body
        else {
            painter.setBrush(QColor(0, 200, 0));
            painter.setPen(QPen(QColor(0, 150, 0), 1));

            painter.drawEllipse(10 + segment.x() * GRID_SIZE + 2,
                               10 + segment.y() * GRID_SIZE + 2,
                               GRID_SIZE - 4, GRID_SIZE - 4);
        }
    }

    // Draw food
    painter.setBrush(QColor(255, 50, 50));
    painter.setPen(QPen(QColor(200, 0, 0), 1));
    painter.drawEllipse(10 + food.x() * GRID_SIZE + 4,
                       10 + food.y() * GRID_SIZE + 4,
                       GRID_SIZE - 8, GRID_SIZE - 8);

    // Draw score and info panel
    painter.setPen(Qt::black);
    QFont font("Arial", 14, QFont::Bold);
    painter.setFont(font);

    // Score display
    painter.drawText(630, 40, "Score:");
    painter.drawText(630, 70, QString::number(score));

    // Length display
    painter.drawText(630, 110, "Length:");
    painter.drawText(630, 140, QString::number(snake.size()));

    // Game status display
    if (!gameRunning) {
        painter.setPen(QColor(100, 100, 100));
        painter.drawText(630, 180, "Not Started");
    } else if (gamePaused) {
        painter.setPen(QColor(255, 140, 0));
        painter.drawText(630, 180, "Paused");
    } else {
        painter.setPen(QColor(0, 150, 0));
        painter.drawText(630, 180, "Playing...");
    }

    // Draw control area border
    painter.setPen(QPen(QColor(200, 200, 200), 1));
    painter.drawRect(620, 0, 180, 480);
}
