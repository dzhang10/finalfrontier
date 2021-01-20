# Quizzify (subject to change)

Team: Devin Zhang and Randy Lu, Period 10

## Project Description
Quizzify will allow users to create quizzes, take quizzes that are already created, and for the quiz creator to see who took their quiz and their scores. The quiz question (up to 520 characters) can be multiple choice (with 2-5 choices) or short response (with answers up to 256 characters).  

## Technical Design

### Using Topics Covered in Class
  - Named pipes will be used to send information from the client to the server and vice versa. 
  - The server will allocate the memory needed to store information in arrays so that it be be processed by other functions.
  - When a quiz is created, 2 files will be created as well (one with the contents of the quiz and another with the responses).
  - If a user started making a quiz and quits (ctl+c) before the quiz is confirmed, the quiz file will be delelted and the user will see a confirmation.
  
### Project Breakdown and Responsibilities
  - Inital User Interface: Devin Zhang
  - Making the Quiz: Devin Zhang & Randy Lu
  - Taking the Quiz: Devin Zhang & Randy Lu
  - Seeing the Quiz Results/Statistics: Randy Lu
  
  See DEVLOG for more specific tasks and contribution from team member.
  
### Data Structures/Algorithms
  - When entering the information to create a quiz, the content of each questions (the actual question, type of question, choices (if applicable), and correct answer) will be stored into an array. 
  - When all the questions are inputted, the questions will be put into a cvs file with a new line separating each question.
  - The contents of each quiz will be stored in its own unique file (named by a unique Quiz ID that will be assigned).
  
  - The file will be read in by a function and it will be parsed into various arrays (one for questions, for the choices, and one for the correct asnwer). Another functions will print the contents of the array into the termainal in an user-friendly way. 
  - As the quiz taker enters their answers, a temporary array will store the user's answers. When all the questions have been answered, a functions will match the answers provided with the correct answer and score the quiz taker's info into a file.
  - The user will see their score as a fraction and a percentage (rounded to nearest percent). Following the score will be all the questions (with correct ones and incorrect ones shown differently). 
  
  - As the quiz maker, you will be able to see the responses to your quiz. By entering the quiz id and the pin number that you set when you created the quiz, a function will read in the contents of the quiz's response file into an array. Another function will print the contents out into the terminal. There will also be test statistic avaliable.

## Project Timeline
  - 01/13/2021 Inital User Interface + Statistic functions
  - 01/15/2021 Making the Quiz Interface
  - 01/18/2021 Taking the Quiz Interface
  - 01/21/2021 Seeing the Quiz Interface
  - 01/23/2021 Bug checks and Sample Quizzes

## List of Required Libraries
  - <stdlib.h>
  - <stdio.h>
  - <strings.h>
  - <time.h>
  - <signal.h>
  - <math.h>
  
## Setting up the Server and Client 
  1. Download or clone the entire repo.
  2. $make
  3. run ./server first on a terminal
  4. run ./client second on another terminal
  5. You will see a welcome message and then follow the prompt
  Note: You must enter the required response in order for the program to work.
### Making the Quiz
  1. Once you run both server and client, type "Make" to start making a quiz.
  2. Enter a Quiz Name
  3. Enter the number of questions using numbers
  4. Enter a 4-Digit pin for your quiz (this is used to access the quiz results later on)
  5. You will be prompted to enter the question, the type of question ("M" for multiple choice and "S" for short response)
  6. If you choose M then you will enter 4 choices and then the letter of the correct answer choice
     If you choose S then you will be prompt to enter the correct answer
  7. At this point, the quiz is not yet created. Type "Go" to actually make the quiz and store it.
  8. You will get a reminder to write down the quizID and quizPin. Users need the quizID to take the quiz and the creator
     needs both to access the results of the quiz.
  9. Type "Done" to get back to the inital prompt. 

### Taking a Quiz
  1. Once you run both the server and the client, type "Take" to start taking the quiz.
  2. Enter the ID of the Quiz that you want to take and then your name.
  3. 
  
## Attempted
