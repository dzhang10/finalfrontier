# proj name undecided

Team: Devin Zhang and Randy Lu, Period 10

## Project Description
__ProjectName__ will allow users to create quizzes, take quizzes that are already created, and for the quiz creator to see who took their quiz and their scores. The quiz question can be multiple choice (with 2-5 choices) or short response (with answers up to 256 characters).  

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
  
  - As the quiz maker, you will be able to see the responses to your quiz. By entering the quiz id and the pin number that you set when you created the quiz, a function will read in the contents of the quiz's response file into an array. Another function will print the contents out into the terminal.

## Project Timeline
  - 01/13/2021 Inital User Interface + Staistic functions
  - 01/15/2021 Making the Quiz Interface
  - 01/18/2021 Taking the Quiz Interface
  - 01/21/2021 Seeing the Quiz Interface
  - 01/23/2021 Bug checks and Sample Quizzes

## List of Required Libraries

## Instructions on How to Use Project
