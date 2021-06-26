#include <iostream>
#include <vector>
#include <stdlib.h>
#include <string>
#include <cstring>
#include <cmath>

using namespace std;

typedef struct node node_t;
typedef struct movie_node node_movie_t;

typedef struct
{
    int day;
    int month;
    int year;
} Date;

struct node
{
    string category;
    node_movie_t *movies;
    node_t *next_category;
};

struct movie_node
{
    string name;
    node_movie_t *next_movie;
    Date *date;
};

//Function Calls
void addCategory(node_t *current, string name);
void printCategories(node_t *start_category);
void addMovie(node_movie_t *movie_node, string movie, Date *date);
void printMovies(node_movie_t *start_movie_node);
void searchCategory(string name);
void searchMovie(node_t *start_category, string movie_name);
int compareDates(Date *date1, Date *date2);
void printCategoriesAndMovies(node_t *start_category);
void removeMovies(node_t *start_category, Date date);
int get_count(node_movie_t *start, node_movie_t *last);
node_movie_t *get_middle(node_movie_t *start, node_movie_t *last);
node_movie_t *get_last(node_movie_t *start);
int searchMovieBinary(node_movie_t *start, string movieName);

//Get Count Function
int get_count(node_movie_t *start, node_movie_t *last)
{
    if (start == NULL)
    {
        return 0;
    }

    node_movie_t *temp = start;
    int count = 1;
    while (temp->name != last->name) //This will check the number of movies in the list
    {
        temp = temp->next_movie;
        count++;
    }

    return count;
}

//Get Last Function
node_movie_t *get_last(node_movie_t *start)
{

    node_movie_t *temp = start;
    while (temp->next_movie->name != start->name) //This will locate the last movie in the list 
    {
        temp = temp->next_movie;
    }

    return temp;
}

//Get Middle Function
node_movie_t *get_middle(node_movie_t *start, node_movie_t *last)
{
    int list_size = get_count(start, last);
    if (list_size == 1)
    {
        return start;
    }
    int middle_index = (int)floor(list_size / 2.0); 
    node_movie_t *middle_movie = start;

    for (int i = 0; i < middle_index; i++) //This will check and find the middle index
    {
        middle_movie = middle_movie->next_movie;
    }

    return middle_movie;
}

//Search Movie in Binary Search Function
int searchMovieBinary(node_movie_t *start, string movieName)
{

    node_movie_t *last = get_last(start);
    int list_size = get_count(start, last);

    //If the list is empty, return 0
    if (list_size == 0)
    {
        return 0;
    }

    node_movie_t *middle = get_middle(start, last);
    while (middle != start)
    {   
        //If the name in middle matches with the movie name
        if (middle->name == movieName)
        {
            return 1;
        }

        if (get_count(start, last) == 2)
        {
            if (start->name == movieName || last->name == movieName)
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }

        //Checks if the string is less than 0
        if (strcmp(movieName.c_str(), middle->name.c_str()) < 0)
        {
            last = middle;
        }

        //Check if string is more than 0
        else if (strcmp(movieName.c_str(), middle->name.c_str()) > 0)
        {
            start = middle;
        }
        middle = get_middle(start, last);
    }

    return 0;
}

//Add Category Function
void addCategory(node_t *current, string name)
{

    node_t *new_category = new node_t();
    new_category->movies = NULL;

    new_category->category = name; //This will allow to add a category in a singly linked list format

    current->next_category = new_category;
}

//Search Category Function
node_t *searchCategory(node_t *start_node, string name)
{

    node_t *temp = start_node;
    while (temp != NULL)
    {
        if (temp->category == name)
        {
            return temp; //This will search the categories inputted and return if found
        }
        temp = temp->next_category;
    }

    return temp;
}

//Print Category Function
void printCategories(node_t *start_category)
{

    cout << endl;
    node_t *temp = start_category;
    while (temp != NULL)
    {
        if (temp->next_category == NULL)
        {
            cout << temp->category << endl; //This will print the categories
        }

        else
        {
            cout << temp->category << " -> "; //This will print the categories and will add an arrow after each
        }
        temp = temp->next_category;
    }
}

