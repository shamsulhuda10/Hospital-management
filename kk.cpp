#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <limits>

using namespace std;

class Doctor; // Forward declaration

const int MAX_PATIENTS = 100;

class Person
{
protected:
    string Name, Address, BGroup, Gender;

public:
    Person(string name, string address, string bGroup, string gender)
        : Name(name), Address(address), BGroup(bGroup), Gender(gender) {}

    virtual void displayInformation() = 0;

    string getName() { return Name; }
    string getAddress() { return Address; }
    string getBGroup() { return BGroup; }
    string getGender() { return Gender; }
};

class Patient : public Person
{
private:
    static int nextPatientID;
    int PatientID;
    int Age;
    string MedicalHistory;
    string DoctorName;
    string AppointmentTime;
    double DoctorFee;

public:
    Patient(string name = "", string address = "", string bGroup = "",
            string gender = "", int age = 0, string medicalHistory = "")
        : Person(name, address, bGroup, gender), PatientID(++nextPatientID), Age(age), MedicalHistory(medicalHistory),
          DoctorName(""), AppointmentTime(""), DoctorFee(0.0) {}

    int getPatientID() { return PatientID; }
    int getAge() { return Age; }
    string getMedicalHistory() { return MedicalHistory; }
    string getDoctorName() { return DoctorName; }
    string getAppointmentTime() { return AppointmentTime; }
    double getDoctorFee() { return DoctorFee; }

    void setAge(int age) { Age = age; }
    void setMedicalHistory(string medicalHistory) { MedicalHistory = medicalHistory; }
    void setDoctorName(string doctorName) { DoctorName = doctorName; }
    void setAppointmentTime(string appointmentTime) { AppointmentTime = appointmentTime; }
    void setDoctorFee(double doctorFee) { DoctorFee = doctorFee; }

    static void resetPatientIDCounter() { nextPatientID = 0; }

    friend istream &operator>>(istream &input, Patient &patient)
    {
        input >> patient.PatientID >> patient.Name >> patient.Address >> patient.BGroup >> patient.Gender >> patient.Age >> patient.MedicalHistory >> patient.DoctorName >> patient.AppointmentTime >> patient.DoctorFee;
        return input;
    }

    friend ostream &operator<<(ostream &output, const Patient &patient)
    {
        output << patient.PatientID << " : " << patient.Name << " : " << patient.Address
               << " : " << patient.BGroup << " : " << patient.Gender << " : " << patient.Age
               << " : " << patient.MedicalHistory << " : " << patient.DoctorName
               << " : " << patient.AppointmentTime << " : " << patient.DoctorFee;
        return output;
    }

    void displayInformation() override
    {
        cout << "\tPatient Information:" << endl;
        cout << "\tName: " << getName() << endl;
        cout << "\tAddress: " << getAddress() << endl;
        cout << "\tBlood Group: " << getBGroup() << endl;
        cout << "\tGender: " << getGender() << endl;
        cout << "\tAge: " << getAge() << endl;
        cout << "\tMedical History: " << getMedicalHistory() << endl;
        cout << "\tDoctor: " << getDoctorName() << endl;
        cout << "\tAppointment Time: " << getAppointmentTime() << endl;
        cout << "\tDoctor Fee: $" << getDoctorFee() << endl;
    }
};

int Patient::nextPatientID = 0;

class Doctor : public Person
{
private:
    string AvailableTime;
    double DoctorFee;

public:
    Doctor(string name, string address, string bGroup, string gender,
           string availableTime, double doctorFee)
        : Person(name, address, bGroup, gender), AvailableTime(availableTime), DoctorFee(doctorFee) {}

    string getAvailableTime() { return AvailableTime; }
    double getDoctorFee() { return DoctorFee; }

    void setAvailableTime(string availableTime) { AvailableTime = availableTime; }
    void setDoctorFee(double doctorFee) { DoctorFee = doctorFee; }

    friend istream &operator>>(istream &input, Doctor &doctor)
    {
        input >> doctor.Name >> doctor.Address >> doctor.BGroup >> doctor.Gender >> doctor.AvailableTime >> doctor.DoctorFee;
        return input;
    }

    friend ostream &operator<<(ostream &output, const Doctor &doctor)
    {
        output << doctor.Name << " : " << doctor.Address
               << " : " << doctor.BGroup << " : " << doctor.Gender
               << " : " << doctor.AvailableTime << " : " << doctor.DoctorFee;
        return output;
    }

