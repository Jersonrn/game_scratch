


class Component {
    public:
        Component();
        virtual ~Component();
};




class Velocity: public Component {
    public:
        float x;
        float y;

        Velocity(float x, float y);
        virtual ~Velocity();
};

class Position: public Component {
    public:
        float x;
        float y;

        Position(float x, float y);
        virtual ~Position();
};
