#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<ctime>
#include<limits>
#include<fstream>
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
    int maxPatientsPerDay;
    int currentAppointments;

public:
    Doctor() : id(""), name(""), specialization(""), available(false), maxPatientsPerDay(10), currentAppointments(0) {}

    Doctor(string id, string name, string specialization, bool available, int maxPatients = 10)
        : id(id), name(name), specialization(specialization), available(available),
          maxPatientsPerDay(maxPatients), currentAppointments(0) {}

    string getId() const { return id; }
    string getName() const { return name; }
    string getSpecialization() const { return specialization; }
    bool isAvailable() const { return available && (currentAppointments < maxPatientsPerDay); }
    int getCurrentAppointments() const { return currentAppointments; }
    int getMaxPatients() const { return maxPatientsPerDay; }

    void setAvailable(bool a) { available = a; }
    void incrementAppointments() { if(currentAppointments < maxPatientsPerDay) currentAppointments++; }
    void decrementAppointments() { if(currentAppointments > 0) currentAppointments--; }
    void resetDailyAppointments() { currentAppointments = 0; }

    void display() const {
        cout << "ID: " << id << "\nName: " << name << "\nSpecialization: " << specialization
             << "\nAvailability: " << (available ? "Available" : "Not Available")
             << "\nAppointments: " << currentAppointments << "/" << maxPatientsPerDay << endl;
    }

    void displaySummary() const {
        cout << id << "\t" << name << "\t" << specialization << "\t"
             << (isAvailable() ? "Yes" : "No") << endl;
    }
    
    // For file handling
    friend ofstream& operator<<(ofstream& ofs, const Doctor& doc) {
        ofs << "Doctor ID: " << doc.id << "\n";
        ofs << "Name: " << doc.name << "\n";
        ofs << "Specialization: " << doc.specialization << "\n"; 
        ofs << "Available: " << doc.available << "\n";
        ofs << "Max Patients Per Day: " << doc.maxPatientsPerDay << "\n";
        ofs << "Current Appointments: " << doc.currentAppointments << "\n";
        return ofs;
    }
    
    friend ifstream& operator>>(ifstream& ifs, Doctor& doc) {
        string temp;
        getline(ifs, temp); // Read "Doctor ID: " line
        doc.id = temp.substr(temp.find(": ") + 2);
        getline(ifs, temp); // Read "Name: " line
        doc.name = temp.substr(temp.find(": ") + 2);
        getline(ifs, temp); // Read "Specialization: " line
        doc.specialization = temp.substr(temp.find(": ") + 2);
        getline(ifs, temp); // Read "Available: " line
        doc.available = stoi(temp.substr(temp.find(": ") + 2));
        getline(ifs, temp); // Read "Max Patients Per Day: " line
        doc.maxPatientsPerDay = stoi(temp.substr(temp.find(": ") + 2));
        getline(ifs, temp); // Read "Current Appointments: " line
        doc.currentAppointments = stoi(temp.substr(temp.find(": ") + 2));
        return ifs;
    }
};

class Patient {
private:
    string id;
    string name;
    int age;
    string gender;
    string disease;
    string contactNumber;
    string address;

public:
    Patient() : id(""), name(""), age(0), gender(""), disease(""), contactNumber(""), address("") {}

    Patient(string id, string name, int age, string gender, string disease,
            string contact = "", string addr = "")
        : id(id), name(name), age(age), gender(gender), disease(disease),
          contactNumber(contact), address(addr) {}

    string getId() const { return id; }
    string getName() const { return name; }
    int getAge() const { return age; }
    string getGender() const { return gender; }
    string getDisease() const { return disease; }
    string getContact() const { return contactNumber; }
    string getAddress() const { return address; }

    void updateInfo(string newName, int newAge, string newGender, string newDisease,
                   string newContact, string newAddress) {
        if(!newName.empty()) name = newName;
        if(newAge > 0) age = newAge;
        if(!newGender.empty()) gender = newGender;
        if(!newDisease.empty()) disease = newDisease;
        if(!newContact.empty()) contactNumber = newContact;
        if(!newAddress.empty()) address = newAddress;
    }

    void display() const {
        cout << "\nPatient Details:\n";
        cout << "ID: " << id << "\nName: " << name << "\nAge: " << age
             << "\nGender: " << gender << "\nDisease: " << disease
             << "\nContact: " << contactNumber << "\nAddress: " << address << endl;
    }

