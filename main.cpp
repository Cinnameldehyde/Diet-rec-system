#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include<string.h>
#include <iomanip>
#include<cmath>
#include <algorithm>
#include <map>
#include <numeric>
#include <set>
#include <thread> // For sleep
#include <chrono> // For sleep duration
#include <cstdlib> // For system calls on macOS/Linux
using namespace std;

// ANSI escape code for bright neon green colour
const string neonGreen = "\033[92m"; // Bright neon green
const string reset = "\033[0m";      // Reset to default colour

// Function to display text with a typewriter effect in bright neon green
void typewriterNeonEffect(const string &text, int delay = 80) {
    cout << neonGreen; // Set text colour to bright neon green
    for (const auto &c : text) {
        cout << c << flush;
        this_thread::sleep_for(chrono::milliseconds(delay));
    }
    cout << reset << endl; // Reset colour and move to the next line
}

// Function to clear screen (macOS/Linux compatible)
void clearScreen() {
    system("clear");
}

// Function to pause for user input (macOS/Linux compatible)
void pauseProgram() {
    cout << neonGreen << "Press Enter to continue..." << reset;
    cin.ignore();
    cin.get();
}

// Intro function using typewriter effect
void intro() {
    typewriterNeonEffect("\n\n\n\t\t\t\t\t==========================================", 50);
    typewriterNeonEffect("\t\t\t\t\t DATA STRUCTURE AND ALGORITHM LAB", 50);
    typewriterNeonEffect("\t\t\t\t\t WELCOME TO OUR PROJECT (PBL)", 100);
    typewriterNeonEffect("\t\t\t\t\t==========================================", 50);

    this_thread::sleep_for(chrono::seconds(1)); // Pause for 1 second

    typewriterNeonEffect("\n\tTOPIC : DIET RECOMMENDATION SYSTEM", 100);
    typewriterNeonEffect("\t===========================================", 50);
    typewriterNeonEffect("\tSUBMITTED BY :", 100);
    typewriterNeonEffect("\t===========================================", 50);

    // Names
    typewriterNeonEffect("\t1. Vanshika Kapoor", 100);
    typewriterNeonEffect("\t2. Udit Gaur", 100);
    typewriterNeonEffect("\t3. Hitendra", 100);
    typewriterNeonEffect("\t4. Svayam", 100);

    this_thread::sleep_for(chrono::seconds(1)); // Pause for 1 second
    pauseProgram();
    clearScreen();
}
struct UserData{
    int age;
    double weight;
    int height;
    double bmi;
    string profession;
    string isVegetarian;
    int kcal;
    string isgain;
    string gender;
};

void read_data(string gender,string pre, int min_age, int max_age,string profession, vector<string>& matchage) {
    fstream fin;
    int age;
    fin.open("class.csv", ios::in);

    vector<string> row;
    string line, word, temp;
    bool skipFirstRow = true;

    while (getline(fin, line)) {
        row.clear();
        stringstream s(line);

        while (getline(s, word, ',')) {
            row.push_back(word);
        }

        if (skipFirstRow) {
            skipFirstRow = false;
            continue;
        }

        if (row.size() > 2) {
            if (row[10] == gender) {
                if(row[6] == pre){
                    if(row[8] == profession){
                        try {
                            age = stoi(row[2]);
                            if (age >= min_age && age <= max_age) {
                                matchage.push_back(row[0]);
                            }
                        } catch (const invalid_argument& e) {
                            cerr << "Error: Cannot convert age to an integer in row: " << line << endl;
                        }
                    }
                }    
            }
        }
    }
    fin.close();
}

void read_BMI(double bmi,vector<string>& matchbmi){
    fstream fin;
    fin.open("class.csv",ios::in);

    vector<string> row;
    string line, word, temp;
    bool skipFirstRow = true;

    while (getline(fin, line)) {
        row.clear();
        stringstream s(line);

        while (getline(s, word, ',')) {
            row.push_back(word);
        }

        if (skipFirstRow) {
            skipFirstRow = false;
            continue;
        }

        if (row.size() > 5) {
            try {
                double bmi2 = stod(row[5]);
                //cout<< bmi2;
                if (bmi2 == bmi) {
                    matchbmi.push_back(row[0]);
                }
            } catch (const invalid_argument& e) {
                cerr << "Error: Cannot convert age to an integer in row: " << line << endl;
            }
        }
    }
    fin.close(); 
}


