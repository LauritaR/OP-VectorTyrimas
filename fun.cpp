/**
 * @file fun.cpp
 * @brief Contains the implementation of the functions declared in fun.h.
 */

#include "fun.h"
/**
 * @brief Overloads the assignment operator.
 * 
 * @param kitas The studentukas object to copy from.
 * @return A reference to the current object.
 */
 studentukas& studentukas::operator=(const studentukas& kitas)
    {
        vardas=kitas.vardas;
        pavarde=kitas.pavarde;
        pazymiukai=kitas.pazymiukai;
        egzas=kitas.egzas;
        return *this;
    }

   /**
 * @brief Move constructor.
 * 
 * @param kitas The studentukas object to move from.
 */
    studentukas::studentukas(studentukas&& kitas)
    {
        vardas=std::move(kitas.vardas);
        pavarde=std::move(kitas.pavarde);
        pazymiukai=std::move(kitas.pazymiukai);
        egzas=std::move(kitas.egzas);
    }

 /**
 * @brief Move assignment operator.
 * 
 * @param kitas The studentukas object to move from.
 * @return A reference to the current object.
 */
    studentukas& studentukas::operator=( studentukas&& kitas)
    {
        vardas=std::move(kitas.vardas);
        pavarde=std::move(kitas.pavarde);
        pazymiukai=std::move(kitas.pazymiukai);
        egzas=std::move(kitas.egzas);
        return *this;
    }
/**
 * @brief Overloads the input operator.
 * 
 * @param in The input stream to read from.
 * @param stud The studentukas object to fill.
 * @return A reference to the input stream.
 */
    std::istream& operator>>(std::istream& in, studentukas& stud)
    {
        in>>stud.vardas>>stud.pavarde;
        stud.pazymiukai.clear();
        int pazymys;
        while(in>>pazymys)
        {stud.setPazymiukai(pazymys);}
        in.clear();
        in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        in>>stud.egzas;
        return in;
    }

/**
 * @brief Overloads the output operator.
 * 
 * @param out The output stream to write to.
 * @param stud The studentukas object to write.
 * @return A reference to the output stream.
 */
    std::ostream& operator<<(std::ostream & out,const studentukas& stud)
    {
        out<<left<<setw(15)<<stud.vardas<<setw(20)<<stud.pavarde;
        for(auto const& paz: stud.pazymiukai)
        { out<<setw(5)<<paz;}
        out<<setw(7)<<fixed<<setprecision(2)<<stud.galutinisVID()<<endl;
        return out;
    }
/**
 * @brief Generates a random name.
 * 
 * @return A string containing the generated name.
 */
string randName()
{
    SetConsoleOutputCP(CP_UTF8);
    RandInt rnd(0,4);
    string names[5]= {"Perkunija", "Gojus", "Elektra", "Dziugimantas", "Lyja"};
    return names[rnd()];
}
/**
 * @brief Generates a random surname.
 * 
 * @return A string containing the generated surname.
 */
