void listAll(string path, const Domain* d) // two-parameter overload
{
    const vector<Domain*> temp = d->subdomains();
    if (temp.size() == 0) {
        cout << path << endl;
        return;
    }
    else {
        int i = 0;
        while (i < temp.size()) {
            string s;
            if (path == "") {
                s = temp[i]->label();
            }
            else {
                s = temp[i]->label() + "." + path;
            }
            listAll(s, temp[i]);
            i++;
        }
    }
}