    void displaySummary() const {
        cout << id << "\t" << name << "\t" << age << "\t" << gender << "\t" << disease << endl;
    }
    
    // For file handling
    friend ofstream& operator<<(ofstream& ofs, const Patient& pat) {
        ofs << "Patient ID: " << pat.id << "\n";
        ofs << "Name: " << pat.name << "\n";
        ofs << "Age: " << pat.age << "\n";
        ofs << "Gender: " << pat.gender << "\n"; 
        ofs << "Disease: " << pat.disease << "\n";
        ofs << "Contact: " << pat.contactNumber << "\n";
        ofs << "Address: " << pat.address << "\n";
        return ofs;
    }
    
    friend ifstream& operator>>(ifstream& ifs, Patient& pat) {
        string temp;
        getline(ifs, temp); // Read "Patient ID: " line
        pat.id = temp.substr(temp.find(": ") + 2);
        getline(ifs, temp); // Read "Name: " line
        pat.name = temp.substr(temp.find(": ") + 2);
        getline(ifs, temp); // Read "Age: " line
        pat.age = stoi(temp.substr(temp.find(": ") + 2));
        getline(ifs, temp); // Read "Gender: " line
        pat.gender = temp.substr(temp.find(": ") + 2);
        getline(ifs, temp); // Read "Disease: " line
        pat.disease = temp.substr(temp.find(": ") + 2);
        getline(ifs, temp); // Read "Contact: " line
        pat.contactNumber = temp.substr(temp.find(": ") + 2);
        getline(ifs, temp); // Read "Address: " line
        pat.address = temp.substr(temp.find(": ") + 2);
        return ifs;
    }
};

struct Appointment {
    string patientId;
    string doctorId;
    string date;
    string time;
    bool completed;
    string notes;
    int appointmentId;

    void display() const {
        cout << "Appointment ID: " << appointmentId << "\nDate: " << date
             << "\nTime: " << time << "\nStatus: "
             << (completed ? "Completed" : "Pending") << "\nNotes: " << notes << endl;
    }
    
    // For file handling
    friend ofstream& operator<<(ofstream& ofs, const Appointment& appt) {
        ofs << "Appointment ID: " << appt.appointmentId << "\n";
        ofs << "Patient ID: " << appt.patientId << "\n";
        ofs << "Doctor ID: " << appt.doctorId << "\n"; 
        ofs << "Date: " << appt.date << "\n";
        ofs << "Time: " << appt.time << "\n";
        ofs << "Completed: " << appt.completed << "\n";
        ofs << "Notes: " << appt.notes << "\n";
        return ofs;
    }
    
    friend ifstream& operator>>(ifstream& ifs, Appointment& appt) {
        string temp;
        getline(ifs, temp); // Read "Appointment ID: " line
        appt.appointmentId = stoi(temp.substr(temp.find(": ") + 2));
        getline(ifs, temp); // Read "Patient ID: " line
        appt.patientId = temp.substr(temp.find(": ") + 2);
        getline(ifs, temp); // Read "Doctor ID: " line
        appt.doctorId = temp.substr(temp.find(": ") + 2);
        getline(ifs, temp); // Read "Date: " line
        appt.date = temp.substr(temp.find(": ") + 2);
        getline(ifs, temp); // Read "Time: " line
        appt.time = temp.substr(temp.find(": ") + 2);
        getline(ifs, temp); // Read "Completed: " line
        appt.completed = stoi(temp.substr(temp.find(": ") + 2));
        getline(ifs, temp); // Read "Notes: " line
        appt.notes = temp.substr(temp.find(": ") + 2);
        return ifs;
    }
};

class HospitalSystem {
private:
    Doctor doctors[MAX_DOCTORS];
    Patient patients[MAX_PATIENTS];
    Appointment appointments[MAX_APPOINTMENTS];
    int docCount = 0;
    int patCount = 0;
    int apptCount = 0;
    int nextAppointmentId = 1;

    int findDoctorIndex(string id) const {
        for(int i = 0; i < docCount; i++) {
            if(doctors[i].getId() == id) return i;
        }
        return -1;
    }

    int findPatientIndex(string id) const {
        for(int i = 0; i < patCount; i++) {
            if(patients[i].getId() == id) return i;
        }
        return -1;
    }

