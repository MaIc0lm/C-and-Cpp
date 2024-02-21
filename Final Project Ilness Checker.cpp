#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <algorithm>

using namespace std;

class SymptomGenerator {
protected:
    char sym[3] = {'*', '+', '-'};

public:
    virtual char get_value() = 0;
};

class PatientSymptomGenerator : public SymptomGenerator {
private:
    int patients;

public:
    PatientSymptomGenerator(int numPatients) : patients(numPatients) {
        srand(static_cast<unsigned int>(time(NULL)));
    }

    char get_value() override {
        return sym[rand() % 3];
    }

    int getPatients() const {
        return patients;
    }
};

class SymptomTable {
public:
    virtual void display() = 0;
};

class PatientSymptomTable : public SymptomTable {
public:
    void display() override {
        cout << "Guide: * Common + Sometimes/Rarely - NO\n";
        cout << "=========================================================================\n";
        cout << "Symptoms \t\t| COVID-19\t|\t Cold \t|\t Flu \t|\n";
        cout << "=========================================================================\n";
        cout << "Fever \t\t\t| \t* \t|\t + \t|\t * \t|\n";
        cout << "Cough \t\t\t| \t* \t|\t + \t|\t * \t|\n";
        cout << "Shortness of Breath \t| \t*\t|\t - \t| \t- \t|\n";
        cout << "Runny Nose \t\t| \t+ \t| \t* \t| \t+ \t|\n";
        cout << "Headaches \t\t| \t+ \t| \t+ \t| \t* \t|\n";
        cout << "Sneezing \t\t| \t- \t| \t* \t| \t- \t|\n";
        cout << "Fatigue \t\t| \t+ \t| \t+ \t| \t* \t|\n";
    }
};

class SymptomChecker {
protected:
    int other;
    int cov;
    int col;
    int flu2;

public:
    virtual void check(int numPatients, const vector<char>& patientSymptoms) = 0;
};

class PatientSymptomChecker : public SymptomChecker {
private:
    int patients;
    vector<char> patientSymptoms;

public:
    PatientSymptomChecker(int numPatients) : patients(numPatients) {
        srand(static_cast<unsigned int>(time(NULL)));
    }

    void check(int numPatients, const vector<char>& generatedSymptoms) override {
        patientSymptoms = generatedSymptoms;
    }

    const vector<char>& getPatientSymptoms() const {
        return patientSymptoms;
    }
};

class SymptomReporter {
private:
    int patients;
    const vector<char>& patientSymptoms;
    int other;
    int cov;
    int col;
    int flu2;

public:
    SymptomReporter(int numPatients, const vector<char>& symptoms)
        : patients(numPatients), patientSymptoms(symptoms), other(0), cov(0), col(0), flu2(0) {}

    void report() {
        for (int i = 0; i < patients; ++i) {
            int covidCount = count(patientSymptoms.begin() + i * 3, patientSymptoms.begin() + (i + 1) * 3, '*');
            int coldCount = count(patientSymptoms.begin() + i * 3, patientSymptoms.begin() + (i + 1) * 3, '+');
            int fluCount = count(patientSymptoms.begin() + i * 3, patientSymptoms.begin() + (i + 1) * 3, '-');

            if (covidCount >= 3) {
                cov++;
            } else if (coldCount >= 3) {
                col++;
            } else if (fluCount >= 3) {
                flu2++;
            } else {
                other++;
            }
        }

        cout << "================================================================\n";
        cout << cov << " patients had symptoms of COVID-19\n";
        cout << col << " patients had symptoms of Cold\n";
        cout << flu2 << " patients had symptoms of flu\n";
        cout << other << " patients had symptoms of other illnesses\n";
        cout << "================================================================\n";

        printPercentageReport("COVID-19", cov, patients);
        printPercentageReport("Cold", col, patients);
        printPercentageReport("Flu", flu2, patients);
        printPercentageReport("Other illnesses", other, patients);
    }

private:
    void printPercentageReport(const string& illness, int count, int totalPatients) const {
        cout << illness << ": [" << (count * 100) / totalPatients << "%]";
        for (int j = 0; j < count; ++j) {
            cout << "+";
        }
        cout << "\n";
    }
};

int main() {
    PatientSymptomTable symptomTable;
    symptomTable.display();

    int numPatients;
    cout << "Enter your number of Patients: ";
    cin >> numPatients;

    PatientSymptomGenerator symptomGenerator(numPatients);
    PatientSymptomChecker symptomChecker(numPatients);

    vector<char> generatedSymptoms;
    for (int i = 0; i < numPatients; ++i) {
        generatedSymptoms.push_back(symptomGenerator.get_value());
    }

    symptomChecker.check(numPatients, generatedSymptoms);

    SymptomReporter symptomReporter(numPatients, symptomChecker.getPatientSymptoms());
    symptomReporter.report();

    return 0;
}
