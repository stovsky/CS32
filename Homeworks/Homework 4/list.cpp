
void listAll(string path, const MenuItem* m) // two-parameter overload
{
    
    if (m->menuItems() == nullptr || m->menuItems()->size() == 0) return;

    for (vector<MenuItem*>::const_iterator it = m->menuItems()->begin(); it != m->menuItems()->end(); it++) {
        cout << path << (*it)->name() << endl;
        listAll(path + (*it)->name() + "/", *it);
    }
    
}