    int findAppointmentIndex(int id) const {
        for(int i = 0; i < apptCount; i++) {
            if(appointments[i].appointmentId == id) return i;
        }
        return -1;
    }

    bool isDoctorAvailable(string doctorId, string date, string time) const {
        for(int i = 0; i < apptCount; i++) {
            if(appointments[i].doctorId == doctorId &&
               appointments[i].date == date &&
               appointments[i].time == time &&
               !appointments[i].completed) {
                return false;
            }
        }
        return true;
    }

    void displayDoctorsBySpecialization(string specialization) const {
        bool found = false;
        cout << "\nDoctors in " << specialization << " department:\n";
        cout << "ID\tName\tSpecialization\tAvailable\n";
        for(int i = 0; i < docCount; i++) {
            if(doctors[i].getSpecialization() == specialization) {
                doctors[i].displaySummary();
                found = true;
            }
        }
        if(!found) cout << "No doctors found in this specialization.\n";
    }

    void displayUpcomingAppointments(string patientId) const {
        bool found = false;
        cout << "\nUpcoming Appointments:\n";
        for(int i = 0; i < apptCount; i++) {
            if(appointments[i].patientId == patientId && !appointments[i].completed) {
                int docIdx = findDoctorIndex(appointments[i].doctorId);
                cout << "Appointment ID: " << appointments[i].appointmentId
                     << "\nDoctor: " << doctors[docIdx].getName()
                     << "\nDate: " << appointments[i].date
                     << "\nTime: " << appointments[i].time << "\n\n";
                found = true;
            }
        }
        if(!found) cout << "No upcoming appointments found.\n";
    }

    void resetDailyAppointments() {
        time_t now = time(0);
        tm *ltm = localtime(&now);
        string today = to_string(ltm->tm_mday) + "/" + to_string(1 + ltm->tm_mon) + "/" + to_string(1900 + ltm->tm_year);

        for(int i = 0; i < docCount; i++) {
            bool hasAppointmentsToday = false;
            for(int j = 0; j < apptCount; j++) {
                if(appointments[j].doctorId == doctors[i].getId() &&
                   appointments[j].date == today &&
                   !appointments[j].completed) {
                    hasAppointmentsToday = true;
                    break;
                }
            }
            if(!hasAppointmentsToday) {
                doctors[i].resetDailyAppointments();
            }
        }
    }

    // File handling methods
    void saveData() {
        ofstream hospitalFile("hospital.txt");
        if (!hospitalFile) {
            cout << "Error saving data to file!" << endl;
            return;
        }

        // Save configuration first
        hospitalFile << "=== HOSPITAL SYSTEM DATA ===\n";
        hospitalFile << "Next Appointment ID: " << nextAppointmentId << "\n\n";

        // Save doctors
        hospitalFile << "=== DOCTORS ===\n";
        hospitalFile << "Doctor Count: " << docCount << "\n";
        for (int i = 0; i < docCount; i++) {
            hospitalFile << doctors[i] << "\n";
        }

        // Save patients
        hospitalFile << "=== PATIENTS ===\n";
        hospitalFile << "Patient Count: " << patCount << "\n";
        for (int i = 0; i < patCount; i++) {
            hospitalFile << patients[i] << "\n";
        }

        // Save appointments
        hospitalFile << "=== APPOINTMENTS ===\n";
        hospitalFile << "Appointment Count: " << apptCount << "\n";
        for (int i = 0; i < apptCount; i++) {
            hospitalFile << appointments[i] << "\n";
        }

        hospitalFile.close();
    }

