#include <sys/mman.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <errno.h>
#include <pthread.h>
#include <memory.h>
#include "multiThreadSorter_thread.h"


void printElement (Movie elem, FILE** fp){
	char* numeric_tmp = (char*)malloc(10);
	fprintf(*fp, "%s,", strcmp(elem.color, "~") == 0 ? "" :elem.color );
	fprintf(*fp, "%s,", strcmp(elem.director_name, "~") == 0? "": elem.director_name);
	fprintf(*fp, "%s,", elem.num_critic_for_reviews == -1? "" : notNum(numeric_tmp, elem.num_critic_for_reviews));
	fprintf(*fp, "%s,", elem.duration == -1? "" : notNum(numeric_tmp, elem.duration));
	fprintf(*fp, "%s,", elem.director_facebook_likes == -1? "" : notNum(numeric_tmp, elem.director_facebook_likes));
	fprintf(*fp, "%s,", elem.actor_3_facebook_likes == -1? "" : notNum(numeric_tmp, elem.actor_3_facebook_likes));
	fprintf(*fp, "%s,", strcmp(elem.actor_2_name, "~") == 0?"":elem.actor_2_name);
	fprintf(*fp, "%s,", elem.actor_1_facebook_likes == -1? "" : notNum(numeric_tmp, elem.actor_1_facebook_likes));
	fprintf(*fp, "%s,", elem.gross == -1 ? "" : notNum(numeric_tmp, elem.gross));
	fprintf(*fp, "%s,", strcmp(elem.genres, "~") == 0?"":elem.genres );
	fprintf(*fp, "%s,", strcmp(elem.actor_1_name, "~") == 0?"":elem.actor_1_name );
	fprintf(*fp, "%s,", strcmp(elem.movie_title, "~") == 0?"":elem.movie_title );
	fprintf(*fp, "%s,", elem.num_voted_users == -1 ? "" : notNum(numeric_tmp, elem.num_voted_users));
	fprintf(*fp, "%s,", elem.cast_total_facebook_likes == -1 ? "" : notNum(numeric_tmp, elem.cast_total_facebook_likes));
	fprintf(*fp, "%s,", strcmp(elem.actor_3_name, "~") == 0?"":elem.actor_3_name );
	fprintf(*fp, "%s,", elem.facenumber_in_poster == -1 ? "" : notNum(numeric_tmp, elem.facenumber_in_poster));
	fprintf(*fp, "%s,", strcmp(elem.plot_keywords, "~") == 0?"":elem.plot_keywords );
	fprintf(*fp, "%s,", strcmp(elem.movie_imdb_link, "~") == 0?"":elem.movie_imdb_link );
	fprintf(*fp, "%s,", elem.num_user_for_reviews == -1 ? "" : notNum(numeric_tmp, elem.num_user_for_reviews));	
	fprintf(*fp, "%s,", strcmp(elem.language, "~") == 0?"":elem.language );
	fprintf(*fp, "%s,", strcmp(elem.country, "~") == 0?"":elem.country );
	fprintf(*fp, "%s,", strcmp(elem.content_rating, "~") == 0?"":elem.content_rating );
	fprintf(*fp, "%s,", elem.budget == -1 ? "" : notNum(numeric_tmp, elem.budget));
	fprintf(*fp, "%s,", elem.title_year == -1 ? "" : notNum(numeric_tmp, elem.title_year));
	fprintf(*fp, "%s,", elem.actor_2_facebook_likes == -1 ? "" : notNum(numeric_tmp, elem.actor_2_facebook_likes));
	fprintf(*fp, "%s,", elem.imdb_score == -1 ? "" : notDouble(numeric_tmp, elem.imdb_score));
	fprintf(*fp, "%s,", elem.aspect_ratio == -1 ? "" : notDouble(numeric_tmp, elem.aspect_ratio));
	fprintf(*fp, "%s\n", elem.movie_facebook_likes == -1 ? "" : notNum(numeric_tmp, elem.movie_facebook_likes));
	free(numeric_tmp);
}

//tid to hold the thread ids, a mutex lock to be implimented later, and these are the argument structs for our functions... typedefing them breaks the code 
pthread_t tid[256];
pthread_mutex_t lock;
int pcounter;

pthread_t did[256];
pthread_t sid[256];
int dcounter;
int scounter;



