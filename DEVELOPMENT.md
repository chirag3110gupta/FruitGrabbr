# Development

---

- **4/17/20** Started trying to link openCV as a CinderBlock, set it up for my macbook and watched videos online to
learn about openCV.
   - Tried many different methods and office hours, finally set it up with David Brewster

- **4/20/20**  Made advancements and got project started
   - Used openCV as an external library, compiled and built the program
   - Implemented webcam and took the images using imwrite and imread functions
   - Made logo using Photoshop and added Logo and Score

- **4/26/20**  Made basic classes like fruit, location and engine
   - Made engine and fruit, wrote all the methods
   - Made fruits fall, wrote step methods for both classes to be executed in each timestep
   - Completed implementations of helpers like checking game state and score
   
- **4/27/20**  Implemented color recognition
    - Implemented color recognition using openCV, made a Matrix mask and stored all green pixels as ON
    and other pixels as OFF
    - Added colors to the fruits, tried adding background texture, but couldnt add to ellipses
    - Made game visually better
    
- **5/2/20** Made the grabber
    - Using the color recognition got container locations, and stored them in a Location Vector 
    - Used the location vector and set that as the game background
    - Game was too blocky and laggy, made the Step functions more frequent
    
- **5/3/20** Finished up game and added draw functions
    - Made a game over and pause state, added enum for storing gamestate
    - Made their respective draw functions for classes and drew them in order of appearance
    - Set a suitable frame rate and timings, made Gamespeed playable and not too difficult
    - Added Background music
    - Added Comments and Documentation, made code more readable
    
Future Plans : If i have time i might execute leaderboard using sql.