    void loadData() {
        ifstream hospitalFile("hospital.txt");
        if (!hospitalFile) {
            cout << "No previous data found. Starting with fresh system." << endl;
            return;
        }

        string line;
        // Read until we find the configuration section
        while (getline(hospitalFile, line)) {
            if (line == "=== HOSPITAL SYSTEM DATA ===") {
                break;
            }
        }

        // Read next appointment ID
        getline(hospitalFile, line); // "Next Appointment ID: X"
        nextAppointmentId = stoi(line.substr(line.find(": ") + 2));

        // Find doctors section
        while (getline(hospitalFile, line)) {
            if (line == "=== DOCTORS ===") {
                break;
            }
        }

        // Read doctor count
        getline(hospitalFile, line); // "Doctor Count: X"
        docCount = stoi(line.substr(line.find(": ") + 2));

        // Read doctors
        for (int i = 0; i < docCount; i++) {
            Doctor doc;
            hospitalFile >> doc;
            doctors[i] = doc;
        }

        // Find patients section
        while (getline(hospitalFile, line)) {
            if (line == "=== PATIENTS ===") {
                break;
            }
        }

        // Read patient count
        getline(hospitalFile, line); // "Patient Count: X"
        patCount = stoi(line.substr(line.find(": ") + 2));

        // Read patients
        for (int i = 0; i < patCount; i++) {
            Patient pat;
            hospitalFile >> pat;
            patients[i] = pat;
        }

        // Find appointments section
        while (getline(hospitalFile, line)) {
            if (line == "=== APPOINTMENTS ===") {
                break;
            }
        }

        // Read appointment count
        getline(hospitalFile, line); // "Appointment Count: X"
        apptCount = stoi(line.substr(line.find(": ") + 2));

        // Read appointments
        for (int i = 0; i < apptCount; i++) {
            Appointment appt;
            hospitalFile >> appt;
            appointments[i] = appt;
        }

        hospitalFile.close();
    }

public:
    HospitalSystem() {
        loadData(); // Load data when system starts
        resetDailyAppointments();
    }

    ~HospitalSystem() {
        saveData(); // Save data when system exits
    }