    void displayInformation() override
    {
        cout << "\tDoctor Information:" << endl;
        cout << "\tName: " << getName() << endl;
        cout << "\tAddress: " << getAddress() << endl;
        cout << "\tBlood Group: " << getBGroup() << endl;
        cout << "\tGender: " << getGender() << endl;
        cout << "\tAvailable Time: " << getAvailableTime() << endl;
        cout << "\tDoctor Fee: $" << getDoctorFee() << endl;
    }
};

class Control
{
public:
    void createFileIfNotExists(string filename)
    {
        ifstream file(filename);
        if (!file)
        {
            ofstream createFile(filename);
            file.close();
        }
    }

    bool login()
    {
        string username, password;
        cout << "\tEnter username: ";
        cin >> username;
        cout << "\tEnter password: ";
        cin >> password;

        // Hardcoded username and password for simplicity
        if (username == "admin" && password == "admin123")
        {
            cout << "\tLogin successful!" << endl;
            return true;
        }
        else
        {
            cout << "\tInvalid username or password. Login failed." << endl;
            return false;
        }
    }

    void savePatientsToFile(string filename, Patient patients[], int numPatients)
    {
        ofstream outfile(filename);
        if (!outfile.is_open())
        {
            cerr << "Error: Unable to open the file for writing. Check file path and permissions." << endl;
            return;
        }

        for (int i = 0; i < numPatients; ++i)
        {
            outfile << patients[i] << endl;
        }

        cout << "Patient data saved to file successfully." << endl;
        outfile.close();
    }

    void readPatientsFromFile(string filename, Patient patients[], int &numPatients)
    {
        ifstream infile(filename);
        if (!infile.is_open())
        {
            cerr << "Error: Unable to open the file for reading. Check file path and permissions." << endl;
            return;
        }

        numPatients = 0;
        while (numPatients < MAX_PATIENTS && infile >> patients[numPatients])
        {
            ++numPatients;
        }

        cout << "Patient data read from file successfully." << endl;
        infile.close();
    }

    void displayPatients(Patient patients[], int numPatients)
    {
        system("cls");
        cout << "\tList of Patients" << endl;
        cout << "\t****************" << endl;

        for (int i = 0; i < numPatients; ++i)
        {
            patients[i].displayInformation();
            cout << endl;
        }

        cout << endl;
    }

    void registerPatient(Patient patients[], int &numPatients)
    {
        system("cls");
        string name, address, group, gender, history;
        int age;

        cout << "\tEnter Name Of Patient: ";
        cin.ignore();
        getline(cin, name);

        cout << "\tEnter Address Of Patient: ";
        getline(cin, address);

        cout << "\tEnter Blood Group Of Patient: ";
        getline(cin, group);

        cout << "\tEnter Gender Of Patient: ";
        getline(cin, gender);

        cout << "\tEnter Age Of Patient: ";
        cin >> age;

        cout << "\tEnter Medical History Of Patient: ";
        cin.ignore();
        getline(cin, history);

        if (numPatients < MAX_PATIENTS)
        {
            patients[numPatients] = Patient(name, address, group, gender, age, history);
            ++numPatients;
            savePatientsToFile("Hospital.txt", patients, numPatients);
            cout << "\tPatient Registered!" << endl;
        }
        else
        {
            cout << "\tHospital at full capacity. Cannot register more patients." << endl;
        }
    }

    void dischargePatient(Patient patients[], int &numPatients)
    {
        system("cls");
        string name;

        cout << "\tEnter Name of Patient: ";
        cin.ignore();
        getline(cin, name);

        int patientIndex = -1;
        for (int i = 0; i < numPatients; ++i)
        {
            if (patients[i].getName() == name)
            {
                patientIndex = i;
                break;
            }
        }

        if (patientIndex != -1)
        {
            for (int i = patientIndex; i < numPatients - 1; ++i)
            {
                patients[i] = patients[i + 1];
            }

            --numPatients;
            savePatientsToFile("Hospital.txt", patients, numPatients);
            cout << "\tPatient Discharged!" << endl;
        }
        else
        {
            cout << "\tPatient Not Found!" << endl;
        }
    }

