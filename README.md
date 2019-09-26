# 141LabsButTernaries
Write a program to change one word into another, such as converting work into play.  At each step only a single letter can be changed at a time, and each word must be a word found in the dictionary.  This is inspired by Robert Frost's poem "Two Tramps in Mud Time" where the last stanza is:

But yield who will to their separation,
My object in living is to unite
My avocation and my vocation
As my two eyes make one in sight.
Only where love and need are one,
And the work is play for mortal stakes,
Is the deed ever really done
For heaven and the future’s sakes.

Use dictionary.txt (taken on a Mac from /usr/share/dict/words) of 235,886 words.  Running the program should look like the following, where user input is shown in bold (though your program when run will not display that in bold):

Program #3: Work Play    
Author: Dale Reed    
Lab: Tues 8am     
System:  Codio 
 
Total number of words: 235886 
Word lengths where there are more than 2000 words:
Length  How Many
------  --------
    4      5272
    5     10230
    6     17706
    7     23869
    8     29989
    9     32403
   10     30878
   11     26013
   12     20462
   13     14939
   14      9765
   15      5925
   16      3377

What length words do you want to use? 4
Number of words read was 5272

Enter starting and ending words, or 'r' for either for a random word: zong zichs
'zong' is not in the dictionary. Please retry.

Enter starting and ending words, or 'r' for either for a random word: song zichs
'zichs' is not of length 4. Please retry.

Enter starting and ending words, or 'r' for either for a random word: song r

Morphing from song to whig.

On each move enter a word of the same length that is at   
most 1 character different and is also in the dictionary, 
or type in 'exit' to exit the interactive portion of the program.
 
1. Previous word is 'song'.  Next word: soig
   *** soig is not in the dictionary.  Please retry.
1. Previous word is 'song'.  Next word: sing
2. Previous word is 'sing'.  Next word: wing
3. Previous word is 'wing'.  Next word: wink
4. Previous word is 'wink'.  Next word: wook
   *** New word must be exactly 1 character different.  Please retry.
4. Previous word is 'wink'.  Next word: wine
5. Previous word is 'wine'.  Next word: exit

Solution is: 
   0. song
  16. tong
 122. toug
 671. thug
2270. thig
3887. whig

I suggest you develop your program one stage at a time, breaking down section using functions.  

Hints
Dictionary
You will read the dictionary file twice.  The first time you will accumulate counts of how many words of each length there are, storing this in an array.  You know that the longest possible word is around 30 characters, so make your counting array of integers that size.  As you read each word, check its size and add one to the corresponding array location in your word length counting array.

You will then close the dictionary file.  Then prompt the user for what size words she wants to deal with, creating a vector of this size using the vector .resize( n) command.  Re-read the dictionary, storing only the words of this size into the newly-created vector.


Random Number Generator
In this program you will allow the user to explicitly type in the starting and ending word, so when this is not done, you can have your program choose words at random. You should only seed the random number generator once in your program, typically near the beginning of main().  That statement should be:   srand( 1);

When setting, for example, the startWord, (which is of type string) you should do something like:
     startWord = dictionary[ rand()%numberOfWords]);
Prompting for start and end Words
This code should be in a function.  startWord and endWord should be declared in main as string, and then passed to functions where they are used.  You should use some kind of loop to read in those values.  Note that the user can enter two words, or enter two single character 'r' which represent random selection of each word.  Read in both words and then handle the cases.  If a word is 'r' then choose a random word, as illustrated above.  Otherwise validate each word to make sure it is in the dictionary and is the proper length.  Since this code is in a loop, if there is some problem, simply use the continue statement to go back up to the top of the loop to retry.  Then use the break statement to break out of the loop once both words are verified.

Handling Interactive User Input

You will need a loop to handle user input.  It should keep going until the end word is found, or the user types in 'exit' to quit the interactive part of the program.  For each user input word you should:
See if 'exit' was entered.  If it was, then break out of the user input and processing loop and return back to main().  This implies that  'exit' cannot be a word on the path to a solution typed in by the user.  You don't need to make any special checks for this, but for this program just assume this is true.
Ensure that the length of the user input was correct.  This means that the proscribed length must also be passed as a parameter to this function.
Ensure the new word is at most one character different from the previous word.  You will need to have separate strings (array of char) to store the current user word and the previous one.  Write a function to count how many characters are different between the two words, and use that result to give an error message and continue back up to top of loop if necessary.
Ensure the word is in the dictionary.  You should write a function for this, as you will need it elsewhere.  
If all the tests are passed, then you have a new current word, that you can copy into the previous word variable for use the next time through the loop.
Computer Generates Solution Path
This is the challenging part of the program.  You will essentially create a tree of all words reachable from the starting word.  The tree keeps growing as you expand each word already in the tree, keeping track of its "children."  Actually using a tree structure for this is beyond what we can comfortably do so far, so instead we will use a vector of strings.  Start by putting the starting word in the vector.  Find all words that are at most 1 letter away from this starting word.  Store each of these words successively in this array, adding them to the end.  Then repeat, moving to the next line to expand that word, and so on.

This process will end once there are no more words to be expanded, or when the ending word is found.  Once the ending word is found we need a way to trace its ancestry back to the starting word.  This means that for each word we need to also store a space and then the vector index of its parent.  You can do this in the same vector, or in a separate parallel vector.
As each word is expanded, add each new word and the index of its parent to the end of the vector.  I highly recommend you print these newly generated words out as you go, perhaps along with their parent's index numbers, to ensure your program is working correctly.

Once the end word is found, use the parent index values to follow ints ancestry back, printing it out as you go, which will give you the solution path in reverse order.  Then figure out how to reverse this solution path, so it gives it to you in order.  Note that your program will give you the first solution path found, not necessarily the shortest solution path found.
Cases we will be checking:
Choosing start and end words: (~10 points)  
Correctly displays counts of word lengths where there are more than 2000 words in the dictionary for that length
Verify start and end words are in the dictionary and are the designated length
Allows selecting random words when 'r' is entered for either or both words. 

 Handling user "moves":   (~15 points)
Verify each new user word is in the dictionary and is the proper length
Verify each new user word is exactly 1 character different from the previous word
Notify user when ending word is found
Handle the user entering "exit" to exit the interactive mode of the program

Solution Path (~30 points)
Computer finds the solution path and shows it if there is one, or indicates that there is no solution if there isn't one.  Solution path is in reverse order.
Same as above, except now the solution path (for any length solution!) is in order.
