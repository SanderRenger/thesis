#include <iostream>
using namespace std;

class STint {
private:
    int value;
    bool infArrival;

public:
    STint(int val = 0, bool infArrival = false) : value(val), infArrival(infArrival) {}

    // Getter for the "never arrive" state
    bool isinfArrival() const {
        return infArrival;
    }

    // Conversion operator to int
    operator int() const {
        if (infArrival) {
            // Return a special value for "never arrive" state, you can choose any value you like.
            return true;
        }
        return value;
    }

    static STint min(const STint& a, const STint& b) {
        if (a.infArrival && b.infArrival) {
            return STint(0,true);
        }
        if (!a.infArrival && b.infArrival) {
            return STint(a,false);
        }
        if (a.value <= b.value) {
            return STint(a,false);
        }
        return STint(b,false);
    }

    static STint less_or_equal(const STint& a, const STint& b) {
        if (a.infArrival && b.infArrival) {
            return STint(0,true);
        }
        if (!a.infArrival && b.infArrival) {
            return STint(a,false);
        }
        if (a.value <= b.value) {
            return STint(a,false);
        }
        return STint(0,true);
    }
    static STint not_equal(const STint& a, const STint& b) {
        if (a.infArrival || b.infArrival) {
            return STint(0,true);
        }

        if (a.value != b.value) {
            return STint(a,false);
        }
        return STint(0,true);
    }

    static STint exclusive_min(const STint& a, const STint& b) {
        if (a.infArrival && b.infArrival) {
            return STint(0,true);
        }
        if (!a.infArrival && b.infArrival) {
            return STint(a,false);
        }
        if (a.value < b.value) {
            return STint(a,false);
        }
        return STint(b,false);
    }

    static STint less_than(const STint& a, const STint& b) {
        if (a.infArrival || b.infArrival || a.value == b.value) {
            return STint(0,true);
        }
        if (!a.infArrival && b.infArrival){
            return STint(a,false);
        }
        if (a.value < b.value) {
            return STint(a,false);
        }
        return STint(0,true);
    }

    static STint max(const STint& a, const STint& b) {
        if (a.infArrival || b.infArrival) {
            return STint(0,true);
        }

        if (a.value >= b.value) {
            return STint(a,false);
        }
        return STint(b,false);
    }

    static STint exclusive_max(const STint& a, const STint& b) {
        if (a.infArrival || b.infArrival || a.value == b.value) {
            return STint(0, true);
        }

        if (a.value > b.value) {
            return STint(a, false);
        }
        return STint(b, false);
    }

    static STint greater_or_equal(const STint& a, const STint& b) {
        if (a.infArrival || b.infArrival || a.value == b.value) {
            return STint(0, true);
        }

        if (a.value >= b.value) {
            return STint(a, false);
        }
        return STint(0, true);
    }

    static STint equal(const STint& a, const STint& b) {
        if (a.infArrival || b.infArrival || a.value == b.value) {
            return STint(0, true);
        }

        if (a.value == b.value) {
            return STint(a, false);
        }
        return STint(0, true);
    }

    static STint greater_than(const STint& a, const STint& b) {
        if (a.infArrival || b.infArrival || a.value == b.value) {
            return STint(0, true);
        }

        if (a.value > b.value) {
            return STint(a, false);
        }
        return STint(0, true);
    }

    static STint print(const STint& a){
        if (a.infArrival) {
            cout << "infinite" << endl;
            return 0;
        }
        cout << int(a) << endl;
        return 0;
    }
    static STint add_variable(const STint& a, const STint& b) {
        if (a.infArrival || b.infArrival) {
            return STint(0,true);
        }
        return STint(a+b,false);
    }

    static STint add_constant(const STint& a, int b) {
        if (a.infArrival) {
            return STint(0,true);
        }
        return STint(a+b,false);
    }
};


int main() {
    STint temp1(40);
    STint temp2(0);
    STint temp3(0,true);

    STint result1 = STint::min(temp1,temp2);
    STint::print(result1);



}
