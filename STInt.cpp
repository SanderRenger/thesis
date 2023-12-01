#include <iostream>
using namespace std;
#include "STint.h"

STint::STint(int val_t, bool infArrival_t){
    value = val_t;
    infArrival = infArrival_t;
};

STint::STint(){
    value = 0;
    infArrival = true;
};

// Getter for the "never arrive" state
STint STint::min(STint a, STint b) {
        if (a.infArrival && b.infArrival) {
            return STint{0,true};
        }
        if (!a.infArrival && b.infArrival) {
            return STint{a.value,false};
        }
        if (a.value <= b.value) {
            return {a.value,false};
        }
        return {b.value,false};
    };

STint STint::less_or_equal(STint a, STint b) {
        if (a.infArrival && b.infArrival) {
            return STint{0,true};
        }
        if (!a.infArrival && b.infArrival) {
            return STint{a.value,false};
        }
        if (a.value <= b.value) {
            return STint{a.value,false};
        }
        return STint{0,true};
    };

STint STint::not_equal(STint a, STint b) {
        if (a.infArrival || b.infArrival) {
            return STint{0,true};
        }

        if (a.value != b.value) {
            return STint{a.value,false};
        }
        return STint{0,true};
    };

STint STint::exclusive_min(STint a, STint b) {
        if (a.infArrival && b.infArrival) {
            return STint{0,true};
        }
        if (!a.infArrival && b.infArrival) {
            return STint{a.value,false};
        }
        if (a.value < b.value) {
            return STint{a.value,false};
        }
        return STint{b.value,false};
    };

STint STint::less_than(STint a, STint b) {
        if (a.infArrival || b.infArrival || a.value == b.value) {
            return STint{0,true};
        }
        if (!a.infArrival && b.infArrival){
            return STint{a.value,false};
        }
        if (a.value < b.value) {
            return STint{a.value,false};
        }
        return STint{0,true};
    };

STint STint::max(STint a, STint b) {
        if (a.infArrival || b.infArrival) {
            return STint{0,true};
        }

        if (a.value >= b.value) {
            return STint{a.value,false};
        }
        return STint{b.value,false};
    };

STint STint::exclusive_max(STint a, STint b) {
        if (a.infArrival || b.infArrival || a.value == b.value) {
            return STint{0, true};
        }

        if (a.value > b.value) {
            return STint{a.value, false};
        }
        return STint{b.value, false};
    };

STint STint::greater_or_equal(STint a, STint b) {
        if (a.infArrival || b.infArrival || a.value == b.value) {
            return STint{0, true};
        }

        if (a.value >= b.value) {
            return STint{a.value, false};
        }
        return STint{0, true};
    };

STint STint::equal(STint a, STint b) {
        if (a.infArrival || b.infArrival || a.value == b.value) {
            return STint{0, true};
        }

        if (a.value == b.value) {
            return STint{a.value, false};
        }
        return STint{0, true};
    };

STint STint::greater_than(STint a, STint b) {
        if (a.infArrival || b.infArrival || a.value == b.value) {
            return STint{0, true};
        }

        if (a.value > b.value) {
            return STint{a.value, false};
        }
        return STint{0, true};
    };

STint::print(STint a){
        if (a.infArrival) {
            cout << "infinite" << endl;
        }
        cout << int(a.value) << endl;
        return 0;
    };
STint STint::add_variable(STint a, STint b) {
        if (a.infArrival || b.infArrival) {
            return STint{0,true};
        }
        return STint{a.value+b.value,false};
    };

STint STint::add_constant(int b) {
        if (infArrival) {
            return {0,true};
        }
        return STint{value+b,false};
    };
int STint::get_int(){
    return value;
}
bool STint::get_bool(){
    return infArrival;
}