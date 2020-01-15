//
// <<Maseeh Khan>>
// U. of Illinois, Chicago
// CS 251: Fall 2019
//
// Project #02: inputs movies and reviews, allowing the user to search
// by movie ID or movie Name.  Uses binary search trees for 
// fast search; no other data structures are allowed.
//

#include <iostream>
#include <fstream>
#include <string>
#include "bst.h"

using namespace std;

//
// Struct MovieData to hold infromation about each movie in the tree
//  (This will be our key)
//
struct MovieData
{
  string  Name;
  int     ID; 
  int     PubYear;
  int     Num5Stars;
  int     Num4Stars;
  int     Num3Stars;
  int     Num2Stars;
  int     Num1Stars;
};


//
// trim
//
// trims whitespace from beginning and end of string.
//
// Ref: https://stackoverflow.com/questions/25829143/trim-whitespace-from-a-string
// Modified: to handle empty strings, and strings of all blanks.
//
string trim(const string& str)
{
  size_t first = str.find_first_not_of(" \t\n\r");
  size_t last = str.find_last_not_of(" \t\n\r");

  if (first == string::npos && last == string::npos)  // empty, or all blanks:
    return "";
  else if (first == string::npos)  // no blanks at the start:
    first = 0;                     // 0-based
  else if (last == string::npos)   // no blanks trailing at end:
    last = str.length() - 1;       // 0-based

  return str.substr(first, (last - first + 1));
}


//
// InputMovies
//
// Inputs the data from the "movies" file, which contains N>0 lines, where
// each line contains:
//     id pubYear name
//
void InputMovies(string moviesFilename, binarysearchtree<int, MovieData> &movies_by_ID,
 binarysearchtree<string, MovieData> &movies_by_Name)
{
  ifstream moviesFile(moviesFilename);
  int      id, pubYear;
  string   name;

  if (!moviesFile.good())
  {
    cout << "**Error: unable to open movies file '" << moviesFilename << "', exiting" << endl;
    return;
  }

  moviesFile >> id;  // get first ID, or set EOF flag if file empty:

  while (!moviesFile.eof())
  {
    // we have more data, so input publication year and movie name:
    moviesFile >> pubYear;
    getline(moviesFile, name);  // movie name fills rest of input line:

    // trim potential whitespace from both ends of movie name:
    name = trim(name);  

    // debugging:
    // cout << id << "," << pubYear << "," << name << endl;

    // copy all the data from each movie into a new movieData struct
    MovieData data  =  MovieData();      // zero initliaze using Default Constructor. We are not using a dynamically allocated object because
    data.PubYear    =  pubYear;          // we don't want to use a pointer here.
    data.ID         =  id;               // for reference visit: https://stackoverflow.com/questions/5914422/proper-way-to-initialize-c-structs
    data.Name       =  name;             // note: Ask Professor Hummel about this dynamic allocation.

    // insert that data into both binary search trees
    movies_by_ID.insert(id, data);
    movies_by_Name.insert(name, data);

    moviesFile >> id;  // get next ID, or set EOF flag if no more data:
  }
}

//
// InputReviews
//
// Inputs the data from the "reviews" file, which contains N>0 lines, where
// each line contains:
//     reviewID movieID rating
//
void InputReviews(string reviewsFilename, binarysearchtree<int, MovieData> &movies_by_ID,
 binarysearchtree<string, MovieData> &movies_by_Name, int &numOfReviews)
{
  ifstream reviewsFile(reviewsFilename);
  int      reviewID, movieID, rating;

  if (!reviewsFile.good())
  {
    cout << "**Error: unable to open movies file '" << reviewsFilename << "', exiting" << endl;
    return;
  }

  reviewsFile >> reviewID;  // get first ID, or set EOF flag if file empty:

  while (!reviewsFile.eof())
  {
    // we have more data, so get movieID and rating:
    reviewsFile >> movieID;
    reviewsFile >> rating;      // Since the last value on each line is an int, we don't have to care about whitespace (i think)


    // debugging:
    // cout << reviewID << "," << movieID << "," << rating << endl;

    // insert that data into both binary search trees
    MovieData* Data = movies_by_ID.search(movieID);     // pointer because search(key) returns a pointer to the data struct
    if (Data != nullptr){
      MovieData* DataByName = movies_by_Name.search(Data->Name);  // Update Data struct in bst movies_by_Name. 
      if (rating == 5){
        Data->Num5Stars++;
        DataByName->Num5Stars++;               
      }                                         
      if (rating == 4){
        Data->Num4Stars++;
        DataByName->Num4Stars++;
      }
      if (rating == 3){
        Data->Num3Stars++;
        DataByName->Num3Stars++;
      }
      if (rating == 2){
        Data->Num2Stars++;
        DataByName->Num2Stars++;
      }
      if (rating == 1){
        Data->Num1Stars++;
        DataByName->Num1Stars++;
      }
    }


    numOfReviews++;
    reviewsFile >> reviewID;  // get next ID, or set EOF flag if no more data:
  }
}

