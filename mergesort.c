#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "multiThreadSorter_thread.h"

void mergeArr(Movie array[], int close, int med, int back, char catagory[])
{
	//Here we set all of the default values that will be used to put together the array.
	int i,j,k;
	int size1 = med - close + 1;
	int size2 = back - med;
	
	Movie* arr1 = (Movie*)malloc(sizeof(Movie)*size1);
	Movie* arr2 = (Movie*)malloc(sizeof(Movie)*size2);
	
	//We separate the arrays and allocate memory to those locations.
	for(i = 0; i < size1; i++)
	{
		memcpy(&arr1[i], &array[close+i], sizeof(Movie) );
	}
	for(j = 0; j < size2; j++)
	{
		memcpy(&arr2[j], &array[med+1+j], sizeof(Movie) );
	}
	
	int a = 0;
	int b = 0;
	int tot = size1+size2;


	i = 0;
	j = 0;
	k = close;
	
	//Here is where the main sorting algo exists. We compare one field in the structs and then move around the whole structs depending on the result. Assuming the order is in decending order.
	while(i < size1 && j < size2)
	{	
		if(strcmp(catagory,"color")==0)
		{
			if(strcmp(((arr1[i]).color),((arr2[j]).color)) < 0)
			{
				memcpy(&array[k], &arr1[i], sizeof(Movie) );
				i++;
			}
			else
			{
				memcpy(&array[k], &arr2[j], sizeof(Movie) );
				j++;
			}
			k++;
		}
		if(strcmp(catagory,"director_name")==0)
		{
			if(strcmp(((arr1[i]).director_name),((arr2[j]).director_name)) < 0)
			{
				memcpy(&array[k], &arr1[i], sizeof(Movie) );
				i++;
			}
			else
			{
				memcpy(&array[k], &arr2[j], sizeof(Movie) );
				j++;
			}
			k++;
		}
		if(strcmp(catagory, "num_critic_for_reviews")== 0)
		{
			if((arr1[i]).num_critic_for_reviews <= (arr2[j]).num_critic_for_reviews)
			{
				memcpy(&array[k], &arr1[i], sizeof(Movie) );
				i++;
			}
			else
			{
				memcpy(&array[k], &arr2[j], sizeof(Movie) );
				j++;
			}
			k++;
		}

		if(strcmp(catagory, "duration")== 0)
		{
			if((arr1[i]).duration <= (arr2[j]).duration)
			{
				memcpy(&array[k], &arr1[i], sizeof(Movie) );
				i++;
			}
			else
			{
				memcpy(&array[k], &arr2[j], sizeof(Movie) );
				j++;
			}
			k++;
		}

			if(strcmp(catagory, "director_facebook_likes")== 0)
		{
			if((arr1[i]).director_facebook_likes <= (arr2[j]).director_facebook_likes)
			{
				memcpy(&array[k], &arr1[i], sizeof(Movie) );
				i++;
			}
			else
			{
				memcpy(&array[k], &arr2[j], sizeof(Movie) );
				j++;
			}
			k++;
		}
		
			if(strcmp(catagory, "actor_3_facebook_likes")== 0)
		{
			if((arr1[i]).actor_3_facebook_likes <= (arr2[j]).actor_3_facebook_likes)
			{
				memcpy(&array[k], &arr1[i], sizeof(Movie) );
				i++;
			}
			else
			{
				memcpy(&array[k], &arr2[j], sizeof(Movie) );
				j++;
			}
			k++;
		}



		if(strcmp(catagory, "actor_2_name")== 0)
		{
			if(strcmp(((arr1[i]).actor_2_name),((arr2[j]).actor_2_name)) < 0)
			{
				memcpy(&array[k], &arr1[i], sizeof(Movie) );
				i++;
			}
			else
			{
				memcpy(&array[k], &arr2[j], sizeof(Movie) );
				j++;
			}
			k++;
		}

			if(strcmp(catagory, "actor_1_facebook_likes")== 0)
		{
			if((arr1[i]).actor_1_facebook_likes <= (arr2[j]).actor_1_facebook_likes)
			{
				memcpy(&array[k], &arr1[i], sizeof(Movie) );
				i++;
			}
			else
			{
				memcpy(&array[k], &arr2[j], sizeof(Movie) );
				j++;
			}
			k++;
		}

			if(strcmp(catagory, "gross")== 0)
		{
			if((arr1[i]).gross <= (arr2[j]).gross)
			{
				memcpy(&array[k], &arr1[i], sizeof(Movie) );
				i++;
			}
			else
			{
				memcpy(&array[k], &arr2[j], sizeof(Movie) );
				j++;
			}
			k++;
		}

		if(strcmp(catagory, "genres")== 0)
		{
			if(strcmp(((arr1[i]).genres),((arr2[j]).genres)) < 0)
			{
				memcpy(&array[k], &arr1[i], sizeof(Movie) );
				i++;
			}
			else
			{
				memcpy(&array[k], &arr2[j], sizeof(Movie) );
				j++;
			}
			k++;
		}

		if(strcmp(catagory, "actor_1_name")== 0)
		{
			if(strcmp(((arr1[i]).actor_1_name),((arr2[j]).actor_1_name)) < 0)
			{
				memcpy(&array[k], &arr1[i], sizeof(Movie) );
				i++;
			}
			else
			{
				memcpy(&array[k], &arr2[j], sizeof(Movie) );
				j++;
			}
			k++;
		}


		if(strcmp(catagory, "movie_title")== 0)
		{
			if(strcmp(((arr1[i]).movie_title),((arr2[j]).movie_title)) < 0)
			{
				memcpy(&array[k], &arr1[i], sizeof(Movie) );
				i++;
			}
			else
			{
				memcpy(&array[k], &arr2[j], sizeof(Movie) );
				j++;
			}
			k++;
		}

			if(strcmp(catagory, "num_voted_users")== 0)
		{
			if((arr1[i]).num_voted_users <= (arr2[j]).num_voted_users)
			{
				memcpy(&array[k], &arr1[i], sizeof(Movie) );
				i++;
			}
			else
			{
				memcpy(&array[k], &arr2[j], sizeof(Movie) );
				j++;
			}
			k++;
		}

			if(strcmp(catagory, "cast_total_facebook_likes")== 0)
		{
			if((arr1[i]).cast_total_facebook_likes <= (arr2[j]).cast_total_facebook_likes)
			{
				memcpy(&array[k], &arr1[i], sizeof(Movie) );
				i++;
			}
			else
			{
				memcpy(&array[k], &arr2[j], sizeof(Movie) );
				j++;
			}
			k++;
		}

		if(strcmp(catagory, "actor_3_name")== 0)
		{
			if(strcmp(((arr1[i]).actor_3_name),((arr2[j]).actor_3_name)) < 0)
			{
				memcpy(&array[k], &arr1[i], sizeof(Movie) );
				i++;
			}
			else
			{
				memcpy(&array[k], &arr2[j], sizeof(Movie) );
				j++;
			}
			k++;
		}

			if(strcmp(catagory, "facenumber_in_poster") == 0)
		{
			if((arr1[i]).facenumber_in_poster <= (arr2[j]).facenumber_in_poster)
			{
				memcpy(&array[k], &arr1[i], sizeof(Movie) );
				i++;
			}
			else
			{
				memcpy(&array[k], &arr2[j], sizeof(Movie) );
				j++;
			}
			k++;
		}

		if(strcmp(catagory, "plot_keywords") == 0)
		{
			if(strcmp(((arr1[i]).plot_keywords),((arr2[j]).plot_keywords)) < 0)
			{
				memcpy(&array[k], &arr1[i], sizeof(Movie) );
				i++;
			}
			else
			{
				memcpy(&array[k], &arr2[j], sizeof(Movie) );
				j++;
			}
			k++;
		}

		if(strcmp(catagory, "movie_imdb_link") == 0)
		{
			if(strcmp(((arr1[i]).movie_imdb_link),((arr2[j]).movie_imdb_link)) < 0)
			{
				memcpy(&array[k], &arr1[i], sizeof(Movie) );
				i++;
			}
			else
			{
				memcpy(&array[k], &arr2[j], sizeof(Movie) );
				j++;
			}
			k++;
		}

			if(strcmp(catagory, "num_user_for_reviews") == 0)
		{
			if((arr1[i]).num_user_for_reviews <= (arr2[j]).num_user_for_reviews)
			{
				memcpy(&array[k], &arr1[i], sizeof(Movie) );
				i++;
			}
			else
			{
				memcpy(&array[k], &arr2[j], sizeof(Movie) );
				j++;
			}
			k++;
		}

		if(strcmp(catagory, "language") == 0)
		{
			if(strcmp(((arr1[i]).language),((arr2[j]).language)) < 0)
			{
				memcpy(&array[k], &arr1[i], sizeof(Movie) );
				i++;
			}
			else
			{
				memcpy(&array[k], &arr2[j], sizeof(Movie) );
				j++;
			}
			k++;
		}

		if(strcmp(catagory, "country") == 0)
		{
			if(strcmp(((arr1[i]).country),((arr2[j]).country)) < 0)
			{
				memcpy(&array[k], &arr1[i], sizeof(Movie) );
				i++;
			}
			else
			{
				memcpy(&array[k], &arr2[j], sizeof(Movie) );
				j++;
			}
			k++;
		}

		if(strcmp(catagory, "content_rating") == 0)
		{
			if(strcmp(((arr1[i]).content_rating),((arr2[j]).content_rating)) < 0)
			{
				memcpy(&array[k], &arr1[i], sizeof(Movie) );
				i++;
			}
			else
			{
				memcpy(&array[k], &arr2[j], sizeof(Movie) );
				j++;
			}
			k++;
		}

			if(strcmp(catagory, "budget") == 0)
		{
			if((arr1[i]).budget <= (arr2[j]).budget)
			{
				memcpy(&array[k], &arr1[i], sizeof(Movie) );
				i++;
			}
			else
			{
				memcpy(&array[k], &arr2[j], sizeof(Movie) );
				j++;
			}
			k++;
		}

			if(strcmp(catagory, "title_year") == 0)
		{
			if((arr1[i]).title_year <= (arr2[j]).title_year)
			{
				memcpy(&array[k], &arr1[i], sizeof(Movie) );
				i++;
			}
			else
			{
				memcpy(&array[k], &arr2[j], sizeof(Movie) );
				j++;
			}
			k++;
		}

			if(strcmp(catagory, "actor_2_facebook_likes") == 0)
		{
			if((arr1[i]).actor_2_facebook_likes <= (arr2[j]).actor_2_facebook_likes)
			{
				memcpy(&array[k], &arr1[i], sizeof(Movie) );
				i++;
			}
			else
			{
				memcpy(&array[k], &arr2[j], sizeof(Movie) );
				j++;
			}
			k++;
		}

			if(strcmp(catagory, "imdb_score") == 0)
		{
			if((arr1[i]).imdb_score <= (arr2[j]).imdb_score)
			{
				memcpy(&array[k], &arr1[i], sizeof(Movie) );
				i++;
			}
			else
			{
				memcpy(&array[k], &arr2[j], sizeof(Movie) );
				j++;
			}
			k++;
		}

			if(strcmp(catagory, "aspect_ratio") == 0)
		{
			if((arr1[i]).aspect_ratio <= (arr2[j]).aspect_ratio)
			{
				memcpy(&array[k], &arr1[i], sizeof(Movie) );
				i++;
			}
			else
			{
				memcpy(&array[k], &arr2[j], sizeof(Movie) );
				j++;
			}
			k++;
		}

			if(strcmp(catagory, "movie_facebook_likes") == 0)
		{
			if((arr1[i]).movie_facebook_likes <= (arr2[j]).movie_facebook_likes)
			{
				memcpy(&array[k], &arr1[i], sizeof(Movie) );
				i++;
			}
			else
			{
				memcpy(&array[k], &arr2[j], sizeof(Movie) );
				j++;
			}
			k++;
		}

	}

	//Here we take any left over values from the temp arrays and add them to the end of the main array. Since they are left over they must be the highest value so it won't mess up the array.
	while(i < size1)
	{
		memcpy(&array[k], &arr1[i], sizeof(Movie) );
		i++;
		k++;
	}

	while(j < size2)
	{
		memcpy(&array[k], &arr2[j], sizeof(Movie) );
		j++;
		k++;
	}
	a = 0;
	//Here we free the arrays since we are done using them.
	free(arr1);
	free(arr2);
}

void mergesort(Movie array[], int left, int right, char catagory[])
{	
	//This is the basic mergesort algo that finds the mid point, then recurssions until the array elements are singular. Then it pushes them to mergeArr which will rearrange and rebuild the original array all sorted out.
	if(left < right)
	{
		int medium = (left + (right-1)) / 2;
		mergesort(array, left, medium, catagory);
		mergesort(array, medium+1, right, catagory);

		mergeArr(array, left, medium, right, catagory);
	}
}
