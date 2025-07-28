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
    Doctor() : id(""), name(""), specialization(""), available(false), maxPatientsPerDay(10), currentAppointments(0) {

    }
    Doctor(string id, string name, string specialization, bool available, int maxPatients = 10)
        : id(id), name(name), specialization(specialization), available(available),
          maxPatientsPerDay(maxPatients), currentAppointments(0) {

    }
    string getId() const {
        return id;
    }
    string getName() const {
        return name;
    }
    string getSpecialization() const {
        return specialization;
    }
    bool isAvailable() const {
        return available && (currentAppointments < maxPatientsPerDay);
    }
    int getCurrentAppointments() const {
        return currentAppointments;
    }
    int getMaxPatients() const {
        return maxPatientsPerDay;
    }

    void setAvailable(bool a) {
        available = a;
    }
    void incrementAppointments() {
        if(currentAppointments < maxPatientsPerDay) currentAppointments++;
    }
    void decrementAppointments() {
        if(currentAppointments > 0) currentAppointments--;
    }
    void resetDailyAppointments() {
        currentAppointments = 0;
    }
    void display() const {
        cout<<"ID: "<<id<<endl;
        cout<<"Name: "<<name<<endl;
        cout<<"Specialization: "<<specialization<<endl;
        cout<<"Availability: "<<endl;
        if (available) {
            cout<<"Available";
        }
        else {
            cout<<"Not Available";
        }
        cout<<endl;
        cout<<"Appointments: "<<currentAppointments<<"/"<<maxPatientsPerDay<<endl;
    }
    void displaySummary() const {
        cout<<id<<"\t"<<name<<"\t"<<specialization<<"\t";
        if (isAvailable()) {
            cout<<"Yes";
        }
        else {
            cout<<"No";
        }
        cout<<endl;
    }
    friend ofstream& operator<<(ofstream& ofs, const Doctor& doc) {
        ofs<<"Doctor ID: "<<doc.id<<endl;
        ofs<<"Name: " <<doc.name<<endl;
        ofs<<"Specialization: "<<doc.specialization<<endl;
        ofs<<"Available: " <<doc.available<<endl;
        ofs<<"Max Patients Per Day: "<<doc.maxPatientsPerDay<<endl;
        ofs<<"Current Appointments: "<<doc.currentAppointments<<endl;
        return ofs;
    }
    friend ifstream& operator>>(ifstream& ifs, Doctor& doc) {
        string temp;
        getline(ifs, temp);
        doc.id = temp.substr(temp.find(": ") + 2);
        getline(ifs, temp);
        doc.name = temp.substr(temp.find(": ") + 2);
        getline(ifs, temp);
        doc.specialization = temp.substr(temp.find(": ") + 2);
        getline(ifs, temp);
        doc.available = stoi(temp.substr(temp.find(": ") + 2));
        getline(ifs, temp);
        doc.maxPatientsPerDay = stoi(temp.substr(temp.find(": ") + 2));
        getline(ifs, temp);
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
    Patient() : id(""), name(""), age(0), gender(""), disease(""), contactNumber(""), address("") {

    }
    Patient(string id, string name, int age, string gender, string disease, string contact = "", string addr = "") : id(id), name(name), age(age), gender(gender), disease(disease), contactNumber(contact), address(addr) {

    }
    string getId() const {
        return id;
    }
    string getName() const {
        return name;
    }
    int getAge() const {
        return age;
    }
    string getGender() const {
        return gender;
    }
    string getDisease() const {
        return disease;
    }
    string getContact() const {
        return contactNumber;
    }
    string getAddress() const {
        return address;
    }
    void updateInfo(string newName, int newAge, string newGender, string newDisease, string newContact, string newAddress) {
        if(!newName.empty()) name = newName;
        if(newAge > 0) age = newAge;
        if(!newGender.empty()) gender = newGender;
        if(!newDisease.empty()) disease = newDisease;
        if(!newContact.empty()) contactNumber = newContact;
        if(!newAddress.empty()) address = newAddress;
    }
    void display() const {
        cout<<endl;
        cout<<"Patient Details:"<<endl;
        cout<<"ID          : "<<id<<endl;
        cout<<"Name        : "<<name<<endl;
        cout<<"Age         : "<<age<<endl;
        cout<<"Gender      : "<<gender<<endl;
        cout<<"Disease     : "<<disease<<endl;
        cout<<"Contact     : "<<contactNumber<<endl;
        cout<<"Address     : "<<address<<endl;
    }
    void displaySummary() const {
        cout<<id<<"\t"<<name<<"\t"<<age<<"\t"<<gender<<"\t"<<disease<<endl;
    }
    friend ofstream& operator<<(ofstream& ofs, const Patient& pat) {
        ofs<<"Patient ID: "<<pat.id<<endl;
        ofs<<"Name: " <<pat.name<<endl;
        ofs<<"Age: " <<pat.age<<endl;
        ofs<<"Gender: "<<pat.gender<<endl;
        ofs<<"Disease: "<<pat.disease<<endl;
        ofs<<"Contact: "<<pat.contactNumber<<endl;
        ofs<<"Address: "<<pat.address<<endl;
        return ofs;
    }
    friend ifstream& operator>>(ifstream& ifs, Patient& pat) {
        string temp;
        getline(ifs, temp);
        pat.id = temp.substr(temp.find(": ") + 2);
        getline(ifs, temp);
        pat.name = temp.substr(temp.find(": ") + 2);
        getline(ifs, temp);
        pat.age = stoi(temp.substr(temp.find(": ") + 2));
        getline(ifs, temp);
        pat.gender = temp.substr(temp.find(": ") + 2);
        getline(ifs, temp);
        pat.disease = temp.substr(temp.find(": ") + 2);
        getline(ifs, temp);
        pat.contactNumber = temp.substr(temp.find(": ") + 2);
        getline(ifs, temp);
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
        cout<<"Appointment ID: "<<appointmentId<<endl;
        cout<<"Date: "<<date<<endl;
        cout<<"Time: "<<time<<endl;
        cout<<"Status: ";
        if (completed) {
            cout<<"Completed";
        }
        else {
            cout<<"Pending";
        }
        cout<<endl;
        cout<<"Notes: "<<notes<<endl;
    }
    friend ofstream& operator<<(ofstream& ofs, const Appointment& appt) {
        ofs<<"Appointment ID: "<<appt.appointmentId<<endl;
        ofs<<"Patient ID: "<<appt.patientId<<endl;
        ofs<<"Doctor ID: "<<appt.doctorId<<endl;
        ofs<<"Date: "<<appt.date<<endl;
        ofs<<"Time: "<<appt.time<<endl;
        ofs<<"Completed: "<<appt.completed<<endl;
        ofs<<"Notes: "<<appt.notes<<endl;
        return ofs;
    }
    friend ifstream& operator>>(ifstream& ifs, Appointment& appt) {
        string temp;
        getline(ifs, temp);
        appt.appointmentId = stoi(temp.substr(temp.find(": ") + 2));
        getline(ifs, temp);
        appt.patientId = temp.substr(temp.find(": ") + 2);
        getline(ifs, temp);
        appt.doctorId = temp.substr(temp.find(": ") + 2);
        getline(ifs, temp);
        appt.date = temp.substr(temp.find(": ") + 2);
        getline(ifs, temp);
        appt.time = temp.substr(temp.find(": ") + 2);
        getline(ifs, temp);
        appt.completed = stoi(temp.substr(temp.find(": ") + 2));
        getline(ifs, temp);
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
        cout<<endl;
        cout<<"Doctors in "<<specialization<<" department:"<<endl;
        cout<<"ID\tName\tSpecialization\tAvailable"<<endl;
        for(int i = 0; i < docCount; i++) {
            if(doctors[i].getSpecialization() == specialization) {
                doctors[i].displaySummary();
                found = true;
            }
        }
        if(!found) cout<<"No doctors found in this specialization"<<endl;
    }
    void displayUpcomingAppointments(string patientId) const {
        bool found = false;
        cout<<endl;
        cout<<"Upcoming Appointments:"<<endl;
        for(int i = 0; i < apptCount; i++) {
            if(appointments[i].patientId == patientId && !appointments[i].completed) {
                int docIdx = findDoctorIndex(appointments[i].doctorId);
                cout<<"Appointment ID: "<<appointments[i].appointmentId<<endl;
                     cout<<"Doctor: "<<doctors[docIdx].getName()<<endl;
                     cout<<"Date: "<<appointments[i].date<<endl;
                     cout<<"Time: "<<appointments[i].time <<endl<<endl;
                found = true;
            }
        }
        if(!found)
            cout<<"No upcoming appointments found"<<endl;
    }
    void resetDailyAppointments() {
        time_t now = time(0);
        tm *ltm = localtime(&now);
        string today = to_string(ltm->tm_mday) + "/" + to_string(1 + ltm->tm_mon) + "/" + to_string(1900 + ltm->tm_year);
        for(int i = 0; i < docCount; i++) {
            bool hasAppointmentsToday = false;
            for(int j = 0; j < apptCount; j++) {
                if(appointments[j].doctorId == doctors[i].getId() && appointments[j].date == today &&! appointments[j].completed) {
                    hasAppointmentsToday = true;
                    break;
                }
            }
            if(!hasAppointmentsToday) {
                doctors[i].resetDailyAppointments();
            }
        }
    }
    void saveData() {
        ofstream hospitalFile("hospital.txt");
        if (!hospitalFile) {
            cout<<"Error saving data to file!"<<endl;
            return;
        }
        hospitalFile<<"=== HOSPITAL SYSTEM DATA ==="<<endl;
        hospitalFile<<"Next Appointment ID: "<<nextAppointmentId<<endl<<endl;
        hospitalFile<< "=== DOCTORS ==="<<endl;
        hospitalFile<<"Doctor Count: "<<docCount<<endl;
        for (int i = 0; i < docCount; i++) {
            hospitalFile<<doctors[i]<<endl;
        }
        hospitalFile<<"=== PATIENTS ==="<<endl;;
        hospitalFile<<"Patient Count: "<<patCount<<endl;
        for (int i = 0; i < patCount; i++) {
            hospitalFile<<patients[i]<<endl;
        }
        hospitalFile<<"=== APPOINTMENTS ==="<<endl;
        hospitalFile<<"Appointment Count: " <<apptCount<<endl;
        for (int i = 0; i < apptCount; i++) {
            hospitalFile<<appointments[i]<<endl;
        }
        hospitalFile.close();
    }
    void loadData() {
        ifstream hospitalFile("hospital.txt");
        if (!hospitalFile) {
            cout<<"No previous data found, Starting with fresh system."<<endl;
            return;
        }
        string line;
        while (getline(hospitalFile, line)) {
            if (line == "=== HOSPITAL SYSTEM DATA ===") {
                break;
            }
        }
        getline(hospitalFile, line);
        nextAppointmentId = stoi(line.substr(line.find(": ") + 2));
        while (getline(hospitalFile, line)) {
            if (line == "=== DOCTORS ===") {
                break;
            }
        }
        getline(hospitalFile, line);
        docCount = stoi(line.substr(line.find(": ") + 2));
        for (int i = 0; i < docCount; i++) {
            Doctor doc;
            hospitalFile >> doc;
            doctors[i] = doc;
        }
        while (getline(hospitalFile, line)) {
            if (line == "=== PATIENTS ===") {
                break;
            }
        }
        getline(hospitalFile, line);
        patCount = stoi(line.substr(line.find(": ") + 2));
        for (int i = 0; i < patCount; i++) {
            Patient pat;
            hospitalFile >> pat;
            patients[i] = pat;
        }
        while (getline(hospitalFile, line)) {
            if (line == "=== APPOINTMENTS ===") {
                break;
            }
        }
        getline(hospitalFile, line);
        apptCount = stoi(line.substr(line.find(": ") + 2));
        for (int i = 0; i < apptCount; i++) {
            Appointment appt;
            hospitalFile >> appt;
            appointments[i] = appt;
        }
        hospitalFile.close();
    }
public:
    HospitalSystem() {
        loadData();
        resetDailyAppointments();
    }
    ~HospitalSystem() {
        saveData();
    }
    void addDoctor() {
        string id, name, specialization;
        char ch;
        int maxPatients;
        cout<<endl;
        cout<<"=== Add New Doctor =="<<endl;
        cout<<"Enter Doctor ID: ";
        cin>>id;
        if(findDoctorIndex(id) != -1) {
            cout<<"Doctor ID already exists"<<endl;
            return;
        }
        cout<<"Enter Name: ";
        cin.ignore();
        getline(cin, name);
        cout<<"Enter Specialization: ";
        getline(cin, specialization);
        cout<<"Enter maximum patients per day (default 10): ";
        if(!(cin >> maxPatients)) {
            maxPatients = 10;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cout<<"Set as available? (Y/N): ";
        cin>>ch;
        bool avail = (toupper(ch) == 'Y');
        cout<<endl;
        cout<<"Review Details:"<<endl;
        cout<<"ID: "<<id<<endl;
        cout<<"Name: "<<name<<endl;
        cout<<"Specialization: "<<specialization<<endl;
        cout<<"Max Patients/Day: "<<maxPatients<<endl;
        cout<<"Available: ";
        if (avail) {
            cout << "Yes";
        }
        else {
            cout << "No";
        }
        cout<<endl;
        cout<<endl;
        cout<<"Confirm save? (Y/N): ";
        cin>>ch;
        if(toupper(ch) != 'Y') {
            cout<<"Operation cancelled"<<endl;
            return;
        }
        doctors[docCount++] = Doctor(id, name, specialization, avail, maxPatients);
        cout<<"Doctor added successfully."<<endl;
    }
    void editDoctor() {
        string id;
        cout<<endl;
        cout<<"=== Edit Doctor ==="<<endl;
        cout<<"Enter Doctor ID: ";
        cin>>id;
        int idx = findDoctorIndex(id);
        if(idx == -1) {
            cout<<"Doctor not found"<<endl;
            return;
        }
        doctors[idx].display();
        string name, specialization;
        char ch;
        int maxPatients;
        cout<<endl;
        cout<<"Enter new Name (leave blank to keep current): ";
        cin.ignore();
        getline(cin, name);
        cout<<"Enter new Specialization (leave blank to keep current): ";
        getline(cin, specialization);
        cout<<"Enter new maximum patients per day (0 to keep current): ";
        cin >>maxPatients;
        cout<<"Toggle availability? (Y/N): ";
        cin>>ch;
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
        bool newAvail;
        if (toggleAvail) {
            newAvail = !doctors[idx].isAvailable();
        } else {
            newAvail = doctors[idx].isAvailable();
        }
        Doctor updated(id, name.empty() ? doctors[idx].getName() : name,
                      specialization.empty() ? doctors[idx].getSpecialization() : specialization,
                      newAvail, maxPatients);
        cout<<endl;
        cout<<"Updated Details:"<<endl;
        updated.display();
        cout<<endl;
        cout<<"Confirm changes? (Y/N): ";
        cin>>ch;
        if(toupper(ch) == 'Y') {
            doctors[idx] = updated;
            cout<<"Doctor information updated successfully."<<endl;
        }
        else {
            cout<<"Changes discarded."<<endl;
        }
    }
    void registerPatient() {
        string id, name, gender, disease, contact, address;
        int age;
        cout<<endl;
        cout<<"=== Patient Registration ==="<<endl;
        cout<<"Enter Patient ID: ";
        cin>>id;
        if(findPatientIndex(id) != -1) {
            cout<<"Patient ID already exists."<<endl;
            return;
        }
        cout<<"Enter Name: ";
        cin.ignore();
        getline(cin, name);
        cout<<"Enter Age: ";
        while(!(cin >> age) || age <= 0) {
            cout<<"Invalid age. Please enter a positive number: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cout<<"Enter Gender (M/F/O): ";
        cin.ignore();
        getline(cin, gender);
        cout<<"Enter Disease/Symptoms: ";
        getline(cin, disease);
        cout<<"Enter Contact Number: ";
        getline(cin, contact);
        cout<<"Enter Address: ";
        getline(cin, address);
        cout<<endl;
        cout<<"Review Details:"<<endl;
        cout<<"ID: "<<id<<endl;
        cout<<"Name: "<<name<<endl;
        cout<<"Age: "<<age<<endl;
        cout<<"Gender: "<<gender<<endl;
        cout<<"Disease: "<<disease<<endl;
        cout<<"Contact: "<<contact<<endl;
        cout<<"Address: "<<address<<endl;
        cout<<endl;
        cout<<"Confirm registration? (Y/N): ";
        char ch;
        cin>>ch;
        if(toupper(ch) == 'Y') {
            patients[patCount++] = Patient(id, name, age, gender, disease, contact, address);
            cout<<"Patient registered successfully."<<endl;
        }
        else {
            cout<<"Registration cancelled."<<endl;
        }
    }
    void updatePatientInfo() {
        string id;
        cout<<endl;
        cout<<"=== Update Patient Information ==="<<endl;
        cout<<"Enter Patient ID: ";
        cin>>id;
        int idx = findPatientIndex(id);
        if(idx == -1) {
            cout<<"Patient not found."<<endl;
            return;
        }
        patients[idx].display();
        string name, gender, disease, contact, address;
        int age = 0;
        cout<<endl;
        cout<<"Enter new Name (leave blank to keep current): ";
        cin.ignore();
        getline(cin, name);
        cout<<"Enter new Age (0 to keep current): ";
        cin>>age;
        cin.ignore();
        cout<<"Enter new Gender (leave blank to keep current): ";
        getline(cin, gender);
        cout<<"Enter new Disease/Symptoms (leave blank to keep current): ";
        getline(cin, disease);
        cout<<"Enter new Contact Number (leave blank to keep current): ";
        getline(cin, contact);
        cout<<"Enter new Address (leave blank to keep current): ";
        getline(cin, address);
        patients[idx].updateInfo(name, age, gender, disease, contact, address);
        cout<<endl;
        cout<<"Updated Information:";
        patients[idx].display();
        cout<<"Patient information updated successfully."<<endl;
    }
    void bookAppointment() {
        string pid, did, date, time;
        char ch;
        cout<<endl;
        cout<<"=== Book Appointment ==="<<endl;
        cout<<"Enter Patient ID: ";
        cin>>pid;
        int pidx = findPatientIndex(pid);
        if(pidx == -1) {
            cout<<"Patient not found."<<endl;
            return;
        }
        cout<<endl;
        cout<<"Available Specializations:"<<endl;
        vector<string> specializations;
        for(int i = 0; i < docCount; i++) {
            if(find(specializations.begin(), specializations.end(), doctors[i].getSpecialization()) == specializations.end()) {
                specializations.push_back(doctors[i].getSpecialization());
                cout<< "- " <<doctors[i].getSpecialization() << endl;
            }
        }
        cout<<endl;
        cout<<"Enter required specialization: ";
        cin.ignore();
        getline(cin, did);
        displayDoctorsBySpecialization(did);
        cout<<endl;
        cout<<"Enter Doctor ID: ";
        getline(cin, did);
        int didx = findDoctorIndex(did);
        if(didx == -1) {
            cout<<"Doctor not found."<<endl;
            return;
        }
        if(!doctors[didx].isAvailable()) {
            cout<<"Doctor is not available for new appointments today."<<endl;
            return;
        }
        cout<<"Enter Appointment Date (DD/MM/YYYY): ";
        getline(cin, date);
        cout<<"Enter Appointment Time: ";
        getline(cin, time);
        if(!isDoctorAvailable(did, date, time)) {
            cout<<"Doctor is not available at that time. Please choose another time."<<endl;
            return;
        }
        cout<<endl;
        cout<<"Appointment Details:"<<endl;
        cout<<"Patient: "<<patients[pidx].getName()<<endl;
        cout<<"Doctor: " <<doctors[didx].getName()<<endl;
        cout<<"Date: " <<date<<endl;
        cout<<"Time: "<<time<<endl;
        cout<<endl;
        cout<<"Confirm booking? (Y/N): ";
        cin>>ch;
        if(toupper(ch) != 'Y') {
            cout<<"Booking cancelled."<<endl;
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
        cout<<"Appointment booked successfully! Appointment ID: "<< newAppt.appointmentId<<endl;
    }
    void completeAppointment() {
        int apptId;
        cout<<endl;
        cout<<"=== Complete Appointment ==="<<endl;
        cout<<"Enter Appointment ID: ";
        cin>>apptId;
        int idx = findAppointmentIndex(apptId);
        if(idx == -1) {
            cout<<"Appointment not found."<<endl;
            return;
        }
        if(appointments[idx].completed) {
            cout<<"Appointment already marked as completed."<<endl;
            return;
        }
        int pidx = findPatientIndex(appointments[idx].patientId);
        int didx = findDoctorIndex(appointments[idx].doctorId);
        cout<<endl;
        cout<<"Appointment Details:"<<endl;
        cout<<"Patient: "<<patients[pidx].getName()<<endl;
        cout<<"Doctor: "<<doctors[didx].getName()<<endl;
        cout<<"Date: "<<appointments[idx].date<<endl;
        cout<<"Time: "<<appointments[idx].time<<endl;
        cout<<"Enter treatment notes: ";
        cin.ignore();
        getline(cin, appointments[idx].notes);
        appointments[idx].completed = true;
        doctors[didx].decrementAppointments();
        cout<<"Appointment marked as completed."<<endl;
    }
    void viewDoctorDetails() const {
        string id;
        cout<<endl;
        cout<<"=== View Doctor Details ==="<<endl;
        cout<<"Enter Doctor ID: ";
        cin>>id;
        int idx = findDoctorIndex(id);
        if(idx == -1) {
            cout<<"Doctor not found."<<endl;
            return;
        }
        doctors[idx].display();
        cout<<endl;
        cout<<"Upcoming Appointments:"<<endl;
        bool hasAppointments = false;
        for(int i = 0; i < apptCount; i++) {
            if(appointments[i].doctorId == id && !appointments[i].completed) {
                int pidx = findPatientIndex(appointments[i].patientId);
                cout<<"Date: "<<appointments[i].date<<" Time: "<<appointments[i].time<< " Patient: "<<patients[pidx].getName()<<endl;
                hasAppointments = true;
            }
        }
        if(!hasAppointments)
            cout<<"No upcoming appointments."<<endl;
    }
    void viewPatientDetails() const {
        string id;
        cout<<endl;
        cout<<"=== View Patient Details ==="<<endl;
        cout<<"Enter Patient ID: ";
        cin>>id;
        int idx = findPatientIndex(id);
        if(idx == -1) {
            cout<<"Patient not found."<<endl;
            return;
        }
        patients[idx].display();
        displayUpcomingAppointments(id);
        cout<<endl;
        cout<<"Appointment History:"<<endl;
        bool hasHistory = false;
        for(int i = 0; i < apptCount; i++) {
            if(appointments[i].patientId == id && appointments[i].completed) {
                int didx = findDoctorIndex(appointments[i].doctorId);
                cout<<"Date: "<<appointments[i].date<<" Doctor: "<<doctors[didx].getName()<<endl;
                cout<<"Notes: "<<appointments[i].notes<<endl<< endl;
                hasHistory = true;
            }
        }
        if(!hasHistory)
            cout<<"No appointment history found."<<endl;
    }
    void displayAllDoctors() const {
        cout<<endl;
        cout<<"=== All Doctors ==="<<endl;
        cout<<"ID\tName\tSpecialization\tAvailable"<<endl;
        for(int i = 0; i < docCount; i++) {
            doctors[i].displaySummary();
        }
    }
    void displayAllPatients() const {
        cout<<endl;
        cout<<"=== All Patients ==="<<endl;
        cout<<"ID\tName\tAge\tGender\tDisease"<<endl;
        for(int i = 0; i < patCount; i++) {
            patients[i].displaySummary();
        }
    }
    void displayDailyAppointments() const {
        string date;
        cout<<endl;
        cout<<"=== Daily Appointments ==="<<endl;
        cout<<"Enter date (DD/MM/YYYY): ";
        cin>>date;
        cout<<endl;
        cout<<"Appointments for " << date << ":"<<endl;;
        bool hasAppointments = false;
        string status;
        for(int i = 0; i < apptCount; i++) {
            if(appointments[i].date == date) {
                int pidx = findPatientIndex(appointments[i].patientId);
                int didx = findDoctorIndex(appointments[i].doctorId);
                cout<<"Time: "<<appointments[i].time<<" Doctor: "<<doctors[didx].getName()<<" Patient: "<<patients[pidx].getName()<<" Status: ";
                if (appointments[i].completed) {
                             status = "Completed";
                }
                else {
                            status = "Pending";
                }
                cout<<"Status:"<<status<<endl;
                hasAppointments = true;
            }
        }
        if(!hasAppointments)
            cout<<"No appointments scheduled for this date."<<endl;
    }
    void menu() {
        int choice;
        do {
            cout<<endl;
            cout<<"=== HOSPITAL MANAGEMENT SYSTEM ==="<<endl;
            cout<<"1. Doctor Management"<<endl;;
            cout<<"2. Patient Management"<<endl;
            cout<<"3. Appointments"<<endl;
            cout<<"4. View Reports"<<endl;
            cout<<"5. Exit"<<endl;
            cout<<"Enter your choice: ";
            while(!(cin >> choice)) {
                cout<<"Invalid input. Please enter a number: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            switch(choice) {
                case 1: doctorMenu(); break;
                case 2: patientMenu(); break;
                case 3: appointmentMenu(); break;
                case 4: reportMenu(); break;
                case 5:
                    cout<<"Exiting system....."<<endl;
                    break;
                default:
                    cout<<"Invalid choice, Please try again."<<endl;
            }
        }
        while(choice != 5);
    }
    void doctorMenu() {
        int choice;
        do {
            cout<<endl;
            cout<<"=== DOCTOR MANAGEMENT ==="<<endl;
            cout<<"1. Add New Doctor"<<endl;
            cout<<"2. Edit Doctor Information"<<endl;
            cout<<"3. View Doctor Details"<<endl;
            cout<<"4. List All Doctors"<<endl;
            cout<<"5. Back to Main Menu"<<endl;
            cout<<"Enter your choice: ";
            cin>>choice;
            switch(choice) {
                case 1: addDoctor(); break;
                case 2: editDoctor(); break;
                case 3: viewDoctorDetails(); break;
                case 4: displayAllDoctors(); break;
                case 5: break;
                default:
                    cout<<"Invalid choice."<<endl;
            }
        }
        while(choice != 5);
    }
    void patientMenu() {
        int choice;
        do {
            cout<<endl;
            cout<<"=== PATIENT MANAGEMENT ==="<<endl;
            cout<<"1. Register New Patient"<<endl;
            cout<<"2. Update Patient Information"<<endl;
            cout<<"3. View Patient Details"<<endl;
            cout<<"4. List All Patients"<<endl;
            cout<<"5. Back to Main Menu"<<endl;
            cout<<"Enter your choice: ";
            cin>>choice;
            switch(choice) {
                case 1: registerPatient(); break;
                case 2: updatePatientInfo(); break;
                case 3: viewPatientDetails(); break;
                case 4: displayAllPatients(); break;
                case 5: break;
                default:
                    cout<<"Invalid choice."<<endl;
            }
        }
        while(choice != 5);
    }
    void appointmentMenu() {
        int choice;
        do {
            cout<<endl;
            cout<<"=== APPOINTMENT MANAGEMENT ==="<<endl;
            cout<<"1. Book New Appointment"<<endl;
            cout<<"2. Complete Appointment"<<endl;
            cout<<"3. View Daily Appointments"<<endl;
            cout<<"4. Back to Main Menu"<<endl;
            cout<<"Enter your choice: ";
            cin>>choice;
            switch(choice) {
                case 1: bookAppointment(); break;
                case 2: completeAppointment(); break;
                case 3: displayDailyAppointments(); break;
                case 4: break;
                default:
                    cout<<"Invalid choice."<<endl;
            }
        }
        while(choice != 4);
    }
    void reportMenu() {
        int choice;
        do {
            cout<<endl;
            cout<<"=== REPORTS ==="<<endl;
            cout<<"1. Doctors by Specialization"<<endl;
            cout<<"2. Patient Appointments"<<endl;
            cout<<"3. Back to Main Menu"<<endl;
            cout<<"Enter your choice:"<<endl;
            cin>>choice;
            switch(choice) {
                case 1: {
                    string spec;
                    cout<<"Enter specialization: ";
                    cin.ignore();
                    getline(cin, spec);
                    displayDoctorsBySpecialization(spec);
                    break;
                }
                case 2: {
                    string pid;
                    cout<<"Enter Patient ID: ";
                    cin>>pid;
                    displayUpcomingAppointments(pid);
                    break;
                }
                case 3:
                    break;
                default:
                    cout<<"Invalid choice."<<endl;
            }
        }
        while(choice != 3);
    }
};

int main() {
    HospitalSystem hospital;
    hospital.menu();
    return 0;
}
