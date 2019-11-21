//
// Created by mbdin on 11/19/2019.
//
#include <iostream>
#include <deque>

using namespace std;

#ifndef OS_P3_LRU_H
#define OS_P3_LRU_H

class LRU {
private:
    int page_faults = 0, page_frames;
    deque<int> ref_string;
    bool found =  false;

public:
    int get_faults() {
        return this->page_faults;
    }

    void set_frames(int page_frames) {
        this->page_frames = page_frames;
    }

    void set_string(deque<int> ref_string) {
        this->ref_string = ref_string;
    }

    void load_pages() {
        cout << "Last Recently Used" << endl;
        int page_table[page_frames], counter[page_frames];

        for (int i = 0; i < page_frames; i++) {
            page_table[i] = ref_string.front();
            counter[i] = 0;
            page_faults++;
            ref_string.pop_front();

            for (int j = i - 1; j > -1; j--)
                counter[j]++;

            cout << page_table[i] << "\t";
        }
        cout << endl;

        int page_index = 0, counter_index, page;
        while (!ref_string.empty()) {
            page = ref_string.front();
            counter_index = 0;

            for (int i = 0; i < page_frames; i++) {
                if (page == page_table[i]) {
                    found = true;
                    counter[i] = 0;
                    //cout << "MATCH" << endl;
                }
                else {
                    if (counter[i] > counter[counter_index]) {
                        page_index = i;
                        counter_index = i;
                    }
                    counter[i]++;
                }
            }

            if (!found) {
                page_table[page_index] = page;
                counter[counter_index] = 0;
                page_faults++;
            }

            ref_string.pop_front();
            found = false;
        }

        cout << "Page faults -\t" << page_faults << endl << endl;
    }
};

#endif //OS_P3_LRU_H
