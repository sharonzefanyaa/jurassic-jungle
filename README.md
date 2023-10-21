# jurassic-jungle

Jurassic Jungle is a jungle in BlueJack Island filled with variety of artificial dinosaurs. The owner of Jurassic Jungle, Mr. James, hired you to create an application to manage the dinosaur data. The program will relies heavily on AVL Tree as its base algorithm. You are to create the application based on the following requirements :
- At the start of the program, there will be 4 menus, which consists of :
  1. See Dinosaur
  2. Add Dinosaur
  3. Remove Dinosaur
  4. Exit

- If user choose menu 1 (See Dinosaur), the program will
  
  - Check data from AVL Tree. If there are no data, display:
  
  There's no dinosaur here!
  
  Press enter to back...

  - Otherwise, prompt user to input View Input. Validate the input must be between “Pre”, “In”, and “Post” (case sensitive)

  **Notes:**
  1. If View Input is “Pre”, display all data in pre-order format
  2. If View Input is “In”, display all data in in-order format
  3. If View Input is “Post”, display all data in post-order format

- If user choose menu 2 (Add Dinosaur), the program will :
  1. Prompt user to input Dinosaur Name. Validate the input must be based on following conditions:
     - Input must be between 10 and 30 characters (inclusive)
     - Input must consists of 3 words minimum
     - Input must starts with “Super” or “Hyper” (case sensitive)
     - Prompt user to input Dinosaur Type. Validate the input must be between “Carnivore”, “Herbivore”, and “Omnivore” (case insensitive)
  2. Prompt user to input Dinosaur Age. Validate the input must be greater than 1000
  3. Prompt user to input Dinosaur Weight. Validate the input must be greater than 10000
  4. Prompt user to input Dinosaur Skill. Validate the input must consist only one word and in capital form
  5. Finally, create a node with all data and push unto the AVL Tree with Dinosaur Age as its key
 
- If user choose menu 3 (Remove Dinosaur), the program will
  
  - Check data from AVL Tree. If there are no data, display:
  
  There's no dinosaur here!
  
  Press enter to back...

  - Otherwise,
  1. Display all data in in-order format
  2. Prompt user to input Dinosaur Name
  3. Check data from AVL Tree based on input
  4. If there are no data exists, display:

  Input Dino to be find: A

  We can't find dino with A name
  
  5. Otherwise, remove corresponding data from AVL Tree and display:

  Input Dino to be find: Brontosaurus Y

  Remove sucessful

- If user choose menu 4 (Exit), the program will close
