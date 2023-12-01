//
// Created by sander on 27/09/2023.
//

#ifndef THESIS_STINT_H
#define THESIS_STINT_H

class STint {
public:
    STint(int val_t, bool infArrival);
    STint();
    bool isinfArrival();
    STint min(STint a, STint b);
    STint less_or_equal(STint a, STint b);
    STint not_equal(STint a, STint b);
    STint exclusive_min(STint a, STint b);
    STint less_than(STint a, STint b);
    STint max(STint a, STint b);
    STint exclusive_max(STint a, STint b);
    STint greater_or_equal(STint a, STint b);
    STint equal(STint a, STint b);
    STint greater_than(STint a, STint b);
    print(STint a);
    STint add_variable(STint a, STint b);
    STint add_constant(int b);
    int get_int();
    bool get_bool();
private:
    int value;
    bool infArrival;
};


#endif //THESIS_STINT_H
