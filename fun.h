#include "mylib.h"
/**
 * @class zmogus
 * @brief Base class for a person object with a name.
 */
class zmogus{
    protected:
        string vardas, pavarde;
    public:
         /**
         * @brief Default constructor for zmogus class.
         */
        zmogus(){}
        /**
         * @brief Constructor for zmogus class with name parameters.
         * @param vardas A string representing the first name of the person.
         * @param pavarde A string representing the last name of the person.
         */
        zmogus(string vardas, string pavarde): vardas(vardas), pavarde(pavarde){}
        /**
         * @brief Virtual destructor for zmogus class.
         */
        virtual ~zmogus(){};
        /**
         * @brief Pure virtual function for setting the first name of the person.
         * @param v A string representing the first name of the person.
         */
        virtual void setVardas(string v) =0;
        /**
         * @brief Pure virtual function for setting the last name of the person.
         * @param p A string representing the last name of the person.
         */
        virtual void setPavarde(string p) =0;
        /**
         * @brief Inline function for getting the first name of the person.
         * @return A string representing the first name of the person.
         */
        inline string getVardas() const{return vardas;}
        /**
         * @brief Inline function for getting the last name of the person.
         * @return A string representing the last name of the person.
         */
        inline string getPavarde() const{return pavarde;} 
};
/**
 * @class studentukas
 * @brief Class for a student object which inherits from the zmogus class and has grade data.
 */
class studentukas:public zmogus{
    private:
    vect<int> pazymiukai; 
    int egzas;
     /**
         * @brief Function for calculating the final grade using the average method.
         * @return A float representing the final grade.
         */
    float galutinisVID()const
        {
            float sum=0,avg=0;
            if(pazymiukai.size()>0)
            {
                for(auto const& paz: pazymiukai)
            {
             sum+=paz;
            }
            avg=((float)sum)/(pazymiukai.size());   
        } 
            return ((0.4*avg)+(0.6*egzas));
        }
/**
         * @brief Function for calculating the final grade using the median method.
         * @return A float representing the final grade.
         */
    float galutinisMed()const
    {   
        float mediana=0;
        vect<int> sorted_paz(pazymiukai);

        sort(sorted_paz.begin(),sorted_paz.end());
    
        if(sorted_paz.size()%2==0)
            {
            mediana=((float)(sorted_paz[(sorted_paz.size()/2.0)-1]+sorted_paz[sorted_paz.size()/2.0])/2.0);
            }
            else 
            {
            mediana=((float)sorted_paz[sorted_paz.size()/2.0]);
            } 
        return ((0.4*mediana)+(0.6*egzas));
    }   
    public:
/**
     * @brief Default constructor for studentukas class.
     */
    studentukas():zmogus{},egzas(0){}
      /**
     * @brief Constructor for studentukas class.
     * @param vardas1 Name of the student.
     * @param pavarde1 Surname of the student.
     * @param paz1 Vector of integers representing the student's grades.
     * @param egz1 The student's exam grade.
     */
    studentukas(string vardas1, string pavarde1,vect<int> paz1, int egz1):zmogus{vardas1,pavarde1}, pazymiukai(std::move(paz1)), egzas(egz1){}
   /**
     * @brief Copy constructor for studentukas class.
     * @param kitas The studentukas object to copy.
     */

    studentukas(const studentukas& kitas): zmogus(kitas.vardas,kitas.pavarde), pazymiukai(kitas.pazymiukai),egzas(kitas.egzas){}
    /**

    @brief Copy assignment operator for studentukas object.
    @param kitas The studentukas object to be copied from.
    @return studentukas& The reference to the copied studentukas object.
    */
    studentukas& operator=(const studentukas& kitas)
    {
        if (&kitas == this)
        return *this;

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

    studentukas(studentukas&& kitas) : zmogus{std::move(kitas.vardas),std::move(kitas.pavarde)}, pazymiukai(std::move(kitas.pazymiukai)), egzas(kitas.egzas)
    {kitas.~studentukas();} 

    /**

        @brief Move assignment operator for studentukas object.
        @param kitas The studentukas object to be moved from.
        @return studentukas& The reference to the moved studentukas object.
        */
    studentukas& operator=( studentukas&& kitas)
    {
        if (&kitas == this)
        return *this;
        pazymiukai.clear();
        vardas = kitas.vardas;
        pavarde = kitas.pavarde;
        pazymiukai = kitas.pazymiukai;
        egzas = kitas.egzas;
        return *this;
    }
        /**

        @brief Input stream operator for studentukas object.
        @param in The input stream to read from.
        @param stud The studentukas object to be read into.
        @return std::istream& The reference to the input stream.
        */
    friend std::istream& operator>>(std::istream& in, studentukas& stud);
    /**

        @brief Output stream operator for studentukas object.
        @param out The output stream to write to.
        @param stud The studentukas object to be written.
        @return std::ostream& The reference to the output stream.
        */
    friend std::ostream& operator<<(std::ostream & out,const studentukas& stud);
    /**

        @brief Getter for the name of the student.
        @return std::string The name of the student.
        */
    inline string getVardas() const{return vardas;}
    /**

    @brief Getter for the surname of the student.
    @return std::string The surname of the student.
    */
    inline string getPavarde() const{return pavarde;}
       /**

        @brief Getter for the list of grades of the student.
        @return std::vector<int> The list of grades of the student.
        */
    inline vect<int> getPazymiai() const{return pazymiukai;}
    /**

        @brief Getter for the exam grade of the student.
        @return int The exam grade of the student.
        */
    inline int getEgzas() const{return egzas;}  
    /**

        @brief Getter for the final grade of the student calculated as an average.
        @return float The final grade of the student calculated as an average.
        */
    inline float getGalutinisVID() const{return galutinisVID();}
    /**

        @brief Getter for the final grade of the student calculated as a median.
        @return float The final grade of the student calculated as a median.
        */
    inline float getGalutinisMED() const{return galutinisMed();} 
    /**

        @brief Checks whether the student has any grades.
        @return true If the student has no grades.
        @return false If the student has at least one grade.
        */
    bool tuscias(){ return pazymiukai.empty();} 
    /**

        @brief Setter for the name of the student.
        @param v The new name of the student.
        */
    void setVardas(string v) { vardas = v;}
    /**

        @brief Setter for the surname of the student.
        @param p The new surname of the student.
        */
    void setPavarde(string p) { pavarde = p;}
    /**

        @brief Adds a grade to the list of grades of the student.
        @param pz The new grade to be added.
        */
    void setPazymiukai(int pz){ pazymiukai.push_back(pz);};
    /**
     * @brief Set the Egzas object.
     * 
     * @param e The new exam grade to be added.
     */
    void setEgzas(int e) { egzas = e; }
    /**
     * @brief Clear grades.
     * 
     */
    void laisvinamaVieta(){pazymiukai.clear();}
 
    ~studentukas()//destructor
    {
        pazymiukai.clear();
    }
};


void pildyk(studentukas &temp);
void spausdinimas(studentukas &temp);
void skaitymas(string read_studentukas, vect<studentukas>& stud); 
void fileGen(string& filename);
void rasymas(string write_studentukas, vect<studentukas>& stud);
string randName();
string randSur();
void skirstymas(string filename);

