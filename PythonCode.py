import re
import string
import os.path
from os import path



def CountAll():
    #Opens the file in read mode
    text = open("CS210_Project_Three_Input_File.txt", "r")

    #Creates an empty dictionary to store "found" words
    dictionary = dict()

    #Checks each line of the input file
    for line in text:
        #removes any errant spaces and newline characters
        line = line.strip()

        #Converts characters to lowercase 
        word = line.lower()
        
        #Checks if the word is already in the dictionary
        if word in dictionary:
            #Increments number of times the word appears
            dictionary[word] = dictionary[word] + 1
        else:
            #If the word is not in the dictionary, It adds it w/ a value of 1
            dictionary[word] = 1

    #Prints all contents of the dictionary
    for key in list (dictionary.keys()):
        print(key.capitalize(), ":", dictionary[key])

    text.close()



def CountInstances(searchTerm):

    #Converts user-inputted search term to lowercase
    searchTerm = searchTerm.lower()

    #Opens the file in read mode
    text = open("CS210_Project_Three_Input_File.txt", "r")

    #Create variable to track how many times item has been "found"
    wordCount = 0

    #Checks each line of the input file
    for line in text:
        #removes any errant spaces and newline characters
        line = line.strip()

        #Converts characters to lowercase 
        word = line.lower()
        
        #Checks if the found word is equal to the user's input
        if word == searchTerm:
            #Increment number of times the word appears
            wordCount += 1

    #Returns the number of times the item was found, as per specification
    return wordCount

    #Closes the opened file
    text.close()

def CollectData():
    #Open the input file in read mode
    text = open("CS210_Project_Three_Input_File.txt", "r")

    #Create and/or write the file frequency.dat
    frequency = open("frequency.dat", "w")

    #Create an empty dictionary to store "found" words
    dictionary = dict()

    #Check each line of the input file
    for line in text:
        #remove any errant spaces and newline characters
        line = line.strip()

        #Convert characters to lowercase for better matching
        word = line.lower()
        
        #Check if the word is already in the dictionary
        if word in dictionary:
            #Increment number of times the word appears
            dictionary[word] = dictionary[word] + 1
        else:
            #If the word is not in the dictionary, add it w/ a value of 1
            dictionary[word] = 1

    #Write each key and value pair to frequency.dat
    for key in list (dictionary.keys()):
        #Format the key-value pair as strings followed by a newline.
        frequency.write(str(key.capitalize()) + " " + str(dictionary[key]) + "\n")

    #Close the opened files
    text.close()
    frequency.close()



    