//Add Movie Function
void addMovie(node_movie_t *start_movie_node, string movie, Date *date)
{
    node_movie_t *temp_check = start_movie_node;
    int count = 0;
    while (true)
    {
        if (temp_check->name == start_movie_node->name && count != 0)
        {
            break; //If movie name exists, it will be added and the function will break
        }
        if (temp_check->name == movie)
        {
            cout << "Movie already exists, so we can't add this one!" << endl; //If the movie name already exists, this message will show
            return;
        }
        temp_check = temp_check->next_movie;
        count++;
    }

    node_movie_t *new_movie = new node_movie_t();
    new_movie->name = movie;
    new_movie->date = date;

    node_movie_t *temp = start_movie_node;
    node_movie_t *prev = NULL;
    int count_2 = 0;
    while (true)
    {
        if (temp->name == start_movie_node->name && count_2 != 0)
        {
            break;
        }

        //If new movie is smaller then insert the movie in
        if (strcmp(new_movie->name.c_str(), temp->name.c_str()) < 0)
        {
            new_movie->next_movie = prev->next_movie;
            prev->next_movie = new_movie;
            return;
        }

        prev = temp;
        temp = temp->next_movie;
        count_2++;
    }

    //Inserting in movie if it is bigger than all existing movies
    prev->next_movie = new_movie;
    new_movie->next_movie = start_movie_node;
}

//Remove Movies Function
void removeMovies(node_t *start_category, Date date)
{
    node_t *temp = start_category;

    while (temp != NULL)
    {
        if (temp->movies != NULL)
        {
            int outerCount = 0;
            node_movie_t *temp_movie = temp->movies;
            node_movie_t *new_movie_list = NULL;
            while (true)
            {
                if (temp_movie->name == temp->movies->name && outerCount != 0) //This will break the loop
                {
                    break;
                }
                if (compareDates(temp_movie->date, &date))
                {
                    //If new movie list equals NULL, it will check through the list and through CLL, it will repeat itself
                    if (new_movie_list == NULL)
                    {
                        new_movie_list = new node_movie_t();
                        new_movie_list->name = temp_movie->name;
                        new_movie_list->next_movie = new_movie_list;
                    }

                    //Otherwise it will check and compare the dates
                    else
                    {
                        node_movie_t *temp_new = new_movie_list;
                        int count = 0;
                        while (true)
                        {
                            if (temp_new->name == new_movie_list->name && count != 0)
                            {
                                break;
                            }
                            temp_new = temp_new->next_movie;
                            count++;
                        }
                        temp_new->next_movie = new node_movie_t();
                        temp_new->next_movie->name = temp_movie->name;
                        temp_new->next_movie->next_movie = new_movie_list;
                    }
                }
                temp_movie = temp_movie->next_movie;
                outerCount++;
            }
            temp->movies = new_movie_list;
        }

        temp = temp->next_category;
    }
}

//Compare Date Function
int compareDates(Date *date1, Date *date2)
{
    //Compares the years
    if (date1->year > date2->year)
    {
        return 1;
    }
    else if (date1->year < date2->year)
    {
        return 0;
    }

    //Compares the months
    else
    {
        if (date1->month > date2->month)
        {
            return 1;
        }
        else if (date1->month < date2->month)
        {
            return 0;
        }

        //Compares the days
        else
        {
            if (date1->day >= date2->day)
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }
    }
}

//Print Movies Function
void printMovies(node_movie_t *start_movie_node)
{
    node_movie_t *temp = start_movie_node;
    int count = 0;
    cout << endl;
    while (true)
    {

        if (temp->next_movie->name == start_movie_node->name)
        {
            cout << temp->name << endl; //This will print the movies
            break;
        }

        else
        {
            cout << temp->name << " -> "; //This will print the movies and will add an arrow after each
        }
        temp = temp->next_movie;
    }
}

//Search Movie Function
void searchMovie(node_t *start_category, string movie_name)
{
    node_t *temp = start_category;

    while (temp != NULL)
    {
        int count = 0;
        node_movie_t *temp_movie = temp->movies;
        if (temp_movie != NULL)
        {
            while (true)
            {
                if (temp_movie->name == temp->movies->name && count != 0) //The list will loop then break
                {
                    break;
                }

                if (temp_movie->name == movie_name) //When movies exists, outputs the movie and it's respective index
                {
                    cout << "Yes! Movie Exists In " << temp->category << " at index: " << count << endl;
                    return;
                }
                count++;
                temp_movie = temp_movie->next_movie;
            }
        }
        temp = temp->next_category;
    }

    cout << "Sorry, the movie you're looking for doesn't exist." << endl;
}

//Print Categories and Movies Function
void printCategoriesAndMovies(node_t *start_category)
{
    node_t *temp = start_category;
    while (temp != NULL)
    {
        cout << "Category: " << temp->category << endl; //Prints out the categories found in the memory
        if (temp->movies != NULL)
        {
            printMovies(temp->movies); //Prints out the movies found the memory
            cout << endl;
        }
        temp = temp->next_category;
    }
}