//calculate BMI func
double BMI(double weight,double height){
    //store the height in Meter
    double h1=height/100.0;
    double bmi= weight/(h1*h1);
    return bmi;

}


void calculate_avg_ratings(const vector<string>& pids) {
    fstream fin;
    fin.open("ratings.csv", ios::in);

    vector<string> row;
    string line, word, temp;
    bool skipFirstRow = true;

    map<string, vector<pair<string, double> > > ratingsMap;

    while (getline(fin, line)) {
        row.clear();
        stringstream s(line);

        while (getline(s, word, ',')) {
            row.push_back(word);
        }

        if (skipFirstRow) {
            skipFirstRow = false;
            continue;
        }

        if (row.size() >= 3) {
            if (find(pids.begin(), pids.end(), row[0]) != pids.end()) {
                const string& pid = row[0];
                const string& fid = row[1];
                double rating = stod(row[2]);
                ratingsMap[pid].push_back(make_pair(fid, rating));
            }
        }
    }
    fin.close();

    for (const auto& entry : ratingsMap) {
        const string& pid = entry.first;
        const vector<pair<string, double> >& ratings = entry.second;

        cout << "PID: " << pid << endl;
        double sum = 0.0;

        for (const auto& fidRating : ratings) {
            const string& fid = fidRating.first;
            const double rating = fidRating.second;

            cout << "FID: " << fid << ", Rating: " << rating << endl;
            sum += rating;
        }

        double avgRating = ratings.empty() ? 0.0 : sum / ratings.size();
        cout << "Average Rating: " << avgRating << endl;
        cout << "------------------------------" << endl;
    }
}


void calculate_avg_rating_for_fid(const string& targetFID) {
    fstream ratingsFile;
    ratingsFile.open("ratings.csv", ios::in);

    //map to store ratings for the given FID
    map<string, vector<double> > ratingsMap;

    vector<string> row;
    string line, word;
    bool skipFirstRow = true;

    //ratings data and populate the ratingsMap
    while (getline(ratingsFile, line)) {
        row.clear();
        stringstream s(line);

        while (getline(s, word, ',')) {
            row.push_back(word);
        }

        if (skipFirstRow) {
            skipFirstRow = false;
            continue;
        }

        if (row.size() >= 3) {
            string fid = row[1];
            double rating = stod(row[2]);

            //FID matches the target FID
            if (fid == targetFID) {
                ratingsMap[targetFID].push_back(rating);
            }
        }
    }

    ratingsFile.close();

    // Calculate the average rating for the target FID
    double avgRating = 0.0;
    if (!ratingsMap[targetFID].empty()) {
        vector<double>& ratings = ratingsMap[targetFID];

        // Calculate the average rating
        double sum = accumulate(ratings.begin(), ratings.end(), 0.0);
        avgRating = sum / ratings.size();
    }

    // Print the average rating and find the FID's name from food.csv
    if (avgRating > 0) {
        fstream foodFile;
        foodFile.open("food.csv", ios::in);

        bool found = false;
        while (getline(foodFile, line)) {
            row.clear();
            stringstream s(line);

            while (getline(s, word, ',')) {
                row.push_back(word);
            }

            if (row.size() >= 2 && row[0] == targetFID) {
                cout << "FID: " << targetFID << ", Name: " << row[2] << ", Average Rating: " << avgRating << endl;
                found = true;
                break;
            }
        }

        foodFile.close();

        if (!found) {
            cout << "FID: " << targetFID << ", Name: Not Found, Average Rating: " << avgRating << endl;
        }
    } else {
        cout << "FID: " << targetFID << ", No ratings found" << endl;
    }
}


