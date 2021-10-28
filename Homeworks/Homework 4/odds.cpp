
void removeOdds(vector<int>& v)
    {
        for (vector<int>::iterator p = v.begin(); p < v.end(); p++) {
            if (*p % 2 == 1) {
                p = v.erase(p);
                p--;
            }
        }
    
    }

