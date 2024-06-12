#include <iostream>
#include <windows.h>
#include <fstream>

using namespace std;

class IDocument
{
public:
    virtual void DocIsOpen(ifstream& file) = 0;
    virtual void DocIsClose(ofstream& filee) = 0;
};

class RealDocument : public IDocument
{
public:
    RealDocument()
    {
        cout << "Create document\n";
        Sleep(3000);
    }

    void DocIsOpen(ifstream& infile) override
    {
        if (infile.is_open())
            cout << "Document is open" << endl;
    }
    void DocIsClose(ofstream& outfile) override
    {
        if (!outfile.is_open())
            cout << "Document is close" << endl;
    }
};

class DocumentProxy : public IDocument
{
    RealDocument* realDocument;
public:
    DocumentProxy()
    {
        realDocument = nullptr;

       
        ofstream file("doc.txt");
        if (file.is_open())
        {
            file << "Some Text";
            file.close();
        }
    }
    ~DocumentProxy()
    {
        delete realDocument;
    }
    void DocIsOpen(ifstream& infile) override
    {
        if (infile.is_open())
            cout << "Document is open" << endl;
    }
    void DocIsClose(ofstream& outfile) override
    {
        if (!outfile.is_open())
            cout << "Document is close" << endl;
    }
};

void client(IDocument* p, ofstream& filee, ifstream& file)
{
    p->DocIsOpen(file);
    p->DocIsClose(filee);
}

int main()
{
    IDocument* p = new DocumentProxy();
    ifstream file("doc.txt");
    ofstream file1("doc.txt");
    client(p, file1, file);

    
}