void calculate_similarity(int age, double weight, int height, double bmi, string isveg, string profe, string gender, const vector<string>& matchingPIDs) {
    fstream fin;
    fin.open("class.csv", ios::in);

    vector<string> row;
    string line, word;
    bool skipFirstRow = true;

    double dage = 0.3;
    double dweight = 0.2;
    double dheight = 0.2;
    double dbmi = 0.1;
    double disveg = 0.05;
    double dprofe = 0.05;
    double dgender = 0.1;

    double totalWeight = dage + dweight + dheight + dbmi + disveg + dprofe + dgender;

    map<string, double> similarityScores;  // Store PID -> Similarity Score

    while (getline(fin, line)) {
        row.clear();
        stringstream s(line);

        while (getline(s, word, ',')) {
            row.push_back(word);
        }

        if (skipFirstRow) {
            skipFirstRow = false;
            continue;
        }

        // Check if the PID is in the matchingPIDs array
        if (row.size() >= 8 && find(matchingPIDs.begin(), matchingPIDs.end(), row[0]) != matchingPIDs.end()) {
            int dbAge = stoi(row[2]);
            double dbWeight = stod(row[3]);
            int dbHeight = stoi(row[4]);
            double dbBmi = stod(row[5]);
            string dbIsVeg = row[6];
            string dbProfe = row[8];
            string dbGender = row[10];

            // Calculate the weighted similarity for each attribute
            double ageSimilarity = dage * (1.0 - abs(age - dbAge) / static_cast<double>(age));
            double weightSimilarity = dweight * (1.0 - abs(weight - dbWeight) / weight);
            double heightSimilarity = dheight * (1.0 - abs(height - dbHeight) / static_cast<double>(height));
            double bmiSimilarity = dbmi * (1.0 - abs(bmi - dbBmi) / bmi);
            double isvegSimilarity = (isveg == dbIsVeg) ? disveg : 0.0;
            double profeSimilarity = (profe == dbProfe) ? dprofe : 0.0;
            double genderSimilarity = (gender == dbGender) ? dgender : 0.0;

            // Calculate the total similarity for this row
            double rowSimilarity = (ageSimilarity + weightSimilarity + heightSimilarity + bmiSimilarity +
                                    isvegSimilarity + profeSimilarity + genderSimilarity) / totalWeight;

            // Store the similarity score in the map with the PID as the key
            similarityScores[row[0]] = rowSimilarity;
        }
    }
    fin.close();

    // Print similarity scores for the matching PIDs
    cout << "Matching PIDs and their Similarity Scores:\n";
    for (const auto& pair : similarityScores) {
        cout << "PID: " << pair.first << ", Similarity Score: " << pair.second << endl;
    }
}

// Structure to hold PID and its similarity score
struct PIDSimilarity {
    string pid;
    double similarityScore;
};

// Quicksort Implementation to sort PIDSimilarity vector in descending order of similarity scores
int partition(vector<PIDSimilarity> &arr, int low, int high) {
    double pivot = arr[high].similarityScore;
    int i = low - 1;

    for(int j = low; j <= high -1; j++) {
        if(arr[j].similarityScore >= pivot) { // Descending order
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i+1], arr[high]);
    return (i+1);
}

void quickSort(vector<PIDSimilarity> &arr, int low, int high) {
    if(low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi -1);
        quickSort(arr, pi +1, high);
    }
}

