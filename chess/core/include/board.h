

class Board {


    private:
        enum {board_size = 8};
        char board_[board_size + 1][board_size + 1];

    public:
        Board();
        void draw();
};