    void displayMedicalHistory(Patient patients[], int numPatients, string patientName)
    {
        system("cls");
        int patientIndex = -1;

        for (int i = 0; i < numPatients; ++i)
        {
            if (patients[i].getName() == patientName)
            {
                patientIndex = i;
                break;
            }
        }

        if (patientIndex != -1)
        {
            cout << "\tMedical History of " << patientName << ":" << endl;
            cout << "\t" << patients[patientIndex].getMedicalHistory() << endl;
        }
        else
        {
            cout << "\tPatient Not Found!" << endl;
        }

        cout << endl;
    }

    void scheduleDoctorAppointment(Patient patients[], int numPatients, Doctor doctor)
    {
        system("cls");

        cout << "\tSchedule an Appointment with Dr. " << doctor.getName() << endl;
        cout << "\tAvailable Time Slots: " << doctor.getAvailableTime() << endl;

        stringstream timeStream(doctor.getAvailableTime());
        const int MAX_SLOTS = 10;
        string availableSlots[MAX_SLOTS];
        int slotCount = 0;
        string slot;

        while (getline(timeStream, slot, '-') && slotCount < MAX_SLOTS)
        {
            availableSlots[slotCount++] = slot;
        }

        cout << "\tChoose a time slot:" << endl;
        for (int i = 0; i < slotCount; ++i)
        {
            size_t hyphenPos = availableSlots[i].find('-');
            if (hyphenPos != string::npos)
            {
                string startTime = availableSlots[i].substr(0, hyphenPos);
                string endTime = availableSlots[i].substr(hyphenPos + 1);
                cout << "\t" << i + 1 << ": " << startTime << " to " << endTime << endl;
            }
            else
            {
                cout << "\t" << i + 1 << ": " << availableSlots[i] << endl;
            }
        }

        cout << "\t" << slotCount + 1 << ": I don't want an appointment. Choose another doctor." << endl;
        cout << endl;

        int selectedSlot;
        cout << "\tEnter the number corresponding to your choice: ";
        cin >> selectedSlot;

        if (selectedSlot >= 1 && selectedSlot <= slotCount)
        {
            string appointmentTime = availableSlots[selectedSlot - 1];
            cout << "\tYou have chosen the time slot: " << appointmentTime << endl;

            cin.ignore();
            string patientName;
            cout << "\tEnter Patient Name: ";
            getline(cin, patientName);

            int patientIndex = -1;
            for (int i = 0; i < numPatients; ++i)
            {
                if (patients[i].getName() == patientName)
                {
                    patientIndex = i;
                    break;
                }
            }

            if (patientIndex != -1)
            {
                patients[patientIndex].setDoctorName(doctor.getName());
                patients[patientIndex].setAppointmentTime(appointmentTime);
                patients[patientIndex].setDoctorFee(doctor.getDoctorFee());

                savePatientsToFile("Hospital.txt", patients, numPatients);

                cout << "\tAppointment scheduled successfully." << endl;
            }
            else
            {
                cout << "\tPatient not found. Appointment scheduling failed." << endl;
            }
        }
        else if (selectedSlot == slotCount + 1)
        {
            cout << "\tYou chose not to have an appointment. Choose another doctor if needed." << endl;
        }
        else
        {
            cout << "\tInvalid choice. Appointment scheduling canceled." << endl;
        }
    }

    void checkPatientsByDoctor(Patient patients[], int numPatients, string doctorName)
    {
        system("cls");
        cout << "\tPatients Under Dr. " << doctorName << "'s Care:" << endl;

        bool found = false;
        for (int i = 0; i < numPatients; ++i)
        {
            if (patients[i].getDoctorName() == doctorName)
            {
                found = true;
                cout << "\tID: " << patients[i].getPatientID() << "\tName: " << patients[i].getName()
                     << "\tAppointment Time: " << patients[i].getAppointmentTime()
                     << "\tDoctor Fee: $" << patients[i].getDoctorFee() << endl;
            }
        }

        if (!found)
        {
            cout << "\tNo patients found under Dr. " << doctorName << "'s care." << endl;
        }

        cout << endl;
    }

    void generateBilling(Patient patients[], int numPatients)
    {
        system("cls");
        string patientName;

        cout << "\tEnter Name of Patient for Billing: ";
        cin.ignore();
        getline(cin, patientName);

        int patientIndex = -1;
        for (int i = 0; i < numPatients; ++i)
        {
            if (patients[i].getName() == patientName)
            {
                patientIndex = i;
                break;
            }
        }

        if (patientIndex != -1)
        {
            cout << "\tBilling Details for " << patientName << ":" << endl;
            cout << "\tDoctor Fee: $" << patients[patientIndex].getDoctorFee() << endl;
        }
        else
        {
            cout << "\tPatient Not Found!" << endl;
        }

        cout << endl;
    }
};