//
// isID checks if the string input is an ID.
// Meaning it should have all numbers. If it does, return true.
// Otherwise, return false.
//
bool isID(string input)
{
  for (size_t x = 0; x < input.size(); ++x){
    if (!isdigit(input[x])){     // check if any character in the string passed is not a number
      return false;              // if so, return false because it's not an ID then
    }
  }
  return true;            // if we go through the entire string and all the characters are digits then we return true
}


//
// getAverage adds all the star reviews from a MovieData struct
//  and divides it by the total number of reviews to return
//  the average review
//
double getAverage(MovieData* data)
{
  int total = 0;                // total number of reviews
  int sum = 0;                  // sum of reviews weighted by their number
  int num5 = data->Num5Stars;
  int num4 = data->Num4Stars;
  int num3 = data->Num3Stars;
  int num2 = data->Num2Stars;
  int num1 = data->Num1Stars;
  total = num5 + num4 + num3 + num2 + num1;
  sum = (num5 * 5) + (num4 * 4) + (num3 * 3) + (num2 * 2) + num1;
  if (total == 0){
    return 0;
  }
  double average = static_cast<double>(sum) / total;   // implicitly converts total to a double as well before divison.
  return average;
}

//
// main
//
int main()
{
  string moviesFilename; // = "movies1.txt";
  string reviewsFilename; // = "reviews1.txt";

  cout << "movies file?> ";
  cin >> moviesFilename;

  cout << "reviews file?> ";
  cin >> reviewsFilename;

  string junk;
  getline(cin, junk);  // discard EOL following last input:


  binarysearchtree<int, MovieData>     movies_by_ID;     // A binary search tree of movies organized by their id number
  binarysearchtree<string, MovieData>  movies_by_Name;   // A binary search tree of movies organized by their name

  int numofReviews = 0;

  InputMovies(moviesFilename, movies_by_ID, movies_by_Name);
  InputReviews(reviewsFilename, movies_by_ID, movies_by_Name, numofReviews);

  cout << "Num movies: "  << movies_by_ID.size() << endl;
  cout << "Num reviews: " << numofReviews        << endl;

  cout << endl;

  cout << "Tree by movie id: size=" << movies_by_ID.size() << ", height=" << movies_by_ID.height() << endl;
  cout << "Tree by movie name: size=" << movies_by_Name.size() << ", height=" << movies_by_Name.height() << endl;
  cout << endl;


  string input;
  while (input != "#") // if # was entered, we don't enter the next loop
  {
    cout << "Enter a movie id or name (or # to quit)> ";
    getline(cin, input); // read entire input line and store it into string input
    if (input == "#"){
      cout << endl;
      break;             // quits current loop if # is entered
    }

    MovieData* Data; // We will have to make this a pointer to the data as the search function returns a pointer to the data or a nullptr if not found.

    if (isID(input)){
        Data = movies_by_ID.search(stoi(input));  // stoi converts the string input into an int
    } 
    else {
        Data = movies_by_Name.search(input);
    }

    if (Data == nullptr){
      cout << "not found..." << endl;
    }
    else{
      cout << "Movie ID: "  << Data->ID        << endl;
      cout << "Movie Name: "<< Data->Name      << endl;
      cout << "Avg rating: "<< getAverage(Data)<< endl;  
      cout << "5 stars: "   << Data->Num5Stars << endl;
      cout << "4 stars: "   << Data->Num4Stars << endl;
      cout << "3 stars: "   << Data->Num3Stars << endl;
      cout << "2 stars: "   << Data->Num2Stars << endl;
      cout << "1 star: "   << Data->Num1Stars << endl;
    }

    cout << endl;
  }
  

  // Test Cases for part 1

  
  // binarysearchtree<int, int>      bst1;
  // binarysearchtree<int, string>   bst2;
  // binarysearchtree<string, int>   bst3;

  // bst1.insert(123, 456);
  // bst2.insert(12, "cool");
  // bst3.insert("pie", 21);

  // int* value = bst1.search(123);
  // cout << *value << endl; // should output 456
  // *value = 789;
  // cout << *value << endl; // should output 789

  // string* sValue = bst2.search(12);
  // cout << *sValue << endl; // should output "cool"
  // *sValue = "amazing";
  // cout << *sValue << endl; // should output "amazing"

  // int* iValue = bst3.search("pie");
  // cout << *iValue << endl; // should output 21
  // *iValue = 42;
  // cout << *iValue << endl; // should output 42

  // bst1.inorder();
  // bst2.inorder();
  // bst3.inorder();

  // binarysearchtree<int, int>    copy1 = bst1; // copy construct

  // cout << bst1.size() << " vs. " << copy1.size() << endl;
  // cout << bst1.height() << " vs. " << copy1.height() << endl;
  // int* value1 = bst1.search(123);
  // int* value2 = copy1.search(123);
  // cout << *value1 << " vs. " << *value2 << endl; // both 456
  // *value2 = 789;      //this should only change bst2:
  // cout << *value1 << " vs. " << *value2 << endl; // 456 vs. 789



  // done:
  return 0;
}
