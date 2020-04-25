//intial size of array
#define initial_size 1

//data from stdin is recorded here
typedef struct movie_data{
	char* color;
	char* director_name;
	int num_critic_for_reviews;
	//datetime?
	int duration; 
	int director_facebook_likes;
	int actor_3_facebook_likes;
	char* actor_2_name;
	int actor_1_facebook_likes;
	int gross;
	char* genres;
	char* actor_1_name;
	char* movie_title;
	int num_voted_users;
	int cast_total_facebook_likes;
	char* actor_3_name;
	int facenumber_in_poster;
	char* plot_keywords;
	char* movie_imdb_link;
	int num_user_for_reviews;
	char* language;
	char* country;
	char* content_rating;
	int budget;
	int title_year;
	int actor_2_facebook_likes;
	double imdb_score;
	double aspect_ratio;
	int movie_facebook_likes;
	
} Movie;

//int to str
char* notNum(char* str, int val);

//double to str
char* notDouble(char* str, double val);

//prints a movie struct element
//void printElement (Movie elem, FILE* fp);

//merge sort functions
void mergeArr(Movie array[], int close, int med, int back, char catagory[]);
void mergesort(Movie array[], int left, int right, char catagory[]);