    void addDoctor() {
        string id, name, specialization;
        char ch;
        int maxPatients;

        cout << "\n=== Add New Doctor ===\n";
        cout << "Enter Doctor ID: ";
        cin >> id;
        if(findDoctorIndex(id) != -1) {
            cout << "Doctor ID already exists.\n";
            return;
        }

        cout << "Enter Name: ";
        cin.ignore();
        getline(cin, name);

        cout << "Enter Specialization: ";
        getline(cin, specialization);

        cout << "Enter maximum patients per day (default 10): ";
        if(!(cin >> maxPatients)) {
            maxPatients = 10;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        cout << "Set as available? (Y/N): ";
        cin >> ch;
        bool avail = (toupper(ch) == 'Y');

        cout << "\nReview Details:\n";
        cout << "ID: " << id << "\nName: " << name << "\nSpecialization: " << specialization
             << "\nMax Patients/Day: " << maxPatients << "\nAvailable: " << (avail ? "Yes" : "No") << endl;

        cout << "\nConfirm save? (Y/N): ";
        cin >> ch;
        if(toupper(ch) != 'Y') {
            cout << "Operation cancelled.\n";
            return;
        }

        doctors[docCount++] = Doctor(id, name, specialization, avail, maxPatients);
        cout << "Doctor added successfully.\n";
    }

    void editDoctor() {
        string id;
        cout << "\n=== Edit Doctor ===\n";
        cout << "Enter Doctor ID: ";
        cin >> id;

        int idx = findDoctorIndex(id);
        if(idx == -1) {
            cout << "Doctor not found.\n";
            return;
        }

        doctors[idx].display();

        string name, specialization;
        char ch;
        int maxPatients;

        cout << "\nEnter new Name (leave blank to keep current): ";
        cin.ignore();
        getline(cin, name);

        cout << "Enter new Specialization (leave blank to keep current): ";
        getline(cin, specialization);

        cout << "Enter new maximum patients per day (0 to keep current): ";
        cin >> maxPatients;

        cout << "Toggle availability? (Y/N): ";
        cin >> ch;
        bool toggleAvail = (toupper(ch) == 'Y');

        if(!name.empty()) {
            size_t pos = name.find_first_not_of(" \t");
            if(pos != string::npos) {
                name = name.substr(pos);
            } else {
                name = doctors[idx].getName();
            }
        }

        if(!specialization.empty()) {
            size_t pos = specialization.find_first_not_of(" \t");
            if(pos != string::npos) {
                specialization = specialization.substr(pos);
            } else {
                specialization = doctors[idx].getSpecialization();
            }
        }

        if(maxPatients <= 0) {
            maxPatients = doctors[idx].getMaxPatients();
        }

        bool newAvail = toggleAvail ? !doctors[idx].isAvailable() : doctors[idx].isAvailable();

        Doctor updated(id, name.empty() ? doctors[idx].getName() : name,
                      specialization.empty() ? doctors[idx].getSpecialization() : specialization,
                      newAvail, maxPatients);

        cout << "\nUpdated Details:\n";
        updated.display();

        cout << "\nConfirm changes? (Y/N): ";
        cin >> ch;
        if(toupper(ch) == 'Y') {
            doctors[idx] = updated;
            cout << "Doctor information updated successfully.\n";
        } else {
            cout << "Changes discarded.\n";
        }
    }

    void registerPatient() {
        string id, name, gender, disease, contact, address;
        int age;

        cout << "\n=== Patient Registration ===\n";
        cout << "Enter Patient ID: ";
        cin >> id;
        if(findPatientIndex(id) != -1) {
            cout << "Patient ID already exists.\n";
            return;
        }

        cout << "Enter Name: ";
        cin.ignore();
        getline(cin, name);

        cout << "Enter Age: ";
        while(!(cin >> age) || age <= 0) {
            cout << "Invalid age. Please enter a positive number: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        cout << "Enter Gender (M/F/O): ";
        cin.ignore();
        getline(cin, gender);

        cout << "Enter Disease/Symptoms: ";
        getline(cin, disease);

        cout << "Enter Contact Number: ";
        getline(cin, contact);

        cout << "Enter Address: ";
        getline(cin, address);

        cout << "\nReview Details:\n";
        cout << "ID: " << id << "\nName: " << name << "\nAge: " << age
             << "\nGender: " << gender << "\nDisease: " << disease
             << "\nContact: " << contact << "\nAddress: " << address << endl;

        cout << "\nConfirm registration? (Y/N): ";
        char ch;
        cin >> ch;
        if(toupper(ch) == 'Y') {
            patients[patCount++] = Patient(id, name, age, gender, disease, contact, address);
            cout << "Patient registered successfully.\n";
        } else {
            cout << "Registration cancelled.\n";
        }
    }

    void updatePatientInfo() {
        string id;
        cout << "\n=== Update Patient Information ===\n";
        cout << "Enter Patient ID: ";
        cin >> id;

        int idx = findPatientIndex(id);
        if(idx == -1) {
            cout << "Patient not found.\n";
            return;
        }

        patients[idx].display();

        string name, gender, disease, contact, address;
        int age = 0;

        cout << "\nEnter new Name (leave blank to keep current): ";
        cin.ignore();
        getline(cin, name);

        cout << "Enter new Age (0 to keep current): ";
        cin >> age;
        cin.ignore();

        cout << "Enter new Gender (leave blank to keep current): ";
        getline(cin, gender);

        cout << "Enter new Disease/Symptoms (leave blank to keep current): ";
        getline(cin, disease);

        cout << "Enter new Contact Number (leave blank to keep current): ";
        getline(cin, contact);

        cout << "Enter new Address (leave blank to keep current): ";
        getline(cin, address);

        patients[idx].updateInfo(name, age, gender, disease, contact, address);

        cout << "\nUpdated Information:\n";
        patients[idx].display();
        cout << "Patient information updated successfully.\n";
    }

    void bookAppointment() {
        string pid, did, date, time;
        char ch;

        cout << "\n=== Book Appointment ===\n";
        cout << "Enter Patient ID: ";
        cin >> pid;
        int pidx = findPatientIndex(pid);
        if(pidx == -1) {
            cout << "Patient not found.\n";
            return;
        }

        cout << "\nAvailable Specializations:\n";
        vector<string> specializations;
        for(int i = 0; i < docCount; i++) {
            if(find(specializations.begin(), specializations.end(), doctors[i].getSpecialization()) == specializations.end()) {
                specializations.push_back(doctors[i].getSpecialization());
                cout << "- " << doctors[i].getSpecialization() << endl;
            }
        }

        cout << "\nEnter required specialization: ";
        cin.ignore();
        getline(cin, did);

        displayDoctorsBySpecialization(did);

        cout << "\nEnter Doctor ID: ";
        getline(cin, did);
        int didx = findDoctorIndex(did);
        if(didx == -1) {
            cout << "Doctor not found.\n";
            return;
        }

        if(!doctors[didx].isAvailable()) {
            cout << "Doctor is not available for new appointments today.\n";
            return;
        }

        cout << "Enter Appointment Date (DD/MM/YYYY): ";
        getline(cin, date);

        cout << "Enter Appointment Time: ";
        getline(cin, time);

        if(!isDoctorAvailable(did, date, time)) {
            cout << "Doctor is not available at that time. Please choose another time.\n";
            return;
        }

        cout << "\nAppointment Details:\n";
        cout << "Patient: " << patients[pidx].getName() << "\nDoctor: " << doctors[didx].getName()
             << "\nDate: " << date << "\nTime: " << time << endl;

        cout << "\nConfirm booking? (Y/N): ";
        cin >> ch;
        if(toupper(ch) != 'Y') {
            cout << "Booking cancelled.\n";
            return;
        }

        Appointment newAppt;
        newAppt.patientId = pid;
        newAppt.doctorId = did;
        newAppt.date = date;
        newAppt.time = time;
        newAppt.completed = false;
        newAppt.notes = "";
        newAppt.appointmentId = nextAppointmentId++;

        appointments[apptCount++] = newAppt;
        doctors[didx].incrementAppointments();
        cout << "Appointment booked successfully! Appointment ID: " << newAppt.appointmentId << endl;
    }

    void completeAppointment() {
        int apptId;
        cout << "\n=== Complete Appointment ===\n";
        cout << "Enter Appointment ID: ";
        cin >> apptId;

        int idx = findAppointmentIndex(apptId);
        if(idx == -1) {
            cout << "Appointment not found.\n";
            return;
        }

        if(appointments[idx].completed) {
            cout << "Appointment already marked as completed.\n";
            return;
        }

        int pidx = findPatientIndex(appointments[idx].patientId);
        int didx = findDoctorIndex(appointments[idx].doctorId);

        cout << "\nAppointment Details:\n";
        cout << "Patient: " << patients[pidx].getName() << "\nDoctor: " << doctors[didx].getName()
             << "\nDate: " << appointments[idx].date << "\nTime: " << appointments[idx].time << endl;

        cout << "Enter treatment notes: ";
        cin.ignore();
        getline(cin, appointments[idx].notes);

        appointments[idx].completed = true;
        doctors[didx].decrementAppointments();

        cout << "Appointment marked as completed.\n";
    }

    void viewDoctorDetails() const {
        string id;
        cout << "\n=== View Doctor Details ===\n";
        cout << "Enter Doctor ID: ";
        cin >> id;

        int idx = findDoctorIndex(id);
        if(idx == -1) {
            cout << "Doctor not found.\n";
            return;
        }

        doctors[idx].display();

        cout << "\nUpcoming Appointments:\n";
        bool hasAppointments = false;
        for(int i = 0; i < apptCount; i++) {
            if(appointments[i].doctorId == id && !appointments[i].completed) {
                int pidx = findPatientIndex(appointments[i].patientId);
                cout << "Date: " << appointments[i].date << " Time: " << appointments[i].time
                     << " Patient: " << patients[pidx].getName() << endl;
                hasAppointments = true;
            }
        }
        if(!hasAppointments) cout << "No upcoming appointments.\n";
    }

    void viewPatientDetails() const {
        string id;
        cout << "\n=== View Patient Details ===\n";
        cout << "Enter Patient ID: ";
        cin >> id;

        int idx = findPatientIndex(id);
        if(idx == -1) {
            cout << "Patient not found.\n";
            return;
        }

        patients[idx].display();
        displayUpcomingAppointments(id);

        cout << "\nAppointment History:\n";
        bool hasHistory = false;
        for(int i = 0; i < apptCount; i++) {
            if(appointments[i].patientId == id && appointments[i].completed) {
                int didx = findDoctorIndex(appointments[i].doctorId);
                cout << "Date: " << appointments[i].date << " Doctor: " << doctors[didx].getName()
                     << "\nNotes: " << appointments[i].notes << "\n" << endl;
                hasHistory = true;
            }
        }
        if(!hasHistory) cout << "No appointment history found.\n";
    }

    void displayAllDoctors() const {
        cout << "\n=== All Doctors ===\n";
        cout << "ID\tName\tSpecialization\tAvailable\n";
        for(int i = 0; i < docCount; i++) {
            doctors[i].displaySummary();
        }
    }

    void displayAllPatients() const {
        cout << "\n=== All Patients ===\n";
        cout << "ID\tName\tAge\tGender\tDisease\n";
        for(int i = 0; i < patCount; i++) {
            patients[i].displaySummary();
        }
    }

    void displayDailyAppointments() const {
        string date;
        cout << "\n=== Daily Appointments ===\n";
        cout << "Enter date (DD/MM/YYYY): ";
        cin >> date;

        cout << "\nAppointments for " << date << ":\n";
        bool hasAppointments = false;
        for(int i = 0; i < apptCount; i++) {
            if(appointments[i].date == date) {
                int pidx = findPatientIndex(appointments[i].patientId);
                int didx = findDoctorIndex(appointments[i].doctorId);
                cout << "Time: " << appointments[i].time << " Doctor: " << doctors[didx].getName()
                     << " Patient: " << patients[pidx].getName()
                     << " Status: " << (appointments[i].completed ? "Completed" : "Pending") << endl;
                hasAppointments = true;
            }
        }
        if(!hasAppointments) cout << "No appointments scheduled for this date.\n";
    }

    void menu() {
        int choice;

        do {
            cout << "\n=== HOSPITAL MANAGEMENT SYSTEM ===\n";
            cout << "1. Doctor Management\n";
            cout << "2. Patient Management\n";
            cout << "3. Appointments\n";
            cout << "4. View Reports\n";
            cout << "5. Exit\n";
            cout << "Enter your choice: ";

            while(!(cin >> choice)) {
                cout << "Invalid input. Please enter a number: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }

            switch(choice) {
                case 1: doctorMenu(); break;
                case 2: patientMenu(); break;
                case 3: appointmentMenu(); break;
                case 4: reportMenu(); break;
                case 5:
                    cout << "Exiting system. Goodbye!\n";
                    break;
                default:
                    cout << "Invalid choice. Please try again.\n";
            }

        } while(choice != 5);
    }

    void doctorMenu() {
        int choice;
        do {
            cout << "\n=== DOCTOR MANAGEMENT ===\n";
            cout << "1. Add New Doctor\n";
            cout << "2. Edit Doctor Information\n";
            cout << "3. View Doctor Details\n";
            cout << "4. List All Doctors\n";
            cout << "5. Back to Main Menu\n";
            cout << "Enter your choice: ";
            cin >> choice;

            switch(choice) {
                case 1: addDoctor(); break;
                case 2: editDoctor(); break;
                case 3: viewDoctorDetails(); break;
                case 4: displayAllDoctors(); break;
                case 5: break;
                default: cout << "Invalid choice.\n";
            }
        } while(choice != 5);
    }

    void patientMenu() {
        int choice;
        do {
            cout << "\n=== PATIENT MANAGEMENT ===\n";
            cout << "1. Register New Patient\n";
            cout << "2. Update Patient Information\n";
            cout << "3. View Patient Details\n";
            cout << "4. List All Patients\n";
            cout << "5. Back to Main Menu\n";
            cout << "Enter your choice: ";
            cin >> choice;

            switch(choice) {
                case 1: registerPatient(); break;
                case 2: updatePatientInfo(); break;
                case 3: viewPatientDetails(); break;
                case 4: displayAllPatients(); break;
                case 5: break;
                default: cout << "Invalid choice.\n";
            }
        } while(choice != 5);
    }

    void appointmentMenu() {
        int choice;
        do {
            cout << "\n=== APPOINTMENT MANAGEMENT ===\n";
            cout << "1. Book New Appointment\n";
            cout << "2. Complete Appointment\n";
            cout << "3. View Daily Appointments\n";
            cout << "4. Back to Main Menu\n";
            cout << "Enter your choice: ";
            cin >> choice;

            switch(choice) {
                case 1: bookAppointment(); break;
                case 2: completeAppointment(); break;
                case 3: displayDailyAppointments(); break;
                case 4: break;
                default: cout << "Invalid choice.\n";
            }
        } while(choice != 4);
    }

    void reportMenu() {
        int choice;
        do {
            cout << "\n=== REPORTS ===\n";
            cout << "1. Doctors by Specialization\n";
            cout << "2. Patient Appointments\n";
            cout << "3. Back to Main Menu\n";
            cout << "Enter your choice: ";
            cin >> choice;

            switch(choice) {
                case 1: {
                    string spec;
                    cout << "Enter specialization: ";
                    cin.ignore();
                    getline(cin, spec);
                    displayDoctorsBySpecialization(spec);
                    break;
                }
                case 2: {
                    string pid;
                    cout << "Enter Patient ID: ";
                    cin >> pid;
                    displayUpcomingAppointments(pid);
                    break;
                }
                case 3: break;
                default: cout << "Invalid choice.\n";
            }
        } while(choice != 3);
    }
};

int main() {
    HospitalSystem hospital;
    hospital.menu();
    return 0;
}
