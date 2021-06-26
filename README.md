# Netflix_Menu_System
Netflix-like Menu System Project


## Objective
***
* The objective of this project is to create a menu program as found in Netflix and other streaming services.
* The user would be able to add cateogories and movies respectively.

## Layout
***
* For the categories section, a Singly Linked List will be implemented so that the user could navigate up or down the menu. 
* For the movies section, a Circular Linked List will be used so that if the user reaches the end of the list, it will circulate back and repeat once again.

## Functions
***
* These are the important functions being used in this program:
	void addCategory(node_t *current, string name); //This will add a category
	void printCategories(node_t *start_category); //This will print the categories
	void addMovie(node_movie_t *movie_node, string movie, Date *date); //This will add a movie into a specific category
	void printMovies(node_movie_t *start_movie_node); //This will print the movies in the category
	void searchCategory(string name); //This will allow the user to search for a category
	void searchMovie(node_t *start_category, string movie_name); //This will allow the user to search for a movie
	int compareDates(Date *date1, Date *date2); //This will compare dates between each movie
	void printCategoriesAndMovies(node_t *start_category); //This will print all the categories and movies that the user has entered
	void removeMovies(node_t *start_category, Date date); //This will remove the movies according to a inputted date by the user
	int get_count(node_movie_t *start, node_movie_t *last); //This will check the number of movies inputted
	node_movie_t *get_middle(node_movie_t *start, node_movie_t *last); //This will get the middle of the list of movies
	node_movie_t *get_last(node_movie_t *start); //This will get the last at the end of the list of movies
	int searchMovieBinary(node_movie_t *start, string movieName); //This will search the movies in Binary Search form

## Instructions/Features
***
* This works like a normal menu system but the outputs will looks as though it's like it's in a list format
* To start the program, the user would need to input a number, which is their choice. It is suggested to start with the first option, where the user can enter a category of their choice. 
* After that, the user will be able to do what they would like in this program for example, adding a movie, searching for a category, etc.
* To end a section in the program, the user would be required to enter the word "END".
* To exit the entire program, the user would need to enter the number 0 and the program will terminate itself.
* There is also a clear Terminal/Command Prompt option, if the user finds their terminal messy, they could use that.