int main()
{
    Control control;
    control.createFileIfNotExists("Hospital.txt");

    // Login
    if (!control.login())
    {
        return 1; // Exit program if login fails
    }

    const int MAX_PATIENTS = 100;
    Patient patients[MAX_PATIENTS];
    int numPatients = 0;

    // Read existing patient data from file
    control.readPatientsFromFile("Hospital.txt", patients, numPatients);

    int choice;

    do
    {
        // Display menu
        system("cls");
        cout << "Hospital Management System" << endl;
        cout << "\t**************************" << endl;
        cout << "\t1. Register Patient." << endl;
        cout << "\t2. Discharge Patient." << endl;
        cout << "\t3. Display Patients List." << endl;
        cout << "\t4. Display Medical History." << endl;
        cout << "\t5. Schedule Doctor Appointment." << endl;
        cout << "\t6. Check Patients by Doctor." << endl;
        cout << "\t7. Generate Billing." << endl;
        cout << "\t8. Logout." << endl;
        cout << "\tEnter Your Choice (1-8): ";

        // Get user choice
        cin >> choice;

        // Process user choice
        switch (choice)
        {
        case 1:
            control.registerPatient(patients, numPatients);
            break;
        case 2:
            control.dischargePatient(patients, numPatients);
            break;
        case 3:
            control.displayPatients(patients, numPatients);
            break;
        case 4:
            {
                cin.ignore();
                string patientName;
                cout << "\tEnter Patient Name: ";
                getline(cin, patientName);
                control.displayMedicalHistory(patients, numPatients, patientName);
            }
            break;
        case 5:
            {
                int doctorChoice;
                cout << "\tChoose a Doctor:" << endl;
                cout << "\t1. Dr. Jamali (9:00-12:00)" << endl;
                cout << "\t2. Dr. Usman (13:00-16:00)" << endl;
                cout << "\t3. Dr. Anas (17:00-20:00)" << endl;
                cout << "\tEnter Doctor Choice (1-3): ";
                cin >> doctorChoice;

                Doctor selectedDoctor("", "", "", "", "", 0.0); // Initialize an empty doctor

                switch (doctorChoice)
                {
                case 1:
                    selectedDoctor = Doctor("Dr. Jamali", "lahore", "A+", "Male", "9:00-12:00", 50.0);
                    break;
                case 2:
                    selectedDoctor = Doctor("Dr. Usman", "karachi", "B-", "Female", "13:00-16:00", 60.0);
                    break;
                case 3:
                    selectedDoctor = Doctor("Dr. Anas", "islamabad", "O+", "Male", "17:00-20:00", 70.0);
                    break;
              default:
                    cout << "\tInvalid Doctor Choice." << endl;
                    break;
                }

                if (selectedDoctor.getName() != "")
                {
                    control.scheduleDoctorAppointment(patients, numPatients, selectedDoctor);
                }
            }
            break;
        case 6:
            {
                int doctorChoice;
                cout << "\tChoose a Doctor:" << endl;
                cout << "\t1. Dr. Jamali" << endl;
                cout << "\t2. Dr. Usman" << endl;
                cout << "\t3. Dr. Anas" << endl;
                cout << "\tEnter Doctor Choice (1-3): ";
                cin >> doctorChoice;

                string doctorName = "";
                switch (doctorChoice)
                {
                case 1:
                    doctorName = "Dr. Jamali";
                    break;
                case 2:
                    doctorName = "Dr. Usman";
                    break;
                case 3:
                    doctorName = "Dr. Anas";
                    break;
                default:
                    cout << "\tInvalid Doctor Choice." << endl;
                    break;
                }

                if (!doctorName.empty())
                {
                    control.checkPatientsByDoctor(patients, numPatients, doctorName);
                }
            }
            break;
        case 7:
            control.generateBilling(patients, numPatients);
            break;
        case 8:
            cout << "\tLogging out..." << endl;
            break;
        default:
            cout << "\tInvalid Choice. Please enter a number between 1 and 8." << endl;
            break;
        }

        // Pause for user to read output
        cout << "\nPress Enter to continue...";
        cin.ignore();
        cin.get();

    } while (choice != 8);

    return 0;
}
