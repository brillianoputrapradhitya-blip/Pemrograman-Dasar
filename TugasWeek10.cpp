#include <iostream>
#include <iomanip>
#include <string>
#include <cctype>

const int studentAmount = 20;

struct studentType{
    std::string studentFName;
    std::string studentLName;
    int testScore;
    char grade;

};

studentType student[studentAmount];
std::string fullName[studentAmount];
int studentInputAmount = 0;

void ReadData(studentType (&studentInfo)[studentAmount]);            //To input and read the data of students
void Grading(studentType (&studentGraded)[studentAmount]);           //Assign grade for each students
void FindHighestScore(studentType (&studentHighest)[studentAmount]); //Find the highest score
void PrintHighestScore(int tempVar);                                 //Print the student who got the highest score

void NameConcatFunc(studentType (&fLName)[studentAmount]);           //Extra function to print the fullname
void PrintAll(studentType (&allStudents)[studentAmount]); //Function to print the student's data with left justification ON EACH COLUMN TABLE!!!


int main(){
    ReadData(student);
    Grading(student);
    NameConcatFunc(student);    
    PrintAll(student);
    FindHighestScore(student);

    return 0;
}



void ReadData(studentType (&studentInfo)[studentAmount]){
    for(int i = 0; i < studentAmount; i++){
        std::cout << "Enter student " << i+1 << " first name: ";
        std::getline(std::cin, studentInfo[i].studentFName);
        
        std::cout << "Enter student " << i+1 << " last name: ";
        std::getline(std::cin, studentInfo[i].studentLName);

        std::cout << "Enter student " << i+1 << " test score: ";
        std::cin >> studentInfo[i].testScore;
        std::cin.ignore();

        studentInputAmount = i + 1;

        if (i == (studentAmount-1)) break;

        std::cout << "Input again? (y/n): ";
        char loopBool;
        loopBool = tolower(loopBool);
        std::cin >> loopBool;
        std::cin.ignore();

        if(loopBool != 'y') break;
        
    }

}

void Grading(studentType (&studentGraded)[studentAmount]){
    for(int i = 0;i < studentAmount; i++){
        if(90 <= studentGraded[i].testScore && studentGraded[i].testScore <= 100){
            studentGraded[i].grade = 'A';
        } else if(80 <= studentGraded[i].testScore && studentGraded[i].testScore <= 89){
            studentGraded[i].grade = 'B';
        } else if(70 <= studentGraded[i].testScore && studentGraded[i].testScore <= 79){
            studentGraded[i].grade = 'C';
        } else if(60 <= studentGraded[i].testScore && studentGraded[i].testScore <= 69){
            studentGraded[i].grade = 'D';
        } else if(50 <= studentGraded[i].testScore && studentGraded[i].testScore <= 59){
            studentGraded[i].grade = 'E';
        } else if(studentGraded[i].testScore <= 49){
            studentGraded[i].grade = 'F';
        }

    }
}

void FindHighestScore(studentType (&studentHighest)[studentAmount]){
    int tempVar = 0;
    for(int i = 0; i < studentAmount; i++){
        if(studentHighest[i].testScore > studentHighest[tempVar].testScore){
            tempVar = i;
        }
    }

    PrintHighestScore(tempVar);
}

void PrintHighestScore(int tempVar){
    std::cout << "\nHIGHEST SCORE IS REACHED BY:\n" << fullName[tempVar] << " (" << student[tempVar].testScore << "/" << student[tempVar].grade 
        << ") \n";
}

void NameConcatFunc(studentType (&fLName)[studentAmount]){
    for(int i = 0; i < studentAmount; i++){
        fullName[i] = fLName[i].studentLName + ", " + fLName[i].studentFName;

    }

}

void PrintAll(studentType (&allStudents)[studentAmount]){
    std::cout << "\n\n" << std::string(22, '=') << "OUTPUT" << std::string(22, '=') << "\n\n";
    std::cout << std::left << std::setw(4) << "ID" << std::left << std::setw(25) << "Student's Name" << std::left << std::setw(15) << "Test Score"
        << std::left << std::setw(7) << "Grade" << "\n" << std::string(50, '=') << std::endl;
    
    for(int i = 0; i < studentInputAmount; i++){
        std::cout << std::left << std::setw(4) << i+1 << std::left << std::setw(25) << fullName[i] << std::left << std::setw(15) << student[i].testScore
            << std::left << std::setw(7) << student[i].grade << "\n"; 
    }


}