bool binarySearch(const vector<PIDSimilarity> &sortedList, const string &target) {
    int left = 0, right = sortedList.size() - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (sortedList[mid].pid == target) {
            return true; // Target found
        } else if (sortedList[mid].pid < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return false; // Target not found
}

void recordFoodRatings(map<string, double>& foodRatings) {
    map<string, string> foodData; // FID -> Food Name
    fstream foodFile;
    foodFile.open("food.csv", ios::in);

    vector<string> row;
    string line, word;
    bool skipFirstRow = true;

    while (getline(foodFile, line)) {
        row.clear();
        stringstream s(line);

        while (getline(s, word, ',')) {
            row.push_back(word);
        }

        if (skipFirstRow) {
            skipFirstRow = false;
            continue;
        }

        if (row.size() >= 2) {
            foodData[row[0]] = row[2]; // Store FID and Food Name
        }
    }
    foodFile.close();

    string ratefood;

    cout << "Do you want to rate foods? (yes or no): ";
    cin >> ratefood;

    if (ratefood == "no" || ratefood == "n") {
        cout << "Exiting the food rating process." << endl;
        return;
    }
    if (ratefood == "yes" || ratefood == "y"){
        cout << "FID - Food Name" << endl;
            for (const auto& food : foodData) {
                cout << food.first << " - " << food.second << endl;
        }
    }

    while (ratefood != "exit") {
        cout << "\nChoose a food item to rate:" << endl;

        string fid;
        double rating;

        cout << "Enter the FID of the food item (or 'exit' to exit): ";
        cin >> fid;

        if (fid == "exit") {
            cout << "Exiting the food rating process." << endl;
            break; // Exit loop
        }

        //enter the FID valid
        if (foodData.find(fid) != foodData.end()) {
            cout << "Rate the food item (out of 5): ";
            cin >> rating;

            if (rating >= 1.0 && rating <= 5.0) {
                // rating store
                foodRatings[fid] = rating;
                cout << "Rating recorded for " << foodData.at(fid) << endl;
            } else {
                cout << "Invalid rating. Please enter a rating between 1 and 5." << endl;
            }
        } else {
            cout << "Invalid FID. Please enter a valid FID." << endl;
        }
    }
}


double calculateAverageUserRating(const map<string, double>& foodRatings) {
    if (foodRatings.empty()) {
        return 0.0;  // No ratings given
    }

    double totalRating = 0.0;
    int numberOfRatings = 0;

    for (const auto& pair : foodRatings) {
        totalRating += pair.second;  // Sum all the ratings
        numberOfRatings++;
    }

    double averageRating = totalRating / numberOfRatings;

    return averageRating;
}

double calculateAvgRatingForPID(const string& targetPID) {
    fstream ratingsFile;
    ratingsFile.open("ratings.csv", ios::in);

    // Map to store ratings for the given PID
    map<string, vector<double> > ratingsMap;

    vector<string> row;
    string line, word;
    bool skipFirstRow = true;

    // Read ratings data and populate the ratingsMap
    while (getline(ratingsFile, line)) {
        row.clear();
        stringstream s(line);

        while (getline(s, word, ',')) {
            row.push_back(word);
        }

        if (skipFirstRow) {
            skipFirstRow = false;
            continue;
        }

        if (row.size() >= 3) {
            string pid = row[0];
            double rating = stod(row[2]);

            // PID matches the target PID
            if (pid == targetPID) {
                ratingsMap[targetPID].push_back(rating);
            }
        }
    }

    ratingsFile.close();

    // Calculate the average rating for the target PID
    double avgRating = 0.0;
    if (!ratingsMap[targetPID].empty()) {
        vector<double>& ratings = ratingsMap[targetPID];

        // Calculate the average rating
        double sum = accumulate(ratings.begin(), ratings.end(), 0.0);
        avgRating = sum / ratings.size();
    }

    return avgRating;
}



void findMatchingFIDs(const vector<string>& matchingPIDs, const map<string, double>& userRatedFIDs, double useravgrating, double pidavgrating) {
    map<string, set<string> > pidToRatedFIDs;

    fstream ratingsFile;
    ratingsFile.open("ratings.csv", ios::in);

    vector<string> row;
    string line, word;
    bool skipFirstRow = true;

    // Read the ratings data and populate the pidToRatedFIDs map
    while (getline(ratingsFile, line)) {
        row.clear();
        stringstream s(line);

        while (getline(s, word, ',')) {
            row.push_back(word);
        }

        if (skipFirstRow) {
            skipFirstRow = false;
            continue;
        }

        if (row.size() >= 3) {
            string pid = row[0];
            string fid = row[1];
            double rate = stod(row[2]);

            // Check if the PID is one of the matching PIDs
            if (find(matchingPIDs.begin(), matchingPIDs.end(), pid) != matchingPIDs.end()) {
                pidToRatedFIDs[pid].insert(fid);
            }
        }
    }

    ratingsFile.close();

    vector<pair<string, double> > matchingFIDsAndRatings;

    // Find FIDs rated by both the user and matching PIDs
    for (const auto& pair : pidToRatedFIDs) {
        const set<string>& pidRatedFIDs = pair.second;

        for (const string& fid : pidRatedFIDs) {
            if (userRatedFIDs.find(fid) != userRatedFIDs.end()) {
                // Fetch the user's rating for this FID
                double userRating = userRatedFIDs.at(fid);
                double pidRating = 0.0;  // You need to fetch the PID's rating for this FID from your data

                // Calculate the correlation for this FID
                double userAvgRating = useravgrating;
                double pidAvgRating = pidavgrating;

                double userDiff = userRating - userAvgRating;
                double pidDiff = pidRating - pidAvgRating;

                double numerator = userDiff * pidDiff;
                double userSquaredDiff = userDiff * userDiff;
                double pidSquaredDiff = pidDiff * pidDiff;

                double denominator = sqrt(userSquaredDiff * pidSquaredDiff);

                // Avoid division by zero by checking the denominator
                if (denominator != 0.0) {
                    double correlationValue = numerator / denominator;
                    cout << "FID: " << fid << ", User Rating: " << userRating << ", Correlation: " << correlationValue << endl;
                } else {
                    cout << "FID: " << fid << ", User Rating: " << userRating << ", Correlation: undefined (division by zero)" << endl;
                }
            }
        }
    }
}

int main() {
    UserData userInput;
    intro();
    // Taking user data
    typewriterNeonEffect("Enter your Gender: ");
    cin >> userInput.gender;

    typewriterNeonEffect("Enter your age: ");
    cin >> userInput.age;

    typewriterNeonEffect("Enter your Height: ");
    cin >> userInput.height;

    typewriterNeonEffect("Enter your weight: ");
    cin >> userInput.weight;

    typewriterNeonEffect("Enter your profession: ");
    cin.ignore(); // Clear newline from previous input
    getline(cin, userInput.profession);

    typewriterNeonEffect("Enter your preference (veg/non-veg): ");
    cin >> userInput.isVegetarian;

    //typewriterNeonEffect("Do you want to gain weight or lose (gain/lose): ");
    //cin >> userInput.isgain;

    userInput.bmi = BMI(userInput.weight, userInput.height);
    userInput.bmi = round(userInput.bmi * 100) / 100;
    cout << neonGreen << "Calculated BMI: " << userInput.bmi << reset << "\n";

    // Vectors for matching data
    vector<string> matchage, matchbmi, matchingpidlist;

    // Matching data by age, gender, preference
    typewriterNeonEffect("Recommended calorie intake:");
    if (userInput.age >= 16 && userInput.age <= 22) {
        if (userInput.gender == "Male") {
            typewriterNeonEffect("16-22 years: About 2,200 - 2,800 calories per day");
        } else {
            typewriterNeonEffect("16-22 years: About 1,800 - 2,200 calories per day");
        }
        read_data(userInput.gender, userInput.isVegetarian, 16, 22, userInput.profession, matchage);
    }

    // Display matching PIDs by age
    if (!matchage.empty()) {
        typewriterNeonEffect("Matching PIDs by age:");
        for (const string& pid : matchage) {
            cout << neonGreen << pid << reset << endl;
            matchingpidlist.push_back(pid);
        }
    } else {
        typewriterNeonEffect("No matching data found for age and criteria.");
    }

    // Matching BMI data
    typewriterNeonEffect("Do you want to check who has a similar BMI? (yes/no)");
    string checkBMI;
    cin >> checkBMI;
    if (checkBMI == "yes" || checkBMI == "y")
        read_BMI(userInput.bmi, matchbmi);
    else
        typewriterNeonEffect("No matching data found for BMI.");




    calculate_similarity(userInput.age,userInput.weight,userInput.height,userInput.bmi,userInput.isVegetarian,userInput.profession,userInput.gender,matchingpidlist);
//find and print ratings for matching pid
     calculate_avg_ratings(matchingpidlist);

//check rating of a particular food and print name and avg rating
    string check_rating;
    string f;
    while (true) {
        cout << "Do you want to see what others have given rating to any particular food item? (y/n): ";
        cin >> check_rating;

        if (check_rating == "n") {
            break;
        } else if (check_rating == "y") {
            cout << "Please provide the FID: ";
            cin >> f;
            calculate_avg_rating_for_fid(f);
        } else {
            cout << "Invalid input. Please enter 'y' for yes or 'n' for no." << endl;
        }
    }

    map<string, double> foodRatings;

    recordFoodRatings(foodRatings);

    double userAverageRating = calculateAverageUserRating(foodRatings);
    cout << "Your average Rating: " << userAverageRating << endl;

    string targetPID;
    cout << "Enter the PID with whom you want to find correlation: ";
    cin >> targetPID;
    double avgRating = calculateAvgRatingForPID(targetPID);
    cout << "Average Rating for " << targetPID << ": " << avgRating << endl;

    findMatchingFIDs(matchingpidlist, foodRatings, userAverageRating, avgRating);

    return 0;    

}

//