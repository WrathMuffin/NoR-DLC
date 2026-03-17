#pragma once

enum Direction { DIR_NONE, DIR_UP, DIR_DOWN, DIR_LEFT, DIR_RIGHT };

class Snake {
public:
    static const int MAX_LEN = 512;

    Snake(int startX, int startY, int cellSize);

    void SetDirection(Direction newDir);
    void Move();
    bool CheckSelfCollision() const;
    bool CheckWallCollision(int cols, int rows) const;

    int  GetHeadX()  const { return bodyX[0]; }
    int  GetHeadY()  const { return bodyY[0]; }
    int  GetLength() const { return length; }
    void Grow()            { length++; }

    void Draw(int cellSize) const;

    int bodyX[MAX_LEN];
    int bodyY[MAX_LEN];

private:
    int length;
    int cellSize;
    Direction dir;
    Direction nextDir;
};