string randSur()
{
    RandInt rnd(0,4);
    string surn[5]= {"Romero", "Garcia", "Moro", "Petersas", "Lehmann"};
    return surn[rnd()];
}
/**

@brief Fills in student's information either manually or with random numbers

@param temp Reference to a studentukas object
*/
void pildyk(studentukas &temp)//funkcija pildyti studentuko duomenis
{
    SetConsoleOutputCP(CP_UTF8);
    string ats="";

    while((ats!="r")&&( ats!="a"))//uzklausa kokiu budu vartotojas nori irasyti pazymius, jeigu atsako nei a nei r-prasoma is naujo
    {
        cout<<"Rankinis įvedimas ar atsitiktiniai skaičiai?(r/a)";
        cin>>ats;  
    }

    if (ats=="r")//kai ivedama raide r
        {  
        cout<<"Įveskite vardą ir pavardę: ";//vartotojas iveda savo varda pavarde
        string vardas,pavarde;
        cin>>vardas>>pavarde;
        temp.setVardas(vardas);
        temp.setPavarde(pavarde);
        int x=0;//x pazymiui
        cout<<"Įveskite pažymius(0-10): ";
        while(cin>>x)//kol skaiciai irasomi
        {
            if(x<=10 && x>=0){
            temp.setPazymiukai(x);//jeigu x maz/lygus nei 10 ir did/lygus 0 tai issaugoma 
            }
            else{
            cout<<"Įveskite skaičių nuo 0 iki 10"<<endl;//jeigu ne tai prasoma ivesti skaiciu vel
            } 
        } 
        cin.clear(); 
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');

        cout<<"Įveskite egzamino pažymį(0-10): ";
        while(true)
        {
            try//exception handling 1
            {
               int egzoPaz;
               cin>>egzoPaz;
               temp.setEgzas(egzoPaz);
               if(cin.fail()||(egzoPaz<0)||(egzoPaz>10))
               {
                throw"Įveskite skaičių nuo 0 iki 10";
               }
               break;
            }
            catch(const char* emsg)
            {
                cout<<emsg<<endl;
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
            }
        }
        }
        else if(ats=="a")//jeigu vartotojas renkasi atsitiktini vykdomass sis kodas
        {
        srand(time(NULL));    
        int size=0;
        temp.setVardas(randName());
        temp.setPavarde(randSur()); 
        cout<<"Kiek namų darbų pažymių norite turėti?";
        while(true)
       {
        try//exception handling 1
        {  
            cin>>size;
            if(cin.fail() ||size<1)//jeigu  netinkamas simbolis vykdomas sis kodas
            {
            throw "Neteisinga įvestis, reikia teigiamo skaičiaus: ";
            }
            break;
           
        }
        catch(const char* msg)     
        {
            cout<<msg<<endl;
            cin.clear();
            cin.ignore(256,'\n');
        }
       }
        cout<<"Namų darbų pažymiai: ";
        RandInt rnd(1,10);
        while(size>0)
        {
            int n=rnd();
            cout<<n<<" ";
            temp.setPazymiukai(n);
            size--; 
        }
        cout<<endl;
        cout<<"Atsitiktinis egzamino pažymys: ";
        int m=rnd();
        cout<<m<<endl;
        temp.setEgzas(m);
    }  
}
/**
 * @brief This function prints the student data to the console.
 *
 * @param temp A reference to the student data to be printed.
 * @throws runtime_error if there are no marks for homework.
 */
