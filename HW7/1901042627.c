#include <stdio.h>
#include <string.h>

/* I used /*  in the comment lines to prevent the program from failing when compiled as gcc -ansi -pedantic-errors 1901042627.c */

void printer_to_file(char*word,char*word2,FILE *text,char*control){   /* The function that does the writing to the file. */
    
    int j,length_word,length_word2;
    length_word=strlen(word);        /* To compare word (word taken from article) and word2 (modified new word) we find their lengths */
    length_word2=strlen(word2);
    
    if(!feof(text)!=0){                 /* operations will continue until the end of the file */
        for(j=0;j<length_word2;j++){
        if(control[j]==1)               /* If the control statement is 1, it means the letter is capital and again enlargement is done. */
            word2[j]=word2[j]-32;
        }
        if((word[0]<97 || word[0]>122) && (word[0]<65 || word[0]>90))   /* The first letter of the word is checked, if not the letter is skipped */
            fseek(text,+1,SEEK_CUR);

        fseek(text,-length_word,SEEK_CUR);  /* in any case it goes back as far as the word itself */
        fprintf(text,"%s",word2);

        if((length_word-length_word2)!=0){      /* If there is a punctuation at the end of the word, skipping is done */
             
             if((word[length_word-1]<97 || word[length_word-1]>122) && (word[length_word-1]<65 || word[length_word-1]>90))
                fseek(text,length_word-length_word2,SEEK_CUR);
        }
    }
    else
        printf("Correction completed successfully! \n");  /* It is stated that the transactions are successful */
}


void find_best_correction(char * word, char result[24],char*file){  /* This function is the main part of the assignment and makes matches where 1 letter is wrong. */
                                                                    /* takes two arrays and one string as input */
    FILE *dictionary;
    int difference,i,j,counter,length,result_counter = 0,priority_case = 0;  /* variables are defined */
    char new_word[24],correct_word[24];;
    
    length = strlen(word);  
    counter = 0;
    for(i=0;i<length;i++){            /* If the word has punctuation marks, they are discarded and a new word is created. */
       
        if((word[i]>=97 && word[i]<=122) || word[i]==38){  /* A special case has been added so that the & sign (38)is not separated.*/
            new_word[counter] = word[i];    
            counter++;
        }
    }
    new_word[counter] = '\0';  /* When the word ends, \ 0 is added to the end, indicating the end */

    strcpy(result, new_word);

    dictionary = fopen(file, "r");  /* dictionary opens */
   

    while(!feof(dictionary)){ /* operations continue until the dictionary ends */
        
        fscanf(dictionary, "%s", correct_word);
        difference = strlen(correct_word) - strlen(new_word);  /* the word is read and the difference is looked at */

        if (difference < 0)
            difference *= -1;     /* If negative, the opposite sign is taken. */

        i = 0;
        while (correct_word[i] != '\0' && new_word[i] != '\0'){   /* the process continues as long as the words are not finished */
            if (correct_word[i] != new_word[i])
                difference++;                       /* the differences count */
            i++;
        }

        if (difference == 0){                  /* if the difference is 0, the word is copied to result and the process is completed */
            fclose(dictionary);
            strcpy(result, correct_word);
            return;
        }

        if (difference < 2) {                   /*If the difference is less than two, that is one, the transactions continue. */
            
            for (j = 0; j < counter; j++){              /* Words are checked in this loop, counter is the number of words in new_word. */
                if (new_word[j] != correct_word[j]){
                    if (correct_word[j] == 97 || correct_word[j] == 101 || correct_word[j] == 105 ||  /* vowels are checked because they have priority */
                        correct_word[j] == 111 || correct_word[j] == 117){
                        
                        if (priority_case > 1){                     /* priority_case starts with 0 this variable contains priority */
                            if (result_counter != 2){
                                strcpy(result, correct_word);
                                result_counter++;					/* If priority case = 2, there are vowels in the variable, and if there is a vowel, we will only look at counter. */ 
                            }
                        } else{
                            strcpy(result, correct_word);   /* This is the first section where priority_case will enter */
                            priority_case = 2;              /* the new value is changed to 2. */
                            result_counter = 1;
                        }
                    }else{
                        if (priority_case > 0){					/* If priority is 0, no words are recorded, 1 means a vowel if silent is 2. */
                            if (result_counter != 2) {
                                strcpy(result, correct_word);
                                result_counter++;				
                            }
                        }else{
                            strcpy(result, correct_word);
                            priority_case = 1;                /* the new value is changed to 1. */
                            result_counter = 1;
                        }
                    }
                    break;  /* loop breaks */
                }
            }
        }
    }
    fclose(dictionary);  /* the dictionary is closed */
}


