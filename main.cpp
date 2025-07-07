#include<iostream>
#include<string>
using namespace std;

const int MAX_DOCTORS = 100;
const int MAX_PATIENTS = 500;
const int MAX_APPOINTMENTS = 500;

class Doctor {
private:
    string id;
    string name;
    string specialization;
    bool available;

public:
    Doctor() {
        id = "";
        name = "";
        specialization = "";
        available = false;
    }

    Doctor(string id, string name, string specialization, bool available) {
        this->id = id;
        this->name = name;
        this->specialization = specialization;
        this->available = available;
    }

    string getId() { return id; }
    string getName() { return name; }
    string getSpecialization() { return specialization; }
    bool isAvailable() { return available; }

    void setAvailable(bool a) { available = a; }

    void display() {
        cout << id << "\t" << name << "\t" << specialization << "\t" << (available ? "Yes" : "No") << endl;
    }
};

class Patient {
private:
    string id;
    string name;
    int age;
    string gender;
    string disease;

public:
    Patient() {
        id = "";
        name = "";
        age = 0;
        gender = "";
        disease = "";
    }

    Patient(string id, string name, int age, string gender, string disease) {
        this->id = id;
        this->name = name;
        this->age = age;
        this->gender = gender;
        this->disease = disease;
    }

    string getId() { return id; }
    string getName() { return name; }
    int getAge() { return age; }
    string getGender() { return gender; }
    string getDisease() { return disease; }

    void displaySummary() {
        cout << id << "\t" << name << "\t" << age << "\t" << gender << "\t" << disease;
    }
};

struct Appointment {
    string patientId;
    string doctorId;
    string dateTime;
    bool completed;
};

class HospitalSystem {
private:
    Doctor doctors[MAX_DOCTORS];
    Patient patients[MAX_PATIENTS];
    Appointment appointments[MAX_APPOINTMENTS];
    int docCount = 0;
    int patCount = 0;
    int apptCount = 0;

    int findDoctorIndex(string id) {
        for(int i = 0; i < docCount; i++) {
            if(doctors[i].getId() == id) return i;
        }
        return -1;
    }

    int findPatientIndex(string id) {
        for(int i = 0; i < patCount; i++) {
            if(patients[i].getId() == id) return i;
        }
        return -1;
    }

public:
    void addDoctor() {
        string id, name, specialization;
        char ch;

        cout << "Enter Doctor ID: ";
        cin >> id;
        if(findDoctorIndex(id) != -1) {
            cout << "Doctor ID already exists." << endl;
            return;
        }

        cout << "Enter Name: ";
        cin.ignore();
        getline(cin, name);

        cout << "Enter Specialization: ";
        getline(cin, specialization);

        cout << "Availability (Y/N): ";
        cin >> ch;
        bool avail = (ch == 'Y' || ch == 'y');

        cout << "Confirm Save? (Y/N): ";
        cin >> ch;
        if(ch != 'Y' && ch != 'y') {
            cout << "Cancelled." << endl;
            return;
        }

        doctors[docCount++] = Doctor(id, name, specialization, avail);
        cout << "Doctor added successfully." << endl;
    }

    void registerPatient() {
        string id, name, gender, disease;
        int age;

        cout << "Enter Patient ID: ";
        cin >> id;
        if(findPatientIndex(id) != -1) {
            cout << "Patient ID already exists." << endl;
            return;
        }

        cout << "Enter Name: ";
        cin.ignore();
        getline(cin, name);

        cout << "Enter Age: ";
        cin >> age;

        cout << "Enter Gender: ";
        cin.ignore();
        getline(cin, gender);

        cout << "Enter Disease: ";
        getline(cin, disease);

        patients[patCount++] = Patient(id, name, age, gender, disease);
        cout << "Patient registered successfully." << endl;
    }

    void bookAppointment() {
        string pid, did, date;

        cout << "Enter Patient ID: ";
        cin >> pid;
        int pidx = findPatientIndex(pid);
        if(pidx == -1) {
            cout << "Patient not found." << endl;
            return;
        }

        cout << "Enter Doctor ID: ";
        cin >> did;
        int didx = findDoctorIndex(did);
        if(didx == -1) {
            cout << "Doctor not found." << endl;
            return;
        }

        if(!doctors[didx].isAvailable()) {
            cout << "Doctor not available." << endl;
            return;
        }

        cout << "Enter Appointment Date and Time: ";
        cin.ignore();
        getline(cin, date);

        appointments[apptCount++] = { pid, did, date, false };
        doctors[didx].setAvailable(false);
        cout << "Appointment booked successfully!" << endl;
    }

    void menu() {
        int choice;

        do {
            cout << "\n=== MENU ===" << endl;
            cout << "1. Add Doctor" << endl;
            cout << "2. Register Patient" << endl;
            cout << "3. Book Appointment" << endl;
            cout << "4. Exit" << endl;
            cout << "Enter choice: ";
            cin >> choice;

            switch(choice) {
                case 1: addDoctor(); break;
                case 2: registerPatient(); break;
                case 3: bookAppointment(); break;
                case 4: cout << "Exiting..." << endl; break;
                default: cout << "Invalid choice." << endl;
            }

        } while(choice != 4);
    }
};

int main() {
    HospitalSystem h;
    h.menu();
    return 0;
}