void sort(char* path, char* col, char* dest, char* filename){
	Movie* arr = malloc(initial_size*sizeof(Movie));
	FILE *fp;
    char *line = NULL;
	char *first_line = (char*)malloc(sizeof(char)*1000);
    size_t len = 0;
    ssize_t read;
	fp = fopen(path, "r");
	if (fp == NULL){
		printf("FAILLL\n");
        exit(EXIT_FAILURE);
	}
	int i = 0;
	
	//puts each row into a struct
	for(i = 0; read = getline(&line, &len, fp) != -1; i++){
		
		//reallocation if exceeds initial size
		if(i%initial_size == 0 && i!=0){
			arr = realloc(arr, sizeof(Movie)*initial_size*(i/initial_size)+ initial_size*sizeof(Movie));
		}
		//breaks each comma to put values into struct fields
		char* tmp = malloc(1000);
		strcpy(tmp, line);
		char *tok = tmp, *end = tmp;
		strsep(&end, ",");
		arr[i].color = strdup(tok);
		if(arr[i].color[0] == '\0')
		{
			arr[i].color = "~";
		}
		tok = end;
		strsep(&end, ",");
		arr[i].director_name = strdup(tok);
		if(!arr[i].director_name)
		{
			arr[i].director_name = "~";
		}
		tok = end;		
		strsep(&end, ",");
		arr[i].num_critic_for_reviews = atoi(strdup(tok));
		if(arr[i].num_critic_for_reviews == '\0')
		{
			arr[i].num_critic_for_reviews = -1;
		}
		tok = end;
		strsep(&end, ",");
		arr[i].duration = atoi(strdup(tok));
		if(arr[i].duration == '\0')
		{
			arr[i].duration = 0;
		}
		tok = end;
		strsep(&end, ",");
		arr[i].director_facebook_likes = atoi(strdup(tok));
		if(arr[i].director_facebook_likes == '\0')
		{
			arr[i].director_facebook_likes = -1;
		}
		tok = end;
		strsep(&end, ",");
		arr[i].actor_3_facebook_likes = atoi(strdup(tok));
		if(arr[i].actor_3_facebook_likes == '\0')
		{
			arr[i].actor_3_facebook_likes = -1;
		}
		tok = end;
		strsep(&end, ",");
		arr[i].actor_2_name = strdup(tok);
		if(arr[i].actor_2_name == '\0')
		{
			arr[i].actor_2_name = "~";
		}

		tok = end;
		strsep(&end, ",");
		arr[i].actor_1_facebook_likes = atoi(strdup(tok));
		if(arr[i].actor_1_facebook_likes == '\0')
		{
			arr[i].actor_1_facebook_likes = -1;
		}	
		tok = end;
		strsep(&end, ",");
		arr[i].gross = atof(strdup(tok));
		if(!arr[i].gross)
		{
			arr[i].gross = -1;
		}
		tok = end;
		strsep(&end, ",");
		arr[i].genres = strdup(tok);
		if(arr[i].genres == '\0')
		{
			arr[i].genres = "~";
		}
	
		tok = end;
		strsep(&end, ",");
		arr[i].actor_1_name = strdup(tok);
		if(arr[i].actor_1_name == '\0')
		{
			arr[i].actor_1_name = "~";
		}
		tok = end;
		strsep(&end, ",");
		arr[i].movie_title = strdup(tok);
		if(arr[i].movie_title == '\0')
		{
			arr[i].movie_title = "~";
		}
		tok = end;
		char* title = (char*)malloc(sizeof(char)*1000);
		title = strdup(arr[i].movie_title);
		if(title[0] == '\"'){
			strsep(&end, "\"");
			strcat(arr[i].movie_title, ",");
			strcat(arr[i].movie_title, tok);
			tok = end;
			strcat(arr[i].movie_title, "\"");
		}
		free(title);
		strsep(&end, ",");
		arr[i].num_voted_users = atoi(strdup(tok));
		if(arr[i].num_voted_users == '\0')
		{
			arr[i].num_voted_users = -1;
		}
		tok = end;
		strsep(&end, ",");
		arr[i].cast_total_facebook_likes = atoi(strdup(tok));
		if(arr[i].cast_total_facebook_likes == '\0')
		{
			arr[i].cast_total_facebook_likes = -1;
		}
		tok = end;
		strsep(&end, ",");
		arr[i].actor_3_name = strdup(tok);
		if(arr[i].actor_3_name == '\0')
		{
			arr[i].actor_3_name = "~";
		}
		tok = end;
		strsep(&end, ",");
		arr[i].facenumber_in_poster = atoi(strdup(tok));
		if(arr[i].facenumber_in_poster == '\0')
		{
			arr[i].facenumber_in_poster = -1;
		}
		tok = end;
		strsep(&end, ",");
		arr[i].plot_keywords = strdup(tok);
		if(arr[i].plot_keywords == '\0')
		{
			arr[i].plot_keywords = "~";
		}
		tok = end;
		strsep(&end, ",");
		arr[i].movie_imdb_link = strdup(tok);
		if(arr[i].movie_imdb_link == '\0')
		{
			arr[i].movie_imdb_link = "~";
		}
		tok = end;
		strsep(&end, ",");
		arr[i].num_user_for_reviews = atoi(strdup(tok));
		if(arr[i].num_user_for_reviews == '\0')
		{
			arr[i].num_user_for_reviews = -1;
		}
		tok = end;
		strsep(&end, ",");
		arr[i].language = strdup(tok);
		if(arr[i].language == '\0')
		{
			arr[i].language = "~";
		}
		tok = end;
		strsep(&end, ",");
		arr[i].country = strdup(tok);
		if(arr[i].country == '\0')
		{
			arr[i].country = "~";
		}
		tok = end;
		strsep(&end, ",");
		arr[i].content_rating = strdup(tok);
		if(arr[i].content_rating == '\0')
		{
			arr[i].content_rating = "~";
		}
		tok = end;
		strsep(&end, ",");
		arr[i].budget = atof(strdup(tok));
		if(!arr[i].budget)
		{
			arr[i].budget = -1;
		}
		tok = end;
		strsep(&end, ",");
		arr[i].title_year = atoi(strdup(tok));
		if(arr[i].title_year == '\0')
		{
			arr[i].title_year = -1;
		}
		tok = end;
		strsep(&end, ",");
		arr[i].actor_2_facebook_likes = atoi(strdup(tok));
		if(arr[i].actor_2_facebook_likes == '\0')
		{
			arr[i].actor_2_facebook_likes = -1;
		}
		tok = end;
		strsep(&end, ",");
		arr[i].imdb_score = atof(strdup(tok));
		if(!arr[i].imdb_score)
		{
			arr[i].imdb_score = -1;
		}
		tok = end;
		strsep(&end, ",");
		arr[i].aspect_ratio = atof(strdup(tok));
		if(!arr[i].aspect_ratio)
		{
			arr[i].aspect_ratio = -1;
		}
		tok = end;
		strsep(&end, ",");
		arr[i].movie_facebook_likes = atoi(strdup(tok));
		if(arr[i].movie_facebook_likes == '\0')
		{
			arr[i].movie_facebook_likes = -1;
		}
		tok = end;
		free(tmp);
		
	}

	int total = i-1;
	int j =1;
	
	
	//checks to sort by which category
	char* catacory= (char*)malloc(sizeof(char)*1000);
	strcpy(catacory, col);

	if(strcmp(col,"director_name") == 0){
	mergesort(arr, 0, total, "director_name");
	}else{
		if(strcmp(col,"color") == 0){
			mergesort(arr, 0, total, "color");
		}else{
			if(strcmp(col,"num_critic_for_reviews") == 0){
					mergesort(arr, 0, total, "num_critic_for_reviews");
			}else{
				if(strcmp(col,"duration") == 0){
					mergesort(arr, 0, total, "duration");
				}else{
					if(strcmp(col,"director_facebook_likes") == 0){
						mergesort(arr, 0, total, "director_facebook_likes");
					}else{
						if(strcmp(col,"actor_3_facebook_likes") == 0){
							mergesort(arr, 0, total, "actor_3_facebook_likes");
						}else{
							if(strcmp(col,"actor_2_name") == 0){
								mergesort(arr, 0, total, "actor_2_name");
							}else{
								if(strcmp(col,"actor_1_facebook_likes") == 0){
									mergesort(arr, 0, total, "actor_1_facebook_likes");
								}else{
									if(strcmp(col,"gross") == 0){
										mergesort(arr, 0, total, "gross");
									}else{
										if(strcmp(col,"genres") == 0){
											mergesort(arr, 0, total, "genres");
										}else{
											if(strcmp(col,"actor_1_name") == 0){
												mergesort(arr, 0, total, "actor_1_name");
											}else{
												if(strcmp(col,"movie_title") == 0){
													mergesort(arr, 0, total, "movie_title");
												}else{
													if(strcmp(col,"num_voted_users") == 0){
														mergesort(arr, 0, total, "num_voted_users");
													}else{
														if(strcmp(col,"plot_keywords") == 0){
															mergesort(arr, 0, total, "plot_keywords");
															}else{
															if(strcmp(col,"movie_imdb_link") == 0){
																mergesort(arr, 0, total, "movie_imdb_link");
																	}else{
																		if(strcmp(col,"num_user_for_reviews") == 0){
																			mergesort(arr, 0, total, "num_user_for_reviews");
																		}else{	
																			if(strcmp(col,"language") == 0){
																				mergesort(arr, 0, total, "language");
																				}else{
																				if(strcmp(col,"country") == 0){
																					mergesort(arr, 0, total, "country");}else{
																					if(strcmp(col,"content_rating") == 0){
																						mergesort(arr, 0, total, "content_rating");}else{
																						if(strcmp(col,"budget") == 0){
																							mergesort(arr, 0, total, "budget");}else{
																							if(strcmp(col,"title_year") == 0){
																								mergesort(arr, 0, total, "title_year");}else{
																								if(strcmp(col,"actor_2_facebook_likes") == 0){
																									mergesort(arr, 0, total, "actor_2_facebook_likes");}else{
																										if(strcmp(col,"imdb_score") == 0){
																											mergesort(arr, 0, total, "imdb_score");}else{
																												if(strcmp(col,"aspect_ratio") == 0){
																													mergesort(arr, 0, total, "aspect_ratio");}else{
																													if(strcmp(col,"movie_facebook_likes") == 0){
																														mergesort(arr, 0, total, "movie_facebook_likes");}else{
																														fprintf( stderr, "Invalid input. Column does not exist.");
																															exit(-1);
	}
	}
	}
	}
	}
	}
	}
	}

																			}
																		}
																	}
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}


if(strcmp(col,"country") == 0)
	mergesort(arr, 0, total, "country");
	

if(strcmp(col,"content_rating") == 0)
	mergesort(arr, 0, total, "content_rating");

if(strcmp(col,"budget") == 0)
	mergesort(arr, 0, total, "budget");

if(strcmp(col,"title_year") == 0)
	mergesort(arr, 0, total, "title_year");

if(strcmp(col,"actor_2_facebook_likes") == 0)
	mergesort(arr, 0, total, "actor_2_facebook_likes");

if(strcmp(col,"imdb_score") == 0)
	mergesort(arr, 0, total, "imdb_score");

if(strcmp(col,"aspect_ratio") == 0)
	mergesort(arr, 0, total, "aspect_ratio");

if(strcmp(col,"movie_facebook_likes") == 0)
	mergesort(arr, 0, total, "movie_facebook_likes");



	//write to new file
	FILE *sorted_fp;
	//create output directory
	char* out_dest = (char*)malloc(1000);
	strcpy(out_dest, dest);	
	strcat(out_dest,"/");
	const char s[2] = ".";
	char* filename_tmp = (char*)malloc(50);
	strcpy(filename_tmp, filename);
	strcat(out_dest,strtok(filename_tmp,s));	
	strcat(out_dest,"-sorted-");
	strcat(out_dest,col);
	strcat(out_dest,".csv");
	sorted_fp = fopen(out_dest, "w");
	if (sorted_fp == NULL){
		printf("wae u do dis\n");
	 exit(EXIT_FAILURE);
	}
	fprintf(sorted_fp, "%s\n", "color,director_name,num_critic_for_reviews,duration,director_facebook_likes,actor_3_facebook_likes,actor_2_name,actor_1_facebook_likes,gross,genres,actor_1_name,movie_title,num_voted_users,cast_total_facebook_likes,actor_3_name,facenumber_in_poster,plot_keywords,movie_imdb_link,num_user_for_reviews,language,country,content_rating,budget,title_year,actor_2_facebook_likes,imdb_score,aspect_ratio,movie_facebook_likes");
	int e = 0;
	//adds each tuple to new file
	while(e < i){
		printElement(arr[e], &sorted_fp);	
		e++;
	}
	
	free(out_dest);
	fclose(fp);
	fclose(sorted_fp);
	free(filename_tmp);
	free(catacory);
   free(line);
   free(arr);
   free(first_line);
}



typedef struct dirp{
	char* path;
	char* catagory;
	char* end;
}dirp, *dp;

typedef struct sortp{
	char* path;
	char* col;
	char* dest;
	char* filename;
}sortp, *sp;

dp arga[256];
sp brga[256];


//Structs to hold the arguments for directory search function (dthre = d threads) and sort arguments (s threads = sthre) 
//char* path, char* col, char* dest, char* filename
void struct_it(sortp* a)
{
	//This is just a tester statement to make sure the threads are making it to the next function. The following statements just convert the new code into the old ones so the function doesnt need to be rewritten.
	
	char path[100];
	strcpy(path, a->path);
	char col[20];
	strcpy(col,a->col);
	char dest[100];
	strcpy(dest, a->dest);
	char filename[50];
	strcpy(filename, a->filename);


	Movie* arr = malloc(initial_size*sizeof(Movie));
	FILE *fp;
    char *line = NULL;
	//for adding to end of file
	char *first_line = (char*)malloc(sizeof(char)*1000);
	
	//for setting flags
	char flags[1000];
	
    size_t len = 0;
    ssize_t read;
	fp = fopen(path, "r");
	if (fp == NULL)
        exit(EXIT_FAILURE);

	//read the first line
	read = getline(&line, &len, fp);
	strcpy(first_line, line);
	strcpy(flags, line);
	
	char* flag_pointer = strtok(flags,",");
	//flag array
	char* flag_arr[29] = {""};
	int flag_counter = 0;
	
	while(flag_pointer!= NULL){
		flag_arr[flag_counter++] = flag_pointer;
		flag_pointer = strtok(NULL, ",");
	}
	
	int i = 0;
	
	//puts each row into a struct
	for(i = 0; read = getline(&line, &len, fp) != -1; i++){
	
		//reallocation if exceeds initial size
		if(i%initial_size == 0 && i!=0){
			arr = realloc(arr, sizeof(Movie)*initial_size*(i/initial_size)+ initial_size*sizeof(Movie));
		}
		//breaks each comma to put values into struct fields
		char* tmp = malloc(1000);
		strcpy(tmp, line);
		char *tok = tmp, *end = tmp;
		int j = 0;
		
		//initialise everything to be "null" value
		arr[i].color = "~";
		arr[i].director_name = "~";
		arr[i].num_critic_for_reviews = -1;
		arr[i].duration = -1;
		arr[i].director_facebook_likes = -1;
		arr[i].actor_3_facebook_likes = -1;
		arr[i].actor_2_name = "~";
		arr[i].actor_1_facebook_likes = -1;
		arr[i].gross = -1;
		arr[i].genres = "~";
		arr[i].actor_1_name = "~";
		arr[i].movie_title = "~";
		arr[i].num_voted_users = -1;
		arr[i].cast_total_facebook_likes = -1;
		arr[i].actor_3_name = "~";
		arr[i].facenumber_in_poster = -1;
		arr[i].plot_keywords = "~";
		arr[i].movie_imdb_link = "~";
		arr[i].num_user_for_reviews = -1;
		arr[i].language = "~";
		arr[i].country = "~";
		arr[i].content_rating = "~";
		arr[i].budget = -1;
		arr[i].title_year = -1;
		arr[i].actor_2_facebook_likes = -1;
		arr[i].imdb_score = -1;
		arr[i].aspect_ratio = -1;
		arr[i].movie_facebook_likes = -1;

		for(j = 0; flag_arr[j] != NULL ; j++){
			char new_tok[1000] = "";
			if(!strstr(flag_arr[j],"movie_title")){
				strsep(&end, ",");
				char* p = strchr(tok,'\n');
				if(p!=NULL){
					strncpy(new_tok, tok, strlen(tok)- 2);
				}else{
					strcpy(new_tok,tok);
				}
				
				if(strstr(flag_arr[j],"color")){
					if(tok != '\0'){
						arr[i].color = strdup(new_tok);
					}
				}
				if(strstr(flag_arr[j],"director_name")){
					if(tok != '\0'){
						arr[i].director_name = strdup(new_tok);
					}	
				}
				if(strstr(flag_arr[j],"num_critic_for_reviews")){				
					if(tok != '\0'){
						arr[i].num_critic_for_reviews = atoi(strdup(new_tok));
					}				
				}
				if(strstr(flag_arr[j],"duration")){				
					if(tok != '\0'){
						arr[i].duration = atoi(strdup(new_tok));
					}	
				}	
				if(strstr(flag_arr[j],"director_facebook_likes")){
					if(tok != '\0'){
						arr[i].director_facebook_likes = atoi(strdup(new_tok));
					}
				}
				if(strstr(flag_arr[j],"actor_3_facebook_likes")){
					if(tok != '\0'){
						arr[i].actor_3_facebook_likes = atoi(strdup(new_tok));
					}
				}
				if(strstr(flag_arr[j],"actor_2_name")){
					if(tok != '\0'){
						arr[i].actor_2_name = strdup(new_tok);
					}
				}
				if(strstr(flag_arr[j],"actor_1_facebook_likes")){
					if(tok != '\0'){
						arr[i].actor_1_facebook_likes = atoi(strdup(new_tok));
					}
				}	
				if(strstr(flag_arr[j],"gross")){
					if(tok != '\0'){
						arr[i].gross = atof(strdup(new_tok));
					}
				}
				if(strstr(flag_arr[j],"genres")){
					if(tok != '\0'){
						arr[i].genres = strdup(new_tok);
					}
				}
				if(strstr(flag_arr[j],"actor_1_name")){
					if(tok != '\0'){
						arr[i].actor_1_name = strdup(new_tok);
					}
				}	
				if(strstr(flag_arr[j],"num_voted_users")){
					if(tok != '\0'){
						arr[i].num_voted_users = atoi(strdup(new_tok));
					}
				}
				if(strstr(flag_arr[j],"cast_total_facebook_likes")){
					if(tok != '\0'){
						arr[i].cast_total_facebook_likes = atoi(strdup(new_tok));
					}
				}
				if(strstr(flag_arr[j],"actor_3_name")){
					if(tok != '\0'){
						arr[i].actor_3_name = strdup(new_tok);
					}
				}
				if(strstr(flag_arr[j],"facenumber_in_poster")){
					if(tok != '\0'){
						arr[i].facenumber_in_poster = atoi(strdup(new_tok));
					}
				}
				if(strstr(flag_arr[j],"plot_keywords")){
					if(tok != '\0'){
						arr[i].plot_keywords = strdup(new_tok);
					}
				}
				if(strstr(flag_arr[j],"movie_imdb_link")){
					if(tok != '\0'){
						arr[i].movie_imdb_link = strdup(new_tok);
					}
				}
				if(strstr(flag_arr[j],"num_user_for_reviews")){
					if(tok != '\0'){
						arr[i].num_user_for_reviews = atoi(strdup(new_tok));
					}
				}
				if(strstr(flag_arr[j],"language")){
					if(tok != '\0'){
						arr[i].language = strdup(new_tok);
					}
				}
				if(strstr(flag_arr[j],"country")){
					if(tok != '\0'){
						arr[i].country = strdup(new_tok);
					}
				}
				if(strstr(flag_arr[j],"content_rating")){				
					if(tok != '\0'){
						arr[i].content_rating = strdup(new_tok);
					}				
				}
				if(strstr(flag_arr[j],"budget")){				
					if(tok != '\0'){
						arr[i].budget = atof(strdup(new_tok));
					}				
				}
				if(strstr(flag_arr[j],"title_year")){				
					if(tok != '\0'){
						arr[i].title_year = atoi(strdup(new_tok));
					}				
				}
				if(strstr(flag_arr[j],"actor_2_facebook_likes")){				
					if(tok != '\0'){
						arr[i].actor_2_facebook_likes = atoi(strdup(new_tok));
					}				
				}
				if(strstr(flag_arr[j],"imdb_score")){				
					if(tok != '\0'){
						arr[i].imdb_score = atof(strdup(new_tok));
					}				
				}
				if(strstr(flag_arr[j],"aspect_ratio")){				
					if(tok != '\0'){
						arr[i].aspect_ratio = atof(strdup(new_tok));
					}			
				}
				if(strstr(flag_arr[j],"movie_facebook_likes")){			
					if(tok != '\0'){
						arr[i].movie_facebook_likes = atoi(strdup(new_tok));
					}				
				}
					tok = end;
			
			}else{
				strsep(&end, ",");
				arr[i].movie_title = strdup(tok);
				if(arr[i].movie_title == '\0'){
					arr[i].movie_title = "~";
				}
				tok = end;
				char* title = (char*)malloc(sizeof(char)*1000);
				title = strdup(arr[i].movie_title);
				if(title[0] == '\"'){
					strsep(&end, "\"");
					strcat(arr[i].movie_title, ",");
					strcat(arr[i].movie_title, tok);
					tok = end;
					strcat(arr[i].movie_title, "\"");
				}
				char* src = (char*)malloc(1000);
				strcpy(src, arr[i].movie_title);
				char* dest = (char*)malloc(1000);
				char* p = strchr(src,'\n');
				if(p!=NULL){
					strncpy(dest,src, strlen(src)-2);
					arr[i].movie_title = strdup(dest);
					
				}
				free(src);
				free(dest);
				free(title);
			}
		}
		free(tmp);
	}
	fclose(fp);
	int total = i-1;
	

	FILE *sorted_fp;
	//create output directory
	char* out_dest = (char*)malloc(1000);
	strcpy(out_dest, dest);	
	strcat(out_dest,"/");
	const char s[2] = ".";
	char* filename_tmp = (char*)malloc(50);
	strcpy(filename_tmp, filename);
	strcat(out_dest,strtok(filename_tmp,s));
	strcat(out_dest,".csv");
	sorted_fp = fopen(out_dest, "a");
	//adds first line to new file
	fflush(sorted_fp);
	//fprintf(sorted_fp, first_line);
	int k = 0;
	//adds each tuple to new file

	while(k < i){
		printElement(arr[k], &sorted_fp);
		k++;
	}
	fclose(sorted_fp);
	free(out_dest);
	free(filename_tmp);
   free(line);
   free(arr);
   free(first_line);
pthread_exit(1);

}


//const char *name, char *catagory, char *end
void listdir(dirp* a)
{
	//This part is a mess that I will clean up but a lot of it is for local thread creation so that every new thread is able to create even more threads. This is only for directory search tho since sorting doesnt create new threads
	
	//printf("\n I am a new thread currently in %s \n",a->path);
	//printf("\n catagory: %s \n", a->catagory);
	//Since most stuff is happening in this function I set 2 arrays of structs. These 2 arrays will hold the arguments for listdir and sort functions. Here I attempt to malloc them 
	

	
	char name[100];
	strcpy(name, a->path);
	char catagory[20];
	strcpy(catagory,a->catagory);
	char end[100];
	strcpy(end, a->end);
	
	//printf("\nWe made it past declaring variables\n");
    DIR *dir;
    struct dirent *entry;
	char conversion[30];
	int counter1 = 0;
	char output[500];
	strcpy(output, "TIDS of all spawned threads: ");

    if (!(dir = opendir(name)))
        return;
	pcounter = 0;
    while ((entry = readdir(dir)) != NULL) 
    {
	
	char path[1024];
        if (entry->d_type == DT_DIR) 
	{
            
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
		{
			continue;
		}
		else
		{
			
			//printf("\n We found a new directory \n");
			snprintf(path, sizeof(path), "%s/%s", name, entry->d_name);		
			
			pthread_t threadid;
			pcounter++;
			did[dcounter] = threadid;
			//My attempt to set the variables of struct dirp manually. The code fails here to get the variables changed.
			arga[pcounter]->path = path;
			arga[pcounter]->catagory = catagory;
			arga[pcounter]->end = end;
			
			//printf("\n WE are sending in %s %s %s\n", arga[pcounter]->path, arga[pcounter]->catagory, arga[pcounter]->end);
			pthread_create(&did[dcounter], NULL,listdir, arga[pcounter]);
			sprintf(conversion, "%i", &sid[scounter]);
			strcat(output,conversion);
			strcat(output, ",");	
			pthread_join(did[dcounter],NULL);
			
			counter1++;
			dcounter++;
			
		}
        } 
	else
	{
		if(strstr(entry->d_name, ".csv") && !strstr(entry->d_name, "All_Files"))
		{
			snprintf(path, sizeof(path), "%s/%s",name, entry->d_name);
			FILE *fp;
				size_t len = 0;
				char *line = NULL;
				ssize_t read;
				fp = fopen(path, "r");
				if (fp == NULL)
					exit(EXIT_FAILURE);
				//read the first line
				read = getline(&line, &len, fp);
				//determines if the columns match
				char* set= malloc(1000);
				strcpy(set,line);
				//printf("%s, \n", path);	
				//printf("%s, \n", set);				
				char* col_tok = malloc(1000);
				col_tok = strtok(set,",");
				while(col_tok!= NULL){
					if(strstr(col_tok, "color")||
					strstr(col_tok, "num_critic_for_reviews")||
					strstr(col_tok, "duration")||
					strstr(col_tok, "director_facebook_likes")||
					strstr(col_tok, "actor_3_facebook_likes")||
					strstr(col_tok, "actor_2_name")||
					strstr(col_tok, "actor_1_facebook_likes")||
					strstr(col_tok, "gross")||
					strstr(col_tok, "genres")||
					strstr(col_tok, "actor_1_name")||
					strstr(col_tok, "movie_title")||
					strstr(col_tok, "num_voted_users")||
					strstr(col_tok, "cast_total_facebook_likes")||
					strstr(col_tok, "actor_3_name")||
					strstr(col_tok, "facenumber_in_poster")||
					strstr(col_tok, "plot_keywords")||
					strstr(col_tok, "movie_imdb_link")||
					strstr(col_tok, "num_user_for_reviews")||
					strstr(col_tok, "language")||
					strstr(col_tok, "country")||
					strstr(col_tok, "color")||
					strstr(col_tok, "content_rating")||
					strstr(col_tok, "budget")||
					strstr(col_tok, "title_year")||
					strstr(col_tok, "actor_2_facebook_likes")||
					strstr(col_tok, "imdb_score")||
					strstr(col_tok, "aspect_ratio")||
					strstr(col_tok, "director_name")||
					strstr(col_tok, "movie_facebook_likes")){

						col_tok= strtok(NULL, ",");
					}else{
						//printf("problem here: |%s|\n", col_tok);
						break;
					}
				}
				
				free(set);
				if(col_tok!=NULL){
					continue;
		
			}
			else
			{
				//printf("\n We found a .csv file \n");
				
				pthread_mutex_lock(&lock);
				pthread_t threadid;
				sortp b = {.path = path, .col = catagory, .dest = end, .filename = entry->d_name};
				brga[scounter]->path = path;
				brga[scounter]->col = catagory;
				brga[scounter]->dest = end;
				brga[scounter]->filename = "All_Files";
				
				sid[scounter] = threadid;
				//printf("Creating new sort Thread\n");
				sleep(1);
				pthread_create(&sid[scounter],NULL, struct_it, brga[scounter]);
				sprintf(conversion, "%i", &sid[scounter]);
				strcat(output,conversion);
				strcat(output, ",");
				pthread_join(sid[scounter],NULL);
				counter1++;
				scounter++;
				pthread_mutex_unlock(&lock);
	
			}
	
			free(line);
			fclose(fp);

			
		}
	

        }
		
    }
	printf("Initial PID: %i\n", getpid());
	printf("%s\n",output);
	printf("Total number of threads: %i\n\n",counter1);


    closedir(dir);

	pthread_exit(1);
}



int main(int argc, char* argv[])
{
	char start[30] = "";
	char end[30] = "";
	char catagory[30] = "";
	pcounter = 0;
	dcounter = 0;
	scounter = 0;
	pthread_mutex_init(&lock, NULL);

	//shares memory between forks
	//int* count = mmap(NULL, sizeof(int), PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, -1, 0);
	//*count = 0;
	//int* children = mmap(NULL, sizeof(int)*255, PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, -1, 0);

	/*Needs to check if argv[5] is present, if not use source directory as destination*/
	//New way to check every argument in the program. It will take in as many as possible and then check to make sure that catagory does not equal '.'
	
	//create file before hand
	FILE * all_files;
	char * new_path = malloc(1000);
	stpcpy(new_path, end);
	strcat(new_path, "All_Files.csv");
	all_files= fopen(new_path,"a");
	fclose(all_files);
	strcpy(start,".");
	strcpy(end,".");
	strcpy(catagory, ".");

	if(argc > 1)
	{
		if(strcmp(argv[1], "-c") == 0)
		{
			strcpy(catagory, argv[2]);
		}
		if(strcmp(argv[1], "-d") == 0)
		{
			strcpy(start, argv[2]);
		}
		if(strcmp(argv[1], "-o") == 0)
		{
			strcpy(end, argv[2]);
		}
	}

	if(argc > 3)
	{
		if(strcmp(argv[3], "-d") == 0)
		{
			strcpy(start, argv[4]);
		}
		if(strcmp(argv[3], "-o") == 0)
		{
			strcpy(end, argv[4]);
		}
		if(strcmp(argv[3], "-c") == 0)
		{
			strcpy(catagory, argv[4]);
		}
	}

	if(argc > 5)
	{
		if(strcmp(argv[5], "-d") == 0)
		{
			strcpy(start, argv[6]);
		}
		if(strcmp(argv[5], "-o") == 0)
		{
			strcpy(end, argv[6]);
		}
		if(strcmp(argv[5], "-c") == 0)
		{
			strcpy(catagory, argv[6]);
		}

	}


	if(strcmp(catagory,".") == 0)
	{
		printf("Error, -c not used in argument");
		return 0;
	}


	DIR* dir = opendir(end);
	if (dir)
	{
		closedir(dir);
	}
	else if(ENOENT ==errno)
	{
		printf("directory no exist. sowwie uwu. \n");
		exit(EXIT_FAILURE);
	};
	//one more tester statement so that we can make sure this works and below is the basics to creating a thread
	//printf("start = %s, end = %s catagory = %s\n",start,end,catagory);	
	
	//here i initialized (or tried to) a bunch of arrays that would hold the arguments for listdir threads and sort threads. Then i am mallocing the arrays that will hold the listdir and sort threadids
		int i;	
	for(i = 0; i < 256; i++)
	{
		arga[i] = (dp) malloc(sizeof(dirp));
	}
	for(i = 0; i < 256; i++)
	{
		brga[i] = (sp) malloc(sizeof(sortp));
	}
		
	dirp a = {.path = start, .catagory = catagory, .end = end};
	
	//printf("\n We are sending in %s %s %s \n", a.path, a.catagory, a.end);
	did[0] = tid[0];
	arga[0]->path = start;
	arga[0]->catagory = catagory;
	arga[0]->end = end;
	//printf("\nfirs values are %s %s %s ",arga[0]->path, arga[0]->catagory, arga[0]->end);
	pthread_create(&did[0], NULL,listdir,arga[0]);	
	pthread_join(did[0], NULL);
	char* new_start = malloc(1000);
	stpcpy(new_start,end);
	strcat(new_start, "/All_Files.csv");
	sleep(3);
	pthread_mutex_destroy(&lock);
	for(i = 0; i < pcounter; i++)
	{
		pthread_join(did[i],NULL);
	}
	for(i = 0; i < scounter; i++)
	{
		pthread_join(sid[i],NULL);
	}
	for(i = 0; i < 256; i++)
	{
		free(arga[i]);	
	}
	for(i = 0; i < 256; i++)
	{
		free(brga[i]);	
	}
	
	sort(new_start, catagory, end, "AllFiles");
	remove("All_Files.csv");
	free(new_start);

	return 0;
		
}


//int to string
char* notNum(char* str, int val)
{
	sprintf(str, "%d", val);
	return str; 
}

//double to string
char* notDouble(char* str, double val)
{
	sprintf(str, "%.6g", val);
	return str; 
}