void two_different_word(char * word, char result[24],char*file){  /* :::...BONUS MISSION...::: */  /* :::...BONUS MISSION...::: */ /* :::...BONUS MISSION...::: */ /* :::...BONUS MISSION...::: */
                                                                 
    FILE *dictionary;                                             /*The function of this part is similar to find_best_correction.*/                                        
    int difference,i,j,length,counter,change = 0;                 /*The most important difference is that it can be corrected by 2 words and is called from the fix_spelling_error2 function.*/                                                                                  
    char new_word[24],correct_word[24];                                           
    int result_counter = 0,priority_case = 0;   /* variables are defined */   
         
    int error_step = 0;

    length = strlen(word);  /* the length of the incoming word is checked*/
    counter = 0;
    for(i=0;i<length;i++){             /* If the word has punctuation marks, they are discarded and a new word is created. */
        
        if((word[i]>=97 && word[i]<=122) || word[i]==38){  /* A special case has been added so that the & sign (38)is not separated.*/
            new_word[counter] = word[i];    
            counter++;
        }
    }
    new_word[counter] = '\0';    /* When the word ends, \ 0 is added to the end, indicating the end */

    strcpy(result, new_word);

    dictionary = fopen(file, "r");   /* dictionary opens */

    while(!feof(dictionary)) {                   /* the process continues as long as the words are not finished */
        fscanf(dictionary, "%s", correct_word);

        difference = strlen(correct_word) - strlen(new_word);      /* if the difference is 0, the word is copied to result and the process is completed */
        if (difference < 0)
            difference *= -1;                                   /* If negative, the opposite sign is taken. */

        i = 0;
        while (correct_word[i] != '\0' && new_word[i] != '\0') {    /* the process continues as long as the words are not finished */
            if (correct_word[i] != new_word[i])
                difference++;                             /* the differences count */
            i++;
        }

        if(difference < 2){
             find_best_correction(word,result,file);   /*if the differences are less than 2, it is sent to the other function. */
            return;                                   /*and the process is terminated */
        }
        if(difference < 3){
            for(j = 0; j < counter; j++){
                if(new_word[j] != correct_word[j]){
                    if(correct_word[j] == 97 || correct_word[j] == 101 || correct_word[j] == 105 ||    /* vowels are checked because they have priority */
                        correct_word[j] == 111 || correct_word[j] == 117){
                        if(priority_case > 1){
                            if(result_counter != 2){
                                strcpy(result, correct_word);
                                result_counter++;
                            }
                        } else{
                            strcpy(result, correct_word);
                            priority_case = 2;
                            result_counter = 1;
                        }
                    }else{
                        if(priority_case > 0){
                            if(result_counter != 2){
                                strcpy(result, correct_word);
                                result_counter++;
                            }
                        }else{
                            strcpy(result, correct_word);
                            priority_case = 1;
                            result_counter = 1;
                        }
                    }
                    break;
                }
            }
        }
    }
    fclose(dictionary);   /* the dictionary is closed */
}


char* fixed1(char*word,int i,int length,FILE* fp){  /* This function is for special occasions. Takes two integers,an array and a file pointer as inputs */

    /*The working principle is briefly as follows: It sends the sent word back by dividing it by the incoming i value.
    It also adjusts the cursor to the size of the word it splits.*/
    
    char temp[24];
    strncpy(temp,word,i);
    temp[i]='\0';           /*We add \ 0 to indicate that the directory is finished */
    strcpy(word,temp);
    fseek(fp,-(length-i),SEEK_CUR);
    return word;
}