//Main Function
int main()
{

    node_t *start_category = new node_t();
    start_category->movies = NULL;

    string input;
    int choice;

    while (true)
    {
        cout << " NN      NN  EEEEEE  TTTTTT  FFFFFF  LL      II    XX      XX" << endl;
        cout << " NN NN   NN  EE        TT    FF      LL      II     XX    XX" << endl;
        cout << " NN   NN NN  EEEE      TT    FFFF    LL      II        XX" << endl;
        cout << " NN      NN  EE        TT    FF      LL      II     XX    XX" << endl;
        cout << " NN      NN  EEEEEE    TT    FF      LLLLLL  II    XX      XX" << endl;
        cout << "\n" << endl;
        cout << "***************************************************************************************" << endl;
        cout << "Enter a number below to get started! To exit any mode, enter END.\n" << endl;
        cout << "1. Add Category, adds in category to category list." << endl;
        cout << "2. Search Category, enter name of category you would like to find." << endl;
        cout << "3. Search Movie, enter name of movie you would like to find." << endl;
        cout << "4. Remove Category, enter name of category you would like to remove." << endl;
        cout << "5. Delete Movie, deletes the movies released prior to the date entered." << endl;
        cout << "6. Print all the categories and movies that have been inputted." << endl;
        cout << "7. Select A Category you have entered." << endl;
        cout << "8. Clear Terminal/Command Prompt." << endl;
        cout << "0. Exit the program." << endl;
        cout << "***************************************************************************************" << endl;

        cout << "Choice: ";
        cin >> choice;

        switch (choice)
        {

        //Case 1 to add category
        case 1:
            while (true)
            {
                cout << "Enter a new category: " << endl;
                getline(cin >> ws, input); //User will input a category into the memory

                if (input == "END")
                { //When user enters END, this function will end
                    break;
                }

                if (start_category->category.length() == 0)
                {
                    start_category->category = input;
                    cout << input << endl;
                }

                else
                {
                    node_t *current = start_category;
                    while (current->next_category != NULL)
                    {
                        current = current->next_category;
                    }

                    addCategory(current, input);
                    printCategories(start_category);
                }
            }
            break;

        //Case 2 to search for a category
        case 2:
            while (true)
            {
                string searchName;
                cout << "Enter name of category you would like to search for: ";
                getline(cin >> ws, searchName); //User will input a category to search for
                if (searchName == "END")
                { //When user enters END, this function will end
                    break;
                }

                node_t *found_category = searchCategory(start_category, searchName);
                if (found_category == NULL) //If the category inputted doesn't exist
                {
                    cout << "Sorry, that category doesn't exist" << endl;
                    ;
                }
                else //If the category inputted exists
                {
                    cout << "Yes! The category exists!" << endl;
                }
            }
            break;

        //Case 3 to search for a movie
        case 3:
            while (true)
            {
                string searchMovieName;
                cout << "Enter the name of the movie you would like to search for: ";
                getline(cin >> ws, searchMovieName); //User will input a movie to search for
                if (searchMovieName == "END")
                { //When user enters END, this function will end
                    break;
                }
                searchMovie(start_category, searchMovieName);
            }
            break;

        //Case 4 to remove a respective category along with its movies
        case 4:
            while (true)
            {
                string searchName;
                cout << "Enter name of category you would like to remove: ";
                getline(cin >> ws, searchName); //User will enter a category to remove
                if (searchName == "END")
                { //When user enters END, this function will end
                    break;
                }

                node_t *temp = start_category;
                node_t *prev = NULL;

                while (temp != NULL)
                {
                    node_t *freeTemp;
                    if (temp->category == searchName)
                    {

                        //If node is the first in linked list
                        if (prev == NULL)
                        {
                            freeTemp = start_category;
                            start_category = start_category->next_category;
                            cout << "Removed " << searchName << " successfully!" << endl;
                            free(freeTemp);
                            break;
                        }

                        //If node is last in linked list
                        else if (temp->next_category == NULL)
                        {
                            free(temp);
                            prev->next_category = NULL;
                            cout << "Removed " << searchName << " successfully!" << endl;
                            break;
                        }

                        //If node is in the middle
                        else
                        {
                            prev->next_category = temp->next_category;
                            temp->next_category = NULL;
                            free(temp);
                            cout << "Removed " << searchName << " successfully!" << endl;
                            break;
                        }
                    }
                    prev = temp;
                    temp = temp->next_category;
                }

                //When it reaches the end of the list
                if (temp == NULL)
                {
                    cout << "Sorry, we can't remove it because the category doesn't exist!" << endl;
                }
            }
            break;

        //Case 5 to remove a movie by an inputted date
        case 5:
            while (true)
            {
                int day, month, year;
                cout << "Enter the deletion date (To Exit, enter 0/0/0): ";
                scanf("%d/%d/%d", &day, &month, &year); //User will enter the date of deletion
                if (day == 0 && month == 0 && year == 0)
                {
                    break;
                }
                Date date;
                date.day = day;
                date.month = month;
                date.year = year;
                removeMovies(start_category, date);
                printCategoriesAndMovies(start_category);
            }
            break;

        //Case 6 to print everything inputted by the user
        case 6:
            cout << "Here is the current list of categories and movies that you have inputted in the program: " << endl;
            printCategoriesAndMovies(start_category); //This will print all the categories and movies that's been in the memory
            break;

        //Case 7 to select a category
        case 7:
        {
            cout << "Enter in category name: ";
            string categoryName;
            cin >> categoryName;
            node_t *temp = start_category;
            while (temp != NULL)
            {
                if (temp->category == categoryName)
                { //If user inputted category matches with the category in memory
                    break;
                }
                temp = temp->next_category;
            }

            //If temp does not equal NULL, it will enter another menu system
            if (temp != NULL)
            {
                int exit = 0;
                while (true)
                {   
                    //To exit this loop
                    if (exit)
                    {
                        break;
                    }

                    cout << "\n***********************************************" << endl;
                    cout << "Enter a number below. To exit any mode, enter END.\n" << endl;
                    cout << "1. Add Movie in Alphabetical Order." << endl;
                    cout << "2. Search Movie by Name." << endl;
                    cout << "3. Print All Movies." << endl;
                    cout << "0. Exit" << endl;
                    cout << "**********************************************" << endl;

                    int choice;
                    cout << "Choice: ";
                    cin >> choice;

                    switch (choice)
                    {

                    //Case 1 to add movie in alphabetical order
                    case 1:
                        while (true)
                        {
                            //User enters the name of the movie
                            string movieName;
                            cout << "Enter your movie name: ";
                            getline(cin >> ws, movieName);
                            if (movieName == "END")
                            { //When user enters END, this function will end
                                break;
                            }

                            //User is asked to input the release date of the movie
                            cout << "Enter in date in the format (dd/mm/yy e.g. 14/5/1963): ";
                            int day, month, year;
                            scanf("%d/%d/%d", &day, &month, &year);
                            Date *date = new Date();
                            date->day = day;
                            date->month = month;
                            date->year = year;

                            node_movie_t *start_movie = temp->movies;

                            if (start_movie == NULL)
                            {
                                start_movie = new node_movie_t();
                                start_movie->name = movieName;
                                start_movie->date = date;
                                start_movie->next_movie = start_movie;
                                temp->movies = start_movie;
                                cout << start_movie->name << endl;
                            }
                            else if (strcmp(movieName.c_str(), start_movie->name.c_str()) < 0)
                            {
                                //If new_movie is smaller than all existing movies then it is placed at the start
                                node_movie_t *new_movie = new node_movie_t();
                                new_movie->name = movieName;
                                new_movie->date = date;

                                new_movie->next_movie = temp->movies;
                                temp->movies = new_movie;
                                printMovies(temp->movies);
                            }
                            else
                            {
                                addMovie(start_movie, movieName, date);
                                printMovies(start_movie);
                            }
                        }

                        break;

                    //Case 2 to search movie by name and get it's index
                    case 2:
                        while (true)
                        {
                            //User enters movie name
                            string searchMovieName;
                            cout << "Enter the name of the movie you would like to search for: ";
                            getline(cin >> ws, searchMovieName);
                            if (searchMovieName == "END")
                            { //When user enters END, this function will end
                                break;
                            }
                            int found = searchMovieBinary(temp->movies, searchMovieName);

                            //If the movie is found
                            if (found)
                            {
                                cout << "Yes, the movie exists in this category!" << endl;
                            }

                            //If the movie is not found
                            else
                            {
                                cout << "Sorry, the movie you are looking for doesn't exist" << endl;
                            }
                        }
                        break;

                    //Case 3 to print all movies
                    case 3:
                        cout << "Here is the current list of movies that are in the category: " << endl;
                        printMovies(temp->movies);
                        break;

                    //Case 0 to exit
                    case 0:
                        cout << "You have exited the section." << endl;
                        exit = 1;
                        break;
                    
                    //Default case to catch input errors
                    default:
                        cout << "ERROR! Please enter a valid number!" << endl;
                        break;
                    }
                }
            }

            //If temp equals NULL
            else
            {
                cout << "Sorry that category doesn't exist!" << endl;
                break;
            }
        }

        //Case 8 to clear the Terminal/Command Prompt
        case 8:
            system("clear");
            break;

        //Case 0 to exit the program
        case 0:
            cout << "\nThank you for using Netflix, you've now exited the program...\n" << endl;
            return 0;

        //Default case to catch error inputs
        default:
            cout << "\nERROR! Please enter a valid number!\n" << endl;
            break;
        }
    }

    return 0;
}