void spausdinimas(studentukas &temp)//duomenu spausdinimui 
{ 
    SetConsoleOutputCP(CP_UTF8);
try//exception handling 2
{
    cout<<setw(30)<<left<<temp.getVardas()<<setw(30)<<left<<temp.getPavarde(); 
    if(temp.tuscias())
    {  
     throw runtime_error("--------------Trūksta namų darbų pažymių---------------");
    }
    else{
        cout<<setw(30)<<fixed<<setprecision(2)<<temp.getGalutinisVID()<<setw(30)<<fixed<<setprecision(2)<<temp.getGalutinisMED()<<endl;
    }
}catch(const runtime_error& e)
{
    cerr<<e.what()<<endl;
}

}
/**
 * @brief This function reads student data from a file and stores it in a vector of student objects.
 *
 * @param read_studentukas The name of the file to be read.
 * @param stud The vector of student objects to store the data.
 */
 void skaitymas(string read_studentukas, vect<studentukas>& stud)
{
    SetConsoleOutputCP(CP_UTF8);
    auto start = std::chrono::high_resolution_clock::now();
    
    studentukas laik;
    stringstream buff;
    ifstream open_f;
    string header;
    
    open_f.open(read_studentukas);

    if (!open_f)
    {
        cerr << "Nepavyko nuskaityti failo: " << read_studentukas << endl;
        while (!open_f)
        {
            cout << "Įrašykite dar kartą: ";
            cin >> read_studentukas;
            open_f.open(read_studentukas);
        }
    }
    else
    {
        {
            buff<<open_f.rdbuf();
            open_f.close();
            string v1,p1;
            vect<int> paz1;
            int egz1;
            getline(buff, header);
            int cnt = count(header.begin(), header.end(), 'N'); 
            while (buff>>v1>>p1)
            {
                
                    laik.laisvinamaVieta();
                    paz1.clear();
        /*             buff >> v1;/*  laik.setVardas(v1); */
                   /* buff >> p1; /* laik.setPavarde(header); */ 
                    int paz;
                    for (int j = 0; j < cnt; j++)
                    {
                        buff >> paz;
                        paz1.push_back(paz);
                        /* laik.setPazymiukai(paz); */
                    }  
                   
                    buff >> egz1;
                      if (paz1.empty()) {
                    break;
                }
                  /*   laik.setEgzas(paz); */
                    stud.push_back(studentukas(v1,p1,paz1,egz1));
                    paz1.clear();
                }
            
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> difference = end - start;
    cout << "Duomenų nuskaitymas iš failo užtruko: " << difference.count() << " s\n";
    start = std::chrono::high_resolution_clock::now();
    sort(stud.begin(), stud.end(), [](const studentukas& a, const studentukas& b) {
        return a.getGalutinisVID() < b.getGalutinisVID();
    });
    end = std::chrono::high_resolution_clock::now();
    difference = end - start;
    cout << "Rūšiavimas užtruko: " << difference.count() << " s\n";
}
/**
 * @brief This function writes the student data to a file.
 *
 * @param write_studentukas The name of the file to be written.
 * @param stud The vector of student objects containing the data to be written.
 */
void rasymas(string write_studentukas, vect<studentukas>& stud) {
     SetConsoleOutputCP(CP_UTF8);
    ofstream out;
    out.open(write_studentukas);
    out<<setw(20)<<left<<"Vardas"<<setw(20)<<left<<"Pavardė"<<setw(20)<<left<<"Galutinis(vid)"<<endl;
    out<<setw(20)<<"---------------------------------------------------------------------------"<<endl; 
   
    char eilute[60];
    for (auto& laik : stud) {
        sprintf(eilute, "%-20s%-20s%-.2f\n", laik.getVardas().c_str(), laik.getPavarde().c_str(), laik.getGalutinisVID());
        out<<eilute;
    }

    out.close();
}
/**
 * @brief This function generates a file with random student data.
 *
 * @param filename The name of the file to be generated.
 */

void fileGen(string& filename)
{   SetConsoleOutputCP(CP_UTF8);
    RandInt rnd(1,10);
    int size,filesize; 
    cout<<"Kiek įrašų? ";
    cin>>filesize;
    cout<<"Kiek pažymių? ";
    cin>>size;

    auto start = std::chrono::high_resolution_clock::now();
    ofstream fin(filename);

    fin<<left<<setw(15)<<"Vardas"<<setw(15)<<right<<"Pavardė";
    for(int i=1;i<=size;i++)
    {
        fin<<setw(7)<<"ND"<<i; 
    }        
    fin<<setw(7)<<"Egz."<<endl;
    srand(time(NULL));
    for(int i=1;i<=filesize;i++)
    {   stringstream output;
        string name=randName();
        string surname=randSur();

        output<<left<<setw(15)<<name<<setw(15)<<right<<surname;
        
        for(int j=1;j<=size;j++)
        {
            int r=rnd();
            output<<right<<setw(8)<<r; 
        }
        int m=rnd();
        output<<right<<setw(7)<< m<<endl;
        fin<<output.str();
    }
    fin.close();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> difference = end - start;
    cout <<filesize<< "Įrašų generavimas užtruko: " << difference.count() << " s\n";
}
/**

@brief This function reads a file with student data and separates them into two groups based on their final grade

@param filename The name of the file to be read
*/
void skirstymas(string filename)
{
    SetConsoleOutputCP(CP_UTF8);
    vect<studentukas> stud;
    skaitymas(filename,stud);

    auto start = std::chrono::high_resolution_clock::now();

    auto vargseliai_iter= partition(stud.begin(),stud.end(), 
    []( studentukas& s){return s.getGalutinisVID()<5.0;});
    
    vect<studentukas> vargseliai(stud.begin(),vargseliai_iter);
    stud.erase(stud.begin(),vargseliai_iter);

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> difference = end - start;
    cout << "Studentų skirstymas užtruko: " << difference.count() << " s\n";  

    start = std::chrono::high_resolution_clock::now();
  
    rasymas ("vargseliai.txt",vargseliai);
    rasymas ("saunuoliai.txt",stud);
    
    end = std::chrono::high_resolution_clock::now();
    difference = end - start;
    cout <<"Įrašų rašymas užtruko: " << difference.count() << " s\n";
}