void fix_spelling_error(char*file1,char*file2){ /*This function is one of the main parts of our homework. Takes file names as input*/

 char word[24], word2[24],control[24],temp2[24];   /* we defined the variables */
 int i,j,length,flag;
    
    FILE *fp = fopen(file1,"r+");   /* We opened the file according to the incoming file name (string) */

    while(!feof(fp)){          /* The process will continue until the file is finished */  
        flag=0;
        fscanf(fp,"%s",word);   /* We read the word and looked at the size */
        length=strlen(word);
        
        for(j=0;j<length;j++){                  /* If there is a capital letter, we convert it to lowercase */
            if((word[j]>=65 && word[j]<=90)){
               word[j]=word[j]+32;
                control[j]=1;       /* With the control statement, we keep the information that the number is large. */
            }
            else 
                control[j]=0;
        }
        for(i=1;i<length;i++){  /* This section looks for different signs in the letters of the word. */
            
            if((word[i]<97 || word[i]>122) && (word[i]<65 || word[i]>90) && word[i]!=38){ /*If it is not a letter and it is not & (38) then this works here A special case has been created for &(38)*/
                                                    
               if(word[i]==39){     /* There is a special case inside the ' sign (39) */                                            
                    fixed1(word,i,length,fp);
                    find_best_correction(word,word2,file2);
                    printer_to_file(word,word2,fp,control);  /* The difference of the apostrophe is that the part after the apostrophe will not be searched in the dictionary. */
                    fseek(fp,+(length-i),SEEK_CUR);         /* so with the cursor, that part is skipped */
                    flag=1;
               }
               else{    
                    fixed1(word,i,length,fp);               /* It is sent to the fixed function, which performs word division, and is cut until the part in between is the sign in between. */
                    find_best_correction(word,word2,file2);  /* It is then sent to the function that finds the best match */
                    printer_to_file(word,word2,fp,control);   /* It is then sent to the function that will do the write operation.*/ 
                    fseek(fp,+1,SEEK_CUR);      /* +1 so that the cursor skips that mark(for example: / . * % #) */
                    flag=1; /* the purpose of this is to understand that the process takes place here and to ensure that it does not work in the other part. */
                }
            }
        }
        if(flag!=1){
            find_best_correction(word,word2,file2);     /*in normal cases this part is performed */
            printer_to_file(word,word2,fp,control);
        }
   }
    fclose(fp);  /* file is closed */
}


void fix_spelling_error2(char*file1,char*file2){ /* :::...BONUS MISSION...::: */  /* :::...BONUS MISSION...::: */ /* :::...BONUS MISSION...::: */ /* :::...BONUS MISSION...::: */

 char word[24], word2[24],control[24],temp2[24];  /* This function is not significantly different from fix_spelling_error.The only difference is that it calls the bonus function.*/
 int i,j,length,flag;
    
    FILE *fp = fopen(file1,"r+");   /* We opened the file according to the incoming file name (string) */

    while(!feof(fp)){          /* The process will continue until the file is finished */  
        flag=0;
        fscanf(fp,"%s",word);   /* We read the word and looked at the size */
        length=strlen(word);
        
        for(j=0;j<length;j++){                  /* If there is a capital letter, we convert it to lowercase */
            if((word[j]>=65 && word[j]<=90)){
               word[j]=word[j]+32;
                control[j]=1;       /* With the control statement, we keep the information that the number is large. */
            }
            else 
                control[j]=0;
        }
        for(i=1;i<length;i++){  /* This section looks for different signs in the letters of the word. */
            
            if((word[i]<97 || word[i]>122) && (word[i]<65 || word[i]>90) && word[i]!=38){ /*If it is not a letter and it is not & (38) then this works here A special case has been created for &(38)*/
                                                    
               if(word[i]==39){     /* There is a special case inside the ' sign (39) */                                            
                    fixed1(word,i,length,fp);
                    two_different_word(word,word2,file2);   
                    printer_to_file(word,word2,fp,control);  /* The difference of the apostrophe is that the part after the apostrophe will not be searched in the dictionary. */
                    fseek(fp,+(length-i),SEEK_CUR);         /* so with the cursor, that part is skipped */
                    flag=1;
               }
               else{    
                    fixed1(word,i,length,fp);               /* It is sent to the fixed function, which performs word division, and is cut until the part in between is the sign in between. */
                    two_different_word(word,word2,file2);   /* We send the values to the function that will find the result with two words difference. */
                    printer_to_file(word,word2,fp,control);   /* It is then sent to the function that will do the write operation.*/ 
                    fseek(fp,+1,SEEK_CUR);      /* +1 so that the cursor skips that mark(for example: / . * % #) */
                    flag=1; /* the purpose of this is to understand that the process takes place here and to ensure that it does not work in the other part. */
                }
            }
        }
        if(flag!=1){
            two_different_word(word,word2,file2);     /*in normal cases this part is performed */
            printer_to_file(word,word2,fp,control);
        }
   }
    fclose(fp);  /* file is closed */
}


int main(){
   
   char*file1="text.txt";           /* we are entering our file names */
   char*file2="dictionary.txt";
   fix_spelling_error(file1,file2);
   fix_spelling_error2(file1,file2); /* If we want to call the bonus task, we just need to activate this part. */
}

/* Author: Dogukan TASTAN all rights reserved 2021 */
/* Number: 1901042627 */







