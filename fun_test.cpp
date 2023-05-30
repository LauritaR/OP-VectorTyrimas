#include "mylib.h"
#include "fun.h"
int main()
{   
    SetConsoleOutputCP(CP_UTF8);
    string ats;
    cout<<"Kaip norėtumėte patikrinti programas?"<<endl;
    cout<<"Funkcionalumo testavimas(f)\nEfektyvumo analizė(e)\nKonteinerių atmnities perskirstymas(p)\n"<<' ';
    cin>>ats;
    if(ats=="f")
    {
        vector<int> orig;
        vect<int> recr;
        cout<<"\nTikrinama reserve(1000) funkcija\n";//reserve
        cout<<"\n std::vector capacity() prieš reserve():"<<orig.capacity();
        orig.reserve(1000);
        cout<<"\n std::vector capacity() po resesrve(): "<<orig.capacity();

        cout<<"\n vect capacity() prieš reserve(): "<<recr.capacity();
        recr.reserve(1000);
        cout<<"\n vect capacity() po reserve(): "<<recr.capacity();


        cout<<"\nTikrinama insert() funkcija\n";//insert

        vector<int> stdVec={1,2,3};
        cout<<"\nstd::vector prieš insert(): ";
        for(const auto& elem:stdVec){cout<<elem<<" ";}
        vector<int>::iterator stdIter=stdVec.begin()+1;
        stdVec.insert(stdIter,4);
        cout<<"\nstd::vector po insert(): ";
        for(const auto& elem:stdVec){cout<<elem<<" ";}

        vect<int> myVect= {1,2,3};
        cout<<"\nvect prieš insert(): ";
        for(const auto& elem:myVect){cout<<elem<<" ";}
        vect<int>::iterator myIter=myVect.begin()+1;
        myVect.insert(myIter,4);
        cout<<"\nstd::vector po insert(): ";
        for(const auto& elem:myVect){cout<<elem<<" ";}
        cout<<endl;

        cout<<"\nTikrinama erase() funkcija\n";//erase

        cout<<"\nstd::vector prieš erase(): ";
        for(const auto& elem:stdVec){cout<<elem<<" ";}

        stdVec.erase(stdVec.begin()+1);
        cout<<"\nstd::vector po erase(): ";
        for(const auto& elem:stdVec){cout<<elem<<" ";}

        cout<<"\nvect prieš erase(): ";
        for(const auto& elem:myVect){cout<<elem<<" ";}
        myVect.erase(myVect.begin()+1);
        cout<<"\nvect po erase(): ";
        for(const auto& elem:myVect){cout<<elem<<" ";} 
        cout<<endl;
        cout<<"\nTikrinama clear() funkcija\n";//clear()
        cout<<"\nstd::vector prieš clear(): ";
        for(const auto& elem:stdVec){cout<<elem<<" ";}

        stdVec.clear();
        cout<<"\nstd::vector po clear(): ";
        for(const auto& elem:stdVec){cout<<elem<<" ";}

        cout<<"\nvect prieš clear(): ";
        for(const auto& elem:myVect){cout<<elem<<" ";}
        myVect.clear();
        cout<<"\nvect po clear(): ";
        for(const auto& elem:myVect){cout<<elem<<" ";} 
        cout<<endl;

        cout<<"\nTikrinama shrink_to_fit() funkcija\n";//shrink_to_fit()
        orig.push_back(1);orig.push_back(3);orig.push_back(5);
        cout<<"\nstd::vector capacity() prieš shrink_to_fit(): "<<orig.capacity();
        orig.shrink_to_fit();
        cout<<"\nstd::vector capacity() po shrink_to_fit(): "<<orig.capacity();

        recr.push_back(1);recr.push_back(3);recr.push_back(5);
        cout<<"\nvect capacity() prieš shrink_to_fit(): "<<recr.capacity();
        recr.shrink_to_fit();
        cout<<"\nvect capacity() po shrink_to_fit(): "<<recr.capacity();
        cout<<endl;
        for(const auto& elem: recr){cout<<elem<<" ";}//push_back demonstravimas
        cout<<endl;

        
        cout<<"\nTikrinamas operator[]\n";//operator[]
        cout<<"\nstd::vector prieš: ";
        for(const auto& elem:orig){cout<<elem<<" ";}
         orig[2]=9;
        cout<<"\nstd::vector po: ";
        for(const auto& elem:orig){cout<<elem<<" ";}
        cout<<endl;
        cout<<"\nvect prieš : ";
        for(const auto& elem:recr){cout<<elem<<" ";}
        recr[2]=9;
        cout<<"\nstd::vector po insert(): ";
        for(const auto& elem:recr){cout<<elem<<" ";}
        cout<<endl;
       
       cout<<"\nTikrinamas push_back su Studentuko objektais\n"<<endl;
       vector<studentukas> foreign;
       studentukas c1("Studentas","Studentaitis",{5,4,10},7);
       studentukas c2("Studentė", "Studentaitė",{10,8,10},6);
       studentukas c3("Richard", "Feynman",{10,10,10},10);
       foreign.push_back(c1);
       foreign.push_back(c2);
       foreign.push_back(c3);
       cout<<c1<<endl;
       cout<<c2<<endl;
       cout<<c3<<endl;
       vect<studentukas> my;
       studentukas s1("Studentas","Studentaitis",{5,4,10},7);
       studentukas s2("Studentė", "Studentaitė",{10,8,10},6);
       studentukas s3("Richard", "Feynman",{10,10,10},10);
       my.push_back(s1);
       my.push_back(s2);
       my.push_back(s3);
       cout<<s1<<endl;
       cout<<s2<<endl;
       cout<<s3<<endl;


        cout<<"Copy constructor ir copy assignment tikrinimas:"<<endl;
        vect<int> v1;
        v1.push_back(1);v1.push_back(2);v1.push_back(3);
        
        vect<int> v2(v1); // Copy constructor
        vect<int> v3;
        v3 = v1; // Copy assignment operator
        
        cout << "v1: ";
        for (int i : v1) {
            cout << i << " ";
        }
        cout << endl;
        
        cout << "v2: ";
        for (int i : v2) {
            cout << i << " ";
        }
        cout << endl;
        
        cout << "v3: ";
        for (int i : v3) {
            cout << i << " ";
        }
       cout << endl;

    cout << endl;

    cout<<"Move constructor ir move assigment tikrinimas: "<<endl;
    {
        vect<int> v4;
        v4.push_back(1);v4.push_back(2);v4.push_back(3);
        
        vect<int> v5(std::move(v4)); // Move constructor
        vect<int> v6;
        v6 = std::move(v5); // Move assignment operator
        
        cout << "v4: ";
        for (int i : v4) {
            cout << i << " ";
        }
        cout << endl;
        
        cout << "v5: ";
        for (int i : v5) {
            cout << i << " ";
        }
        cout << endl;
        
        cout << "v6: ";
        for (int i : v6) {
           cout << i << " ";
        }
        cout <<endl;
    }
    cout <<endl;
    }

    else if(ats=="e")//spartos analize
    {
        unsigned int sz = 10000;  // 100000, 1000000, 10000000, 100000000
        vector<int> v1;
        vect<int> v2;
        for(int i=0;i<5;i++)
        {
        auto start = std::chrono::high_resolution_clock::now(); 
                for (int i = 1; i <= sz; ++i)
                v1.push_back(i);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> difference = end - start;
        cout <<"std::vector programos laikas su "<<sz<<" elementų "<< difference.count() << " s\n"; 

             start = std::chrono::high_resolution_clock::now(); 
                for (int i = 1; i <= sz; ++i)
                v2.push_back(i);
             end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> difference2 = end - start;
        cout <<"vect programos laikas su " <<sz<<" elementų "<<difference2.count() << " s\n";
        cout<<endl;
        sz*=10; 
        v1.clear();
        v2.clear();
        }
    }
    else if(ats=="p")
    {
        vector<int> stdVec;
        vect<int> myVec;
        unsigned int sz=100000000;
        int alloc_count=0,temp_cpct_std=0,temp_cpct_my=0;
        for(int i=0;i<=sz;++i)
        {
            if(stdVec.capacity()!=temp_cpct_std)
            {
                temp_cpct_std=stdVec.capacity();
                alloc_count++;
            }
            stdVec.push_back(i);
        }
        cout<<"\nstd::vector perskirtymų kiekis: "<<alloc_count;
        alloc_count=0;
        for(int i=0;i<=sz;++i)
        {
            if(myVec.capacity()!=temp_cpct_my)
            {
                temp_cpct_my=myVec.capacity();
                alloc_count++;
            }
            myVec.push_back(i);
        }
        cout<<"\nvect perskirtymų kiekis: "<<alloc_count;
    }
    else
    {
        exit(0);
    }
}