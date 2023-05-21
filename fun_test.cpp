#include "mylib.h"
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
        cout<<"\nTikrinamas operator[]\n";
        cout<<"\nstd::vector prieš: ";
        for(const auto& elem:orig){cout<<elem<<" ";}
         orig[2]=9;//operator[]
        cout<<"\nstd::vector po: ";
        for(const auto& elem:orig){cout<<elem<<" ";}
        cout<<endl;

        cout<<"\nvect prieš : ";
        for(const auto& elem:recr){cout<<elem<<" ";}
        recr[2]=9;
        cout<<"\nstd::vector po insert(): ";
        for(const auto& elem:recr){cout<<elem<<" ";}
        cout<<endl;
       
    
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
        unsigned int sz=10000000;
        int alloc_count=0,temp_cpct=0;
        for(int i=1;i<=sz;++i)
        {
            if(stdVec.capacity()!=temp_cpct)
            {
                temp_cpct=stdVec.capacity();
                alloc_count++;
            }
            stdVec.push_back(i);
        }
        cout<<"\nstd::vector perskirtymų kiekis: "<<alloc_count;
        alloc_count=0;
        for(int i=1;i<=sz;++i)
        {
            if(myVec.capacity()!=temp_cpct)
            {
                temp_cpct=myVec.capacity();
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