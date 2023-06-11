class Gnu {
public:
    int id;
    Gnu(int id);
    void operator()();
};

ostream& operator<<(ostream & os, const Gnu & g);
