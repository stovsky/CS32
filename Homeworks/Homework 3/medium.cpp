class Medium {
public:
    Medium(string id) : m_id(id) {}
 
    virtual ~Medium() {
        cout << m_id << "." << endl;
    }
    
    
    string id() const {
        return m_id;
    }
    
    virtual string transmit(string msg) const {
        string s = "text: ";
        s += msg;
        return s;
    }
    
    virtual string connect() const = 0;
    
private:
    
    string m_id;
    
};

class TwitterAccount : public Medium {
public:
    TwitterAccount(string id) : Medium(id) {}
    
    virtual string connect() const {
        return "Tweet";
    }
    
    virtual ~TwitterAccount() {
        cout << "Destroying the Twitter account ";
    }
};

class Phone : public Medium {
public:
    Phone(string id, CallType type) : Medium(id), m_type(type) {}
    
    virtual string connect() const {
        return "Call";
    }
    
    virtual string transmit(string msg) const {
        string s;
        if (m_type == TEXT) {
            s = "text: ";
            s += msg;
        }
        else {
            s = "voice: ";
            s += msg;
        }
        return s;
    }
    
    virtual ~Phone() {
        cout << "Destroying the phone ";
    }
    
private:
    
    CallType m_type;
    
};

class EmailAccount : public Medium {
public:
    EmailAccount(string id) : Medium(id) {}
    
    virtual string connect() const {
        return "Email";
    }
    
    virtual ~EmailAccount() {
        cout << "Destroying the email account ";
    }
};
