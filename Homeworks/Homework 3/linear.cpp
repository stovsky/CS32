bool allTrue(const string a[], int n)
{
    if (n <= 0) return true;
    if (n == 1) return somePredicate(a[0]);

    return somePredicate(a[0]) && allTrue(a + 1, n - 1);
    
}

int countFalse(const string a[], int n)
{
    int counter = 0;
    if (n <= 0) return 0;
    if (n == 1) {
        if (somePredicate(a[0])) return 0;
        else return 1;
    }
    if (!somePredicate(a[0])) counter++;
    return counter + countFalse(a + 1, n - 1);
}

int firstFalse(const string a[], int n)
{
    if (n <= 0) return -1;
    if (!somePredicate(a[0])) return 0;
    
    int i = firstFalse(a + 1, n - 1);
    if (i == -1) return -1;
    
    return i + 1;
    
}

int indexOfLeast(const string a[], int n)
{
    if (n <= 0) return -1;
    if (n == 1) return 0;
    
    int i = indexOfLeast(a, n - 1);
    
    if (a[i] <= a[n - 1]) return i;
    else return n - 1;
     

}

bool includes(const string a1[], int n1, const string a2[], int n2)
{
    if (n2 <= 0) return true;
    if (n1 <= 0 || n1 < n2) return false;
    
    if (a1[0] == a2[0]) return includes(a1 + 1, n1 - 1, a2 + 1, n2 - 1);
    else return includes(a1 + 1, n1 - 1, a2, n2);
    
}
