#include <iostream>
#include <memory>
#include <functional>

using namespace std;

struct A {
    int data;

};

struct B {
    B() { b = new int[4]; }

    int * b;
    ~B() { delete [] b; }
    B(const B &) = delete;
    void operator= (const B & ) = delete;
};

struct BhasA;

struct AhasB {
    AhasB(shared_ptr<BhasA> b) : m_b(b)  {
        resource = new int[4];
    };

    weak_ptr<BhasA> m_b;
    int * resource;

    ~AhasB() {delete [] resource;}
    AhasB(const AhasB &) = delete;
    void operator=(const AhasB &) = delete;
};

struct BhasA {
    BhasA() {resource = new int[4];};

    shared_ptr<AhasB> m_a;
    int * resource;

    ~BhasA() {delete [] resource;}
    BhasA(const BhasA &) = delete;
    void operator=(const BhasA &) = delete;
};

void foo(unique_ptr<A> p) {
    cout << p->data << endl;
}

void foo2(shared_ptr<A> p) {
    cout << p->data << endl;
}

int main(){
    unique_ptr<A> pa(new A {4} );
    cout << pa -> data << endl;

    foo(move(pa));
    //Running valgrind gives
    //==892== All heap blocks were freed -- no leaks are possible

    shared_ptr<A> sa(new A {5});
    cout << sa -> data << endl;
    foo2(sa);            // All heap blocks were freed -- no leaks are possible
    //foo2(move(sa));    // All heap blocks were freed -- no leaks are possible

    weak_ptr<A> wa = sa;
    cout << wa.lock()->data;

    shared_ptr<BhasA> bptr(new BhasA);
    shared_ptr<AhasB> aptr(new AhasB(bptr));
    bptr->m_a=aptr;


    //unique_ptr<B> pb(new B[2]); //LEAK SUMMARY: definitely lost: 24 bytes in 1 blocks
    auto deleter = [&](B* b) {delete [] b;}; // Used https://stackoverflow.com/questions/10319009/unique-ptrt-lambda-custom-deleter-for-array-specialization
    unique_ptr<B, decltype(deleter)> pb2(new B[2], deleter);

    function<void(B*)> fb = [&](B* b) {delete [] b;};
    //unique_ptr<B, function<void(B*)> > pb1(new B[2],  fb);  // I'm not sure if you ment just using fb or declaring the lambda inside the parameter, I made both
    unique_ptr<B, function<void(B*)> > pb1(new B[2],  [&](B* b) {delete [] b;});

    return 0;
}
